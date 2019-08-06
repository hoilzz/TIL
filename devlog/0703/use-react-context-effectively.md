# React Context 효과적으로 사용하기

local state 와 React Context는 상태 관리를 편하게 도와준다. 이 포스팅은 context를 효과적으로 사용하는 방식을 알려준다. 그래서 context objects의 유지보수와 개발자 경험을 개선시켜준다.

```js
// src/count-context.js

const CountStateContext = React.createContext();
const CountDispatchContext = React.createContext();
```

CountStateContext는 초기 값을 갖지 않는다. 만약 초기값이 필요하다면 React.createContext({ count: 0 }) 을 호출하면 된다. 하지만 초기 값은 필요 없다. 초기 값은 아래와 같은 상황에서 필요하다.

```js
function CountDisplay() {
  const { count } = React.useContext(CountStateContext);
  return <div>{count}</div>;
}
ReactDOM.render(<CountDisplay />, document.getElementById("⚛️"));
```

CountStateContext에 대한 초기값이 없기 때문이다. 물론 초기값 없기 때문에 위 코드는 error가 발생한다. (useContext의 리턴값을 디스트럭쳐링 하는 곳에서..) 왜냐하면 default value는 undefined이기 때문이다.

근데, context가 실제로 값이 없다면 무엇을 사용해야 할까? 만약 기본 값이 제공된다면 별로 도움이 되지 않는다. context를 사용하고 생성하는 곳은 useful value를 제공하는 provider 내부에서 렌더링 되는 context consumer다.

**CountDispatchContext 는 뭘까?**
context 문제를 피하는 가장 간단한 방법은, 상태를 분할하고 컨텍스트로 dispatch하는 것이다.

## custom Provider component

위 컨텍스트 모듈을 사용하기 위해, Provider를 사용하고 값을 제공하는 구성 요소가 필요하다.

우리 컴포넌트는 다음과 같이 사용된다.

```js
function App() {
  return (
    <CountProvider>
      <CountDisplay />
      <Counter />
    </CountProvider>
  );
}
ReactDOM.render(<App />, document.getElementById("⚛️"));
```

```js
// src/count-context.js
import React from "react";
const CountStateContext = React.createContext();
const CountDispatchContext = React.createContext();
function countReducer(state, action) {
  switch (action.type) {
    case "increment": {
      return { count: state.count + 1 };
    }
    case "decrement": {
      return { count: state.count - 1 };
    }
    default: {
      throw new Error(`Unhandled action type: ${action.type}`);
    }
  }
}
function CountProvider({ children }) {
  const [state, dispatch] = React.useReducer(countReducer, { count: 0 });
  return (
    <CountStateContext.Provider value={state}>
      <CountDispatchContext.Provider value={dispatch}>
        {children}
      </CountDispatchContext.Provider>
    </CountStateContext.Provider>
  );
}
export { CountProvider };
```

## custom consumer hook

context 사용하기 위한 API는 다음과 같다.

```js
import React from "react";
import { SomethingContext } from "some-context-package";

function YourComponent() {
  const something = React.useContext(SomethingContext);
}
```

더 나은 유저 경험을 제공하기 위해, 다음과 같이 customhook을 이용하자.

```js
import React from "react";
import { useSomething } from "some-context-package";
function YourComponent() {
  const something = useSomething();
}
```

```js
...
function useCountState() {
  const context = React.useContext(CountStateContext)
  if (context === undefined) {
    throw new Error('useCountState must be used within a CountProvider')
  }
  return context
}
function useCountDispatch() {
  const context = React.useContext(CountDispatchContext)
  if (context === undefined) {
    throw new Error('useCountDispatch must be used within a CountProvider')
  }
  return context
}
export {CountProvider, useCountState, useCountDispatch}
```

useCountState와 useCountDispatch 커스텀 훅은 가장 가까운 CountProvider에게서 제공된 context value를 useContext를 사용한다. 그러나, 만약 값이 없다면 error message를 던질거다.
