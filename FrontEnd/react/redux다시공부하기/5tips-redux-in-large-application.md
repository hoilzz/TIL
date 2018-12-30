# 5 tips for working with redux in large application

[five-tips-for-working-with-redux-in-large-applications](https://techblog.appnexus.com/five-tips-for-working-with-redux-in-large-applications-89452af4fdcb)을 읽고 다시 정리해보기

## 1. 데이터 저장시 index 사용, 접근시 selector 사용

적절한 데이터 구조를 선택하는 것, 그 방법 중 index 사용은 API로부터 얻은 Serializable data(id가 있는)를 저장할 때 굉장히 유용하다. `hashmap`과 비슷하게 데이터를 저장한다. key를 객체의 id로, value는 객체로 표현한다. hashmap의 이점인 데이터 접근시 O(1)의 이득을 얻을 수 있다.

위와 같이 안한다면,

- REST API(/users)에서 가져온 데이터를 array로 그대로 담는다고 해보자. 특정 user 객체를 불러오려면 최대 O(N)만큼 반복문을 수행해야 한다.
- selected/unselected처럼 특정 상태의 유저를 계속 추적해야 한다면
  - 2개의 서로 다른 array에 데이터를 저장해야 한다.
  - selected/unselected유저의 index를 저장하는 array가 필요하다.

우리는 index를 사용하여 데이터를 저장하는 방식으로 위 문제를 해결할 것이다.

```javascript
{
 "usersById": {
    123: {
      id: 123,
      name: "Jane Doe",
      email: "jdoe@example.com",
      phone: "555-555-5555",
      ...
    },
    ...
  }
}
```

위 구조로 얻는 이득

- user object를 index로 간단히 찾기

```javascript
const user = state.userById[userId]
```

- array를 통해 간단하게 user를 렌더링하는 부분을 selector 패턴에서는 아래와 같이 사용

```javascript
const getUsers = ({userById}) => {
  return Object.keys(userById).map(id => userbyId[id])
}
```

- selected user만 필요하다면?

```javascript
const getSelectedUsers = ({ selectedUserIds, userById }) => {
  return selectedUserIds.map(id => userById[id])
```

- 그외에.. 이득보는 부분
  - state 모양 바꿔야하는데 selector가 없으면 view코드 전부 수정
  - selector 있으면 selector만 수정하면 됨


## view, edit state와 canonical state간의 분리

> 서비스를 통해 얻은 데이터를 canonical state라고 한다.

state는 canonical state 외에도 `ui 관련 상태`나 `app 전체 상태`를 포함하고 있다. canonical state를 다른 state와 함께 저장시, 여러 source에서 여러 데이터를 fetch해야하는 경우 확장하기 어렵다.

대신에,
canonical state만을 담은 reducer를 만들었다. 왜 이렇게 해야 할까?

REST API로 받은 유저 리스트가 있다고 하자. index storage 패턴을 따라 아래와 같은 state를 가지게 된다.

```javascript
{
  usersById: {
    123: {
      id: 123,
      name: "Jane Doe",
      email: "jdoe@example.com",
      phone: "555-555-5555",
      ...
    },
    ...
  }
}
```

*view에서 유저 정보를 수정할 수 있게 해보자*

edit아이콘 클릭시 수정 중인 상태가 반영되도록 state를 구성하자. 이번에는 canonical state와 viewState를 분리하는 대신 edit state를 user obj에 그냥 새로운 field로 넣어보자

```javascript
usersById: {
    123: {
      id: 123,
      name: "Jane Doe",
      email: "jdoe@example.com",
      phone: "555-555-5555",
      ...
      isEditing: true,
    },
    ...
  }
}
```

정보 수정 뒤, 수정 버튼 누르면 서비스에 반영된다. 서비스는 user의 새로운 state를 돌려주는데, canonical state에 덮어쓰면 `isEditing` field가 누락된다. 얘만 빼고 반영하자니 상태 변화 로직이 복잡해진다.

대신, canonical state는 다른 reducer에 보관한다. 그러면

- action을 단순하게 유지하고 변화 추적이 쉽다.
- 유저가 행동을 취소할 때, 쉽게 canonical state로 돌아갈 수 있다.

> 유저가 수정 버튼 누르고 이름, 이메일 수정 후 취소 버튼 누른다고하자. view는 취소 전 상태로 돌아가야 하는데, canonical state를 덮어쓰는 접근법이라면, REST API를 호출하여 old state로 되돌려야 한다. 대신 editing state를 다른곳에 보관하자.

```javascript
{
 usersById: {
    123: {
      id: 123,
      name: "Jane Doe",
      email: "jdoe@example.com",
      phone: "555-555-5555",
      ...
    },
    ...
  },
  editingUsersById: {
    123: {
      id: 123,
      name: "Jane Smith",
      email: "jsmith@example.com",
      phone: "555-555-5555",
    }
  }
```

canonicalState와 복사본(edtingUsersById)를 가지고 있으므로, 유저의 취소를 쉽게 반영할 수 있다.

종합하면 `edit`, `view` 그리고 `canonical state`를 서로 분리하는 방식은 유지보수를 용이하게 한다.


이점은
- 코드의 modularity를 높인다
- 구조적인 코드를 만든다.
- 이 떄, 리듀서를 쪼개면 재사용도 용이하게 한다.


## 3. view 간 state를 공유할 땐 신중하게

새로운 기능 추가 요구를 감당하기 위해 서로다른 view와 store를 관리해야한다. 그래서 페이지마다 top level reducer를 두는 게 도움이 될 수 있다.

예를 들어 users 페이지는 API로부터 받은 데이터를 users reducer에 저장한다. 현재 유저의 도메인을 추적하는 다른 페이지는 다른 도메인 API로부터 데이터를 받아 저장할 것이다. 

상태는 아래와 같다.

```javascript
{
  usersPage: {
    usersById: {...},
    ...
  },
  domainsPage: {
    domainsById: {...},
    ...
  }
}
```

위와 같이 페이지를 조작하면 **view와 관련된 데이터를 분리하여 관리할 수 있다.**
- 이 때 각 페이지는 필요한 state만 관리하고, reducer 파일은 view 파일과 같은 위치에 둘 수 있다. 

어플리케이션 규모가 커질 때, 같은 데이터에 의존하는 두 가지 view 간에 state를 공유할 필요를 느낄 수 있다. 이 때, state를 공유하는 reducer를 만들기 전에 아래 3가지를 고민하자.

**1. 이 데이터에 얼마나 많은 view와 reducer가 의존하는가?**
**2. 각 페이지가 이 데이터의 고유한 복사본을 필요 하는가?**
**3. 얼마나 데이터가 자주 바뀌는가?**

예를 들어, 앱의 모든 페이지에서 로그인된 유저 현재 정보를 보여줘야한다. 그 정보는 리듀서에 저장된다. 그리고 모든 페이지가 이 데이터에 의존성을 가지므로, 이 경우 1개 페이지 1개 리듀서 전략은 통하지 않는다. 이 경우 reducer를 공유하는 것은 좋은 전략이다. 

공유하게 되면 유저가 방문 하는 첫 페이지에서 current user reducer가 load됐는지 확인하고, 정보가 없다면 fetch 할 것이다. 

- 부적절한 경우를 찾아보자.

유저에게 도메인 뿐만 아니라 서브 도메인이 있다고 해보자. 이 경우 어플리케이션에 서브 도메인 페이지를 추가하여 유저의 모든 서브 도메인을 보여줄 것이다. 그리고 도메인 페이지는 선택된 도메인에 대해 모든 서브 도메인을 보여줄 수 있는 옵션이 있다. 또한, 도메인 및 서브 도메인은 언제든 추가 수정 삭제 될 수 있다. 그래서 각 페이지는 고유한 데이터 사본(cState)를 필요로 한다. 


*사실 이부분 잘 이해 안됨*

## 4. reducer 재사용 하기




## summary

1. 데이터 저장시 index 사용, 접근시 selector 사용

- REST API(/users)에서 가져온 데이터를 그대로 array에 담으면
  - 특정 user 객체를 불러오기 위해 O(N)만큼 반복문 수행
  - selected/unselected처럼 특정 상태의 유저를 계속 추적할 경우
    - 2개의 서로 다른 array에 객체를 저장
    - 혹은 selected/unselected 유저의 index를 저장하는 array 필요

- hashmap과 같이 index로 저장하면
  - user object를 index로 간단히 찾기 가능.
  - 특정 user 찾기를 selector 패턴으로 아래와 같이 사용

```javascript
const getUsers = ({userById}) => {
  return Object.keys(userById).map(id => userbyId[id])
}
```

- selected user만 필요하다면?

```javascript
const getSelectedUsers = ({ selectedUserIds, userById }) => {
  return selectedUserIds.map(id => userById[id])
```

selector 패턴의 이점?
  - state 모양 바꿔야하는데 selector가 없으면 view 코드 전부 수정
  - selector 있으면 selector만 수정하면 됨.


2. view, edit state, canonical state 분리

canonical state : 데이터베이스에 저장된 정확한 상태 이하 cState

cState를 다른 state와 함께 저장시 편리하지만, 여러 source에서 여러 데이터를 fetch해야 하는 경우 확장성이 낮다.

- 해결책은?
  - cState 따로 저장.

- 좋은점은?
  - modularity 높이고, 더 구조적인 코드 만듬

그리고 이케 작성하면 canonical state가 아닌 상태를 canonical state와 함꼐 보관하지 않도록 유도한다.

- 왜?
  - 유저 정보 수정시, edit 버튼 누른 후, 수정 중인 상태가 반영되도록 state 구성해보자.
  - 일단, edit state 가 user obj(cState)에 추가된 경우

```javascript
usersById: {
    123: {
      id: 123,
      name: "Jane Doe",
      email: "jdoe@example.com",
      phone: "555-555-5555",
      ...
      isEditing: true,
    },
    ...
  }
}
```

이케 하면 문제는
- 수정 버튼 누르고, user의 새로운 state를 돌려주는데, 이 떄, canonical state에 덮어쓰면 `isEditing` 누락
  - 얘(isEditing)만 빼고 반영하면 상태 변화 로직이 복잡

이걸 해결 하기 위해
- cState는 다른 reducer에 보관.
```javascript
{
 usersById: {
    123: {
      id: 123,
      name: "Jane Doe",
      email: "jdoe@example.com",
      phone: "555-555-5555",
      ...
    },
    ...
  },
  editingUsersById: {
    123: {
      id: 123,
      name: "Jane Smith",
      email: "jsmith@example.com",
      phone: "555-555-5555",
    }
  }
```
좋은점?
  - action 단순하게 유지 가능
  - 유저가 행동 취소시 쉽게 canonical State로 돌아갈 수 있음


