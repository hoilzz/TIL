# 리액트로 앱 상태 관리 하기

[application state management with react](https://kentcdodds.com/blog/application-state-management-with-react)를 번역한 글.

어떤 애플리케이션이든 상태관리는 힘들다. 상태 관리 라이브러리는 많다. 그리고 매일 새로운게 나온다.("easier redux" 추상화 버전이 npm에 엄청 많다.) 상태 관리가 어려운 문제인데, 그 문제를 해결하기 위해 해결책을 과도하게 설계하고 있다고 생각한다.

React hook이 릴리즈 되고 (React Context의 엄청난 개선과 함께) 상태 관리 메서드는 갱장히 간결해졌다.

우리는 앱을 만들기 위해 리액트 컴포넌트를 레고 블럭으로 생각한다. 그리고 필자는 사람들이 이 얘기를 듣고 state 측면을 배제한 채 말했다고 생각한다. **필자의 상태 관리 문제의 해결책 뒷편의 비밀은 앱 상태를 앱 트리 구조와 매핑하는 방법에 대해 생각하는 것이다.**

리덕스가 성공적인 이유 중 하나는 리액트 리덕스의 [Prop drilling](https://kentcdodds.com/blog/prop-drilling) 문제를 해결한 것이다. `connect` 함수에 컴포넌트를 전달하면 각기 다른 트리의 부분에서 데이터를 공유할 수 있다. 리듀서, 액션 생성자도 갱장히 훌륭하다. 근데 개발자의 prop drilling pain point를 해결해준게 가장 큰 이유라고 확신한다.

**불행하게도.. 개발자들이 모든 상태를 리덕스에 넣는 것을 보았다. 글로벌 앱 상태 뿐만 아니라 로컬 스테이트에도.. 많은 문제를 발생시키지만, 가장 중요한 것은 어떤 상태의 인터랙션을 유지할 떄, 그것은 궁극적으로 많은 파일을 열고, 코드를 추적하며 무엇이 일어나고 어떤 영향을 미치는지 알아내야 한다..**

**명백하게 말하면, 글로벌 상태는 괜찮지만, simple state(모달이 열리고 닫히는, form input value state와 같은) 는 큰 문제가 될 수 있다. 최악의 경우 스케일링 하기 어렵다. 앱이 커질수록 이 문제는 커진다. 애플리케이션의 다른 부분을 연결하기 위해 서로 다른 리듀서를 연결하면 되지만, 모든 액션 생성자와 리듀서를 통과하는 방향성은 최적의 방법이 아니다.**

모든 상태를 단일 객체로 갖는 것은 다른 문제를 야기한다. `<Context.Provider>`가 새로운 값을 얻었을 때, 값을 소비하는 모든 컴포넌트는 업데이트되고 렌더링 해야 한다. 이것은 잠재적인 퍼포먼스 이슈를 발생시킨다. 요점은 만약 local 상태를 분리하여 해당 상태값이 중요한 곳 가까이 있는 리액트 트리에 위치한다면 이 문제를 가질 필요가 없다는 것이다.

---

> 리액트는 상태 관리 라이브러리다.

리액트 앱 만들 때, `<App />`에서 시작하여 `<input />`이나 `<div />`로 끝나는 컴포넌트 트리를 구성할 수 있다. 앱이 1개의 중앙 컴포넌트에서 렌더링되는 모든 하위 컴포넌트를 관리하지 않는다. 대신에, 각 개별 컴포넌트가 하위 컴포넌트들을 관리하는 것이 UI 만드는 효과적인 방법이다.

```js
function Counter() {
  const [count, setCount] = React.useState(0);
  const increment = () => setCount(c => c + 1);
  return <button onClick={increment}>{count}</button>;
}
function App() {
  return <Counter />;
}
```

클래스 컴포넌트로도 작성할 수 있다. 훅은 약간 더 쉽게 만든다.(특히 context)

```js
class Counter extends React.Component {
  state = { count: 0 };
  increment = () => this.setState(({ count }) => ({ count: count + 1 }));
  render() {
    return <button onClick={this.increment}>{this.state.count}</button>;
  }
}
```

"OK, kent, 단일 컴포넌트에서 관리되는 상태는 쉬운데, 컴포넌트간에 상태 공유해야되면 어케해야되? 예를 들어 다음 코드처럼"

```js
function CountDisplay() {
  // where does `count` come from?
  return <div>The current counter count is {count}</div>;
}
function App() {
  return (
    <div>
      <CountDisplay />
      <Counter />
    </div>
  );
}
```

`count`는 `<Counter />` 내부에서 관리된다. <CountDisplay />에서 `count` 값에 접근 및 <Counter>에서 업데이트 하기 위해 이제 상태 관리 라이브러리가 필요하다.

이 문제에 대한 오래된 해결책은 [Lifting State Up](https://reactjs.org/docs/lifting-state-up.html)이다.

```js
function Counter({ count, onIncrementClick }) {
  return <button onClick={onIncrementClick}>{count}</button>;
}
function CountDisplay({ count }) {
  return <div>The current counter count is {count}</div>;
}
function App() {
  const [count, setCount] = React.useState(0);
  const increment = () => setCount(c => c + 1);
  return (
    <div>
      <CountDisplay count={count} />
      <Counter count={count} onIncrementClick={increment} />
    </div>
  );
}
```

상태를 책임지는 대상을 변경했고 갱장히 직관적이다. 우리는 상태를 앱의 최상단으로 계속 끌어 올릴 수 있다.

"Sure Kent, prop drilling 문제는 어케할꺼야?"

많은 사람들은 `react-redux`로 도달했다. 이 메커니즘을 사용하여 문제를 해결했기 때문이다. 하지만 `context`는 공식적인 React API다. 문제 없이 이것을 직접 사용할 수 있다.

```js
// src/count/count-context.js
import React from "react";

const CountContext = React.createContext();

function useCount() {
  const context = React.useContext(CountContext);
  if (!context) {
    throw new Error(`useCount must be used within a CountProvider`);
  }
  return context;
}

function CountProvider(props) {
  const [count, setCount] = React.useState(0);
  const value = React.useMemo(() => [count, setCount], [count]);
  return <CountContext.Provider value={value} {...props} />;
}

export { CountProvider, useCount };

// src/count/page.js
import React from "react";
import { CountProvider, useCount } from "./count-context";

function Counter() {
  const [count, setCount] = useCount();
  const increment = () => setCount(c => c + 1);
  return <button onClick={increment}>{count}</button>;
}

function CountDisplay() {
  const [count] = useCount();
  return <div>The current counter count is {count}</div>;
}

function CountPage() {
  return (
    <div>
      <CountProvider>
        <CountDisplay />
        <Counter />
      </CountProvider>
    </div>
  );
}
```

> NOTE: That particular code example is VERY contrived and I would NOT recommend you reach for context to solve this specific scenario. Please read Prop Drilling to get a better sense for why prop drilling isn't necessarily a problem and is often desirable. Don't reach for context too soon!

`useContext` hook에서 상태 업데이트하는 공통 방법에 대한 로직을 이용하는 것이 굉장히 cool하다.

```js
function useCount() {
  const context = React.useContext(CountContext);
  if (!context) {
    throw new Error(`useCount must be used within a CountProvider`);
  }
  const [count, setCount] = context;
  const increment = () => setCount(c => c + 1);
  return {
    count,
    setCount,
    increment
  };
}
```

`useState` 보다 `useReducer`로 쉽게 변경할 수 있다.

```js
function countReducer(state, action) {
  switch (action.type) {
    case "INCREMENT": {
      return { count: state.count + 1 };
    }
    default: {
      throw new Error(`Unsupported action type: ${action.type}`);
    }
  }
}
function CountProvider(props) {
  const [state, dispatch] = React.useReducer(countReducer, { count: 0 });
  const value = React.useMemo(() => [state, dispatch], [state]);
  return <CountContext.Provider value={value} {...props} />;
}
function useCount() {
  const context = React.useContext(CountContext);
  if (!context) {
    throw new Error(`useCount must be used within a CountProvider`);
  }
  const [state, dispatch] = context;
  const increment = () => dispatch({ type: "INCREMENT" });
  return {
    state,
    dispatch,
    increment
  };
}
```

이것은 엄청난 유연성을 제공하고 복잡성을 줄인다. 이 방식으로 할 때 기억해야할 중요한 몇가지

1. 앱의 모든 상태가 single state object 내부에 있을 필요가 없다. 논리적으로 분리된 채(유저 세팅이 반드시 노티(알림)와 동일한 컨텍스트에 있을 필요가 없다)로 유지해라. 이 방식으로 여러개 provider를 가질 수 있다.

2. 모든 컨텍스트는 global하게 접근할 필요가 없다. **가능한 필요한 곳에 가깝게 state를 유지해라**

```js
function App() {
  return (
    <ThemeProvider>
      <AuthenticationProvider>
        <Router>
          <Home path="/" />
          <About path="/about" />
          <UserPage path="/:userId" />
          <UserSettings path="/settings" />
          <Notifications path="/notifications" />
        </Router>
      </AuthenticationProvider>
    </ThemeProvider>
  );
}
function Notifications() {
  return (
    <NotificationsProvider>
      <NotificationsTab />
      <NotificationsTypeList />
      <NotificationsList />
    </NotificationsProvider>
  );
}
function UserPage({ username }) {
  return (
    <UserProvider username={username}>
      <UserInfo />
      <UserNav />
      <UserActivity />
    </UserProvider>
  );
}
function UserSettings() {
  // this would be the associated hook for the AuthenticationProvider
  const { user } = useAuthenticatedUser();
}
```

각 페이지는 컴포넌트에 필요한 데이터를 가진 자신의 provider를 가진다. 코드 스플리팅은 "just works". 각 provider에서 data를 가져오는 방법은 provider가 사용하는 hook과 앱에서 데이터를 가져오는 방법에 달려있다. 하지만 너는 어디서 어떻게 작동하는지 찾기 위해 시작할 위치를 알고 있다. (provider에서)

## Conclusion

class component로도 위 방법을 사용할 수 있다.(굳이 hook 안이용해도됨). hook은 위 방법을 쉽게 만든다. 가능한 상태를 local에서 유지하고 prop drilling이 진짜로 문제가 될 때만 context를 사용하자. 이 방법대로 하는 것은 상태 interaction을 유지보수하기 쉽게 만든다.

## 요약

prop drilling pain point를 해결해준 redux. (리덕스 성공한 이유 중 하나)

- connect 함수에 컴포넌트 전달하면 각기 다른 트리의 부분에서 데이터 공유 가능.

모든 상태를 redux를 넣는 개발자들 많음.

- 글로벌 앱 상태 뿐만 아니라 로컬 스테이트도.. redux에서 관리
- 이거는 많은 문제를 일으킴
  - 어떤 상태의 인터랙션을 유지할 때,
    - 리듀서, 액션 크리에이터, 액션 타입, dispatch 호출 같은 인터랙션을 포함하여,
    - 많은 파일을 열고
    - 그 파일의 코드를 추적하여
    - 무엇이 일어나고, 그것이 코드에 어떤 영향을 미치는지 알아내야함
  - to be clear, 글로벌 상태는 괜찮지만 simple state(모달 닫고/열기, form input value state)는 큰 문제가 될 수 있다.
    - 확장하기 어려움
    - 어플리케이션 커질수록 문제는 더욱 어려워짐
    - 여러 부분을 관리 하기 위해 여러 리듀서를 연결할 수 있지만, 모든 액션 크리에이터와 리듀서를 우회하는것은 최적이 아니다(?)
