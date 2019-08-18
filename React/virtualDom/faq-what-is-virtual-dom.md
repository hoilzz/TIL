# What is Virtual DOM?

ReactDOM과 같은 라이브러리로 "real" DOM과 동기화되어있고 메모리상에서 ideal or virtual UI Description이 유지되는 프로그래밍 개념이다. 이러한 과정은 [reconciliation](https://reactjs.org/docs/reconciliation.html) 이다.

> Reconciliation
> 매번 업데이트 될 때마다(setState or props 변화) 뭐가 변경됐는지 신경쓸 필요가 없다.
> 뭐가 변경되었는지 "diffing" 알고리즘 사용한다. 이것을 통해 좋은 성능을 내는 앱을 위해 충분히 빠르게 구동되면서 예측가능한 컴포넌트 업데이트를 가능하게 한다.

이러한 접근은 React의 선언적(declarative) API를 가능하게 한다: UI에 원하는 state를 리액트에게 말하고, DOM이 해당 상태와 일치하는지 확인한다. 이것은 앱을 빌드하는 데 사용해야하는 attribute 조작, 이벤트 핸들링, 수동 DOM update를 추상화시킨다.

Virtual DOM은 특정 기술이라기 보다는 패턴에 가깝기 때문에, 사람들은 가끔 다양한 의미로 말한다. 리액트 세계에서 virtual DOM은 보통 [React elements](https://reactjs.org/docs/rendering-elements.html)와 연관이 있다. 리액트 엘리먼트는 UI를 나타내는 객체이기 때문이다. 그러나 리액트는 컴포넌트 트리에 대해 추가 정보를 가지고 있기 위해 "fibers"라는 내부 객체를 사용한다. 그것들은 virtual DOM 구현체의 일부다.

## React Fiber란?

Fiber는 React 16의 new reconciliation engine이다. 주요 목표는 incremental(?)virtual DOM 렌더링을 가능하게 한다.
[Read More](https://github.com/acdlite/react-fiber-architecture)
