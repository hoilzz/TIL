# setState()

> setState(nextState, callback)

current state를 nextState로 머지하는 것을 수행. `event handler`와 `server 요청 callback`으로부터 UI update trigger를 위한 주요 메서드다.

첫번째 인자는
1. `object`가 될 수 있다. (containing zero or more keys to update)
2. update할 key가 포함된 오브젝트를 리턴하는 `function` (of state and props)

Here is the simple object usage.
> this.setState({mykey: 'my new value'});
시그니처를 가진 함수를 인자로 보내는 것도 가능하다 `function(state, props) => newState`. 이것은 any value를 세팅하기 전에 state와 props의 이전 값을 참고하는 atomic update를 큐잉한다. 예를 들어, `props.step`에 의한 state의 값을 증가시킨다고 가정해보자.

```javascript
this.setState((prevState, props)=>{
  return {myInteger: prevState.myInteger + props.step}
})
```

second parameter는 실행될 예정인 optional callback function이다. 한 번 `setState`가 완료되고 component가 re-rendered된다.

`setState()`는 즉시 `this.state`를 변화시키지 못하지만 pending state transition을 생성한다.

## State Updates are Merged
`setState()`호출 했을 때, React는 current state로 제공한 object를 머지한다. 예를 들어 state가 몇몇 독립적인 변수를 포함한다고 해보자.

```javascript
constructor(props) {
  super(props);
  this.state = {
    posts: [],
    comments: []
  };
}
```
독립적인 각각의 `setState()`호출로 state를 업데이트할 수 있다.

```javascript
componentDidMount() {
  fetchPosts().then(response => {
    this.setState({
      posts: repsonse.posts
    });
  });

  fetchComments().then(response => {
    this.setState({
      comments: response.comments
    });
  });
}
```
merging is shallow, so `this.setState({comments})`는 `this.state.posts`를 온전한 상태로 놔둔다. 하지만 완전히 `this.state.comments`를 대체한다.

## summary
2. State Updates are Merged
  - 독립적인 각각의 `setState()`호출로 독립적인 변수들을 업데이트할 수 있음
  - merging is shallow, so `this.setState({comments})`는 `this.state.posts`를 온전한 상태로 놔두고
  - `this.state.comments`를 대체한다.
