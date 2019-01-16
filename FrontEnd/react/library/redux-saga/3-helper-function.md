# 헬퍼 함수

action이 dispatch 되었을 때 태스크를 만들기 위해 내부 함수들을 감싸는 헬퍼 이펙트 제공

`takeEvery`

```js
import { call, put } from "redux-saga/effects";

export function* fetchData(action) {
  try {
    const data = yield call(Api.fetchUser, action.payload.url);
    yield put({ type: "FETCH_SUCCEEDED", data });
  } catch (err) {
    yield put({ type: "FETCH_FAILED", err });
  }
}
```

위 태스크를 FETCH_REQUESTED 액션마다 실행 하려면

```js
import { takeEvery } from "redux-saga/effects";

function* watchFetchData() {
  yield takeEvery("FETCH_REQUESTED", fetchData);
}
```

`takeEvery`는

- 여러 개의 fetchData 인스턴스를 동시에 시작하게 함.
- 1개 혹은 여러개의 종료되지 않은 fetchData task들이 있으면 새로운 fetchData task를 시작 가능
- 만약 마지막으로 발생된 리퀘스트의 응답만 얻고 싶으면 `takeLatest` 헬퍼 사용

```js
import { takeLatest } from "redux-saga/effects";

function* watchFetchData() {
  yield takeLatest("FETCH_REQUESTED", fetchData);
}
```

takeEvery와 달리 takeLatests는 단 1개의 fetchData만 실행되게 함.

다른 액션들을 보고 있는 여러개의 Saga를 가진다면,
Saga를 생성하기 위해 사용된 fork와 비슷한 동작을 하는
내장 함수들과 함께 여러개의 **워쳐** 들을 만들 수 있음

```js
import { takeEvery } from 'redux-saga'

// FETCH_USERS
function* fetchUsers(action) { ... }

// CREATE_USER
function* createUser(action) { ... }

// use them in parallel
export default function* rootSaga() {
  yield takeEvery('FETCH_USERS', fetchUsers)
  yield takeEvery('CREATE_USER', createUser)
}
```

## Summary

- 액션이 디스패치되었을 때 __태스크를 만들기 위해__ 내부 함수들을 감싸는 헬퍼 이펙트를 제공

특정 태스크를 특정 액션마다 실행 하게 하려면 takeEvery를 이용

```js
function* watchFetchData() {
  yield takeEvery("FETCH_REQUESTED", fetchData); // 요청할 때마다 fetchData 실행
}
```

takeEvery는
- 여러 개의 fetchData 인스턴스 동시에 시작하게 함.
- 종료되지 않은 여러개 fetchData task가 있다면 새로운 fetchData task로 시작 가능

takeLatest
- 마지막으로 발생된 리퀘스트의 응답만 얻고 싶다면 얘 사용