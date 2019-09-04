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

[useeffect-vs-uselayouteffect](https://kentcdodds.com/blog/useeffect-vs-uselayouteffect) 번역

## useEffect

`componentDidMount`, `componentDidUpdate`, `componentWillUnmount`를 useEffect로 대체 가능하다.

**the one catch** 는 리액트가 너의 컴포넌트를 렌더링하고 effect callback이 브라우저 페인팅을 block하지 못한다는 것을 확신한 **후에** 실행한다. 렌더링 후에 동기적으로 실행되는 클래스컴포넌트의 cmd, cmu와 다르다. 이 방식이 더 퍼포먼스적으로 좋다.

그러나 이펙트가 DOM(via DOM Node ref)을 변경시키고 effect가 그것을 변경시키고 렌더링 하는 시간사이에 DOM 변경이 DOM node의 appearance를 변경시킬거라면, **useEffect를 사용하지 마라.** 이것은 `useLayoutEffect`를 사용해야한다. 그렇지 않다면 유저는 DOM 변경이 적용될 때, 깜빡이는 것을 볼 수 있다. **useEffect를 피하고 useLayoutEffect를 사용해야한다**

## Q&A

Q. useEffect 와 클래스 컴포넌트의 라이프사이클 차이점은?

Q. useEffect는 언제 실행되는가?
A. every rerender(첫렌더 포함)

Q. 그럼 뭐가좋은가?
A. 일단은 mouting, updating 이런 용어 대신에 after render마다 이펙트는 실행된다고 **쉽게** 생각할 수 있다.

Q. useEffect에서 count 상태를 콘솔에 출력해준다고 하자. JS 개발자라면 이 함수가 한번 전달되면 리렌더 될 때마다 count값이 계속 똑같은 값을 출력해줄텐데 어떻게 다른 값이 출력될까?
A. useEffect에 전달된 함수는 렌더링 마다 다르다. 즉, 렌더링될 때마다 이전에 전달된 함수를 대체한다. 그래서 각 이펙트는 특정 렌더에 종속한다고 볼 수 있다.
