# JSX

```js
const element = <h1>Hello, World</h1>;
```

위 태그 문법은 문자열도 아니고 HTML도 아닌 JSX다. JSX는 JS의 확장 문법이다. UI가 어케 생겼는지 설명하려면 React와 함께 사용하는 것이 좋다.

## Why JSX ?

리액트는 UI 로직이 렌더링 로직과 본질적으로 결합되어 있다고 받아들인다. 이벤트 핸들링 되는 방식, state가 시간에 따라 변하는 방식, UI에 노출하기 위해 데이터를 준비하는 방식..

**리액트는 마크업과 로직을 분리된 파일로 놓는 기술 대신에, 둘 다 포함하는 컴포넌트라는 느슨하게 연결된 단위로 관심사를 분리한다.**

사실 리액트는 JSX를 필요로 하지 않지만, JS code 내에서 UI 작업할 때 visual적으로 도움이 된다.

### JSX

- JSX에 JS 표현식을 중괄호로 표현 가능
- JSX 또한 표현식.
  - 컴파일되고 나면 JSX 표현식은 자바스크립트 객체로 인식된다.
  - 즉, `if`, `for`문 반복 내에서 jsx를 사용 가능하고 매개 변수로 전달, 함수에서 반환될 수 있다는 의미다.

### JSX 객체 표현

babel은 JSX를 `React.createElement()` 호출로 컴파일 한다.

```js
const element = <h1 className="greeting">Hello, world!</h1>;
```

```js
const element = React.createElement(
  "h1",
  { className: "greeting" },
  "Hello, world!"
);
```

## Summary

Q. JSX란?
A. JSX는 JS의 확장 문법이다. 바벨이 createElement로 JSX 문법을 대체하고, 이 함수는 객체를 반환한다.

Q. react에서 JSX는 필수인가?
A. 아니다. 하지만 JS code 내에서 UI 작업시 visual적으로 도움이 된다.(마크업 같이 생겼으니까)

Q. JSX를 쓰면 뭐가 좋은가?
A. JSX에서 JS 표현식을 중괄호로 표현 가능. JSX는 결국 js 객체인데, 이 말은 즉 JSX를 함수의 반환값, 매개변수, for문 내에서 반복하는데 사용될 수 있다.
