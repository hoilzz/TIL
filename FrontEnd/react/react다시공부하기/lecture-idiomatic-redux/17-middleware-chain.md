# 17. middleware chain


## Introducing Middleware Functions

**store의 메서드를 확장했지만, public API를 오버라이드 하는 것과 custom function으로 대체하는 것은 좋지 않다.**

이 패턴을 없애기 위해, middleware function의 배열을 선언한다. `middlewares` 배열은 나중에 single step으로 적용할 함수가 포함된다. middleware 배열에 addLoggingToDispatch와 addPromiseSupportToDispatch를 푸시하자.

store를 첫번쨰 인자로 갖고 middleware 배열을 두 번쨰 인자로 갖는 wrapDispatchWithMiddleware() 함수를 만들자.

```javascript
const wrapDispatchWithMiddlewares = (store, middlewares) =>
  middlewares.forEach(middleware =>
    store.dispatch = middleware(store);
  );

const configureStore = () => {
  const store = createStore(todoApp);
  const middlewares = [promise];

  if (process.env.NODE_ENV !== 'production') {
    middlewares.push(logger);
  }

  wrapDispatchWithMiddlewares(store, middlewares);

  return store;
};
```

`wrapDispatchWithMiddlewares()` 내부에서 middleware의 forEach 메서드를 사용할 것이다.

특히, store와 함께 미들웨어를 호출한 결과를 가리키도록 `store.dispatch`함수를 오버라이드할 것이다.

```javascript
const wrapDispatchWithMiddlewares = (store, middlewares) => middlewares.forEach(middleware => store.dispatch = middleware(store))
```

**미들웨어는 first-class concept이다.** `addLogginToDispatch`를 `logger`로 리네임하고 `addPromiseSupportTodispatch`를 `promise`로 리네임할 것이다.

```javascript
// Before
const addPromiseSupportToDispatch = (store) => {
  return (next) => {
    return (action) => {
      if (typeof action.then === 'function') {
        return action.then(next);
      }
      return next(action);
    };
  }
};

// After
const promise = (store) => (next) => (action) => {
  if (typeof action.then === 'function') {
    return action.then(next);
  }
  return next(action);
}
```

함수를 리턴하는 함수를 리턴하는 함수다. promise로 바꿔서 가독성 좋아졌다.


## Summary

커링, arrow function, rename function을 통해 가독성을 높임. 또한 public