# combineReducer 사용하기

슬라이스 리듀서들로 이루어진 객체를 취하는 고차 리듀서다.

`combineReducers`에서 ES6의 객체 리터럴로 상태의 형태를 정의한 예제다.

```javascript
// reducers.js
export default theDefaultReducer = (state = 0, action) => state;

export const firstNamedReducer = (state = 1, action) => state;

export const secondNamedReducer = (state = 2, action) => state;


// rootReducer.js
import {combineReducers, createStore} from "redux";

import theDefaultReducer, {firstNamedReducer, secondNamedReducer} from "./reducers";

// 객체의 형태를 정의하기 위해 ES6의 객체리터럴 단축문법을 사용
const rootReducer = combineReducers({
    theDefaultReducer,
    firstNamedReducer,
    secondNamedReducer
});

const store = createStore(rootReducer);
console.log(store.getState());
// {theDefaultReducer : 0, firstNamedReducer : 1, secondNamedReducer : 2}
```


일반적으로 이름에 "reducer"와 같은 단어 포함하는 건 좋은 습관이 아니다. **Key에는 보유한 데이터의 도메인, 유형을 단순하게 반영해야 한다.**

개선해보자.

```javascript
import {combineReducers, createStore} from "redux";

// default import의 이름을 원하는 대로 바꿀 수 있습니다. 이는 import에도 사용될 수 있습니다.
import defaultState, {firstNamedReducer, secondNamedReducer as secondState} from "./reducers";

const rootReducer = combineReducers({
    defaultState,                   // default import에서 신중하게 다시 명명된 것과 동일한 키 이름
    firstState : firstNamedReducer, // 변수이름 대신 키 지정
    secondState,                    // default import에서 신중하게 다시 명명된 것과 동일한 키 이름
});

const reducerInitializedStore = createStore(rootReducer);
console.log(reducerInitializedStore.getState());
// {defaultState : 0, firstState : 1, secondState : 2}
```