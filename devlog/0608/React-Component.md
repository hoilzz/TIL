# React Component가 뭐에요?

리액트 컴포넌트는 상태를 가지고 있다. 이 상태는 객체로 관리된다. 이 객체는 직접 변경될 수 없고, 새로운 객체를 리턴해야 한다. 이 상태가 변경될 때마다 컴포넌트는 리렌더링 된다. 이 떄, 전체 리렌더링이 아닌 virtual DOM에 저장된 기존 DOM tree와 비교하여 변경된 부분만 DOM이 새로 생성된다.

이 때 상태뿐만 아니라 이 컴포넌트가 prop으로 받고 있는 상태에 대해서도 리렌더링이 동일한 조건으로 동작한다.

## Component and Props

**컴포넌트는 JS funtion과 같다.**
임의의 입력(prop이라고 부른다)을 받아들이고 어떤게 화면에 나타나야 하는지를 설명하는 리액트 엘리먼트를 반환한다.

컴포넌트에는 funtional과 class component가 있다. class component는 추가 기능을 더 가진다.

### 컴포넌트 렌더링하기

```js
const element1 = <div />;
const element2 = <Welcome name="Sara" />;
```

리액트가 user-defined 컴포넌트를 보면 , component에 단일 객체를 전달한다. 이것은 **props** 라고 부른다.

### props are read-only

컴포넌트는 자신의 `props`을 절대 수정하지 않아야한다.

```js
function sum(a, b) {
  return a + b;
}
```

위 함수는 순수함수다.
왜냐하면 input을 변경하지 않고 항상 동일 input 동일 return이기 때문이다.

반대로, 아래 함수는 순수하지 않은 함수다. 왜냐면 input을 변경하기 떄문이다.

```js
function withdraw(account, amount) {
  account.total -= amount;
}
```

리액트는 유연하지만 엄격한 1가지 규칙이 있다.

**모든 리액트 컴포넌트는 prop과 관련한 동작에서 pure function처럼 행동해야 한다.**
