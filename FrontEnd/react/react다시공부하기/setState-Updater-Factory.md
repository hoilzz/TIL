# setState-Updater-Factory

`setState()`는 컴포넌트 state 변경을 큐에 쌓는다. 그리고 이 컴포넌트와 컴포넌트 자식이 update된 state로 re-render 되야하는 것을 react에게 말한다. 이것은 event handler나 server response를 받아서 UI를 업데이트 해야 하는 primary method다.

`setState()`를 컴포넌트를 업데이트 해야하는 immediate 명령어가 아닌 *request*로 생각하자. 더 나은 퍼포먼스를 위해, React는 setState를 딜레이 하고 single pass로 몇몇 컴포넌트를 업데이트 한다. React는 state 변화가 즉시 적용된다고 보장하지 않는다.

`setState`는 컴포넌트를 항상 즉시 업데이트 하지 않는다. batch 돌리거나 update를 미룰 수도 있다. 이것은 `setState()`를 호출 한 후에 `this.state`의 값을 읽는 것을 잠재적으로 업데이트 전 값을 가져올 수 있는 함정이 있다. 대신에, `componentDidmount` or `setState` **callback인 `setState(updater, callback)`을 사용하자. (업데이트가 적용된 후에 호출되도록 보장되어있다.)** 만약 이전 값 기반으로 state를 set해야 한다면, `updater` argument에 대해 읽어보자

> (prevState, props) => stateChage

`shouldComponentUpdate()`가 false를 리턴하지 않으면 `setState()`는 항상 리렌더 한다. 만약 mutable object가 사용되고 조건부 렌더링 로직이 `shouldComponentUpdate()` 내부에 구현되있지 않으면, `setState()`를 호출하는 것은 new state가 이전 state와 다를 때만 불필요한 re-render를 피할 수 있다.

## 요약

setState가 호출되면 무조건 re-render된다. (단, SCU가 false를 리턴하지 않을 경우)
setState는 컴포넌트를 즉시 업데이트 하지 않는다. batch or defer update 한다. 그래서, setState 이후 this.state를 통해 뭔가 그리거나 값을 이용한다면 함정에 당할 수 있다. 그래서

componentDidMount나 setState(update, callback)을 활용하자. (업데이트가 적용 된 후에 callback이 호출되도록 보장되어있다.)