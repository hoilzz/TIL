# State

setState()에 대해 알아야할 3가지

1. state 직접 변경하지 않기

setState()를 사용해서 변경하자.

2. state update는 비동기일 수 있다.

**React는 여러개의 `setState()` call을 성능을 위해 단일 업데이트로 배치를 돌린다.**

3. state updates는 머지된다.

`setState()`를 호출할 때, 리액트는 너가 제공한 객체를 현재 state에 머지한다.

예를 들어, state는 몇가지 독립적인 변수를 포함한다.

```js
constructor(props) {
  super(props);
  this.state = {
    posts: [],
    comments: []
  };
}
```

별개의 `setState()` 호출로 state를 독립적으로 업데이트할 수 있다.

```js
  componentDidMount() {
    fetchPosts().then(response => {
      this.setState({
        posts: response.posts
      });
    });

    fetchComments().then(response => {
      this.setState({
        comments: response.comments
      });
    });
  }
```

merging은 shallow다. 그래서 `this.setState({comments})`는 `this.state.posts`를 그대로 두지만 `this.state.comments`를 완전히 대체한다.

## 데이터는 아래로 흐른다.

부모나 자식 컴포넌트는 어떤 컴포넌트가 stateful한지 stateless한지 알지 못하고 신경쓰지 않는다. 이것이 상태를 local 상태 or 캡슐화된 상태 라고 부르는 이유다. 상태를 소유하거나 변경할 수 있는 컴포넌트 외의 컴포넌트들은 상태에 접근할 수 없다.

컴포넌트는 state를 prop처럼 전달해줄 수 있다.

```js
<FormattedDate date={this.state.date} />
```

FormattedDate 컴포넌트는 date를 prop으로 받고, 이 prop의 출처가 Clock의 state인지 Clock의 prop인지 아니면 직접 타이핑 된 값인지 알 수 없다.

이거슨 `top-down` or `unidirectional(단방향)` 데이터 플로우라고 부른다.

어떤 상태든 특정 컴포넌트가 소유할 수 있고, 해당 state에서 파생된 모든 데이터 또는 UI는 트리의 컴포넌트 **아래** 에만 영향을 미친다.

## Summary

setState는 여러개의 setState를 단일 업데이트로 배치를 돌린다.
