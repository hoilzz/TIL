# React.ref

Ref는 render메서드에서 생성된 DOM노드, React 엘리먼트에 접근하는 방법을 제공한다.

React에서 자식 컴포넌트의 UI 상태를 수정하려면 새로운 props를 전달하여 리렌더링해야한다. 하지만 일반적인 데이터 플로를 벗어나 자식을 직접 수정해야 하는 경우가 있다. 여기서 자식은 React 컴포넌트의 인스턴스 일 수 있고, DOM element 일 수 있다.

ref는 다음과 같이 사용된다.

## Ref 생성하기

createRef()를 통해 생성하고, `ref` 어트리뷰트를 통해 리액트 엘리먼트에 부착된다.
**컴포넌트의 인스턴스가 생성될 때 Ref를 프로퍼티로 추가한다. 그래서 컴포넌트의 인스턴스 어느곳에서도 Ref에 접근 가능하다.**

## Ref에 접근하기

render 메서드 내에서 ref가 엘리먼트에 전달되었을 때, 그 노드에 대한 참조값은 `ref.current`에 담긴다.

```js
const node = this.myRef.current;
```

ref의 값은 노드의 유형에 따라 다르다.

- ref 어트리뷰트가 HTML 엘리먼트에 쓰였다면, DOM element를 current 프로퍼티 값으로서 받는다.
- ref 어트리뷰트가 커스텀 클래스 컴포넌트에 쓰였다면, 마운트된 컴포넌트의 인스턴스를 current 프로퍼티 값으로 받는다.
- **함수 컴포넌트는 인스턴스가 없기 때문에 ref 어트리뷰트를 사용할 수 없다.**

## Ref에 값은 언제 할당될까?

컴포넌트가 마운트 될 때 React는 `current` 프로퍼티에 DOM 엘리먼트를 대입한다.
마운트가 해제되면 `current`프로퍼티는 null로 되돌려 놓는다.
ref 수정작업은 CDM or CDU 생명주기 메서드가 호출되기 전에 이루어진다.
즉 commit 단계에 이루어진다. 아래를 참고하자.

[react-lifecycle-methods-diagram/](http://projects.wojtekmaj.pl/react-lifecycle-methods-diagram/)

## 부모 컴포넌트에게 DOM ref 공개하기

부모가 자식컴포넌트 DOM 노드엥 접근해야하는 경우가 있다.
자식 컴포넌트의 DOM 노드에 접근하는 것은 컴포넌트 캡슐화를 파괴하기 때문에 권장되지 않는다. 하지만 이 상황이 꼭 있다.(자식 컴포넌트의 DOM 노드를 포커스 하기 or 크기 또는 위치 계산하기 등)

해결방법 1. 자식 컴포넌트에 ref 사용하기
자식 컴포넌트가 함수형 컴포넌트일 경우 동작 안함.

해결방법 2. [ref forwardding](https://ko.reactjs.org/docs/forwarding-refs.html) (>=16.3)

ref 포워딩은 자식 컴포넌트의 ref를 자신의 ref로써 외부에 노출시키게 된다.

## Forwardding Refs

자식 컴포넌트에 ref를 전달하는 기법이다. 재사용 가능한 컴포넌트 라이브러리를 만들 때 유용하다. 가장 일반적인 시나리오를 보자.

native Button DOM element를 렌더하는 FacnyButton component가 있다고 하자.

```js
function FancyButton(props) {
  return <button className="FancyButton">{props.children}</button>;
}
```

리액트 컴포넌트는 렌더링하는 아웃풋을 포함하여 구현체를 숨긴다. `FancyButton`을 이용하는 다른 컴포넌트는 FancyButton 내부의 button에 대한 ref를 소유 **할 필요가 없다.** 왜냐하면 서로 의존하게 되는 것을 막아주기 때문이다.

`FeedStory` or `Comment`와 같은 application-level에서 캡슐화는 이상적이지만, FancyButton과 MyTextInput과 같은 재사용성이 높은 **leaf** component에서는 불편할 수 있다. 이러한 컴포넌트는 비슷한 방식ㅇ으로 앱의 모든곳에서 사용될 수 있다. 그리고 DOM node에 접근하는 것(포커싱, 선택, 애니메이션 등)은 피할 수 없다.

**Ref forwarding은 컴포넌트가 받은 ref를 가질 수 있고 더 하위로 전달할 수 있도록 하는 opt-in 기능이다.**

```js
const FancyButton = React.forwardRef((props, ref) => (
  <button ref={ref} className="FancyButton">
    {props.children}
  </button>
));

// You can now get a ref directly to the DOM button:
const ref = React.createRef();
<FancyButton ref={ref}>Click me!</FancyButton>;
```

이러한 방식ㅇ으로 FancyButton을 이용하는 컴포넌트는 하위에 있는 `button` DODM node에 대한 ref를 가지고 접근할 수 ㅇ있다.

step-by-stepㅇ으로 무슨일이 일어나는지 알아보자.

1. createRef로 ref만들고 ref 변수를 FancyButton에 할당했다.
2. JSX attribute로 명시하여 (`<FancyButton ref={ref}>`) ref를 하위로 전달했다.
3. React는 forwardRef 내부 함수의 2번째 인자로 ref를 전달했다.
4. JSX attribute로 명시하여 ref 인자를 포워딩했다. `<button ref={ref}>`
5. ref가 부착될 때, `ref.current`는 <button> DOM node를 가리킨다.

> Note
> 두 번째 인자인 ref 인자는 React.forwardRef로 호출된 컴포넌트로 정의할 때만 존재한다.
> 일반적인 함수 or 클래스 컴포넌트는 `ref` 인자를 받지 못한다. 그래서 ref는 prop으로 이용하지 못한다.
> Ref forwarding은 DOM component로 제한되는게 아니다. class component instance에도 forwarding 할 수 있다.
