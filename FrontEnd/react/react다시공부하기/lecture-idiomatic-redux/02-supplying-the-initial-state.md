# initial state 할당하기

initial state는 root reducer에 의해 결정된다. 이 경우에 root reducer는 `todos`와 `visibilityFilter`에서 `combineReducers`를 호출한 결과다.

...중략

가끔 app 시작 전에 동기적으로 store에 data를 로드하기를 원한다. 예를 들어 이전 세션에 남은 Todos가 있을 수 있다. Redux는 `createStore` 함수에 2번쨰 인자로 `persistedState`를 통과시키도록 한다.

```javascript
const persistedState = {
  todos: [{
    id: 0,
    text: 'Welcome Back!',
    completed: false
  }]
}

const store = createStore(
  todoApp,
  persistedState
)
```

`persistedState`를 통과시켰을 때, 이용가능한 reducer에 default value를 덮어쓸 것이다. 예를 들어, `todos`를 배열로 제공했지만, `visibilityFilter`의 값은 명시하지 않았기 때문에 default `SHOW_ALL`이 사용될 것이다.

