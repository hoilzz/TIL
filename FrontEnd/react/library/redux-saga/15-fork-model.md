# fork model

2개의 이펙트를 통해 태스크를 백그라운드에서 실행 가능 
- fork는 결합된 포크 만들 때 
- spawn은 분리된 포크 만들 때 

## 결합된 fork

다음의 규칙에 따라 그들의 부모와 결합됨.

### 완료

사가는 다음 사건에만 종료됨.
- 자신의 명령 모두 이행
- 모든 결합된 포크들이 종료된 뒤 

```js
import { delay } from 'redux-saga'
import { fork, call, put } from 'redux-saga/effects'
import api from './somewhere/api' // app specific
import { receiveData } from './somewhere/actions' // app specific

function* fetchAll() {
  const task1 = yield fork(fetchResource, 'users')
  const task2 = yield fork(fetchResource, 'comments')
  yield call(delay, 1000)
}

function* fetchResource(resource) {
  const {data} = yield call(api.fetch, resource)
  yield put(receiveData(data))
}

function* main() {
  yield call(fetchAll)
}
```

call(fetchAll)이 종료되려면
- fetchAll의 모든 body가 종료된 뒤 
- 2개의 포크된 태스크들이 종료된 뒤

사실 결합된 포크들은 병렬 이펙트와 같은 의미를 공유 
- 병렬로 태스크 실행 
- 부모는 그 안에서 실행된 모든 태스크가 종료된 뒤 종료 

```js
function* fetchAll() {
  yield [
    call(fetchResource, 'users'),     // task1
    call(fetchResource, 'comments'),  // task2,
    call(delay, 1000)
  ]
}
```

## 에러 전달 

병렬 이펙트든 fork된 이펙트든 셋 중 1개가 실패하면 바로 실패.

즉 다음의 경우에 취소됨 
- 자신의 내용이 에러를 throw
- 결합된 포크에서 예상치 못한 에러 발생

이 때 실패할 경우, 부모 제너레이터에서 catch구간에 잡힘 
- 봉쇄된 호출을 사용하고 있기 때문 
- 또한, fork된 태스크에서는 에러 못잡음.

## 취소 

사가 취소하기는 다음을 야기
- 메인 태스크의 취소 (봉쇄된 현재 이펙트 취소)
- 실행 중인 모든 결합된 포크들의 취소 
