# Usage With React

[Usage With React](http://redux.js.org/docs/basics/UsageWithReact.html)를 발번역한 글입니다.

일단, Redux는 React와 관련이 없다는 점을 강조한다. Redux apps은 React, Angular, Ember, jQuery, or vanilla Javascript로 작성할 수 있다.

이것은 Redux는 React와 Deku와 같이 라이브러리와 함께 잘 작동하다는 뜻이다. 왜냐하면 React나 Deku 같은 얘들이 UI를 state의 function으로 표현하도록 하기 때문이다. 그리고 Redux는 action에 대한 응답으로 state update를 발생시킨다.

## Installing React Redux

Redux에서 React binding이 기본적으로 포함되어있지 않다. 그래서 너는 명시적으로 설치해줘야해.

```javascript
npm install --save react-redux
```

## Presentational and Container Components

Redux를 바인딩한 React는 **보여주는 컴포넌트와 컨테이너 컴포넌트를 구분하는(seperating presentational and container components)** 아이디어를 받아들인다. 이 용어가 안 익숙하면 [이거](https://medium.com/@dan_abramov/smart-and-dumb-components-7ca2f9a7c7d0) 먼저 읽어봐. 그리고 이거 읽어. 걔네는 굉장히 중요하니까!!(난 일단 안읽음)

걔네들 차이점에 대해 알아보자.

|  |  Presentational Components | Container Components|
|:--------:|:------------------------|:-------------------------|
|목적| 보여지는 방법(markup, styles) | 동작하는 방법(data fetching, state updates)
|Aware of Redux| No| Yes|
|데이터 읽기| props에서 데이터 읽어오기 | Redux state 구독하기(subscribe)|
|데이터 변경하기| props로부터 콜백 호출하기| Redux action을 dispatch하기|
|Are Written| By hand| 보통 React Redux에 의해 발생|

우리가 작성하는 대부분의 컴포넌트는 presentational하다. 하지만 우리는 Redux store에 그것들을 연결하기 위해 약간의 컨테이너 컴포넌트를 생성해야 한다. This and the design brief below
만약 container component가 너무 복잡하다면(i.e. 그것은 셀수 없는 콜백을 가지면서 굉장히 중첩된 presentational component를 가진다.) FAQ에서 알려준 것처럼 component tree 내에서 다른 컨테이너를 소개한다.

> Why don't I have this.props.dispatch available in my connected component? from FAQ
`connect()` 함수는 2가지 주요 인자를 가진다.(둘다 optional)
첫번째는 `mapStateToProps`다. 이것은 store가 변경될 때 데이터를 가져오기 위해 너가 제공하는 함수다. 그리고 그 값들을 props로 너의 컴포넌트에 전달한다.
둘째, `mapDispatchToProps`다. 이것은 store의 `dispatch` 함수를 이용하도록 만들기 위해 너가 제공하는 함수다. 보통 dispatch가 호출 되자 마자 action들이 자동으로 dispatch하는 action creators의 pre-bound versions 을 생성한다.

너가 직접 `mapDispatchToProps` 함수를 제공하지 않는다면 `connect()`호출할 때 react redux는 기본 버전을 제공할 것이다. 이것은 단순히 props로써 `dispatch` 함수를 리턴한다. 이 말은 즉, 너가 너가 만든 함수를 제공하지 않는다면, `dispatch`는 자동으로 제공되지 않는다. 만약 너가 여전히 prop으로써 그것을 이용하기를 원한다면, `mapDispatchToProps` 구현부에 명시적으로 그것을 너자신에게 리턴할 필요가 있다.


기술적으로, `store.subscribe()`를 이용하여 직접 container components를 작성할 수 있다. 근데 그걸 권장하지 않을거다. 왜냐하면 React Redux는 많은 성능 최적화를 만들어서 직접 하기엔 좀 힘들다. 이러한 이유로 container component를 작성하는 것보다 React Redux가 제공한 `connect()`를 이용하여 그것들을 생성해라.

## Designing Component Hierarchy

[root state object의 모양을 설계하는 방법](http://redux.js.org/docs/basics/Reducers.html)이 기억나는가?
UI 계층을 설계할 시간이다. 이건 Redux-specific task는 아니다. 이 프로세스를 설명하는 [Thinking in React](https://facebook.github.io/react/docs/thinking-in-react.html)는 좋은 튜토리얼이다.

우리가 디자인 할거는 TodoList item 프로젝트다. 투두 아이템 볼 수 있고, 클릭하면 완료된 것처럼 체크도 되고, 유저가 새로운 투두 추가도 할 수 이싿. 푸터에서는  전체보기, 완료돈 것만 보기, active todo만 보기 등에 대한 토글도 된다.

## Designing Presentational Components

다음 presentational components와 this props는 간단하게 나온다.

- `TodoList`는 visible todos를 보여주는 리스트다.
  - todos : Array
  - onTodoClick(id: number)
- Todo는 single todo item
  - text: string
  - completed: boolean
  - onClick
- Link는 callback이 있는 link
  - onClick() : link가 클릭 될 때 호출하기 위한 콜백
- Footer는 유저가 현재 visible todo를 변경할 수 있다.
- App은 root component

데이터가 어디서 오는지 어떻게 바꾸는지 모른다. 주어진 것만 렌더링한다.

## Designing Container Components

**presentational components**와 Redux를 연결하기 위해 **container components**가 필요하다.

예를 들어, presentational `TodoList` Component는 `VisibleTodoList`와 같은 컨테이너가 필요하다.

VisibleTodoList 컨테이너는

- Redux store를 subscribe
- 현재 visibility filter를 적용하는 방법을 알고 있음

visibility filter 바꾸기 위해 `Link`를 제공하는  `FilterLink` container component 제공

Link는 클릭시 적절한 action을 dispatch한다.

- VisibleTodoList : 현재 visibility filter에 따라 todo를 필터링 하고 todoList를 렌더링 한다.
- FilterLink는 현재 visibility filter를 얻어서 link를 렌더링한다.
  - filter: string

## Designing Other Components

\
