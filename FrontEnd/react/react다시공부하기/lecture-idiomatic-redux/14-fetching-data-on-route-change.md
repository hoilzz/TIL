# 14. fetching data on route change

`VisibleTodoList` 컴포넌트는 `connect`와 `withRouter`로 인해 생성된다.

`fetchTodos` API 쓰기 적절한 곳은 `componentDidMount()`다. 이 함수를 사용하기 위해 class 컴포넌트를 만들자.

## Creating new react component

## adding lifecycle hooks

컴포넌트가 마운트 될 때, 현재 필터에서 todos를 가져온다. 필터를 prop으로 직접 이용 가능한 점은 편리하다. params에서 filter를 계산하여 `mapStateToProps`를 변경한다. 하지만 return 객체의 하나로 전달할 것이다. 그래서 이제는 filter와 todos를 visibleTodoList에서 얻을 수 있다.

mapStateToProps.js

```javascript
const mapStateToProps = (state, { params }) => {
  const filter = params.filter || 'all';
  return {
    todos: getVisibleTodos(state, filter),
    filter,
  };
};
```

```javascript
class VisibleTodoList extends Component {
  componentDidMount() {
    fetchTodos(this.props.filter).then(todos =>
      console.log(this.props.filter, todos)
    );
  }
  componentDidUpdate(prevProps) {
   if (this.props.filter !== prevProps.filter) {
     fetchTodos(this.props.filter).then(todos =>
       console.log(this.props.filter, todos)
     );
   }
 }
}
```



## summary

- filter를 props로 받아서 처리하기 위해 mapStateToProps의 ownProps 매개변수를 이용
  - props로 받아야 하는 이유는 visibleTodoList 컨테이너 컴포넌트에서 filter 가 바뀔 떄마다 해당 filter를 가지고 fetch 하기 위해서

- 첫 렌더링 떄 fetchTodos하고, prevProps와 비교하여 filter가 변경될 때마다 fetch 하기위해 class component로 변경