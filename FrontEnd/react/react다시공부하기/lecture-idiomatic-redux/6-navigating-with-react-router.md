# <Link>

real link 와 같이 행동하면서 visibility filter 를 제어하는 link 로 만들어보자.

- back button 동작하게 만들기
- filter 바꿀 때마다 URL 변경하기

`filter`라고 불리는 Route path 에 파라미터 추가해보자. 해당 값이 Optional 이라는 걸 React router 에게 알려주기 위해 괄호로 감싸자.

```javascript
<Route path="/(:filter)" component={App} />
```

## Update Links in Footer.js

visibility filter link 를 업데이트 해보자

이전 구현체는 `filter` prop 컨벤션을 사용했다. 하지만, 주소창에 보여줘야하는 "active"와 "completed" path 로 할당하기 위해 코드를 변경해보자.

```javascript
// <FilterLink filter="SHOW_ALL">
//   All
// </FilterLink>
// {", "}
// <FilterLink filter="SHOW_ACTIVE">
//   Active
// </FilterLink>
// {", "}
// <FilterLink filter="SHOW_COMPLETED">
//   Completed
// </FilterLink>
<FilterLink filter="all">All</FilterLink>;
{
  (', ');
}
<FilterLink filter="active">Active</FilterLink>;
{
  (', ');
}
<FilterLink filter="completed">Completed</FilterLink>;
```

## FilterLink.js 업데이트

기존에 `FilterLink`는 클릭될 때마다 action을 dispatch했다. 그리고나서 active state를 store에서 읽고 `filter`prop과 스토어의 `visibilityFilter`를 비교한다.

*FilerLink.js*
```javascript
const mapStateToProps = (state, ownProps) => ({
  active: ownProps.filter === state.visibilityFilter,
});

const mapDispatchToProps = (dispatch, ownProps) => ({
  onClick() {
    dispatch(setVisibilityFilter(ownProps.filter));
  },
});

const FilterLink = connect(
  mapStateToProps,
  mapDispatchToProps
)(Link);

export default FilterLink;
```

하지만 라우터가 URL 내부의 상태를 관리하도록 변경하기 위해 위 코드는 필요하지 않다.

FilterLink는 `filter`를 prop으로 받고, React Router Link를 통해 그것을 렌더링한다.

`to` prop은 링크가 가리키는 path와 일치한다. 그래서 만약 filter가 `all`이면, root path를 이용하고 그렇지 않으면 URL path인 `filter`를 이용할 거다.

```javascript
import { NavLink } from 'react-router-dom';

const FilterLink = ({ filter, children }) => (
    <NavLink
        exact
        to={'/' + (filter === 'all' ? '' : filter)}
        activeStyle={{
            textDecoration: 'none',
            color: 'black',
        }}
    >
        {children}
    </NavLink>
);
```