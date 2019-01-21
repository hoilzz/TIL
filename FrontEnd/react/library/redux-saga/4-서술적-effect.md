# 4. Declarative Effects

Saga 로직 표현을 위해 제너레이터로부터 온 순수 JS 객체를 yield
이런 오브젝트들을 __이펙트__ 라고 부름

이펙트는 미들웨어에 의해 해석된 몇몇 정보를 담고 있는 객체

이펙트를 만들기 위해 `redux-saga/effects`에서 제공하는 함수 이용

---

Promise를 yield해보자.

```js
import { takeEvery } from 'redux-saga/effects'
import Api from './path/to/api'

function* watchFetchProducts() {
  yield takeEvery('PRODUCTS_REQUESTED', fetchProducts)
}

function* fetchProducts() {
  const products = yield Api.fetch('/products')
  console.log(products)
}
```

- 제너레이터 안에서 직접 비동기 함수 호출 하는 대신
- __함수 호출에 관한 설명만 yield 가능__

- 제너레이터는 __명령을 담고 있는 순수한 객체를 yield__
- redux-saga 는 이런 명령들의 실행을 처리
- 결과를 제너레이터에 돌려줌

```js
import { call } from 'redux-saga/effects'

function* fetchProducts() {
  const products = yield call(Api.fetch, '/products')
  // ...
}
```

`call(fn, ...args)` 사용
- fetch 요청을 즉시하지 않는 것.
- 대신, __call은 이펙트에 대한 설명을 생성__
