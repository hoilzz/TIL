# Colocating Selectors with reducers

VisibleTodoList 내부에서, mapStateToPros 함수는 getVisibleTodos 함수를 사용한다. todos 와 일치하는 state 의 조각을 전달한다. **만약 state 구조 바꾸면, getVisibleTodos 함수를 사용하는 곳의 코드를 다 변경해줘야한다.**

이 문제를 없애기 위해, `getVisibleTodos`를 view layer 밖으로 옮긴다. 그리고 `todos` reducer 를 포함하는 파일 내부로 옮긴다. 이렇게 하는 이유는 reducer 는 state 의 `todos` 내부 구조를 모두알고있기 떄문이다.

## Updating our reducer

getVisibleTodos 는 reducer 로 옮기고 named export 하게 만든다.

**컨벤션은 간단하다. default export 는 항상 reducer 함수다. 하지만 `get`으로 시작하는 named export 는 UI 가 display 할 수있도록 데이터를 준비해놓는 함수다.**
이것을 _selector_ 라고 부를꺼다. 왜냐하면 현재 상태에서 무언가를 select 하기 때문이다.

`state` 인자는 특정 리듀서의 상태와 상응한다. 그래서 셀렉터에서는 동일한 컨벤션을 따를거다.

## Updating the root reducer

visibleTodoList 내부에서, `todos` 값을 state 에서 읽을 수 있기때문에 **state 구조에 의존적**이다.

_rootReducer.js_
```javascript

// todos를 인자로 받기 때문에, state.todos로 호출한다. 그래서 state 구조에 의존적
// const getvisibleTodos(todos, filter) => ...

// 애초에 state를 인자로 받아 state구조에 의존하지 않도록 변경
export const getVisibleTodos = (state, filter) =>
  fromTodos.getVisibleTodos(state.todos, filter);
```

named selector export 와 함께 root reducer 를 업데이트해보자. `getVisibleTodos` 또한 호출될 것이고 이전처럼 state 와 filter 도 허용한다. 그러나, 이번에는 `state`는 combined reducer 의 state 와 일치한다.

이제 `todos` file 에 정의된 `getVisibleTodos` 함수를 호출할 수 있다. 하지만 named import 로 사용할 수 없다. 왜냐하면 스코프 내에 동일한 이름을 사용하는 함수가 있기 떄문이다.

이것을 가능하게 하기 위해, 모든 exports 들을 객체로 가져오는 name space import syntax 를 사용하자. (`fromTodos`라고 부를거다)

다른 파일에서 우리가 정의한 함수를 호출하기 위해, `fromTodos.getVisibleTodos()`를 사용하자.

## VisibleTodoList 업데이트

`VisibleTodoList` component 로 돌아가서 루트 리듀서 파일에서 `getVisibleTodos`를 임포트하자.

mapStateToProps 에 getVisibleTodos 함수를 매핑하자.

이케하면 좋은게
`getVisibleTodos`는 application state shape 에 대한 정보를 캡슐화했다. 그래서 전체 어플리케이션 상태를 전달할 수 있고 , selector 를 통해 로직에 따라 visible todos 를 셀렉트 하는 방법을 이해할 것이다.

## summary

여튼 최종적으로

`todos: getVisibleTodos(todos, filter)`에서 `todos: getVisibleTodos(state, params.filter || 'all')` 이 구조를 만들어서 얻는 이득
- state 구조가 변경되더라도 UI 를 사용하는 곳은 state 만 넣어주면 된다.
  - 왜냐하면 해당함수는 셀렉터 함수이기 때문이다.
  - 셀렉터 함수는 전체 어플리케이션 상태에 대한 정보를 알고 있고 해당 로직에 따라 state 만 넣어주면 select 해주기 때문이다.

- selector을 root reducer로 옮겼다.
  - 컴포넌트가 들고 있지 않고 리듀서에 둠으로써 재사용성을 높이기 위해서

- root reducer는 프록시 역할만 하고, 실제 셀렉터하는 곳은 관련 서브 리듀서로
  - 

