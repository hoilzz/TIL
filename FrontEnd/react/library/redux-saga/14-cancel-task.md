# 14. 태스크 취소

태스크가 fork되었다면, `yield cancel(task)`를 사용하여 취소 가능.

이 과정이 동작하는 방식을 살펴보자.
UI 명령으로 백그라운드 싱크를 시작/중지하는 예제임.

```js
import { take, put, call, fork, cancel, cancelled } from 'redux-saga/effects'
import { delay } from 'redux-saga'
import { someApi, actions } from 'somewhere'

function* bgSync() {
  try {
    while (true) {
      yield put(actions.requestStart())
      const result = yield call(someApi)
      yield put(actions.requestSuccess(result))
      yield call(delay, 5000)
    }
  } finally {
    if (yield cancelled())
      yield put(actions.requestFailure('Sync cancelled!'))
  }
}

function* main() {
  while ( yield take(START_BACKGROUND_SYNC) ) {
    // starts the task in the background
    const bgSyncTask = yield fork(bgSync)

    // wait for the user stop action
    yield take(STOP_BACKGROUND_SYNC)
    // user clicked stop. cancel the background task
    // this will cause the forked bgSync task to jump into its finally block
    yield cancel(bgSyncTask)
  }
}
```

- bgSyncTask의 취소는 finally 구간으로 점프시킴.
- 여기서 `yield cancelled()` : 취소 여부 확인

실행중인 태스크 취소시, 순간 block된 태스크가 있는 현재 이펙트 또한 취소됨.
- block된 1번 call이 다른 call(2번) effect를 수행할 경우, 1번 call을 cancel하면 하위 (2번) call도 취소

## fork effect로 제너레이터 테스트하기

테스트할 때 createMockTask를 사용해야함.
이 함수가 반환하는 객체는 fork 테스트 후에 next의 인자로 주어져야함.
mock task가 cancel로 이어질 수 있음.

