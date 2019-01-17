# 6. error handling

Api.fetch가 fallback과 같은 이유로 reject된 Promise를 리턴할 경우.

Saga 안에서 `PRODUCT_REQ_FAILED` action을 스토어에 dispatch 하여 에러 핸들링.

일단 try/catch로 에러를 잡자.

```js
function* fetchProducts() {
  try {
    const products = yield call(Api.fetch, '/products')
    yield put({ type: 'PRODUCTS_RECEIVED', products })
  }
  catch(error) {
    yield put({ type: 'PRODUCTS_REQUEST_FAILED', error })
  }
}
```