# Error Boundaries

과거에, component 내부의 JS error는 리액트 내부 상태를 파괴시키곤 했다. 이것은 다음 렌더 때 emit cryptic error를 일으킨다. 이것은 어플리케이션 코드의 이전 오류로 인해 발생한다. 리액트에서는 컴포넌트에서 이러한 에러를 우아하게 처리하는 방법을 제공하지 않고 그것들을 recover할 수도 없다.

## Error Boundaries

UI 내부의 JS error는 전체 앱을 부수지 않아야한다. 이것을 해결하기 위해 error boundary가 있다.

Error boundaries는 리액트 컴포넌트다.
이것은 충돌된 컴포넌트 트리 대신에 **child component 트리 내부 어디서든 error를 캐치하고, 그 에러를 기록하고 fallback UI를 보여준다**

> 에러 바운더리는 다음의 경우 에러를 catch하지 못한다
> Event handlers
> async code(setTimeout, raf)
> ssr
> boundary 자체에서의 에러

---

[static getDerivedStateFromError()](https://reactjs.org/docs/react-component.html#static-getderivedstatefromerror) 나 [componentDidCatch()](https://codesandbox.io/s/errorboundary-vyd11?fontsize=14) 라이프사이클 메서드를 이용하여 class component는 error boundary가 될 수 있다.

error가 throw된 후에 fallback UI를 렌더링하기 위해 static getDerivedStateFromError를 사용하자.
에러 정보를 로깅하기 위해 componentDidCatch를 이용하자.

> getDerivedStateFromError(error)
> 자식 컴포넌트에서 error가 throw된 후에 호출.
> throw된 error를 인자로 받음
> state 업데이트 하기 위해 / fallback UI를 보여주기 위해 값을 리턴하여 state 업데이트한다.
> render phase에서 호출됨

> componentDidCatch(error, errorInfo(errorInfo.componentStack))
> 자식 컴포넌트에서 error가 throw된 후에 호출.
> error, errorInfo를 인자로 받음
> logging error하기 위해 사용됨.
> commit phase동안 호출되서 side-effect 허용
> 여기서 setState를 호출하여 fallback UI를 렌더할 수 있다. 하지만 이건 미래에 deprecated 될 것이다.
> fallback rendering을 다루기 위해 getDderivedStateFromError를 사용하자.

[그래서 둘 중에 뭘 써야하는데?](https://github.com/reactjs/reactjs.org/pull/1223)

error report는 componentDidCatch를 fallback UI를 보여주는 건 getDerivedStateFromError를 사용하자.(공홈의 예제도 그렇게 되어있다.)
위 링크의 내용에 대해 요약하자면..

**SSR 렌더링에서 동작 여부**

- CDC(componentDidCatch)는 SSR에서 동작하지 못한다. 왜냐하면 SSR은 commit phase가 없다.
- getDerivedStateFromError(DSE)는 render phase기 때문에 server에서 에러 핸들링 가능

**Render Phase의 복구가 더 안전하다**

- CDC를 통한 오류 복구는 약간 janky하다.
  - 오류가 발생한 컴포넌트 아래의 모든 항목에 대해 null의 중간 커밋에 의존하기 떄문이다.

**비동기 렌더링이 더 최적화되어있다**

- **commit 단계의 state-updates는 항상 동기로 실행된다.**
  - 그래서 CDC에서 에러 복구는 최적이 아니다. 왜냐하면 fallback UI가 항상 동기적응로 렌더되기 때문이다. (오류 복구가 최우선 관심사이기 때문에 사실 이건 문제가 안된다.)

https://codesandbox.io/embed/errorboundary-vyd11

```js
import React, { useState } from 'react';
1;
import ReactDOM from 'react-dom';
// import ErrorBoundary from "./ErrorBoundary";
import './styles.css';

class ErrorBoundary extends React.Component {
  constructor(props) {
    super(props);
    this.state = { error: null, errorInfo: null };
  }

  /**
   * 자식 컴포넌트에서 error가 throw 된 후에 호출된다.
   * throw된 에러는 파라미터로 받고 state를 업데이트하기 위해
   * 값을 리턴한다.
   * Note: render phase에서 호출된다. 그래서 side-effect 허용하지 않는다.
   * 그런 경우엔, componentDidCatch를 사용하자.
   * @param {*} error
   */
  static getDerivedStateFromError(error) {
    // Update state so the next render will show the fallback UI.
    console.error('1. getDerived', error);
    return {
      error: error
    };
  }

  /**
   * 자식 컴포넌트에서 에러가 throw되고 나서 호출된다.
   * "commit" phase동안 호출되서 side-effect이 허용된다.
   * @param {*} error
   * @param {*} errorInfo
   */
  componentDidCatch(error, errorInfo) {
    // Example "componentStack":
    //   in ComponentThatThrows (created by App)
    //   in ErrorBoundary (created by App)
    //   in div (created by App)
    //   in App
    console.log('2. componentDidCatch');
    this.setState({
      error: error,
      errorInfo: errorInfo
    });
    // You can also log error messages to an error reporting service here
  }

  render() {
    if (this.state.errorInfo) {
      // Error path
      return (
        <div>
          <h2>Something went wrong.</h2>
          <details style={{ whiteSpace: 'pre-wrap' }}>
            {this.state.error && this.state.error.toString()}
            <br />
            {this.state.errorInfo.componentStack}
          </details>
        </div>
      );
    }
    // Normally, just render children
    return this.props.children;
  }
}

class BuggyCounter extends React.Component {
  constructor(props) {
    super(props);
    this.state = { counter: 0 };
    this.handleClick = this.handleClick.bind(this);
  }

  handleClick() {
    this.setState(({ counter }) => ({
      counter: counter + 1
    }));
  }

  render() {
    if (this.state.counter === 5) {
      // Simulate a JS error
      throw new Error('I crashed!');
    }
    return <h1 onClick={this.handleClick}>{this.state.counter}</h1>;
  }
}

function App() {
  return (
    <ErrorBoundary>
      <div>
        <p>
          These two counters are inside the same error boundary. If one crashes,
          the error boundary will replace both of them.
        </p>
        <BuggyCounter />
        <BuggyCounter />
        <hr />
      </div>
    </ErrorBoundary>
  );
}

ReactDOM.render(<App />, document.getElementById('root'));
```

에러 바운더리는 `catch{}` 블록처럼 동작한다. 실제로 대부분 error boundary component를 한 번 선언하여 app 전체에서 사용한다.

**error boundaries는 트리 내부에서 바운더리 아래에 있는 컴포넌트의 error만 catch 한다.** 만약 에러 메시지 렌더링 하는데 실패한다면 에러는 가장 가까운 error boundary로 propogate한다. catch문과 동일하게 동작한다고 생각하자.

## Error Boundaries 위치

에러 바운더리의 세분화는 개발자에게 달려있다.

1. route component의 top-level에 두고 "Something went wrong"을 보여주거나
2. 에러 바운더리 내에서 개별 위젯으로 wrapping하여 대응할 수 있다.

## Uncaught Error에 대한 새로운 행위

React 16부터, error boundary 내에서 잡지 못하는 에러는 전체 React Component tree를 언마운팅할거다.

이것에 대해 많은 논의를 거쳤는데, 예컨대 메신저 앱의 경우 스타일이 깨진 UI를 보여준채로 잘못된 유저에게 메시지를 보내는 것보다는 아무것도 렌더링 하지 않는게 낫다고 판단했다.

페북 메신저에서는 message input이 별개의 error boundaries를 갖는다. 만약 input area의 UI가 충돌을 일으키고 이쪽만 error boundary를 노출한다. 나머지는 interactive하게 남아있다.

처리되지 않은 예외에 대해, JS error 리포팅 서비스를 이용하기를 권장한다.

## Component Stack Trace

CRA 에서 기본으로 제공하는데, 개발 모드에서 렌더링 되는 동안 출력된다.

만약 CRA가 아니라면 [plugin](https://www.npmjs.com/package/babel-plugin-transform-react-jsx-source)을 추가하자. 이것은 production에서는 disable 되고 development에서만 활성화된다.

## Event Handler는 어케할까?

event handler의 error를 recover하기 위해 error boundary를 사용할 수 없다. 리액트는 스크린에 뭘 display할지 여전히 알고 있다.

걍 핸들러 함수 내부에서 try catch로 처리하는 수밖에 없다.

## Summary

Error Boundary 는 필수다. try catch를 통해 에러를 처리하듯이 컴포넌트 내부의 에러를 핸들링 하기 때문이다.

getDerivedStateFromError 나 ComponentDidCatch를 이용한 클래스 컴포넌트가 Error Boundary다.

위치는 보통 top-level에 둔다.

- 에러가 발생한 곳만 에러 바운더리로 처리하고 나머지 컴포넌트의 interaction을 유지하고 싶다면 별개의 error boundary로 특정 컴포넌트 위에서 wrapping하면 된다.

모든 에러를 catch하지 않는다.
그래서 JS error reporting(sentry..)을 사용하자.

component stack trace는 CRA에서 기본 제공한다. 만약 CRA가 아닌 자체 FE 환경 구축했다면 [plugin](https://www.npmjs.com/package/babel-plugin-transform-react-jsx-source)추가 할것을 권장한다.
