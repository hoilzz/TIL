# 15. fetched data로 action dispatch 하기

fetchData라는 이름의 common code로 추출하기

## Updating fetchData()

fetch한 todos와 함꼐 호출하는 callback prop을 `receiveTodos`를 갖자.


## Updating VisibleTodoList component with filter

action creator를 통해 filter를 전달하여 `fetchData`함수를 업데이트 해야한다.

props로부터 receiveTodos와 filter를 가져오기 위해, ES6 destructuring syntax를 사용했다. **여기서 `filter`를 즉시 destructure한건 왕중요하다.** 왜냐하면 콜백이 호출할 당시에, `this.props.filter`는 바뀔 수도있다. 왜냐하면 유저가 마우스 클릭을 통해 필터를 변경했을 수도 있기 때문이다.

```javascript
fetchData() {
  const { filter, receiveTodos } = this.props;
  fetchTodos(filter).then(todos =>
    receiveTodos(filter, todos)
  );
}
```

## Summary

store의 filter를 connect를 통해 가져온다. 이 filter는 api 요청시에 필요하다. filter의 값은 url의 path가 달라질 때마다 값을 읽어오는데, 위 예제 코드와 같이 미리 destructure를 하여 side-effect가 없도록 값을 읽어오도록 하자.