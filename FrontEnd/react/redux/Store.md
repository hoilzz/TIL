# Store

여태 "what happend"에 대해 나타는 `actions`를 정의하고 action에 따라 state를 update하는 `reducer`를 정의 했다.

<br>
**`Store`**는 action과 reducer를 함꼐 가져오는 Object다.
- application state를 유지한다.
- `getState()`를 통해 state에 접근을 허용한다.
- `dispatch(action)`을 통해 state가 업데이트 되도록 한다.
- `subscribe(listener)`를 통해 리스너를 등록한다
- `subscribe(listener)`에 의해 리턴된 function을 통해 listener 등록 취소 처리한다.

Redux에서 a single store만 가지는 것은 중요하다. data 처리를 분리할 때, 많은 store 대신에 [reducer composition](https://github.com/reactjs/redux/blob/master/docs/basics/Reducers.md#splitting-reducers)을 사용할 것이다.

만약 리듀서를 가지고 있다면 store를 생성하는 것은 쉽다. 이전 섹션에서, 리듀서들을 하나로 combine하기 위해 `combineReducers()`를 사용했다. 그것을 이제 import해서 `createStore()`에 인자로 넣어보자

```javascript
  import { createStore } from 'redux'
  import todoApp from './reducers'
  let store = createStore(todoApp)
```

## Dispatching actionTypes
store 1개 만들었다. UI 없이 update logic을 test해 볼 수 있다.

```javascript
// Every time the state changes, log it
// Note that subscribe() returns a function for unregistering the listener
let unsubscribe = store.subscribe(() =>
  console.log(store.getState())
)

// Dispatch some actions
store.dispatch(addTodo('Learn about actions'))
store.dispatch(addTodo('Learn about reducers'))
store.dispatch(addTodo('Learn about store'))
store.dispatch(toggleTodo(0))
store.dispatch(toggleTodo(1))
store.dispatch(setVisibilityFilter(VisibilityFilters.SHOW_COMPLETED))
```

UI 작성 없이 reducer와 action creator를 위해 테스트할 수 있다. mock 없이도 되는 이유는 리듀서가 `pure function` 이기 때문이다.
