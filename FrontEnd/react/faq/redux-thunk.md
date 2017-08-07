# redux-thunk 

Redux를 위한 middleware다. middleware는 action이 dispatch되어 reducer에 넘어가기 전 단계다.

## Motivation

Redux thunk는

- action 대신에 **함수를 리턴하는** action creator를 작성하도록 해준다.
- thunk는 action dispatch를 지연시키기 위해 이용된다.
- 만약 조건이 만족하다면 dispatch 하도록 이용된다.

내부 함수는 store 메서드인 `dispatch`와 `getState`를 파라미터로 받는다.

비동기로 dispatch를 수행할 함수를 리턴하는 action creator

```javascript
const INCREMENT_COUNTER = 'INCREMENT_COUNTER';

function increment() {
  return {
    type: INCREMENT_COUNTER
  };
}

function incrementAsync() {
  return dispatch => {
    setTimeout(() => {
      // Yay! Can invoke sync or async actions with `dispatch`
      dispatch(increment());
    }, 1000);
  };
}
```

조건부 dispatch를 수행할 함수를 리턴하는 action creator

```javascript
function incrementIfOdd() {
  return (dispatch, getState) => {
    const { counter } = getState();

    if (counter % 2 === 0) {
      return;
    }

    dispatch(increment());
  };
}
```