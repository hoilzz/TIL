# From Classes to Hooks

## lifecycle 메서드와 훅 일치시키기

- constructor

함수형 컴포넌트는 생성자가 필요 없다. useState에서 state를 초기화할 수 있다. 만약 초기 state 계산이 비싸다면, useState에 전달해라.

## SCU 구현하기

```js
const Button = React.memo(props => {
  // component
})일
```

prop에 shallow compare를 하기 위해 React.memo에 함수형 컴포넌트를 전달하자.

이것은 Hook이 하는 것처럼 compose하지 않기 때문에 Hook이 아니다. React.memo는 PureComponent와 동일하다. prop만 비교한다. (2번째 인자에 custom 비교 함수 전달할 수 있다. true를 리턴하면 update를 스킵한다.)

**리액트 메모는 state를 비교하지 않는다. 왜냐하면 비교할 state 객체가 없기 때문이다.**
하지만 children을 pure하게 만들 수 있거나 useMemo를 통해 개별 children을 최적화 할 수 있다.

## 연산 메모이징 하기

useMemo hook은 여러번의 렌더동안 이전 계산을 "기억해서" 연산을 캐싱하도록 해준다.

```js
const memoizedValue = useMemo(() => computeExpensiveValue(a, b), [a, b]);
```

이 코드는 computeExpensiveValue(a,b)를 호출한다. 디펜던시인 `[a,b]`가 마지막 값 이후로 변경되지 않는다면, useMemo는 함수 호출을 스킵한다. 그리고 마지막에 연산된 값을 재사용한다.

렌더링 동안 useMemo에 전달된 함수는 호출되는 점을 기억해라.
렌더링 하는 동안 평범하게 할 수 없는 어떤 것이든 useMemo 내부에 전달된 함수에서 하지 마라.
예를 들어, side effect는 useMemo가 아닌 useEffect에서 해야한다.

**useMemo는 시맨틱 보장이 아닌 퍼포먼스 최적화에 사용된다.** 미래에 리액트는 이전에 메모된 값을 "잊어버리고" 다음 렌더 때 재계산 하도록 선택할 수 있다. 예를 들어서 offscreen component의 메모리를 확보한다. useMemo없이 너의 코드는 동작할거다. 그리고 퍼포먼스 최적화를 위해 추가될거다.

useMemo는 값비싼 child의 re-render를 스킵하도록 해준다.

```js
function Parent({ a, b }) {
  // Only re-rendered if `a` changes:
  const child1 = useMemo(() => <Child1 a={a} />, [a]);
  // Only re-rendered if `b` changes:
  const child2 = useMemo(() => <Child2 b={b} />, [b]);
  return (
    <>
      {child1}
      {child2}
    </>
  );
}
```

이 접근은 loop에서 동작하지 않는다. 왜냐하면 hook은 loop 내부에서 동작할 수 없기 때문이다. 하지만 list item을 위해 별개의 컴포넌트로 추출하여 useMemo를 호출 할 수 있다.

## 값비싼 객체를 레이지하게 생성하기

useMemo는 동일한 dependencies라면 값비싼 계산을 메모이징한다.
그러나, 그것은 hint만 제공하고 재실행되지 않는 계산을 보장하지 못한다.

하지만 가끔 객체가 **단 한번만 생성된다는 것을** 아는 경우엔 어케 할까?

**첫번째 일반적인 유즈 케이스는 initial state 생성되는게 값비쌀 때**

```js
function Table(props) {
  // ⚠️ createRows() is called on every render
  const [rows, setRows] = useState(createRows(props.count));
  // ...
}
```

무시된 initial state를 다시 만들지 않기 위해 useState에 함수를 전달할 수 있다.
[useState initialValue를 함수로 전달시 호출 횟수](https://codesandbox.io/s/usestate-test-v5k84)

```js
function Table(props) {
  // ✅ createRows() is only called once
  const [rows, setRows] = useState(() => createRows(props.count));
  // ...
}
```

리액트는 첫 렌더에만 이 함수를 호출한다.

**useRef() initial value를 재생성하고 싶지 않은 경우**
한 번만 생성된 클래스 인스턴스를 원한다고 해보자.

```js
function Image(props) {
  // ⚠️ IntersectionObserver is created on every render
  const ref = useRef(new IntersectionObserver(onIntersect));
  // ...
}
```

useRef는 useState와 같이 오버로드된 특별한 함수가 아니다.
대신에, 생성과 세팅을 레이지하게 할 수 있는 함수를 작성할 수 있다.

```js
function Image(props) {
  const ref = useRef(null);

  // ✅ IntersectionObserver is created lazily once
  function getObserver() {
    if (ref.current === null) {
      ref.current = new IntersectionObserver(onIntersect);
    }
    return ref.current;
  }

  // When you need it, call getObserver()
  // ...
}
```

---

## Q&A

Q. SCU를 hook에서 동일하게 구현할 수 있나?
A. React.memo로 비슷하게 구현할 수 있다. 비슷한 이유는 React.memo는 state를 비교하지 않는다. React.memo는 SCU보다 PureComponent와 동일하다고 볼 수 있다. 또한, useMemo를 이용하여 children component를 SCU처럼 구현할 수 있다. useMemo의 dependency를 개발자가 직접 정하여, 해당 dependency의 shallow compare시 변경되었을 때만 리렌더링한다.

Q. 연산이 비싼 객체가 단 한번 생성되는 경우, 레이지하게 생성하려면 어떤 기법을 사용할 수 있는가?
A. 특정 변수에 useRef를 호출. 함수 하나를 만들어서 ref.current에 값을 할당하는 코드 작성. 필요할 때 함수 호출.

## 놓치기 쉬운 최적화

```js
useState(createObjByExpensiveCalculation());
```

위 코드는 함수가 리렌더 될 때마다 호출된다. JS 함수 호출 시 인자를 먼저 평가하기 때문이다.

다음과 같이 고쳐주자

```js
useState(() => createObjByExpensiveCalculation());
```
