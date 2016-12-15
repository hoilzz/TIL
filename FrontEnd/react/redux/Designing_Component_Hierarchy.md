# Designing Component Hierarchy
UI hierarchy를 설계해보자. [Thinking in React](https://facebook.github.io/react/docs/thinking-in-react.html)는 좋은 튜토리얼이다.

우리의 설계는 간단하다.
- todo item 리스트 보여주기
- 클릭시, todo item은 완료 체크 표시 한다.
- 유저가 new todo를 추가할 필드 보여주기
- footer에서, show all / only completed / active todos 에 대한 토글 만들거야.

## presentational components

+ `TodoList`

...

dumb components는 *look* 을 나타내지만

- data의 출처
- data를 변경하는 방법

을 모른다.

- 그들은 오직 받은것만 렌더링 한다.
- 만약 Redux에서 어딘가로 migrate 한다면, 모든 컴포넌트를 동일하게 유지할 수 있다. 그들은 Redux에서 의존성을 가지고 있지 않다.

## Container components
presentational component와 Redux를 연결하기 위해 container component가 필요하다.

예를 들어, presentational TodoList component는 Redux store를 subscribe하고 현재 visibility filter를 적용할 방법을 알고 있는 VisibleTodoList와 같은 container가 필요하다. visibility filter를 변경하기 위해,  FilterLink container component를 제공할 것이다.


## Other components
가끔 component가 presentational 인지 container여야만 한지 말하기 어렵다. 예를 들어, form과 function은 한쌍이다.

  - **AddTodo**는 Add button을 가진 input field다.

기술적으로 우리는 이것을 2개의 컴포넌트로 쪼개야 하지만 이 시점에서 하기엔 너무 이르다. presentation과 굉장히 작은 component 내부의 로직을 mix하는 것은 괜찮다. 그것이 커졌을 때, 그것을 쪼개는 방식은 더 애매해질거다. 그래서 믹스한채로 냅둘거다.

## Implementing components

## Container Components

container를 생성하여 those presentational components를 Redux에 hook up 할 시간이다. 기술적으로 container component는 Redux state tree를 읽고 presentation component가 렌더링할 props를 공급하기 위해 `store.subscribe()`를 사용하는 react component다. container component는 직접 작성해야하지만, `connect()` function으로 container component 생성하는 것을 제안한다. (이것은 불필요한 re-render를 막기 위해 유용한 최적화를 제공한다.)

`connect()`를 사용하기 위해, 현재 redux store state를 presentational component의 props로 변형하는 방법을 말해줄 `mapStateProps`라고 불리는 특별한 함수를 정의해야 한다.

```javascript
const getVisibleTodos = (todos, filter) => {
  switch (filter) {
    case 'SHOW_ALL':
      return todos
    case 'SHOW_COMPLETED':
      return todos.filter(t => t.completed)
    case 'SHOW_ACTIVE':
      return todos.filter(t => !t.completed)
  }
}

const mapStateToProps = (state) => {
  return {
    todos: getVisibleTodos(state.todos, state.visibilityFilter)
  }
}
```

state를 읽는 것 외에, container component는 action을 dispatch할 수 있다. 비슷한 방식으로, `dispatch()`를 받고 너가 presentational component에 대입하기를 원하는 callback props를 리턴하는 `mapDispatchToProps()`를 정의할 수 있다. 
