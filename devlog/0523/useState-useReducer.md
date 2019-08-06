# useState vs useReducer

useState에 primitive 값만 관리했다.

그러다가 여러개의 아코디언의 열고닫힘 상태를 관리해야했다. 그래서 부모 컴포넌트에서 다음과 같이 상태 관리하려했다.

```js
const defaultOpenState = {
  acco1: true,
  acco2: true,
  acco3: true,
  acco4: true
}; // 처음엔 다 열려 있는 상태.

function Component() {
  const [openState, setOpenState] = useState(defaultOpenState);

  const handleClickAcco = useCallback(
    name => {
      setOpenState({
        ...openState,
        [name]: !openState[name]
      });
    },
    [openState]
  ); // 나는 1개의 아코디언 상태만 바꿨는데.. 4개의 아코디언의 함수가 다시 실행되는 상황..
  // 왜냐면 openState는 새로운 상태 객체를 갖기 떄문에.. useCallback deps가 콜백함수 다시 만듬

  return (
    <>
      <Acco1 onClick={handleClickAcco} />
      <Acco2 onClick={handleClickAcco} />
      <Acco3 onClick={handleClickAcco} />
      <Acco4 onClick={handleClickAcco} />
    </>
  );
}
```

useReducer로 위문제를 해결할 수 있지 않을까? 해서 관련 포스팅을 찾았다. 거기서 글들좀 발췌해보겠다.
[should i useState or useReducer](https://kentcdodds.com/blog/should-i-usestate-or-usereducer)

`useReducer`보다 `useState`를 선호하는 1가지 상황이 있다.

**component를 프로토타이핑/빌딩 하고 구현히 확실하지 않을 때**

...

## useReducer가 항상 더 나은 상황일 때

상태의 1가지 요소가 다른 상태 값에 의존한다면 useReducer가 항상 나을 것이다.

---

[the state reducer pattern with react hooks](https://kentcdodds.com/blog/the-state-reducer-pattern-with-react-hooks)

state reducer 패턴은 제어의 역전을 허용한다. 즉, API 작성자가 API 사용자에게 내부적으로 어떻게 작동할지 권한을 주는 것이다.

> 제어의 역전
> 제어권을 다른 대상에게 위임하고
> 실행에 필요한 객체의 생성 사용 등 제어권한을 위임하는 것.
> 다른 시스템이 무엇읋 할지 추측하지 않아도 됨.
> 의존성 주입은 제어의 역전의 대표적인 방식.

## hooks로 state reducer 이용하기

컨셉은 다음과 같다.

1. End User는 action을 한다.
2. Dev는 dispatch를 호출한다.
3. hook은 필요한 변경을 결정한다.
4. hook은 추가 변경에 대해 dev 코드를 호출한다. **이것이 제어의 역전이다**
5. hook은 state 변경을 만든다.

---

Toggle component는 유저가 Switch 컴포넌트를 4번 이상 클릭하지 못하게 한다. (유저가 리셋 버튼을 누르면 초기화)

```js
function Toggle() {
  const [clicksSinceReset, setClicksSinceReset] = React.useState(0);
  const tooManyClicks = clicksSinceReset >= 4;
  const { on, toggle, setOn, setOff } = useToggle();
  function handleClick() {
    toggle();
    setClicksSinceReset(count => count + 1);
  }
  return (
    <div>
      <button onClick={setOff}>Switch Off</button>
      <button onClick={setOn}>Switch On</button>
      <Switch on={on} onClick={handleClick} />
      {tooManyClicks ? (
        <button onClick={() => setClicksSinceReset(0)}>Reset</button>
      ) : null}
    </div>
  );
}
```

이 문제에 대한 쉬운 해결책은 `handleClick` 함수에 if 문을 추가하고 `tooManyClicks`가 true면 `toggle`을 호출하지 않는다. 하지만 이 예제의 목적을 유지하자.

제어의 역전을 위해 `useToggle` hook을 변경해보는건 어떨까?

API를 먼저 생각해보자. 그리고나서 구현하자.

사용자라면 state update 될 때마다 hooks을 통해 그것이 실제로 일어나기 전에 수정해보자. like so:

```js
function Toggle() {
  const [clicksSinceReset, setClicksSinceReset] = React.useState(0);
  const tooManyClicks = clicksSinceReset >= 4;
  const { on, toggle, setOn, setOff } = useToggle({
    modifyStateChange(currentState, changes) {
      if (tooManyClicks) {
        // other changes are fine, but on needs to be unchanged
        return { ...changes, on: currentState.on };
      } else {
        // the changes are fine
        return changes;
      }
    }
  });
  function handleClick() {
    toggle();
    setClicksSinceReset(count => count + 1);
  }
  return (
    <div>
      <button onClick={setOff}>Switch Off</button>
      <button onClick={setOn}>Switch On</button>
      <Switch on={on} onClick={handleClick} />
      {tooManyClicks ? (
        <button onClick={() => setClicksSinceReset(0)}>Reset</button>
      ) : null}
    </div>
  );
}
```

좋아졌다.(사람들이 "switch off" or "Switch on" 버튼을 클릭할 때 일어나는 변화를 막는 거 빼고는..)

`<Switch/>`가 상태 토글하는 것을 막는 걸 구현해보자.

`modifyStateChange`가 `reducer`가 호출하도록 바꾸는 건 어떨까? 그리고 2번째 인자로 `action`을 받자.

action은 무슨 변경 타입이 일어나는지 결정하는 `type`을 가진다.

```js
const { on, toggle, setOn, setOff } = useToggle({
  reducer(currentState, action) {
    if (tooManyClicks && action.type === "TOGGLE") {
      // other changes are fine, but on needs to be unchanged
      return { ...action.changes, on: currentState.on };
    } else {
      // the changes are fine
      return action.changes;
    }
  }
});
```

control의 종류를 부여했다. `TOGGLE` type을 스트링으로 사용하지 말자.
대신에 참조값으로 변경하자. 이거는 typo를 피하고 editor 자동완성을 개선시켜준다.

```js
reducer(currentState, action) {
      if (tooManyClicks && action.type === useToggle.types.toggle) {
        // other changes are fine, but on needs to be unchanged
        return {...action.changes, on: currentState.on}
      } else {
        // the changes are fine
        return action.changes
      }
    },
```

## hooks 으로 state reducer 구현하기

완성된 API가 만족스럽다. `useToggle` hook으로 구현하는 방법을 보자.

```js
function useToggle() {
  const [on, setOnState] = React.useState(false);
  const toggle = () => setOnState(o => !o);
  const setOn = () => setOnState(true);
  const setOff = () => setOnState(false);
  return { on, toggle, setOn, setOff };
}
```

이 helper function 에 로직을 추가할 수 있다. 하지만 로직 추가하게 되면 단순한 훅일지라도 조금 성가신다.

대신에, `useState`에서 `useReducer`로 재작성할 것이다. 그리고 많이 쉬워진 구현체로 만들 것이다.

```js
function toggleReducer(state, action) {
  switch (action.type) {
    case "TOGGLE": {
      return { on: !state.on };
    }
    case "ON": {
      return { on: true };
    }
    case "OFF": {
      return { on: false };
    }
    default: {
      throw new Error(`Unhandled type: ${action.type}`);
    }
  }
}
function useToggle() {
  // useState를 useReducer로 변경.
  const [{ on }, dispatch] = React.useReducer(toggleReducer, { on: false });
  const toggle = () => dispatch({ type: "TOGGLE" });
  const setOn = () => dispatch({ type: "ON" });
  const setOff = () => dispatch({ type: "OFF" });
  return { on, toggle, setOn, setOff };
}
```

이제 문자열 타입을 제거하고 `type` 프로퍼티를 추가하자.

```js
function toggleReducer(state, action) {
  switch (action.type) {
    case useToggle.types.toggle: {
      return { on: !state.on };
    }
    case useToggle.types.on: {
      return { on: true };
    }
    case useToggle.types.off: {
      return { on: false };
    }
    default: {
      throw new Error(`Unhandled type: ${action.type}`);
    }
  }
}

function useToggle() {
  const [{ on }, dispatch] = React.useReducer(toggleReducer, { on: false });
  const toggle = () => dispatch({ type: useToggle.types.toggle });
  const setOn = () => dispatch({ type: useToggle.types.on });
  const setOff = () => dispatch({ type: useToggle.types.off });
  return { on, toggle, setOn, setOff };
}
useToggle.types = {
  toggle: "TOGGLE",
  on: "ON",
  off: "OFF"
};
```

이제 유저는 `useToggle` 함수에 환경설정 객체로 `reducer`를 전달할 수 있다.

```js
function useToggle({ reducer }) {
  const [{ on }, dispatch] = React.useReducer(toggleReducer, { on: false });
  const toggle = () => dispatch({ type: useToggle.types.toggle });
  const setOn = () => dispatch({ type: useToggle.types.on });
  const setOff = () => dispatch({ type: useToggle.types.off });
  return { on, toggle, setOn, setOff };
}
```

자 이제 개발자가 정의한 `reducer`를 가진다. 우리 리듀서와 어떻게 합칠 수 있을까?

Well remember that the developer needs to know what our changes will be, so we'll definitely need to determine those changes first. Let's make an inline reducer:

개발자는 무엇이 변경되는지 알아야 하기 떄문에, 우리가 먼저 그 변경들을 결정할 필요가 있다는 것을 기억하자.

일단 인라인 리듀서를 만들자.

```js
function useToggle({ reducer }) {
  const [{ on }, dispatch] = React.useReducer(
    (state, action) => {
      const changes = toggleReducer(state, action);
      return changes;
    },
    { on: false }
  );
  const toggle = () => dispatch({ type: useToggle.types.toggle });
  const setOn = () => dispatch({ type: useToggle.types.on });
  const setOff = () => dispatch({ type: useToggle.types.off });
  return { on, toggle, setOn, setOff };
}
```

직관적인 리팩토링이다. toggle hook의 기능은 변경되지 않았다.
(실제로 블랙박스와 세부 구현체의 매직..)

```js
function useToggle({reducer}) {
  const [{on}, dispatch] = React.useReducer(
    (state, action) => {
      const changes = toggleReducer(state, action)
      return reducer(state, {...action, changes})
    },
    {on: false},
  )
  ...
}
```
