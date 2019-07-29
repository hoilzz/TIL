# React - 기본 이론

## Transformation

React의 핵심 전제는 UI는 단순히 데이터를 다양한 데이터 형태로 변환하는 것이다. 

```js
function NameBox(name) {
  return {
    fontWight: 'bold',
    labelContent: name
  }
 }
```

## 추상화

단일 함수 내에서 복잡한 UI는 맞지 않는다. UI는 세부 구현체를 유출하지 않는 재사용 가능한 조각으로 추상화 되는 것은 중요하다. 하나의 함수를 다른 함수에서 호출하는 것과 같이

```js
function FancyUserBox(user) {
  return {
    borderStyle: '1px solid blue',
    childContent: [
      'Name: ',
      NameBox(user.firstName + ' ' + user.lastName)
    ]
  };
}
```

```js
{ firstName: 'Sebastian', lastName: 'Markbåge' } ->
{
  borderStyle: '1px solid blue',
  childContent: [
    'Name: ',
    { fontWeight: 'bold', labelContent: 'Sebastian Markbåge' } // nameBox
  ]
};
```

## Composition

재사용 가능한 feature를 만들기 위해, leaves만 재사용하고 new containers(`FancyUserBox`)를 빌드하는 것으로 충분하지 않다. 

다른 추상화를 구성하는 컨테이너에서 추상화를 빌드할 필요가 있다. `composition`에 대해 내가 생각한 방식은 2개 이상의 다른 추상화를 새로운 1개로 결합하는 것이다.

```js
function FancyBox(children) {
  return {
    borderStyle: '1px solid blue',
    children: children
  };
}

function UserBox(user) {
  return FancyBox([
    'Name: ',
    NameBox(user.firstName + ' ' + user.lastName)
  ]);
}
```

> FancyBox가 children으로 인자를 받아서 다른 컴포넌트와 composition하고 있다. 기존에 FancyUserBox는 NameBox 컴포넌트를 무조건 렌더링 하여 의존성 결합이 강했다. 해서 재사용이 어려웠지만, children 인자로 의존성을 주입하여 재사용성을 높였다.

## State

UI는 단순히 server / business logic 상태의 복제가 __아니다__. 실제로  다른 상태가 아닌 정확한 투영?(projection)에 많은 상태가 있다. 예를 들어, 만약 text field에서 타이핑 한다면, 다른 탭이나 모바일 디바이스에 복제되지 않는다. 스크롤 위치는 너가 거의 여러개 투영에서 거의 복제하고 싶지않는 전형적인 예제다.

우리는 불변 데이터 모델을 선호한다. 최상단에 있는 단일 원자 상태를 업데이트하는 함수를 쓰레드한다?

```js
function FancyNameBox(user, likes, onClick) {
  return FancyBox([
    'Name: ', NameBox(user.firstName + ' ' + user.lastName),
    'Likes: ', LikeBox(likes),
    LikeButton(onClick)
  ]);
}

// Implementation Details

var likes = 0;
function addOneMoreLike() {
  likes++;
  rerender();
}

// Init

FancyNameBox(
  { firstName: 'Sebastian', lastName: 'Markbåge' },
  likes, // state
  addOneMoreLike // setStateFn
);
```

> FancyNameBox라는 함수가 있다. 이 함수는 최상단에서(위치가 아닌 컴포넌트 트리에서 최상단) 호출되며, 단일 상태를 가진다.

NOTE: 이 예제는 상태를 업데이트하기 위해 side-effects를 사용한다. 이러한 실제 멘탈 모델은 "update" pass 동안 다음 상태 버전을 리턴한다. 

## Memoization Map

만약 함수가 순수함수인것을 안다면, 동일한 함수를 계속 호출하는 것은 낭비다. 마지막 인자와 결과의 추적을 유지하는 함수의 메모이징 버전을 생성할 수 있다. 만약 동일한 값을 이용하는 것을 유지하려면 재실행할 필요가 없다.

```js
function memoize(fn) {
  var cachedArg;
  var cachedResult;
  return function(arg) {
    if(cachedArg === arg) {
      return cachedResult;
    }
    cachedArg = arg;
    cachedResult = fn(arg);
    return cachedResult;
  }
}

var MemoizedNameBox = memoize(NameBox);

function NameAndAgeBox(user, currentTime) {
  return FancyBox([
    'Name: ',
    MemoizedName
  ])
}
```

## Lists

대부분의 UI는 리스트에서 각 아이템에 대한 여러개의 다양한 값을 생산하는 form list다. 이것은 계층을 만든다. 

리스트에서 각 아이템에 대한 상태를 관리하기 위해, 특정 아이템에 대한 상태를 쥐고 있는 Map을 만들 수 있다. 


```js
// users 데이터 리스트
// {Map} - likesPerUser 
// 
function UserList(users, likesPerUser, updateUserLikes) {
  return users.map(user => FancyNameBox(
    user,
    likesPerUse.get(user.id),
    () => updateUserLikes(user.id, likesPerUser.get(user.id) + 1)
  ))
}

var likesPerUser = new Map();

function updateUserLikes(id, likeCount) {
  likesPerUser.sert(id, likeCount);
  rerender();
}

UserList(data.users, likesPerUser, updateUserLikes);
```

NOTE: 여러개의 다른 인자를 FancyNameBox에 전달할 수 있다. 이것은 메모이징을 부시는데, 그 당시에 1가지 값만 기억할 수 있기때문이다. 

## Continuations

불행하게도, UI 목록에 너무 많은 리스트가 있어서, 명시적으로 관리해야하는 boilerplate가 많이 있다. 

함수의 실행을 연기하여 보일러플레이트 중 일부를 핵심 비즈니스 로직 밖으로 옮길 수 있다. 그러고나서 보일러플레이트가 없는 core 함수 외부에서 상태를 전달할 수 있다. 

이것은 보일러플레이트를 줄여주지 않지만, 적어도 크리티컬 비즈니스 로직 밖으로 이동시켜준다.

```js
function FancyUserList(users) {
  return FancyBox(
    UserList.bind(null, users)
  );
}

const box = FancyUserList(data.users);
const resolvedChildren = box.children(likesPerUser, updateUserLikes);
const resolvedBox = {
  ...box,
  children: resolvedChildren
};
```