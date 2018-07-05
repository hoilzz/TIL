# UNSAFE_componentWillReceiveProps

> NOTE:
이 라이프사이클 메서드는 버그와 비일관성이 생긴다. 그리고 그것은 deprecated될 이유다.

만약 **prop이 변경될 때 몇몇 데이터를 재계산하기위해** `componentWillReceiveProps`를 사용한다면, memoization helper를 대신 사용해라.

만약 **prop이 변경될 때 state를 reset**하기 위해 `componentWillReceiveProps`를 사용한다면, component를 [fully controlled](https://reactjs.org/blog/2018/06/07/you-probably-dont-need-derived-state.html#recommendation-fully-uncontrolled-component-with-a-key) or [fully uncontrolled with a key](https://reactjs.org/blog/2018/06/07/you-probably-dont-need-derived-state.html#recommendation-fully-uncontrolled-component-with-a-key)로 만들어라.

---

마운팅되는 동안 React는 `componentWillReceiveProps()`를 초기 prop으로 호출하지 않는다. 만약 컴포넌트의 prop이 업데이트될 때만 호출한다. `this.setState()`를 호출하는 것은 componentWillReceiveProps()를 트리거하지 않는다. 

---


`componentWillReceiveProps()`는 마운트된 컴포넌트가 새로운 props를 받기 전에 호출된다. 만약 변경된 prop으로 state를 업데이트 해야한다면(예를 들어 state를 props로 리셋하기)
