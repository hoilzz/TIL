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
ReactDOM.render(<CountDisplay />, document.getElementById('⚛️'));
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
ReactDOM.render(<App />, document.getElementById('⚛️'));
```

```js
// src/count-context.js
import React from 'react';
const CountStateContext = React.createContext();
const CountDispatchContext = React.createContext();
function countReducer(state, action) {
  switch (action.type) {
    case 'increment': {
      return { count: state.count + 1 };
    }
    case 'decrement': {
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
      <CountDispatchContext.Provider value={dispatch}>{children}</CountDispatchContext.Provider>
    </CountStateContext.Provider>
  );
}
export { CountProvider };
```

## custom consumer hook

context 사용하기 위한 API는 다음과 같다.

```js
import React from 'react';
import { SomethingContext } from 'some-context-package';

function YourComponent() {
  const something = React.useContext(SomethingContext);
}
```

더 나은 유저 경험을 제공하기 위해, 다음과 같이 customhook을 이용하자.

```js
import React from 'react';
import { useSomething } from 'some-context-package';
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
그러나 만약 값이 없다면, CountProvider 내부에서 렌더된 컴포넌트아니라고 도움이 되는 error message를 던지자.
도움이 될만한 에러 메시지를 제공하자.(_#FailFast_)

## Typescript

TS를 이용할 때 `defaultValue`를 스킵하는 이슈를 피할 수 있는 방법을 알아보자.

```js
// src/count-context.tsx
import * as React from 'react'
type Action = {type: 'increment'} | {type: 'decrement'}
type Dispatch = (action: Action) => void
type State = {count: number}
type CountProviderProps = {children: React.ReactNode}

<!-- ------------------------------ 1 ------------------------------- -->
const CountStateContext = React.createContext<State | undefined>(undefined)
const CountDispatchContext = React.createContext<Dispatch | undefined>(
  undefined,
)

function countReducer(state: State, action: Action) {
  switch (action.type) {
    case 'increment': {
      return {count: state.count + 1}
    }
    case 'decrement': {
      return {count: state.count - 1}
    }
    default: {
      throw new Error(`Unhandled action type: ${action.type}`)
    }
  }
}

function CountProvider({children}: CountProviderProps) {
  <!-- ------------------------------ 2 ------------------------------- -->
  const [state, dispatch] = React.useReducer(countReducer, {count: 0})
  return (
    <CountStateContext.Provider value={state}>
      <CountDispatchContext.Provider value={dispatch}>
        {children}
      </CountDispatchContext.Provider>
    </CountStateContext.Provider>
  )
}

function useCountState() {
  <!-- ------------------------------ 3 ------------------------------- -->
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

context는 undefined로 생성될 수 있지만(1), 초기화할 때 값을 넣어줘서(2) 문제를 해결하자.

## What about async actions?

비동기 요청을 해야하는 상황이고 해당 요청 과정에서 여러개를 dispatch해야 하는 경우 어떻게 될까?
물론 컴포넌트에서 구현할 수 있지만, 그렇게 하면 모든 컴포넌트에 수동으로 모두 작업해줘야한다.

dispatch를 받는 컨텍스트 내에서 헬퍼 함수를 만들자.

```js
// user-context.js
async function updateUser(dispatch, user, updates) {
  dispatch({ type: 'start update', updates });
  try {
    const updatedUser = await userClient.updateUser(user, updates);
    dispatch({ type: 'finish update', updatedUser });
  } catch (error) {
    dispatch({ type: 'fail update', error });
  }
}
export { UserProvider, useUserDispatch, useUserState, updateUser };
```

위 헬퍼함수를 사용하는 쪽은..

```js
// user-profile.js
import { useUserState, useUserDispatch, updateUser } from './user-context';
function UserSettings() {
  const { user, status, error } = useUserState();
  const userDispatch = useUserDispatch();
  function handleSubmit(event) {
    event.preventDefault();
    updateUser(userDispatch, user, formState);
  }
  // more code...
}
```

## state and dispatch separation is annoying

```js
const state = useCountState();
const dispatch = useCountDispatch();

// verbose하다면 아래와 같이 바꾸자.

function useCount() {
  return [useCountState(), useCountDispatch()];
}
```

## conclusion

`CountContext`를 export하지말자. 컨텍스트 값을 제공하는 것과 consume할 수 있는 것을 딱 하나씩 expose 하자.
사람들이 상황에 맞는 방식으로 컨텍스트 값을 사용하고, consumer에게 유용한 유틸리티를 제공할 수 있다.

1. 모든 상태 공유 문제를 해결하기 위해 context에 도달하지 말자.
2. 컨텍스트는 전체 앱에 글로벌이지 않아야만 한다. 특정 트리에 적용될 수 있다.
3. 논리적으로 분리된 여러개의 컨텍스트를 가질 수 있다.
