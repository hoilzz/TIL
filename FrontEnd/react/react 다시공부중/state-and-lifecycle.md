# State and Lifecycle

```javascript
function tick() {
  const element = (
    <div>
      <h1>Hello, world!</h1>
      <h2>It is {new Date().toLocaleTimeString()}.</h2>
    </div>
  );
  ReactDOM.render(
    element,
    document.getElementById('root')
  );
}

setInterval(tick, 1000);
```

Clock component의 재사용성 을 높이고 캡슐화 해보자. 자신의 타이머를 세팅하고 매 초마다 업데이트할 것이다.

시계가 보이는 방식을 `캡슐화` 해보자.

```javascript
function clock(props){
    return(
        <div>
        <h1>Hello, world!</h1>
        <h2>It is {props.date.toLocaleTimeString()}.</h2>
        </div>
    )
}

function tick(){
    ReactDOM.render(
        <Clock date={new Date()} />,
        document.getElementById('root')
    );
}

setInterval(tick, 1000);
```

...

**State는 props와 비슷하지만, private 하고 완전히 컴포넌트에 의해 컨트롤된다.** class로 정의된 컴포넌트는 추가 피처를 가진다. Local state가 대표적인 추가 피처다. 

## Converting a Functino to a Class

```javascript
class Clock extends React.Component {
  constructor(props) {
    super(props);
    this.state = {date: new Date()};
  }

  render() {
    return (
      <div>
        <h1>Hello, world!</h1>
        <h2>It is {this.state.date.toLocaleTimeString()}.</h2>
      </div>
    );
  }
}
```

initial `this.state`를 할당하는 `class constructor`를 추가하자. class **Component는 항상 `props`와 함께 base constructor를 호출해야한다.**


## Adding Lifecycle Methods to a Class

리소스가 제거 될 때 컴포넌트가 사용하는 리소스를 확보하는 것은 중요하다. `Clock`이 DOM에 처음으로 렌더링 될 때 마다 timer를 설정할 것이다. 이것은 `mounting`이라고 부른다. `Clock`이 만든 DOM이 제거될 때마다 timer를 클리어할거다. 이것을 `unmounting`이라고 부른다.

```javascript
componentDidMount() {
    this.timerID = setInterval(
      () => this.tick(),
      1000
    );
  }
```

`this.props`는 React 자체에 의해 설정되고 `this.state`는 특별한 의미가 있지만, visual output에 사용되지 않는 것을 저장하는 경우 클래스에 수동으로 필드를 추가할 수 있다.

`render()`에서 사용하지 않는다면, 그것은 state 내부에 있지 않아야 한다.

```javascript
componentWillUnmount() {
    clearInterval(this.timerID);
}
```

`clock` component를 매 초마다 실행 하는 `tick()`을 호출하는 메서드를 구현할 거다. 

```javascript
class Clock extends React.Component {
  constructor(props) {
    super(props);
    this.state = {date: new Date()};
  }

  componentDidMount() {
    this.timerID = setInterval(
      () => this.tick(),
      1000
    );
  }

  componentWillUnmount() {
    clearInterval(this.timerID);
  }

  tick() {
    this.setState({
      date: new Date()
    });
  }

  render() {
    return (
      <div>
        <h1>Hello, world!</h1>
        <h2>It is {this.state.date.toLocaleTimeString()}.</h2>
      </div>
    );
  }
}

ReactDOM.render(
  <Clock />,
  document.getElementById('root')
);
```

1. `<Clock />`이 `ReactDOM.render()`를 통과할 때, React는 `Clock` Component의 constructor를 호출할 것이다. `Clock`은 현재 시간을 DP할 필요가 있기 때문에, `this.state`로 이니셜라이징한다. 우리는 state를 나중에 업데이트할 것이다.

2. React는 `Clock` component의 `render()` 메서드를 호출할 것이다. React는 `Clock`의 render output과 일치시키기 위해 DOM을 업데이트 할 것이다.

3. `Clock` output이 DOM 내부에 삽입될 때, React는 `...

4. `Clock` component는 `setState()`를 호출하여 UI update를 예약한다. `setState()` 호출 덕분에, React는 state가 변경된 것을 알고 `render()`를 다시 호출한다. 

## State 올바르게 사용하기

1. Do Not Modify State Directly
2. State updates는 비동기로 이뤄진다. 
    - React는 퍼포먼스 때문에 여러개의 `setState()`를 1개의 업데이트로 간주한다.
    -  `this.props`와 `this.state`가 비동기로 업데이트 되기 때문에, 다음 state를 계산할 때 해당 값을 신뢰하지 않아야 한다.

**다음 코드는 업데이트에 실패할 것이다.**

```javascript
// Wrong
this.setState({
  counter: this.state.counter + this.props.increment,
});
```

**이것을 고치기 위해, 객체가 아닌 함수를 사용해라. 그 함수는 이전 상태를 첫번째 인자로 받고, 두번째 인수로 업데이트가 적용될 때의 props를 받는다.** 

```javascript
// Correct
this.setState((prevState, props) => ({
  counter: prevState.counter + props.increment
}));
```

## State Update는 머지된다.

`setState()`를 호출할 때, React는 너가 제공한 객체를 현재의 state로 머지한다. 예를 들어 state가 몇몇 독립적인 변수를 포함한다고 해보자.

```javascript
constructor(props) {
    super(props);
    this.state = {
        posts: [],
        comments: []
    };
}
```

독립적으로 별개의 `setState()` 호출로 업데이트할 수 있다.

```javascript
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

merging is shallow라서 `this.setState({comments})`는 `this.state.posts`를 온전하게 냅둔다. 하지만 완전히 `this.state.comments`를 교체한다. 

## the data flows down

걍 일방향으로 흐른다를 설명하고 싶은듯.


## Summary

**State는 `private`하고 완전히 컴포넌트에 의해 컨트롤된다.** state는 class 컴포넌트만 가질 수 있다.
- 직접 수정하지 말기
- 비동기로 이뤄진다.
- 여러개의 setState()를 1개의 업데이트로 간주한다.
- this.props와 this.state는 비동기로 업데이트 된다. 그래서 다음과 같은 코드를 지양하자.

```javascript
this.setState({
  counter: this.state.counter + this.props.increment,
});

// 업데이트를 위해 객체가 아닌 함수를 사용하고, 함수의 첫번째 인자는 이전상태, 두 번째 인수로 업데이트가 적용될 때의 props를 받는다.

this.setState((prevState, props) => ({
  counter: prevState.counter + props.increment
}));
```

render()로 어떤 컴포넌트 렌더링 할 때, 해당 컴포넌트의 constructor 먼저 호출한다. `setState()` 호출시 컴포넌트의 state가 바꼈으므로 `render()`를 다시 호출한다.

