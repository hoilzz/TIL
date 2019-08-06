# 함수형 setState

[functional-setState-is-the-future-of-react](https://www.freecodecamp.org/news/functional-setstate-is-the-future-of-react-374f30401b6b/)

setState를 깊게 이해해보자.

리액트는 JS에서 함수형 프로그래밍을 대중화했다. 이것은 리액트가 사용하는 Component 기반 UI 패턴을 적용하는 거대한 프레임워크로 이끌었다.

저자가 지은 이름인데.. Functional setState라고..

댄이 이 패턴에 대한 설명했었는데, **Functional setState** 패턴은 다음과 같다.

> state 변경을 컴포넌트 클래스와 분리하여 선언하라.

응?

## 우리가 이미 아는 거는..

컴포넌트는 프로퍼티를 받고 UI element를 리턴하는 함수다.

```js
function User(props) (
  <div>user</div>
)
```

컴포넌트는 상태를 가지고 관리한다. state는 class `constructor` 함수 안에서 선언된다.

상태를 관리하기 위해, 리액트는 `setState()`를 제공한다.

아마 다음과 같이 사용할거다

```js
class User {
  increaseScore() {
    this.setState({ score: this.state.score + 1 });
  }
}
```

`setState()`에 업데이트되야하는 상태의 부분을 포함하고 있는 **object** 를 전달한다. 다시 말하면, 객체는 컴포넌트 상태에 있는 키와 일치하는 키들을 가져야하고, setState()는 상태(state)에 오브젝트를 merge 업데이트하거나 set한다. 그래서 setState다.

## 너가 모를 수도 있는거..

setState에는 객체를 전달하는 거 대신에 **function** 을 전달할 수 있다.

그 함수는 다음 상태를 계산하고 리턴하기 위해 컴포넌트의 _이전 state_ 와 _현재 state_ 를 받는다.

```js
this.setState((prevState, prevProps) => {
  return {
    score: prevState.score - 1,
  };
});
```

## setState에 함수를 왜 전달해야 할까?

[state 업데이트는 비동기다.](https://reactjs.org/docs/state-and-lifecycle.html#state-updates-may-be-asynchronous)

[setState가 호출 될 떄 일어나는 일](https://reactjs.org/docs/reconciliation.html)을 생각해보자.
리액트는 현재 state에 전달된 객체를 **merge** 한다. 그러고 나서 **reconciliation** 이 시작된다. 이것은 새로운 React Element tree를 생성하고, setState에 전달한 객체를 기반으로 변경된 것을 이해하기 위해 기존 트리와 새 트리를 비교한다.

사실 리액트는 단순하게 set-State 하지 않는다.

setState 호출시 즉시 state를 업데이트 하지 않는다.

> 리액트는 multiple setState호출을 퍼포먼스때문에 단일 업데이트로 batch 시킨다.

이게 뭘 의미할까?

첫째로, "multiple setState() calls"는 단일 함수 내부에서 setState()를 1번 이상 호출하는 것이다.

```js
handleClick = () => {
  // setState is asyncronous, and batch update
  this.setState({ count: this.state.count + 1 });
  this.setState({ count: this.state.count + 1 });
  this.setState({ count: this.state.count + 1 });
};
```

React는 setState를 3번 하는 것 대신에, 다음과 같이 3번 호출하지 않는다.
"ㄴㄴㄴㄴ 난 산을 세번 오르지 않을거임, 매 여행에서 상태 조각을 업데이트하고 들고다니지 않을거임. 차라리 모든 조각들을 한꺼번에 들고, **딱 한번만 업데이트 할거임** "

이거슨 **batching** 이다

setState는 플레인 오브젝트를 전달하는 점을 기억해라.
리액트가 multiple setState call을 만난다면, setState call에 전달된 객체를 추출하여 배치 돌린다. 그리고 단일 객체로 merge하여, 단일 객체를 이용하여 setStae를 진행한다.

JS merge object를 살펴보자.

```js
const singleObject = Object.assign(
  {},
  objectFromSetState1,
  objectFromSetState2,
  objectFromSetState3
);
```

위 패턴은 **object composition** 이다.

merging or composing object는: 만약 3개의 객체가 동일한 key를 가진다면 Object.assign() 에 전달된 마지막 오브젝트의 키의 값이 반영된다.

여튼 리액트로 다시 돌아와서, 객체를 전달한 setState를 여러번 호출하면, 리액트는 **merge** 할거다. 또한, 동일한 키를 포함한다면 마지막 객체의 키에 대한 값이 반영된다.

여튼 setState에 객체를 전달하는 것은 문제가 발생한다. setState로 이전 state를 통해 다음 state를 계산할 때 진짜 문제가 발생한다. **왜냐하면 this.props.와 this.state는 비동기로 업데이트 되기때문에, 다음 state를 계산하기 위해 해당 값에 의존하지 않아야한다.**

## Functional setState 구조대

**functional setState** 는 문제를 해결할거다.

**Dan은 functional setState를 할 때, 업데이트는 큐에 쌓일 거고 호출된 순서대로 실행될거라고 말했다.**

그래서, 리액트는 object를 머지하는 것 대신에, 함수를 호출순으로 큐에 쌓이게 해야한다.

리액트는 이전 state를 함수에 전달하여 queue에 있는 각 함수를 호출하여 업데이트한다. 이 state는 첫번째 functional setState call 이전의 state 거나 큐에 있는 이전 functional setState의 최신 업데이트된 state일 수 있다.

```js
class User {
  state = { score: 0 };
  //fake setState
  setState(state, callback) {
    console.log('state', state);
    this.state = Object.assign({}, this.state, state);
    if (callback) callback();
  }
}

const Justice = new User();

const updateQueue = [
  state => ({ score: state.score + 1 }),
  state => ({ score: state.score + 1 }),
  state => ({ score: state.score + 1 }),
];

// recursively update the state in the order
function updateState(component, updateQueue) {
  if (updateQueue.length === 1) {
    return component.setState(updateQueue[0](component.state));
  }

  return component.setState(updateQueue[0](component.state), () =>
    updateState(component, updateQueue.slice(1))
  );
}
updateState(Justice, updateQueue);
```

핵심은 리액트가 functional setState에서 함수를 실행한다는 점이다. 리액트는 업데이트된 state의 새로운 카피본을 전달하여 상태를 업데이트 한다. functional state가 이전 state 기반 state를 set하는 것을 가능하게 한다.

[setState test](https://codesandbox.io/s/setstate-vs-usestate-cc1yb)
