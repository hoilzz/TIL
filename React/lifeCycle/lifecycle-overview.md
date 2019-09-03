# LifeCycle Overview

[lifecycle overview](http://projects.wojtekmaj.pl/react-lifecycle-methods-diagram/)

[react profiler](https://ko.reactjs.org/blog/2018/09/10/introducing-the-react-profiler.html)

## render phase

- Pure
- no sideEffect
- React가 pause, abort, restart 할 수 있다.
- DOM에 어떤 변경을 해야하는지 결정(계산)한다.
  - react는 `render`를 호출하고 이전 render와 결과를 비교한다.(DOM diffing)
- User가 원한다면 abort 될 수 있다.(SCU)
  - 만약 abort되면 DOM은 업데이트 되지 않는다.

```
constructor
componentWillMount
componentWillReceiveProps
componentWillUpdate
getDerivedStateFromProps
shouldComponentUpdate
render
setState
```

## pre-commit phase

- 실제 DOM에 반영되기 전에 VDOM에 어떤 변화가 일어나는지 알 수 있다.

```
getSnapshotBeforeUpdate
```

## commit phase

- react가 변경을 적용할 시기다. (React DOM의 경우에, 이것은 React가 DOM을 삽입/업데이트/제거 하는 시기다.)
- DOM을 동작시킨다
- run side Effect
- update 스케줄링

```
// React updates DOM andd refs
componentDidMount
componentDidUpdate
componentWillUnmount
```

## render vs commit phase

render phase는 변경될 때마다 호출된다.
commit phase는 production mode에서 단 한번 호출된다.

이것은 side-effects 함수를 render phase에서 호출하면 안된다는 말이다.

즉, getDerivedStateFromError에서 log 요청을 하면 동일 에러를 여러번 전송하기 떄문에 componentDidCatch를 사용해야 한다.
