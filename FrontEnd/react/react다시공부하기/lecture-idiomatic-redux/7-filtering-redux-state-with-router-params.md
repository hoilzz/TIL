# filtering redux state with react router params

React Router에서 제공하는 Link를 이용해서 link 클릭할 때 마다 URL은 업데이트 된다. 그러나, 컨텐츠는 업데이트 되지 못하고 있다. 왜냐하면 visible `TodoList` component는 URL에서 값을 읽어 오는게 아닌, store의 visibilityFilter에 의존하고 있기 때문이다.

여튼 필터는 redux store에서 관리 안함

**링크 누를 떄마다 url 뒤의 path가 filter 이름으로 바뀌는데 이 path를 통해 filter 값을 변경할거임.**

- store에서 값 읽어오는거 ownProps를 통해 상위 컴포넌트에서 전달한 값 읽어오기로 변경

## Updating App.js

`visibleTodoList` component는 app에서 렌더링되기 때문에, `filter` prop을 mapStateToProps 함수에서 이용하기 위해 filter prop을 추가해야 한다.

React router는 파라미터가 `match`라는 특별한 prop 내에서 route handler component에서 이용 가능하도록 만들어주고 있다. 그래서 App component에 `match`를 prop으로 추가할 것이다.

-> **router handler component에서는 match라는 얘로 route 관련 값을 받을 수 있다**

이제 visibility Filter는 React Router가 관리한다. visibility Reducer가 불필요하고 combineReducer에서도 슬라이스 리듀서로 선언된 코드를 삭제하자.