# fetched data로 state 업데이트하기

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

서버에서 온 모든 데이터가 클라에서 이용가능할 때만 위 코드가 동작할거다. **일반적으로는 무언가를 가져오는 application에서는 사용할 수 없다.**

만약 서버에서 todos가 천단위로 내려오면, 전부 가져와서 필터링 하는것은 비 실용적이다..

## Refactoring getVisibleTodos

엄청 큰 1개의 `id`s를 유지하는 것보다,

- every filter's tab에 대해 `id`s 리스트를 유지하는 것이 낫다.
- 그래서 그것들은 분리되서 저장되고 fetched된 데이터와 함께 action에 따라 채워질 것이다.

`getAllTodos` selector를 지울거다. 왜냐하면 `allTodos`에 대해 접근하지 않을거기 때문이다.

```javascript
export const getVisbileTodos = (state, filter) => {
  const ids = state.idsByFilter[filter];
  return ids.map(id => state.byId[id]);
}
```

## Refactoring todos

*todos reducer before*

```javascript
const todos = combineReducers({
  byId,
  allIds
})
```

*todos reducer after*

```javascript
const todos = combineReducers({
  byId,
  idsByFilter
})
```

## Creating idsByFilter

idsByFilter는 모든 필터에 대해 `id`s 별개 리스트를 결합한다. 그래서 `all`필터에 대해 `allIds`가 있고, `active` filter 에 대해 `activeIds`있고, `completed` filter에 대해 `completedIDs`가 있다.

```javascript
const idsByFilter = combineReducers({
  all: allIds,
  active: activeIds,
  completed: completedIds,
});
```

## allIds 리듀서 업데이트하기

원래 `allIDs` 리듀서는 `ADD_TODO` action과 IDs의 배열을 관리했다.

서버로부터 fetch된 데이터에 대해 응답하기 위해 뭔가 가르칠꺼다.

*allIds before*
```javascript
const allIds = (state = [], action) => {
  switch (action.type) {
    case 'ADD_TODO':
      return [...state, action.id];
    default:
      return state;
  }
}
```

`ADD_TODO`를 `RECEIVE_TODOS`로 리네이밍 하자. `RECEIVE_TOODS` action을 처리하기 위해,

**server 응답으로 얻은 todos의 새로운 배열을 리턴할거다.**

이 새로운 todos 배열을 함수에 매핑할 거다. 이 함수는 단지 `todo`에서 id를 셀렉트하는 거다. 모든 IDs를 active IDs, completed IDs로 분리하기로 결정했고 그래서 그것들은 **완전히 독립적으로 fetch될 것이다.**

*allIds after*

```javascript
const allIds = (state = [], action) => {
  switch (action.type) {
    case 'RECEIVE_TODOS':
      return action.response.map(todo => todo.id);
    default:
      return state;
  }
}
```

## activeIds reducer 생성하기

`activeIds` reducer는 `id`s의 배열을 추적할 것이다.(단, active tab에서 `todos`만 추적할 것이다) `allIds` reducer가 전에 하던것과 동일하게 `RECEIVE_TODOS` action을 처리할 필요가 있다.

*activeIds reducer*

```javascript
const activeIds = (state = [], action) => {
  switch (action.type) {
    case 'RECEIVE_TODOS':
      return action.response.map(todo=>todo.id)
    default:
      return state;
  }
}
```


## 올바른 배열로 업데이트하기

`activeIds`와 `allIds`는 `RECIEVE_TODOS` 액션이 실행될 때, 새로운 state를 리턴해야 한다. 하지만 어떤 `id`배열이 업데이트 되야 하는지 알려줄 방법이 필요하다.

만약 `RECEIVE_TODOS` action을 재호출한다면, action 객체에 `filter`를 전달해야 한다. 이것은 우리가 reducer와 상응하는 filter와 action 내부의 filter를 비교할 수 있게 해준다.

*activeIds reducer*

```javascript
const activeIds = (state = [], action) => {
  if (action.filter !== 'active') {
    return state;
  }
}
```

## completedIds reducer 만들기

이 리듀서는 다른 filter 리듀서와 동일하다.

```javascript
const completedIds = (state = [], action) => {
  if (action.filter !== 'completed') {
    return state;
  }
  switch (action.type) {
    case 'RECEIVE_TODOS':
      return action.response.map(todo => todo.id);
    default:
      return state;
  }
};
```

## Updating the byId Reducer

ids 관리하는 리듀서를 가지고 있다. 서버의 응답값의 new `todos`를 실제로 처리하기 위해 byId reducer를 업데이트 해야한다.

*byId before*

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

기존의 case문을 지우면서 시작하자. 왜냐하면 데이터는 더이상 로컬에 없기 때문이다. 대신에, `RECEIVE_TODOS` action을 다른 리듀서에서 처리하자.

그리고나서, `state`object의 shallow copy인 `nextState`를 만들꺼다. 응답값의 every `todo` 오브젝트를 통해 이터레이트를 돌리고 `nextState`에 할당한다.

`nextState`의 entry에 있는 모든 것을 fetch된 new todo로 변경할 것이다.

마침내, next version of the llokup table을 리듀서로부터 반환할 것이다.

*byId after*

```javascript
const byId = (state = {}, action) => {
  switch (action.type) {
    case 'RECEIVE_TODOS': // eslint-disable-line no-case-declarations
      const nextState = { ...state };
      action.response.forEach(todo => {
        nextState[todo.id] = todo;
      });
      return nextState;
    default:
      return state;
  }
};
```

## finishing up

마지막에, `todo.js`의 import를 지울 수 있고, file도 지워도 상관없다. 왜냐하면 adding and togglinf todos 로직이 API에서 구현됐기 때문이다.


## summary

기존에 로컬에 모든 todo(많아야 20개정도..?)가 있을 때는 아래 코드가 잘 동작한다.

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

- 근데, 무언가(일부)를 가져오는 상황에선 사용할 수 없다.
  - 사실 무언가라는게 뭔지도 모르겠고 왜 사용못하는지 모르겠수다.
- 또한, 서버에서 todos가 천단위로 내려오면, 전부 가져와서 필터링 하는 것은 비 실용적

그래서

- filter tab에 대해 `id`s 리스트를 유지하기
- 분리해서 저장하기
  - fetch된 데이터와 함께 action에 따라 채우기

```javascript
export const getVisbileTodos = (state, filter) => {
  const ids = state.idsByFilter[filter];
  return ids.map(id => state.byId[id]);
}

const todos = combineReducers({
  byId,
  idsByFilter
})

const idsByFilter = combineReducers({
  all: allIds,
  active: activeIds,
  completed: completedIds,
});
```