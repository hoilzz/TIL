```js
function useToggle({ reducer }) {
  const [{ on }, dispatch] = React.useReducer(
    (state, action) => {
      const changes = toggleReducer(state, action);
      return reducer(state, { ...action, changes });
    },
    { on: false }
  );
  const toggle = () => dispatch({ type: useToggle.types.toggle });
  const setOn = () => dispatch({ type: useToggle.types.on });
  const setOff = () => dispatch({ type: useToggle.types.off });
  return { on, toggle, setOn, setOff };
}
```

개발자용 `reducer`를 호출하고

original `action`과 `changes` 프로퍼티를 가진 새로운 `action` 객체를 만들 수 있다.

original reducer가 리턴한 것을 개발자 리듀서로 보내서 원하는 상태를 반환받을 수 있다.

state updates를 완벽하게 제어할 수 있따. (thanks to `useReducer`)

모든 사람이 `reducer` feature를 원하지않을 수 있다.

그래서 default 설정인 `{}`를 할당하자.

```js
function useToggle({ reducer = (s, a) => a.changes } = {}) {
  const [{ on }, dispatch] = React.useReducer(
    (state, action) => {
      const changes = toggleReducer(state, action);
      return reducer(state, { ...action, changes });
    },
    { on: false }
  );
  const toggle = () => dispatch({ type: useToggle.types.toggle });
  const setOn = () => dispatch({ type: useToggle.types.on });
  const setOff = () => dispatch({ type: useToggle.types.off });
  return { on, toggle, setOn, setOff };
}
```

## conclusion

final version

```js
mport React from 'react'
import ReactDOM from 'react-dom'
import Switch from './switch'
function toggleReducer(state, action) {
  switch (action.type) {
    case useToggle.types.toggle: {
      return {on: !state.on}
    }
    case useToggle.types.on: {
      return {on: true}
    }
    case useToggle.types.off: {
      return {on: false}
    }
    default: {
      throw new Error(`Unhandled type: ${action.type}`)
    }
  }
}
function useToggle({reducer = (s, a) => a.changes} = {}) {
  const [{on}, dispatch] = React.useReducer(
    (state, action) => {
      const changes = toggleReducer(state, action)
      return reducer(state, {...action, changes})
    },
    {on: false},
  )
  const toggle = () => dispatch({type: useToggle.types.toggle})
  const setOn = () => dispatch({type: useToggle.types.on})
  const setOff = () => dispatch({type: useToggle.types.off})
  return {on, toggle, setOn, setOff}
}
useToggle.types = {
  toggle: 'TOGGLE',
  on: 'ON',
  off: 'OFF',
}
function Toggle() {
  const [clicksSinceReset, setClicksSinceReset] = React.useState(0)
  const tooManyClicks = clicksSinceReset >= 4
  const {on, toggle, setOn, setOff} = useToggle({
    reducer(currentState, action) {
      if (tooManyClicks && action.type === useToggle.types.toggle) {
        // other changes are fine, but on needs to be unchanged
        return {...action.changes, on: currentState.on}
      } else {
        // the changes are fine
        return action.changes
      }
    },
  })
  return (
    <div>
      <button onClick={setOff}>Switch Off</button>
      <button onClick={setOn}>Switch On</button>
      <Switch
        onClick={() => {
          toggle()
          setClicksSinceReset(count => count + 1)
        }}
        on={on}
      />
      {tooManyClicks ? (
        <button onClick={() => setClicksSinceReset(0)}>Reset</button>
      ) : null}
    </div>
  )
}
function App() {
  return <Toggle />
}
ReactDOM.render(<App />, document.getElementById('root'))
```

우리가 이 포스팅에서 한 것은 유저가 리듀서의 모든 상태 업데이트를 hook으로 가능하게 했다.
hook의 방식을 유연하게 만들지만, 상태를 업데이트 하는 방법이 이제 API의 일부임을 의미하며,

만약 우리가 어떻게 그런 일이 일어나는지 변경한다면, 사용자들에게 엄청난 변화가 될 수 있다.

복잡한 hook과 component를 trade-off 하는 것은 가치있는 일이다.
