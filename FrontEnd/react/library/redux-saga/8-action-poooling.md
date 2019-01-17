# 액션 풀링

여태까지 각 액션에 새로운 task를 만들기 위해 `takeEvery` 이펙트 사용.
- 매번 fetchProducts action creator를 호출시,
- 그 action creator는 데이터 컨트롤을 위해 썽크를 dispatch 하는 것처럼

새로운 이펙트 `take`
- action 감시 프로세스의 전체적인 제어 가능
- 복잡한 데이터 컨트롤 플로우 설계 가능

## 간단한 로거

아래 사가는 dispatch되는 모든 action을 watch

---

`take`
- 특정한 액션을 기다리기 위해 미들웨어에게 알려주는 명령 오브젝트

- 반면에 `call` 이펙트는 미들웨어가 프로미스의 resolve를 기다리게 함
- `takeEvery`의 경우에, 실행된 태스크는 다시 실행될 때에 대한 관리 방법이 없음.
  - 언제 감시를 멈춰야 하는지에 대한 관리 방법 엇음

- take는 takeEvery와 다름.
- 컨트롤의 방향이 정반대.
- __핸들러 태스크에 푸시되고 있는 액션들 대신, 사가는 스스로 액션을 풀링함.__
  - 이는 사가가 일반 함수 콜 하는 것처럼 보임.
  - 전통적인 액션의 푸시 접근법을 해결함

예시
```js
import { take, put } from 'redux-saga/effects'

function* watchFirstThreeTodosCreation() {
  for (let i = 0; i < 3; i++) {
    const action = yield take('TODO_CREATED')
  }
  yield put({type: 'SHOW_CONGRATULATION'})
}
```

처음 세 번의 TODO_CREATED 액션 후에,
watchFirstThreeTodosCreation은 축하메시지를 띄우고 종료.

이는 제너레이터가 가비지 컬렉션이 되고, 더 이상 불필요한 감시는 없음을 의미

### Pull 접근법의 다른 이점

동기적 스타일로 컨트롤 플로우 표현 가능.
- takeEvery나 thunk 이용했다면 LOGIN, LOGOUT 2개의 태스크(thunk) 작성

__풀 모델__ 사용시
같은 액션 반복해서 핸들링하지 않고 같은 곳에 플로우 작성 가능.

```js
function* loginFlow() {
  while(true) {
    yield take('LOGIN');
    // ...login logic
    yield take('LOGOUT');
    // logout login
  }
}
```

위 `loginFlow`는 에상되는 액션순서 전달
- LOGIN 액션이 LOGOUT 액션 전에 와야함.

