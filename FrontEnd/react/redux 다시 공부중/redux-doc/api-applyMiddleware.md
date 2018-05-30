# applyMiddleware(...middleware)

middleware는 redux를 커스텀 functionality로 확장하기 위한 방식이다. 미들웨어는 store의 dispatch를 감싸게 해준다. 미들웨어의 핵심 특징은 composable한 것이다. 멀티 미들웨어는 서로 결합될 수 있다. (각 미들웨어가 체인에서 앞인지 뒤인지 알필요 없다.)

미들웨어의 가장 일반적인 유즈 케이스는 비동기 액션 지원이다. async action을 dispatch 하도록 하게 함으로써 지원 가능하다.

예를 들어, redux-thunk는 함수를 디스패치 하여 action creator를 제어 역전한다. `dispatch`를 인자로 받는다. 그리고 비동기로 호출한다. 그러한 함수를 thunk로 부른다. 

## 인수

-  `...middleware` (arguments) : 미들웨어 API를 따르는 함수다.
    - store: 각 미들웨어는 `store`의 `dispatch`와 `getState` 함수를 명명된 인수로 받아서, 함수로 반환한다.
    - next : 위에서 반환한 함수는 미들웨어의 디스패치 함수에서 `next`로 주어진다. 그래서 다른 인수와 함께, 아니면 다른 시점에, 아니면 전혀 호출되지 않을 수도 있는 `next(action)`을 호출하는 `action`의 함수다.
    - action : 체인의 마지막 미들웨어는 `next`인자로 스토어의 `dispatch`를 받아 체인을 마무리한다. (= `next(action)`)

그러므로 미들웨어의 시그니처는 `({ getState, dispatch }) => next => action` 이다.

```javascript
applyMiddleware(...middleware);
applyMiddleware(store => next => action);
applyMiddleware(({ getState, dispatch }) => next => action);
```