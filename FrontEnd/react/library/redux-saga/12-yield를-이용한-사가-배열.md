# yield*를 이용한 사가 배열

```js

function* playLevelOne() { ... }

function* playLevelTwo() { ... }

function* playLevelThree() { ... }

function* game() {
  const score1 = yield* playLevelOne()
  yield put(showScore(score1))

  const score2 = yield* playLevelTwo()
  yield put(showScore(score2))

  const score3 = yield* playLevelThree()
  yield put(showScore(score3))
}
```