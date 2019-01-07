# 리덕스 미들웨어 적용하기

`wrapDispatchWithMiddlewares`를 구현해야한다면 미들웨어는 꽤 유용하지 않다. 이거 지우고, 대신에 `applyMiddleware`라는 리덕스 util을 이용하자.

*before configureStroe*
```javascript
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

`configureStore` 함수를 보면, `store`가 바로 필요없다는 것을 알 수 있다. 