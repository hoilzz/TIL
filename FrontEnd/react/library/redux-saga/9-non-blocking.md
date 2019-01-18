# 9. non-blocking 호출

```js
function* loginFlow() {
  while (true) {
    yield take('LOGIN')
    // ... perform the login logic
    yield take('LOGOUT')
    // ... perform the logout logic
  }
}
```

##

```js
function* authorize(user, password) {
  try {
    const token = yield call(Api.authorize, user, password)
    yield put({type: 'LOGIN_SUCCESS', token})
    return token
  } catch(error) {
    yield put({type: 'LOGIN_ERROR', error})
  }
}

function* loginFlow() {
  while (true) {
    const {user, password} = yield take('LOGIN_REQUEST')
    const token = yield call(authorize, user, password)
    if (token) {
      yield call(Api.storeItem, {token})
      yield take('LOGOUT')
      yield call(Api.clearItem, 'token')
    }
  }
}
```

위 코드의 문제점은 사용자가 로그인 버튼 누르고 기다리는 동안,
즉, Api.authroize가 오랜시간 펜딩 중일 때..
이 때, `loginFlow`가 `authorize` 호출에 의해 block 되어 있음.

사용자가 못참고 로그아웃을 누르면 `LOGOUT`은 무시됨.
왜냐하면 block상태라 `yield take('LOGOUT')`을 만나지 않았기 때문.

문제 발생 이유는
- call 이 blocking 이펙트이기 때문
- 즉 제너레이터 호출 종료 전까지 아무것도 수행 불가
- `LOGOUT`과 `authorize`은 동시 발생적임
  - authorize 뿐만 아니라, 호출 중간에 일어날 수 있는 우발적인 `LOGOUT` 액션 또한 watch하기를 원함.

문제 해결하려면
- `authorize` 논블락킹으로 변경
- `LOGOUT`을 계속해서 watch

그래서 `fork`를 사용해보자.
- 태스크를 fork하면, 백그라운드에서 진행.
- fork된 태스크는 종료될 때까지 진행하지 않고 플로우를 계속해서 진행.

```js
import { fork, call, take, put } from 'redux-saga/effects'
import Api from '...'

function* authorize(user, password) {
  try {
    const token = yield call(Api.authorize, user, password)
    yield put({type: 'LOGIN_SUCCESS', token})
    yield call(Api.storeItem, {token})
  } catch(error) {
    yield put({type: 'LOGIN_ERROR', error})
  }
}

function* loginFlow() {
  while (true) {
    const {user, password} = yield take('LOGIN_REQUEST')
    yield fork(authorize, user, password)
    yield take(['LOGOUT', 'LOGIN_ERROR'])
    yield call(Api.clearItem, 'token')
  }
}
```

바뀐거
- token 받는 로직을 authroize 내부로 이동
  - fork를 통해 백그라운드 동작이라 결과를 얻을 수 없기 때문
- LOGOUT, LOGIN_ERROR를 동시에 watch

아직 남은 문제점
- API 호출 도중에 `LOGOUT`을 받는다면, authorize 프로세스를 취소해야함.
  - 그렇게 안하면 2개의 동시 발생적인 태스크가 진행됨
  - authorize 태스크는 계속 성공 or 실패 결과 기다릴거고
    - LOGIN_SUCCESS or LOGIN_ERROR를 dispatch해서 엇갈린 상태가 만들어지게됨.

- fork된 태스크를 취소하기 위해 `cancel`을 사용하자.

```js
function* loginFlow() {
  while (true) {
    const {user, password} = yield take('LOGIN_REQUEST')
    // fork return a Task object
    const task = yield fork(authorize, user, password)
    const action = yield take(['LOGOUT', 'LOGIN_ERROR'])
    if (action.type === 'LOGOUT')
      yield cancel(task)
    yield call(Api.clearItem, 'token')
  }
}
```

yield fork는 태스크 오브젝트를 리턴.

또 다른 문제 상황이 있다.
로그인 요청(LOGIN_REQ) 후, `isLoginPending` flag값을 true로 설정하여 스피너 보여줄 수 있다.
만약 API 호출 도중 LOGOUT을 받고 태스크가 정지된다면, 또다시 엇갈린 상태로 끝남.

`cancel` 이펙트는 청소 로직을 실행할 기회를 제공
- finally 구간안에서 취소 로직 다룰 수 있음
- `cancelled`라는 이펙트를 사용하여 취소로직 생성

```js
function* authorize(user, password) {
  try {
    const token = yield call(Api.authorize, user, password)
    yield put({type: 'LOGIN_SUCCESS', token})
    yield call(Api.storeItem, {token})
    return token
  } catch(error) {
    yield put({type: 'LOGIN_ERROR', error})
  } finally {
    if (yield cancelled()) {
      // ... put special cancellation handling code here
    }
  }
}
```

그래서
- RESET_LOGIN_PENDING을 액션 디스패치 하거나
- 더 간단한건, LOGOUT 액션에게 리듀서에게 isLoginPending 처리하게 하기.