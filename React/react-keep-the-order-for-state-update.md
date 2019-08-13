# setState 호출은 언제, 그리고 왜 일괄 처리 되는가?

## setState

[setState에 대해 간단히 알아보자.](https://ko.reactjs.org/docs/react-component.html#setstate)

setState는

- 컴포넌트 state의 변경 사항을 대기열(like queue)에 추가한다.
- React에게 해당 컴포넌트와 그 자식들이 갱신된 state를 사용하여 리렌더되야한다고 알린다.

이벤트 핸들러, 서버 응답 등에 따라 UI를 갱신해야 할 때 위와 같은 동작을 이용한다.

setState가 컴포넌트 갱신하는데 있어서 _즉각적인 명령_ 이 아닌 _요청_ 이라고 생각하자.
Performance 향상을 위해 React는 이 **메서드의 실행을 지연시켜 여러 컴포넌트를 한 번에 갱신** 시킨다. React는 state 변화가 즉시 적용되는 것을 보장하지 않는다.

그래서, setState는 여러 변경사항을 일괄 갱신 or 나중으로 미룰 수 있다.
이와 같은 특성으로, setState 호출 후에 `this.state` 접근하는 것은 잠재적인 문제를 일으킨다.

대신, `componentDidUpdate`, `setState(updater, callback)` 을 사용하자. 이것은 갱신이 적용된 뒤에 실행되는 것이 보장된다. 이전 state 값을 기준으로 state를 설정해야 한다면 updater((state, props) => stateChange) 인자를 사용하자.

```js
// setState의 updater 함수
(state, props) => stateChange;
```

`state`는 변경 사항이 적용되는 시점에 컴포넌트가 가지는 state에 대한 참조다.
updater의 결과는 state에 shallow merge 된다. setState의 첫번째 인자는 객체도 가능하다.

```js
setState({ quantity: 2 });
```

위와 같은 경우에도 비동기 수행되고, **같은 주기 동안 여러번 호출되면 일괄 처리된다.** 예컨대 같은 주기동안 상품 수량을 한 번이상 증가시킨 다면 아래 결과와 같다.

```js
Object.assign(
  prviousState,
  { quantity: state.quantity + 1 },
  { quantity: state.quantity + 1 }
);
```

바로 직전 호출 결과를 계속 덮어쓰기 때문에, 수량값은 단 한 번 증가하게 된다. 그래서 state 변경시 이전 state의 값에 기반한다면, `updater` 함수를 이용하자.

```js
this.setState(state => {
  quantity: state.quantity + 1;
});
```

---

setState는

- React에게 해당 컴포넌트와 그 자식들이 갱신된 state를 사용하여 리렌더 되야한다고 알린다.

- 컴포넌트 갱신하는데 있어서 즉각 명령이 아닌 요청

  - 컴포넌트의 state 변경 사항을 대기열(like queue)에 추가
  - performance 향상을 위해 React는 해당 메서드 실행을 지연시켜 여러 컴포넌트를 한번에 갱신 시킨다.

- tip
  - 이전 값을 이용하여 여러번 state를 업데이트 하는 경우, updater 함수를 이용하자.
  - 비동기로 일괄 처리하기 때문에 한 번 실행한 것과 동일한 결과를 보여준다.

---

그럼 다시 돌아와서, 언제 호출되고 왜 일괄 처리 되는지 알아보자.

리액트 공홈 문서에서는 퍼포먼스를 이유로, 메서드의 실행을 지연시켜 여러 컴포넌트를 한 번에 갱신시킨다고 했다. 만약 지연시키지 않고 일괄처리 하지 않는다면, 불필요하게 리렌더가 많이 일어나서 그렇지 않을까라고 생각했다.

다음 댄이 남긴 stackoverflow 답변에서 자세히 알아보자.

---

## does react keep the order for state update?

[does-react-keep-the-order-for-state-update?](https://stackoverflow.com/questions/48563650/does-react-keep-the-order-for-state-updates/48610973#48610973)

질문 내용은.. 여러 컴포넌트에서 setState 호출시 순서 보장 여부다.

1. 동일 컴포넌트 내에서
2. 다른 컴포넌트 간

다음은 답변 내용이다.

둘다

**업데이트 순서** 는 항상 보장되어있다. Whether you see an intermediate state "between" them or not depends on whether you're inside in a batch or not. (대충 배치 내부에 있는지에 따라 보장 여부가 달라진다는 말인거 같다)

React 16 초기 버전에서, **React event handles 내부의 벙데이트만 기본적으로 배치로 돌아간다.** event handle 밖에서는 강제로 배치 돌게하는 unstable API를 사용해야한다.(rare case)

미래에 React 17에서, 이러한 조건을 생각하지 않도록 모든 곳에서 배치 업데이트 할 수 있도록 할 거다.

---

이것을 이해하기 위한 핵심은 몇개의 컴포넌트 간에, 리액트 이벤트 핸들러 내부에서 `setState()` 호출이 몇 번 일어나는 것과 상관없이, 이벤트가 끝날 때 단 한 번 리렌더링이 된다.

이것은 큰 어플리케이션에서 퍼포먼스를 내기 위해 중요하다. 만약 click event 핸들러로 Child 와 Parent가 각각 setState()를 호출하면, Child가 2번 리렌더 되는 것을 누구도 원치 않을 것이다.

이벤트 핸들러 내부에서 setState가 일어난다면, 이벤트 끝에 setState가 전부 flush된다. (그래서 중간 state를 볼 수 없다.)

업데이트는 일어난 순서에 따라 **shallow merge** 된다.
{a: 10} -> {b: 20} -> {a:30}은 {a: 30, b: 20}.

배치의 끝에 UI를 리렌더 할 때 this.state object는 업데이트 된다.

---

위 질문 예제에서 "intermediate state"를 볼 수 없다. 왜냐하면 리액트 이벤트 핸들러 내부에 있어서 배치를 돌기 때문이다. (왜냐하면 리액트는 그 이벤트가 존재하는 것을 안다.)

리액트 16에서는, **React event handle 외부에서는 기본적으로 배치를 돌지 않는다.**
AJAX response handler에서는 setState가 일어나는대로 처리되기 때문이다.

```js
promise.then(() => {
  // We're not in an event handler, so these are flushed separately.
  this.setState({ a: true }); // Re-renders with {a: true, b: false }
  this.setState({ b: true }); // Re-renders with {a: true, b: true }
  this.props.setParentState(); // Re-renders the parent
});
```

17에서는 전부 배치 돌도록 API를 구현할 것이다.

위 글에서 나온 예제를 간단히 구현해보았다.

[research setState](https://codesandbox.io/s/research-setstate-sfnur)

- 1,2 번 컴포넌트는 순서 보장을 확인할 수 있는 방법을 못찾았고.. stackoverflow 예제에서도 단순히 예제로서의 역할..
- 3번째 컴포넌트에서, event handler 외부에서 setState가 배치로 돌지 못하는 것을 확인할 수 있다.

---

요약하자면,
리액트는 이벤트 핸들러 내부에서만 기본적으로 배치를 돌기 떄문에, 혼란스러운 토픽이다. 이것은 미래에 직관적으로 변경될 것이다. 배치를 덜 사용하는 것이 아닌 기본적으로 배치를 더 사용할 수 있도록..

setState를 비동기를 통해 일괄 처리 하는 이유는 성능 때문이다.

- 큰 어플리케이션에서 click event handler로 child와 Parent가 각각 setState를 호출하면, child가 불필요하게 2번 리렌더 되는 것은 누구도 원치 않는다.

setState는 shallow merge된다. Object.assign({}, {a: 50}, {b: 30}, {a: 80}, ...) 과 동일하다.
