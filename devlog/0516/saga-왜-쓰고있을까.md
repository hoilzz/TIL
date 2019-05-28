# Saga

- 부작용들(데이터 요청과 같은 비동기 작업, 브라우저 캐시와 같이 순수하지 않은 것)을 쉽게 관리

- 애플리케이션에서 필요한 사이드 이펙트를 별도의 스레드로 분리해서 관리 가능

  - 리덕스의 미들웨어로 리덕스 액션은 스레드를 시작, 중지, 취소 시킬 수 있다.

- Saga는 각 작업을 어떻게 관리할지에 대해 관심을 둔다.

## 예를 들어보자.

여행 관련 서비스가 있다. 여행 예약에 항공예약, 숙소, 차량 렌트가 있다. 사용자는 그냥 여행 프로그램을 예약한다. 서비스 내부적으로는 비행기, 숙소, 차량 렌트 모두 같이 예약한다.

## Saga의 방식

Saga의 WorkFlow를 이해하는게 가장 중요.
Saga는 액션을 연주하는 연주자처럼 이해하자.

Redux는 액션을 통해 데이터(state)가 업데이트되고 뷰(View)가 변화한다.
Saga는 이 액션과 데이터(state) 사이를 연주한다.

간단한 예제를 보자.

```js
// 1. Dispatch Action
{
  type: INCREMENT_ASYNC;
}

// 2. Wait 1000ms
delay(1000);

// 3. Dispatch Action
{
  type: INCREMENT;
}

// 4. Reducer
switch (action) {
  case INCREMENT:
    return state + 1;
  default:
    return state;
}
```

1초마다 state가 증가하는 2가지 액션 `INCREMENT`와 `INCREMENT_ASYNC`가 있다.
`INCREMENT`는 리듀서에서 받아서 직접 처리하는 액션이다.
`INCREMENT_ASYNC`는 1초 후에 +1을 처리하는 액션이다.
리듀서는 순수 함수이기 때문에 이 액션을 직접 처리하지 못한다.

비동기 동작인 2,3번은 Saga를 이용해 구현할 수 있다.(generator function을 사용하는 이유)

```js
import { delay } from "redux-saga"; // 참고: delay는 단순히 1초후에 Resolve가 되는 Promise다.
import { put, takeEvery } from "redux-saga/effects";

// INCREMENT_ASYNC 액션이 Dispatch 되면 `incrementAsync`를 수행하도록 등록한다.
export function* watchIncrementAsync() {
  yield takeEvery(INCREMENT_ASYNC, incrementAsync);
}

function* incrementAsync(action) {
  yield delay(1000); // 1초를 기다리고
  yield put({ type: INCREMENT }); // INCREMENT 액션을 Dispatch한다.
}
```

[!img](https://image.toast.com/aaaadh/real/2017/techblog/3%282%29.png)

1번을 주목하자.
Saga에서만 특정 액션을 처리하고, 리듀서에서 그 액션을 처리하지 않는 경우,
그 액션은 리덕스에 도달할까? 도달한다면 언제 도달할까?

Saga를 통하는 모든 액션은 리듀서에 먼저 도달한다.
Saga에서는 액션을 기다리고 처리하는 코드는 다음 형태로 구현되어 있다.

```js
function sagaMiddleware({ getState, dispatch }) {
  /* Saga 초기화 .... */

  return next => action => {
    const result = next(action); // hit reducers  --- 액션은 리듀서에 먼저 도달한다.
    sagaStdChannel.put(action); // Saga에 액션이 Dispatch 됐음을 알린다.
    return result;
  };
}
```

정확히 얘기하면, Saga는 지나간 액션이 리듀서에 도달했는지, 중간에 변형 혹은 필터링 됐는지 모른다.
액션이 Dispatch 되는 과정에 관여하지 않는다.
액션이 지나가는 것을 그저 바라보고 (**watch**) Saga의 연주를 시작한다. 이거시 Saga의 방식이다.

1. 모든 액션은 리듀서에 먼저 도달한다.(사실은 그냥 액션이 지나가는 것을 본 이후 동작)
2. 지나간 액션을 자신의 채널에 알린다.
3. 각 액션에 따른 작업을 처리하고, 필요에 따라 그 결과를 다시 put(dispatch)한다.

## Summary

애플리케이션을 개발하며 사이드 이펙트, 비동기, 혹은 이외의 것들

1. 병렬 처리
2. A 액션이 dispatch 된 이후 B 액션의 Dispatch까지 한 번 더 기다린 이후 어떤 작업 처리
3. 일괄적인 실패, 에러 처리
4. 리액트 컴포넌트 성능 (일부 상황에 대해 컴포넌트의 Reconciliation을 방지 가능)
5. Socket 연동..

**개인적으로 좋았던점**

- thunk에 비해 action creator에서 처리해야할 로직이 줄어든다.
- 다양한 사이드 이펙트 헬퍼 함수를 제공해준다.
- 체이닝을 통해 일련의 액션들을 오케스트레이션 할 수 있다.
- 액션은 pure function으로써 단순히 dispatch에 집중하고, reducer는 상태를 업데이트하는데 집중하고, saga에서는 비동기 로직과 같은 부작용이 있는 동작에 대해 처리를 집중할 수 있다. thunk에서는 액션생성자에서 일련의 과정들을 전부 처리해주어야하고, 순수함수가 아닌 promise객체를 리턴하는 경우가 있다. 즉, action 이 과도한 책임을 가진다.

**아쉬운점**

- saga 함수가 작성된 파일이 추가되어서 관리해야할 대상이 늘어난다(근데 유지보수가 나쁘다는 얘기아님, 굳이 아쉬운점)
