## slice reducer 간 데이터 공유하기

sliceReducerA가 sliceReducerB의 상태 조각이 필요하거나,
sliceReducerB가 전체 상태 트리를 인자로 필요로 한다면,

위 요구사항은 combineReducer가 처리하지 못한다.
추가 인자로 필요한 데이터를 전달할 수 있는 custom function을 작성하여 해결 가능하다.

### 1. comebineReducer 함수 내부에서 action에 따라 slice Reducer에게 추가 인자 전달하기

```js
function combinedReducer(state, action) {
  switch (action.type) {
    case 'A_TYPICAL_ACTION': {
      return {
        a: sliceReducerA(state.a, action),
        b: sliceReducerB(state.b, action)
      };
    }
    case 'SOME_SPECIAL_ACTION': {
      return {
        // specifically pass state.b as an additional argument
        a: sliceReducerA(state.a, action, state.b),
        b: sliceReducerB(state.b, action)
      };
    }
    case 'ANOTHER_SPECIAL_ACTION': {
      return {
        a: sliceReducerA(state.a, action),
        // specifically pass the entire state as an additional argument
        b: sliceReducerB(state.b, action, state)
      };
    }
    default:
      return state;
  }
}
```

### 2. action의 payload에 추가 데이터 주기

thunk function or saga function or 비슷한 접근방식으로 쉽게 해결가능.

```js
function someSpecialActionCreator() {
  return (dispatch, getState) => {
    const state = getState();
    const dataFromB = selectImportantDataFromB(state);

    dispatch({
      type: 'SOME_SPECIAL_ACTION',
      payload: {
        dataFromB
      }
    });
  };
}
```

위와 같이 하면 parent reducer는 1번과 같이 특별히 할게 없음. 제일 간단한 해결 방ㅇ법.

### 3. combineReducer 로 생성된 리듀서를 이용하여 처리하기

각 slice reducer는 독립적으로 업데이트할 수 있다. 또한, "special" case를 처리하기위한 다른 리듀서를 사용할 수 있다. 래핑된 함수는 final result를 생성하기 위해 다른 리듀서를 호출한다.

```js
const combinedReducer = combineReducers({
  a: sliceReducerA,
  b: sliceReducerB
});

function crossSliceReducer(state, action) {
  switch (action.type) {
    case 'SOME_SPECIAL_ACTION': {
      return {
        // specifically pass state.b as an additional argument
        a: handleSpecialCaseForA(state.a, action, state.b),
        b: sliceReducerB(state.b, action)
      };
    }
    default:
      return state;
  }
}

function rootReducer(state, action) {
  const intermediateState = combinedReducer(state, action);
  const finalState = crossSliceReducer(intermediateState, action);
  return finalState;
}
```
