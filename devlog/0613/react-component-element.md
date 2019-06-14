# React component, React element, and Instance

components, instances, elements의 차이에 대해 알아보자.

## 인스턴스 관리하기

리액트 뉴비라면, component class와 인스턴스로만 작업할거다. 클래스를 생성하여 `Button` _component_ 를 선언할 수 있다. app이 실행 될 떄, 화면에 각 state와 프로퍼티를 가진 컴포넌트의 _instance_ 가 있다. 이것은 전통적인 object-기반 UI 프로그래밍이다.

_elements_ 를 왜 도입해야할까?

전통 UI 모델에서, child component instance를 생성하고 제거하는 것은 너한테 달려있다. 만약 `Form` component가 `Buttom` component를 렌더링하려면, instance를 생성해야 하고 새로운 정보를 사용하여 수동으로 최신 상태를 유지해야한다.

## Elements는 트리를 설명한다.

리액트에서, _elements_ 가 rescue 되는 곳이다. \_\_엘리먼트는 component 인스턴스나 DOM node 그리고 그것이 원하는 속성을 설명하는 plain object다. 그것은 컴포넌트 타입(예를 들어, `Button`) 정보, 그 컴포넌트의 프로퍼티(예컨대 `color`), 그리고 내부 child elements를 포함하고 있다.

엘리먼트는 실제 인스턴스는 아니다. 오히려, 개발자가 스크린에 보여주기를 원하는 것을 리액트에게 말하는 방법이다. 엘리먼트에서 어떤 메서드든 호출할 수 없다. 2가지 필드로 된 불변의 description 객체다. (`type: (string | ReactClass)` and `props: Object`)

Elements는 실제 인스턴스가 아닌 컴포넌트에 관한 정보를 담은 plainObject다.

## Dom ELements

엘리먼트의 `type`이 string일 때, 그것은 tag name을 가진 DOM node를 나타낸다. 그리고 `props`은 attribute와 상응한다. 이것은 React가 렌더할 것이다:

```js
{
  type: 'button',
  props: {
    className: 'button button-blue',
    children: {
      type: 'b',
      props: {
        children: 'OK!'
      }
    }
  }
}
```

이 엘리먼트는 다음 HTML을 plain object로 나타내는 방법이다.

```html
<button class="button button-blue">
  <b>
    OK!
  </b>
</button>
```

컨벤션대로, element tree를 생성할 때, 1개 이상의 child element가 `children` prop으로 명시해준다.

child and parent elements 둘 다 _description_ 이고 _actual instance_ 가 아닌 점이 중요하다. 그것들이 생성될 때 화면에 어떤 것도 참조하지 않는다.

리액트 elements는 순회하기 쉽다. 파싱할 필요도 없고 실제 DOM element보다 훨씬 가볍다. (왜냐면 걍 객체니까!)

## Component Elements

그러나, 엘리먼트 `type`은 React component에 맞는 함수거나 클래스가 될 수 있다.

```js
{
  type: Button,
  props: {
    color: 'blue',
    children: 'OK!'
  }
}
```

이것이 React의 core idea다.

DOM node를 설명하는 엘리먼트와 같이 컴포넌트를 설명하는 엘리먼트 또한 엘리먼트다. 그것들은 중첩될 수 있고 서로 섞일 수 있다.

이 기능은 `DangerButton` component를 `color` 프로퍼티를 가진 `Button`으로 정의한다.

```js
const DangerButton = ({ children }) => ({
  type: Button,
  props: {
    color: "red",
    children: children
  }
});
```

DOM과 컴포넌트 elements를 단일 엘림너트 트리에서 작성할 수 있다.

```js
const DeleteAccount = () => ({
  type: 'div',
  props: {
    children: [{
      type: 'p',
      props: {
        children: 'Are you sure?'
      }
    }, {
      type: DangerButton,
      props: {
        children: 'Yep'
      }
    }, {
      type: Button,
      props: {
        color: 'blue',
        children: 'Cancel'
      }
   }]
});
```

JSX를 선호한다면,

```js
const DeleteAccount = () => (
  <div>
    <p>Are you sure?</p>
    <DangerButton>Yep</DangerButton>
    <Button color="blue">Cancel</Button>
  </div>
);
```

이 mix and matching은 서로 디커플링 된 컴포넌트를 유지하도록 도와준다. 그것들은 _is-a_ 와 _has-a_ 관계를 composition 을 통해 독점적으로 표현할 수 있기 때문이다.

- `Button`은 특정 프로퍼티를 가진 DOM `<button>`이다
- `DangerButton`은 특정 프로퍼티를 가진 `Button`이다.
- `DeleteAccount`는 `Button`과 `<div>` 내부에 있는 `DangerButton`을 포함한다.

## Components 는 엘리먼트 트리를 캡슐화한다.

React가 function or class `type`으로 된 엘리먼트를 볼 때,

리액트는 해당 `props`이 주어진다면, 그 컴포넌트에게 렌더링할 element를 물어본다.

아래 엘리먼트를 볼 때,

```js
{
  type: Button,
  props: {
    color: 'blue',
    children: 'OK!'
  }
}
```

리액트는 `Button`에게 렌더링 할것을 물어본다. `Button`은 다음 엘리먼트를 리턴한다.

```js
{
  type: 'button',
  props: {
    className: 'button button-blue',
    children: {
      type: 'b',
      props: {
        children: 'OK!'
      }
    }
  }
}
```

리액트는 페이지의 모든 컴포넌트에 대해 기본(underlying) DOM tag element를 알 때까지 과정을 반복한다.

React는 세상의 모든 작은 것을 이해할 때까지 모든 "X is Y"에 대해 "What is Y?"라고 묻는 어린애와 같다.

위의 `Form` 예제 기억하니? 리액트로 작성하면 다음과 같다.

```js
const Form = ({ isSubmitted, buttonText }) => {
  if (isSubmitted) {
    // Form submitted! Return a message element.
    return {
      type: Message,
      props: {
        text: "Success!"
      }
    };
  }

  // Form is still visible! Return a button element.
  return {
    type: Button,
    props: {
      children: buttonText,
      color: "blue"
    }
  };
};
```

React Component의 경우에, props은 input이다. 그리고 엘리먼트 트리는 아웃풋이다.

\_\_리턴된 엘리먼트 트리는 DOM nodes를 설명하는 엘리먼트 이고 다른 컴포넌트를 설명하는 element다.
