# Normalizing the state shape

state tree 내부에서 `todo` objects 의 배열을 todos 로 나타낸다. 그러나, real app 에서 single array 이상일 수도 있고 다른 배열에서 동일한 ids 를 가진 todos 의 sync 가 맞지 않을 수 있다.

_todos.js_ Before

```javascript
const todos = (state = [], action) => {
  switch (action.type) {
    case 'ADD_TODO':
      return [...state, todo(undefined, action)];
    case 'TOGGLE_TODO':
      return state.map(t => todo(t, action));
    default:
      return state;
  }
};
```

_todos.js_ 리팩토링하기

state 를 db 로 다루기, **todos 를 id 에 의해 인덱싱된 obejct 로 유지할 것이다.**

- reducer 를 `byID`로 리네이밍하기
- 마지막 index 에 new item 추가 or 매번 매핑하기 말고 lookup table 내부의 값으로 변경할 것이다.

`TOGGLE_TODO`와 `ADD_TODO`는 동일한 로직을 가진다. (둘 다 룩업 테이블에서 key 값에 id 를 찾거나 추가, value 는 action 에서 태운 값)

`action.id`의 값이 이전 `action.id`값과 `action` 으로 reducer 를 호출한 결과가 되는 new lookup table 을 리턴할거다.

```javascript
const byId = (state = {}, action) => {
  switch (action.type) {
    case 'ADD_TODO':
    case 'TOGGLE_TODO':
      return {
        ...state,
        [action.id]: todo(state[action.id], action),
      };
    default:
      return state;
  }
};
```

## adding an allIds reducer

이제 `byId` map 에서 todos 자체를 유지한다. `id`s 의 배열이 되도록 리듀서의 상태를 만든다.

이 리듀서는 action 의 type 에서 스위치할 것이다. `ADD_TODO`만 신경쓸건데 그 이유는 만약 new todo 가 추가되면 new `id`를 가진 새로운 `id`s 배열을 리턴해야 한다.

다른 action 의 경우, 현재 state 를 리턴해주면 된다.

```javascript
const allIds = (state = [], action) => {
  switch (action.type) {
    case 'ADD_TODO':
      return [...state, action.id];
    default:
      return state;
  }
};
```

`todos.js`에서 단일 리듀서로 export 해야한다. 그래서 `byId`와 `allIds` 리듀서를 컴바인 하기위해 combineReducers()를 다시 사용한다.

> Note: combined reducers 를 너가 원하는 만큼 사용할 수 있다. top-level reducer 에서만 사용하지 않아도 된다. 사실 너의 앱이 커질때마다 이런 경우는 허다하다. 몇가지 장소에 combineReducer 를 사용할 것이다.

## Updating getVisibleTodos selector

reducer 에서 state shape 을 변경했다. 변경된 state shape 을 의존하는 selector 를 업데이트해보자.

state object 는 이제 `byId`와 `allIds` 필드를 포함한다. 왜냐하면 combined reducer 의 state 와 일치하기 때문이다.

todos 의 배열을 더이상 사용하지 않기 떄문에, 배열을 생성하는 `getAllTodos` 셀렉터를 만들자.

`getAllTodos`는 todos.js 에서만 사용하기 때문에 `allIds`와 state 의 `byId` lookup table 을 매핑한 결과를 리턴하자.

```javascript
const getAllTodos = state => state.allIds.map(id => state.byId[id]);
```

`getVisibleTodo` 셀렉터 내부에서 필터링된 todos 배열을 얻기 위해 new selector(`getAllTodos`)를 사용하고 있다.

`allTodos`는 컴포넌트가 예측하는 todos 의 배열이다. 그래서 셀렉터로부터 리턴할 수 있고 component 코드가 변경되는 것에 대해 걱정할 필요가 없다.

```javascript
export const getVisibleTodos = (state, filter) => {
  const allTodos = getAllTodos(state);
  switch (filter) {
    case 'all':
      return allTodos;
    case 'completed':
      return allTodos.filter(t => t.completed);
    case 'active':
      return allTodos.filter(t => !t.completed);
    default:
      throw new Error(`Unknown filter: ${filter}.`);
  }
};
```

## Extracting the todo Reducer

todos.js 는 넘 커졌다. single todo 를 관리하는 파일을 따로 생성하자.

`todo.js`를 reducer 폴더에서 생성하자. todos.js 에서 todo 를 호출하여 관리하자.

## Summary

todos 를 id 에 의해 인덱싱된 object 로 유지

- todos 를 byId 로 변경하기
  - 내부 구조도 `id: value`인 lookup table 로 변경하기
- allIds reducer 추가하기

  - id 만 관리되는 배열 만들기

- combineReducer 는 top-level 뿐만 아니라 여러 레벨에서 사용가능. 앱 커지면 저절로 필요성 느낄 것이다.

- selector 업데이트하기

  - state 구조 바꼈다. selector 도 동일하게 바꿔주자.
  - todos 는 배열을 더이상 사용하지 않기 떄문에 배열을 생성해주는 getAllTodos 셀렉터를 만들자.

- getVisibleTodo 에서 getAllTodos 를 가져와서, 이 데이터의 필터링된 결과를 리턴한다.
