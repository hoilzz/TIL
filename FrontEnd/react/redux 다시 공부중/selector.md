# Selectors in Redux are a MUST

redux selector가 해결할 수 있는 것은 많다.

crazy search page 작업했었다. normal text query외에 user는 filter의 개수를 선택할 수 있다. 필터는 모든 종류와 모양으로 나온다: 몇몇은 checkbox 집합, 일부는 중첩된 체크박스 트리이며 일부는 텍스트 상자로 필터링할 수 있다. 그것 뿐만 아니라, AND와 OR를 결합하여 복잡한 쿼리를 만들 수 있다.

겁나 빡센 스펙이었고, 개발하던 중에 selector는 도움이 되었다.

## Keeping state flat

프로젝트 개발 초기에 아래와 비슷한 store 모양을 가지고 있었다.

```javascript
const store = {
  filters: {
    locations: [],
  }
}
```

`locations`은

```javascript

```

## separating concerns

`locationByPath`는 너무 많은 정보를 담고 있다. 양쪽 도메인(id, value, heierarchy and UI data)을 다 가지고 있다. 대부분의 경우 도메인과 UI 데이터는 서로 다른 니즈와 라이프사이클을 가지고 있기 때문에 잘못된 설계다. 예를 들어, 나의 경우에는 필터가 스토어에서 한 번 로드되면 절대 업데이트 되지 않는다. 반대로, `checked` 프로퍼티는 checkbox의 상태가 바뀔 떄마다 토글된다. 그러므로, 2개를 분리하기로 했다.

```javascript
const locationsByPath = {
  1: {
    id: 1,
    value: 'Europe',
  },
  '1/2': {
    id: 2,
    value: 'Central Europe',
  },
  '1/2/3': {
    id: 3,
    value: 'Italy',
  },
  // ...
}

const checkedLocationsPaths = ['1', '1/2', '1/2/3']
```

이케 하면 좋은 거는 엄청 쉽게 노드를 확인할 수 있다.

```javascript
const newCheckedLocations = checkedLocationsPaths.includes('1/2/3') ?
  checkedLocationPaths: checkedLocationPaths.concat('1/2/3')
```

또한, `checkedLocationsPaths`와 `locationsByPath`는 독립적이다. 즉, 얘네는 다른 라이프사이클을 따를 수 있다. 예를 들어, `checkedLocationsPaths`는 `locationsByPath`가 로딩되기 전에 스토어에서 보여질 수 있다.

불행히도, flat state로 리팩토링 하는 것은 reducer 부분은 쉬웠지만 컴포넌트 부분은 어려웠다. initial nested shape은 컴포넌트가 처리하기에 더 쉬웠다.

```javascript
const Component = ({ value, checked, children }) =>
  <div>
    <input type='checkbox' value={value} checked={checked} />
    {children.map(({ value, checked, children }) =>
      <Component
        value={value}
        checked={checked}
        children={children}/>
    }
  </div>
```

flat state를 다루기 위해 컴포넌트에 로직을 추가했다. 하지만 그것이 올바른 위치였을까? 그렇게 생각하지 않는다. 그렇게 하면 컴포넌트에 state의 모양을 연결하는 것을 의미한다.

## selector to the rescue

reducer는 상태를 특정 모양으로 작성하는 역할을 한다. 그러므로, reading part를 처리하기 위해 가능한 가까이 배치하는 것이 좋다. 그것이 selector의 역할이다.

동일한 곳에 `initialState`를 갖는 것은 R/W 측면에서 올바른 장소다.

```javascript

```



---

1. 데이터 저장시 index 사용, 접근시 selector 사용

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

- 그외에..
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

페이지마다 top level reducer를 두는 게 도움이 될 수 있다.


## 4. reducer 재사용 하기


