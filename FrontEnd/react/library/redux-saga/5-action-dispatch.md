# store에 액션 dispatch 하기

save 후 스토어에게 fetch가 성공했다고 알려주는 action을 dispatch 해보자.

스토어는 `dispatch`함수를 제너레이터에게 넘기면, 제너레이터는 이 함수를 fetch 응답 받은 후에 실행 할거임.

```js
function* fetchProducts(dispatch) {
  const products = yield call(Api.fetch, '/products');
  dispatch({ type: 'PRODUCTS_RECEIVED', products })
}
```

이 방법은 제너레이터 내부에서 함수를 직접 호출하는 것과 비슷한 단점 가짐.
- 만약 fetchProducts가 응답값 받은 후에 dispatch 수행하는 것을 테스트하고 싶다면,
  _dispatch 함수를 흉내내야함?_

- 흉내내는 것 대신 declarative effect가 필요.
  - 그저 dispatch는 미들웨어가 하도록 하자.
  - 그럼 yield된 이펙트를 검사하고 정확한 명령이 포함되어있는지 확인만 하면 됨.

__그래서 dispatch 이펙트를 생성하는 `put` 함수를 제공__

```js
function* fetchProducts() {
  const products = yield call(Api.fetch, '/products');
  // dispatch 이펙트를 생성하고 yield
  yield put({ type: 'PRODUCT_RECEIVED', products })
}
```

_여튼 dispatch를 PUT으로 대체한다는 거 같음?_


제너레이터를 테스트 해보자.

```js
const iterator = fetchProducts()

// expects a call instruction
assert.deepEqual(
  iterator.next().value,
  call(Api.fetch, '/products'),
  "fetchProducts should yield an Effect call(Api.fetch, './products')"
)


// create a fake response
const products = {};

assert.deepEqual(
  iterator.next(products).value,
  put({ type: 'PRODUCTS_RECEIVED', products }),
  "fetchProducts should yield an Effect put({ type: 'PRODUCTS_RECEIVED', products })"
)

```