# Reducer
변화를 일으키는 함수
순수해야한다
- 비동기 작업 X
- 인수 변경 X
- 동일한 인수 = 동일한 결과
즉, 똑같은 인수로 실행했는데 첫번째, 두번째 결과가 다르면 안된다. 이 소리는 Date.now , Randomize 함수 쓰면 안되나는 말

이전 상태와 액션을 받아서 다음 상태를 반환
`(previousState, action) => newState`
- action : 어떤 작업을 할지 정보를 지닌 객체
  - 이걸 전달해주면 이거에 따라 새로운 상태 반환
- **이전 상태 변경이 아닌 새로운 상태를 반환하는 것**
  - 기존 상태를 복사하고 액션에 따른 변화를 준다음에 반환

<br>
### counter.js
- action types 먼저 불러오기
```javascript
import * as types from '../actions/ActionsTypes';
```
- 위와같이 하면 types안에 action들이 다 들어옴

- 리듀서의 초기 상태 정하기
  - 리듀서의 함수가 파라미터로 이전 상태값과 액션을 전달 받음
  - 처음에 이전상태가 정의 되어있지않는데
  - 그 때 사용할 초기 상태 정의하자 (상수 형태로)

```javascript
const initialState = {
  number: 0,
  dummy: 'dumbdumb',
  dumbOjbect : {
    d:0,
    u:1,
    m:2,
    b:3
  }
};
```

- 리듀서는 함수다
  - 내보내야 하니까 `export default`
- 아래 함수가 처음 실행시 `state`가 `undefined`
  - 이럴 때 우리가 지정한 `initialState` 실행
  - 근데 if문 안하고 파라미터에 `defaultArgument`로 `state = initialState`로 해도됨

```javascript
export default function counter(state = initialState, action){

  switch(action.type){
    case types.INCREMENT:
      // 기존 값에 있는 넘버를 불러와서 거기에다가 1을 더한 값을 새로운 객체를 만들어 반환
      // return { number : state.number + 1}
      // state.number를 증가시키는게 아닌 state.number + 1이라는 객체를 생성하여 반환
      // 만약에 리턴할 값이 하나 더 있다고 해보자.
      // return { ...state, number : state.number + 1 };
      // 이렇게 하면 기존의 값에 새로운 값을 추가하면서 덮어씌움
      // 예를 들어 state객체 안에 있는 값 중에 객체 형태로 되있을 때 그 값 중 하나만 바꾼다고 해보자.
      // 위 dumbOjbect 중 u의 값만 0으로 바꾸고 싶다면?
        return {
          ...state,
          number: state.number + 1,
          dumbObject: { ...state.dumbObject, u: 0 }
          // 위와 같이 하면 기존값은 그대로 있고 u만 덮어씌움
        };
    case types.DECREMENT:
      return {
        ...state,
        number: state.number - 1
      };
     // action case의 default
     default:
      return state;

  }
}
```
- 이 카운터 리듀서에 다룰 액션이 2개다 (인크리먼트, 디크리먼트)

```javascript
return {
  ...state,
  number: state.number + 1,
  dumbObject: { ...state.dumbObject, u: 0 }
  // 위와 같이 하면 기존값은 그대로 있고 u만 덮어씌움
};
```

- 기존 값의 number를 불러와서 거기에다가 1을 더한 값을 새로운 객체를 만들어 반환
  - `state.number`를 증가시키는게 아닌 `state.number + 1`이라는 객체를 생성하여 반환
  - 만약에 리턴할 값이 하나 더 있다면..?
```javascript
return {
  ...state,
  number : state.number + 1
}
```
- 위와 같이 하면 기존의 값에 새로운 값 추가하면서 덮어씌움
- 예를 들어 state 객체 안에 있는 값 중에 객체 형태로 되어 있을 때 그 값 중 하나만 바꾼다고 해보자.
- 위 dumbObject 중 u의 값만 0으로 바꾸고 싶다면?
```javascript
return {
  ...state,
  number : state.number +1,
  dumbObject: {...state.dumbObject, u : 0}
}
```
- 스토어는 리듀서에게 액션을 모든 리듀서에게 전파하는데
  - 이 때 counter.js와 관계 없는 setColor 액션을 받았을 때 default로 분기되어 기존 state가 그대로 반환됨
  - setColor는 counter.js에서 state 그대로 반환하니까 다른 리듀서에서 이 액션을 처리할 수 있나 알아봄

## ui.js

```javascript
import * as types from '../actions/ActionsTypes';

const initialState = {
  color: [255, 255, 255]
};

export default function ui(state = initialState, action) {
  if(action.type === types.SET_COLOR) {
    return {
      // color 값 외에 신경 쓸거 없으니까 새로운 객체 만들자 걍
      // 객체의 내용은 color의 값은 action에서 가져온다
      color: action.color
    };
  }
  else {
    return state;
  }
}
```
- action 불러오기
- 초기 상태 작성
- 리듀서 함수 작성
- color 값 외에 신경 쓸 게 없으니 새로운 객체를 그냥 만들자
```javascript
return {
  // color 값 외에 신경 쓸거 없으니까 새로운 객체 만들자 걍
  // 객체의 내용은 color의 값은 action에서 가져온다
  color: action.color
};
```

## index.js
- 현재 리듀서 2개 있음
- 2개 이상 일 때 이 리듀서를 합쳐야 한다
- 직접 하기 or 리덕스 안에 있는 도구 사용하기
```javascript
import {combineReducers} from 'redux';
import counter from './Counter';
import ui from './Ui';

const reducers = combineReducers({
  counter, ui
});

export default reducers;
```

































































































































































































































































































ㅍ
