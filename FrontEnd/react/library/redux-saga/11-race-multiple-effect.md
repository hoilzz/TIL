# 여러 이펙트의 경주

여러 태스크를 병렬로 시작하지만, 전부 기다리고 싶지 않을 때가 있음.
`race`로 여러 이펙트를 경주시킬 수 있음

_응답시간을 1초로 제한_

```js
import { race, take, put } from "redux-saga/effects";
import { delay } from "redux-saga";

function* fetchPostsWithTimeout() {
  const { posts, timeout } = yield race({
    posts: call(fetchApi, "/posts"),
    timeout: call(delay, 1000)
  });

  if (posts) put({ type: "POSTS_RECEIVED", posts });
  else put({ type: "TIMEOUT_ERROR" });
}
```

_경주에서 진 이펙트 자동 취소_

- 아래 예제는 CANCEL_TASK 액션이 dispatch 되면, race는 자동으로 backgroundTask를 취소(태스크 내부에 취소 에러를 throw)

```js
function* backgroundTask() {
  while (true) { ... }
}

function* watchStartBackgroundTask() {
  while (true) {
    yield take('START_BACKGROUND_TASK')
    yield race({
      task: call(backgroundTask),
      cancel: take('CANCEL_TASK')
    })
  }
}
```
