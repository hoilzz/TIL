# useEffect vs useLayoutEffect

[hooks-effect](https://ko.reactjs.org/docs/hooks-effect.html)
[useeffect-vs-uselayouteffect](https://kentcdodds.com/blog/useeffect-vs-uselayouteffect)

2가지를 번역 요약

## useEffect

Effect hook은 함수형 컴포넌트에서 side effect를 수행할 수 있게 한다.

Data fetching, setting up a subscription, 리액트 컴포넌트에서 manually changing the DOM 과 같은 것들이 side effect다.

크게 2가지 종류의 side effect가 있다.

- cleanup이 필요 없는 거
- cleanup이 필요한거

### Effects without cleanup

**리액트가 DOM을 업데이트한 후에 코드가 실행됐으면 하는데**
네트워크 요청, DOM 변경 등이 cleanup을 필요로 하지 않는다.

이제 class와 hook을 비교해보자.

#### Example Using classes

```js
class Example extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      count: 0,
    };
  }

  componentDidMount() {
    document.title = `You clicked ${this.state.count} times`;
  }

  componentDidUpdate() {
    document.title = `You clicked ${this.state.count} times`;
  }

  render() {
    return (
      <div>
        <p>You clicked {this.state.count} times</p>
        <button onClick={() => this.setState({ count: this.state.count + 1 })}>
          Click me
        </button>
      </div>
    );
  }
}
```

2개의 라이프사이클 메서드에 반복되는 코드가 있다.

매번 렌더될때마다 어떤 코드를 실행시키고 싶은데 class component에는 그게 없다.

#### Example Using Hooks

```js
function Example() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    document.title = `You clicked ${count} times`;
  });

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>Click me</button>
    </div>
  );
}
```

**useEffect는 뭘할까??**

- 렌더 후에 컴포넌트가 뭔가 할 필요가 있다면 훅을 이용하여 리액트에게 말한다.

**왜 컴포넌트 안에서 호출하는가?**

- count 상태 변수에 접근하도록 하기 위해 컴포넌트 내부에 위치해야한다.
- 이미 함수 스코프에 있고, 훅은 React 관련 API를 도입하지 않기 위해 JS closure를 활용했다.

**useEffect는 every render마다 호출되는가?**

- ㅇㅇ
- first render와 every update마다
- mounting, updating과 같은 용어 대신에, "after render"마다 이펙트는 실행된다고 쉽게 생각할 수 있다.
- 리액트는 effect 수행한 후에 DOM update를 보장한다.

## Detailed 설명

```js
function Example() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    document.title = `You clicked ${count} times`;
  });
}
```

useEffect는 DOM이 업데이트된 후에 실행된다. 그러므로 count는 가장 최근에 변경된 값을 가진다.

숙련된 JS 개발자는 **useEffect에 전달된 함수가 렌더링마다 다르다** 는 것을 알것이다. 이것은 의도된거다. 사실 effect 내부에서 해당 값이 업데이트 되지 않는 것에 걱정하지 않으면서 count value읽도록 한다. 리렌더 할때마다, 이전 것을 대체하면서 _different_ effect를 스케줄링한다. 이런 방식으로, 이것은 render 결과의 부분처럼 effect가 행동하도록 한다. 각 이펙트는 특정 렌더에 _종속_ 한다.

> componentDidMount or componentDidUpdate와 달리, useEffect로 스케줄링된 effect는 브라우저가 스크린 업데이트 하는 것을 block하지 않는다. 이것은 app이 더 책임감을 갖도록 한다. effect의 대부분은 동기적으로 일어날 필요가 없다. 만약에 동기적으로 일어나야하는 즉, 일반적이지 않은 케이스에서 (layout 측정하는거), useLayoutEffect hook을 사용하면된다.

### Effects with Cleanup

외부 데이터를 구독 한다고 해보자. 메모리 누수때문에 cleanup은 중요하다. hook과 클래스에서 사용방식을 비교해보자.
예를 들어, 외부 데이터 소스에 구독을 세팅한다고 해보자. 메모리 누수되지 않기 위해 cleanup은 중요하다.

#### Example Using Classes

클래스에서는 CMD에서 구독하고, CWU에서 clena up 한다. 구독과 cleanup은 연관된 effect이더라도, Lifecycle method는 로직을 강제로 분리하도록 한다.

#### Example Using Hooks

useEffect는 구독의 추가/제거를 한곳에서 할 수 있게 해준다.

**왜 effect에서 함수를 리턴하는가?**
모든 이펙트는 clean up 하는 함수를 리턴한다. 이것은 구독 추가/제거를 한곳에서 할 수 있도록 해준다.

**리액트가 effect를 clean up 하는 시점은 정확히 언제인가?**
리액트는 컴포넌트가 언마운트 될 때 cleanup을 수행한다. 그러나 앞에서 말했듯이 effect는 every render마다 실행된다.
**이것이 React가 다음 effect를 실행하기 전에 이전 렌더링의 effect를 clean up 하는 이유다.** 뒤에서 이 방식을 버그를 피하기 좋은 이유, 퍼포먼스 이슈가 발생할 경우 동작을 해제하는 방법에 대해 설명할거다.

## Tips for Using Effects

### Tip: 관심사 분리를 위한 여러개의 이펙트 사용하기

```js
componentDidMount() {
    document.title = `You clicked ${this.state.count} times`;
    ChatAPI.subscribeToFriendStatus(
      this.props.friend.id,
      this.handleStatusChange
    );
  }

  componentDidUpdate() {
    document.title = `You clicked ${this.state.count} times`;
  }

  componentWillUnmount() {
    ChatAPI.unsubscribeFromFriendStatus(
      this.props.friend.id,
      this.handleStatusChange
    );
  }

  handleStatusChange(status) {
    this.setState({
      isOnline: status.isOnline
    });
  }
```

CDM, CDU에 document.title 세팅하는게 분리되어 있고, 구독 로직은 CDM, CWU에 분산되어있다. CDM의 앞의 두가지 일을 전부 하고 있다.

hook은 이걸 어케 해결했을까? state hook을 1개 이상 사용하는 것과 같이 여러개의 effect를 사용할 수 있다. 이것은 연관되지 않은 로직을 다른 이펙트로 분리할 수 있다.

## Explanation: why effects run on each update

effect cleanup phase가 unmounting때 한번 실행되는게 아닌, every re-render 후에 일어나는 이유에 대해 알아보자. 이러한 설계가 왜 때문에 더 적은 버그를 가진 컴포넌트를 생성하는데 도움이 되는지 알아보자.

```js
  componentDidMount() {
    ChatAPI.subscribeToFriendStatus(
      this.props.friend.id,
      this.handleStatusChange
    );
  }

  // componentDidUpdate(prevProps) {
  //   // Unsubscribe from the previous friend.id
  //   ChatAPI.unsubscribeFromFriendStatus(
  //     prevProps.friend.id,
  //     this.handleStatusChange
  //   );
  //   // Subscribe to the next friend.id
  //   ChatAPI.subscribeToFriendStatus(
  //     this.props.friend.id,
  //     this.handleStatusChange
  //   );
  // }

  componentWillUnmount() {
    ChatAPI.unsubscribeFromFriendStatus(
      this.props.friend.id,
      this.handleStatusChange
    );
  }
```

friend prop이 변경된다면 변경된 id를 구독하지 못해서 버그가 발생한다. 결국, subscribe를 다시 해줘야하는데, 위 주석을 해제해야한다. hook은 굉장히 간단해진다.

```js
function FriendStatus(props) {
  // ...
  useEffect(() => {
    // ...
    ChatAPI.subscribeToFriendStatus(props.friend.id, handleStatusChange);
    return () => {
      ChatAPI.unsubscribeFromFriendStatus(props.friend.id, handleStatusChange);
    };
  });
```

hook은 위 버그로부터 고통받지 않아도 된다.

next effect 적용하기 전에 이전 effect를 cleanup 한다. 이것을 설명하기 위해, 이 컴포넌트가 시간이 지남에 따라 구독/구독해제 하는 일련의 과정을 보자.

```js
// Mount with { friend: { id: 100 } } props
ChatAPI.subscribeToFriendStatus(100, handleStatusChange); // Run first effect

// Update with { friend: { id: 200 } } props
ChatAPI.unsubscribeFromFriendStatus(100, handleStatusChange); // Clean up previous effect
ChatAPI.subscribeToFriendStatus(200, handleStatusChange); // Run next effect

// Update with { friend: { id: 300 } } props
ChatAPI.unsubscribeFromFriendStatus(200, handleStatusChange); // Clean up previous effect
ChatAPI.subscribeToFriendStatus(300, handleStatusChange); // Run next effect

// Unmount
ChatAPI.unsubscribeFromFriendStatus(300, handleStatusChange); // Clean up last effect
```

hook은 일관성을 유지하고 클래스 컴포넌트에서 업데이트 로직을 놓쳐서 발생할 수 있는 일반적인 버그를 막는다.

### Tip: 이펙트 스킵하여 퍼포먼스 최적화하기

모든 렌더마다 effect를 cleanup 하여 재생성하면 퍼포먼스 문제가 생긴다. 클래스 컴포넌트에서는 prevState나 prevState로 조건문을 만들어서 이 문제를 해결했다.

hook에서는 리렌더 동안 특정 값이 변경되지 않는다면 cleanup-applying hook 과정을 skip하도록 할 수 있다.
이거는 쉬어서 넘어간다.

[useeffect-vs-uselayouteffect](https://kentcdodds.com/blog/useeffect-vs-uselayouteffect) 번역

## useEffect

`componentDidMount`, `componentDidUpdate`, `componentWillUnmount`를 useEffect로 대체 가능하다.

**1가지 문제점은** 리액트가 너의 컴포넌트를 렌더링 한후에 effect를 실행한다. 그리고 effect callback이 브라우저 페인팅을 block하지 않는다. 렌더링 후에 **동기적으로 실행되는 클래스컴포넌트의 cmd, cdu** 와 다르다. 이 방식이 더 퍼포먼스적으로 좋다. (cmd, cmu는 동기적으로 일어나서 브라우저 페인팅을 block할 수 있다.)

그러나 이펙트가 DOM(DOM Node ref를 통해)을 변경시키고 렌더링 하는 시간과 effect가 변경하는 시간 사이에 DOM 변경이 DOM node의 appearance를 변경시킨다면, **useEffect를 사용하고 싶지 않을거다.** 이것은 `useLayoutEffect`를 사용해야한다. 그렇지 않다면 유저는 DOM 변경이 적용될 때, 깜빡이는 것을 볼 수 있다. **useEffect를 피하고 useLayoutEffect를 사용해야한다**

## useLayoutEffect

리액트가 모든 DOM 변경을 수행한 후에 **즉시 동기적으로** 실행된다. 만약 DOM 측정(scroll position 가져오기나 element 스타일 가져오기)이나 DOM 변경 or state 업데이트하고 동기적으로 리렌더를 트리거 해야한다면 유용하다.

as far as scheduling, 이거는 CMD/CMU와 같은 방식으로 동작한다. 코드는 브라우저는 페인트할 기회를 갖기 전에 DOM이 업데이트 되고 즉시 실행된다.(유저는 실제로 브라우저가 리페인트 할 떄까지 업데이트된걸 보지 못한다.)

### Summary

- useLayoutEffect: DOM을 변경하고/거나 측정을 수행해야한다면 요고 이용
- useEffect: DOM과 상호작용하지 않거나 DOM 변경이 unobservable 하다면 (근데 대부분 요고 사용할거다.)

## Q&A

Q. useEffect 와 클래스 컴포넌트의 라이프사이클 차이점은?

Q. useEffect는 언제 실행되는가?
A. every rerender(첫렌더 포함)

Q. 그럼 뭐가좋은가?
A. 일단은 mouting, updating 이런 용어 대신에 after render마다 이펙트는 실행된다고 **쉽게** 생각할 수 있다.

Q. useEffect에서 count 상태를 콘솔에 출력해준다고 하자. JS 개발자라면 이 함수가 한번 전달되면 리렌더 될 때마다 count값이 계속 똑같은 값을 출력해줄텐데 어떻게 다른 값이 출력될까?
A. useEffect에 전달된 함수는 렌더링 마다 다르다. 즉, 렌더링될 때마다 이전에 전달된 함수를 대체한다. 그래서 각 이펙트는 특정 렌더에 종속한다고 볼 수 있다.

Q. 클래스 컴포넌트와 비교했을 때 좋은점?
A. props의 특정 값을 이용하여 구독중일 때, 특정 props가 변한다면 총 3가지 라이프사이클을 이용하여 cleanup,apply를 다시 해야한다. 하지만 hook은 1개의 useEffect로 3가지 라이프사이클 역할을 할 수 있다.

Q. useEffect가 componentDidMount, componentDidUpdate와 같은 클래스 컴포넌트의 라이프사이클와 차이점은?
A. [useEffect는 렌더링 한 후에 effect를 실행한다.](https://codesandbox.io/s/useeffect-sunseo-lyt4x) CDM과 CDU는 동기적으로 일어나서 브라우저 페인팅을 block할 수 있다. effect callback은 브라우저 페인팅을 block하지 않는다. useLayoutEffect는 CDM과 CDU처럼 동작한다. 그래서, 브라우저 페인팅을 블락하고 동기적으로 바로 DOM 변경을 해야하는 경우 사용한다. (유저는 실제로 브라우저가 리페인트할 때까지 업데이트된걸 보지 못한다.)