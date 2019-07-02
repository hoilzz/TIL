# React component, React element, and Instance

components, instances, elements의 차이에 대해 알아보자.

## 인스턴스 관리하기

리액트 뉴비라면, component class와 인스턴스로만 작업할거다. 클래스를 생성하여 `Button` _component_ 를 선언할 수 있다. app이 실행 될 떄, 화면에 각 state와 프로퍼티를 가진 컴포넌트의 _instance_ 가 있다. 이것은 전통적인 object-기반 UI 프로그래밍이다.

_elements_ 를 왜 도입해야할까?

전통 UI 모델에서, child component instance를 생성하고 제거하는 것은 너한테 달려있다. 만약 `Form` component가 `Buttom` component를 렌더링하려면, instance를 생성해야 하고 새로운 정보를 사용하여 수동으로 최신 상태를 유지해야한다.

## Elements는 트리를 설명한다.

리액트는 _elements_ 가 rescue 되는 곳이다. **엘리먼트는 component 인스턴스나 DOM node 그리고 그것이 원하는 속성을 설명하는 plain object다.** 그것은 컴포넌트 타입(예를 들어, `Button`) 정보, 그 컴포넌트의 프로퍼티(예컨대 `color`), 그리고 내부 child elements를 포함하고 있다.

엘리먼트는 실제 인스턴스는 아니다. 오히려, 개발자가 스크린에 보여주기를 원하는 것을 리액트에게 말하는 방법이다. 엘리먼트에서 어떤 메서드든 호출할 수 없다. 2가지 필드로 된 불변의 description 객체다. (`type: (string | ReactClass)` and `props: Object`)

Elements는 실제 인스턴스가 아닌 컴포넌트에 관한 정보를 담은 plainObject다. 이 엘리먼트로 어떤 메서드든 호출할 수 없다. 이것은 `type: (string | ReactClass)` and `props: Object`이 2가지 필드를 가진 불변의 description object다.

## Dom Elements

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
    color: 'red',
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
        text: 'Success!'
      }
    };
  }

  // Form is still visible! Return a button element.
  return {
    type: Button,
    props: {
      children: buttonText,
      color: 'blue'
    }
  };
};
```

React Component의 경우에, props은 input이다. 그리고 엘리먼트 트리는 아웃풋이다.

**리턴된 엘리먼트 트리는 DOM nodes를 설명하는 엘리먼트와 다른 컴포넌트를 설명하는 element를 포함한다.** **이것이 개발자에게 내부 DOM 구조에 의존하는 것 없이 UI의 독립적인 부분을 구성하도록 해준다.**

우리는 React가 인스턴스를 생성하고, 업데이트하고, 파괴하도록 한다. 우리는 컴포넌트에서 리턴하는 엘리먼트로 그것들(인스턴스)을 설명하고, 리액트는 인스턴스를 관리하는데 신경쓴다.

> ;
> 개발자는 UI의 독립적인 부분만 구성하면, 리액트가 알아서 기본 DOM tag element 알 때까지 알아서 반복해서 순회함. 우리는 UI를 정의해놓기만 하면 리액트가 알아서 인스턴스 생성/업데이트/파괴 한다. 즉, 우리는 jsx로 컴포넌트 정의만 해놓으면 알아서 인스턴스 관리한다.

## Components는 Classes or Functions가 될 수 있다.

위 코드에서, `Form`, `Message`, and `Button`은 리액트 컴포넌트다. 이 컴포넌트들은 위와 같이 함수 혹은 `React.Component`를 상속하는 클래스로 작성될 수 있다. 컴포넌트를 선언하는 3가지 방법은 거의 비슷하다.

```js
// 1) As a function of props
const Button = ({ children, color }) => ({
  type: 'button',
  props: {
    className: 'button button-' + color,
    children: {
      type: 'b',
      props: {
        children: children
      }
    }
  }
});

// 2) Using the React.createClass() factory
const Button = React.createClass({
  render() {
    const { children, color } = this.props;
    return {
      type: 'button',
      props: {
        className: 'button button-' + color,
        children: {
          type: 'b',
          props: {
            children: children
          }
        }
      }
    };
  }
});

// 3) As an ES6 class descending from React.Component
class Button extends React.Component {
  render() {
    const { children, color } = this.props;
    return {
      type: 'button',
      props: {
        className: 'button button-' + color,
        children: {
          type: 'b',
          props: {
            children: children
          }
        }
      }
    };
  }
}
```

컴포넌트가 클래스로 정의됐을 때, 함수형 컴포넌트보다 조금 더 강력하다. 그것은 local state를 저장할 수 있고 DDOM node가 생성되거나 파괴될 때 커스텀 로직을 수행할 수 있다.

함수형 컴포넌트는 덜 강력하지만 심플하다. `render()`라는 단일 method를 가진 클래스 처럼 행동한다. 만약 클래스에서만 이용가능한 기능이 필요하지 않다면, 함수형 컴포넌트를 대신 사용하자.

**그러나, 함수형이든 클래스든, 근본적으로 그것들은 리액트에게 전부 컴포넌트다. 그것들은 input으로 prop을 가지고 output으로 엘리먼트를 리턴한다.**

## Top-Down Reconciliation

너가 다음을 호출할 때,

```js
ReactDOM.render(
  {
    type: Form,
    props: {
      isSubmitted: false,
      buttonText: 'OK!'
    }
  },
  document.getElementById('root')
);
```

리액트는 `props`가 주어졌을 떄, `Form` component에게 해당 컴포넌트가 리턴하는 엘리먼트 트리가 뭔지 물어본다. 단순한 primitives 관점에서 너의 컴포넌트 트리에 대한 이해를 점점 "refine" 할 것이다. (다음 코드를 보며 점점 정제(refine)하는 과정을 이해하자)

```js
// React: You told me this...
{
  type: Form,
  props: {
    isSubmitted: false,
    buttonText: 'OK!'
  }
}

// React: ...And Form told me this...
{
  type: Button,
  props: {
    children: 'OK!',
    color: 'blue'
  }
}

// React: ...and Button told me this! I guess I'm done.
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

ReactDOM.render() 나 setState()를 호출할 때 시작되는 reconciliation을 리액트가 호출하는 과정이다. reconciliation의 끝에, 리액트는 결과 DOM tree를 알고 `react-dom`이나 `react-native`같은 렌더러는 DOM nodes를 업데이트 하기 위한 필수적인 최소 변경 요소들을 적용한다.

점진적인 refining 과정은 React app이 최적화하기 쉬운 이유다. 만약 컴포넌트 트리의 어떤 부분이 리액트가 효율적으로 방문하기에 너무 크다면, 관련 props이 변경되지 않았을 경우 "refining" 과정과 트리의 특정 부분을 diffing을 스킵하라고 말할 수 있다. 만약 props이 immutable 하다면 props의 변경 여부 계사하는 것은 빠르다. 그래서 리액트와 불변성은 함께 잘 동작하고 최소 노력으로 큰 최적화를 제공한다.

이 포스팅에서 instance에 대한 얘기는 별로 없고 components와 elements에 대해서 많이 얘기한 걸 알고 있을거다. 사실 instance는 리액트보다 object 기반 UI framework에서 더 중요하다.

class로 선언된 컴포넌트만 instance를 갖고 그것들을 개발자가 직접 생성할 일은 없다: 리액트가 너를 위해 대신 해준다. parent component instance가 child component instance에 접근하는 메커니즘(ref)은 존재하지만, 일반적으로 피해야한다.

리액트는 모든 클래스 컴포넌트의 인스턴스를 생성하는데 신경써야한다. 그래서 object 기반 방식에서 메서드와 local state를 가진 컴포넌트를 작성할 수 있다. 하지만 그 이외의 인스턴스는 React의 프로그래밍 모델에서 중요하지 않고 React 자체에서 관리된다.

## Summary

_element_ 는 DOM nodes 나 다른 컴포넌트의 관점에서 스크린에 노출되는 것을 설명하는 plain object다. Elements는 자신의 prop에서 다른 엘리먼트를 포함할 수 있다. React element를 생성하는 것은 값싼 비용이 든다. **엘리먼트가 한 번 생성되면 절대 변경될 일이 없다.**

_component_ 는 몇가지 다른 방법으로 선언된다. `render()` 메서드를 가진 클래스다. 대신, 단순한 경우에 함수로도 정의될 수 있다. 2가지 경우 모두, props을 input으로 받고 element tree를 output으로 리턴한다.

컴포넌트가 input으로 prop을 받을 때, 특정 부모 컴포넌트는 `type`과 props을 가진 엘리먼트를 리턴하기 때문이다. 사람들이 리액트에서 props flows가 단방향이라고 얘기하는 이유다.(parent to children)

_instance_ 는 너가 작성한 클래스에서 `this`로 참조하는 것이다. lifecycle event에 반응하고 local state를 저장할 때 유용하다.

함수형 컴포넌트는 인스턴스를 가지지 않는다. 클래스 컴포넌트는 인스턴스를 갖지만 component instance를 직접 생성할 필요가 없다. 리액트가 알아서 한다.

끝으로, elements를 생성하기 위해, [React.createElement()](https://reactjs.org/docs/react-api.html#react.createelement), [JSX](https://reactjs.org/docs/jsx-in-depth.html), element factory helper를 이용해라. 엘리먼트를 plain object로 직접 작성하지 말아라. 걍 엘리먼트가 plain object인것만 알아둬라.
