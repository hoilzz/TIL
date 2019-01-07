# 8. params를 connected component에 주입하기 위해 withRouter를 이용하기

App Component 내부의 Router에서 params.filter를 읽어서 전달해주고 있다. 왜냐하면 Route handle component에 `params` prop을 주입해주고 있기 때문이다.

route handler의 상위 레벨에서 `params`를 전달하는 것은 별로 좋지 않다. 대신에 `VisibleTodoList` 자체 컴포넌트 내부에서 current Router `params`를 읽기 위한 방법을 찾아보자.

## VisibleTodoList 업데이트

`react-rouiter`의 `withRouter`를 사용하자. **withRouter는 리액트 컴포넌트를 가지고 params와 같은 router-related props을 주입시킨 component를 리턴해준다.**

`mapStateToProps` 내부에서 `params`를 이용하기를 원한다. 그래서 `connect()` 결과를 wrapping 할것이다. 그래서 연결된 component는 `params`를 prop으로 받을 것이다.

## Summary

기존에 App Component에서 Router의 params.filter를 자식-자식-자식.. 에게 전달하는 것보다
필요한 컴포넌트에서 params를 읽을 수 있도록 해보자. (context API라고 생각해보자)

react-router의 withRouter를 통해 router-related props를 주입시킨 component를 리턴받자.

