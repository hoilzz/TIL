# react in runtime

리액트는 시간이 지남에 따라 변화할 수 있는 리를 출력한다. 보통 이 트리는 UI를 표현하는데 쓰인다. 이것은 `호스트 트리`.

> 안정성 호스트 트리
> 대부분 갱신은 전체 구조를 뜯어고치지 않음.
> 모든 상호작용 요소들이 매번 다른 조합으로 만들어진다면 매우 사용하기 어려움

> 규칙성 호스트 트리
> 무작위 형태가 아닌 일관된 모습과 동작을 가진 UI 패턴(버튼, 목록, 아바타)

## 호스트 객체

호스트 객체는

- 일반적인 DOM노드.
  - DOM API를 가지고 있음(appendChild 등)
- 다른 호스트 객체 자식으로 포함 가능.

## 렌더러

> 리액트 렌더러 중에는 ReactDOM, React Native 등이 있음

React가 특정 **호스트 환경** 과 통신하고 **호스트 객체** 를 관리한다.

렌더러는 2가지 모드를 가진다.

1. 변경 모드

- 대부분 렌더러가 요거임
- DOM 작동 방식임
  - 노드 생성, 노드 추가 제거 가능

2. 영속 모드

- 리액트는 요기서도 작동 가능
- appendChild와 같은 메서드 제공 ㄴㄴ
- _부모 트리를 복제하고 항상 최상위 하위를 대체하는 호스트 환경을 위한 모드_
- _호스트 트리 수준의 불변성은 멀티 스레딩을 쉽게 만든다_

리액트 사용자는 위 모드에 대해 고민할 필요 ㄴㄴ

> _전 React가 단순히 한 모드에서 다른 모드로 전환하는 어댑터가 아니라는 것을 강조하고 싶습니다. 이 유용성은 저수준 뷰 API 패러다임과 교차합니다._

## React Element

호스트 환경에서 호스트 객체(such as DOM Node) 제일 작은 구성요소다.
React에서 제일 작은 구성요소는 React Element다.

```js
// JSX는 아래 오브젝트를 만들기 위한 편의구문입니다.
// <button className="blue" />
{
  type: 'button',
  props: { className: 'blue' }
}
```

React ELement는 가볍고 호스트 객체를 직접 관여하지 않음. 걍 화면에 그리고 싶은 정보만 들어 있음.

호스트 객체처럼 리액트 엘리먼트도 트리로 구성될 수 있음.

```js
// JSX는 아래 오브젝트를 만들기 위한 편의구문입니다.
// <dialog>
//   <button className="blue" />
//   <button className="red" />
// </dialog>
{
  type: 'dialog',
  props: {
    children: [{
      type: 'button',
      props: { className: 'blue' }
    }, {
      type: 'button',
      props: { className: 'red' }
    }]
  }
}
```

React Element는

- **영속성을 가지지 않는다. 즉, 매번 새로 만들어지고 버려진다.**
- 불변이다.
  - 자식이나 prop 직접 수정 불가.
  - 다른 렌더링을 하려면 새로운 react 엘리먼트 트리를 생성한다.

> 리액트 엘리먼트는 영화의 프레임.
> 매 순간 어케 보여야되는지 파악하고 변경되지 않는다.

## 진입점

컨테이너 호스트 객체 내부에 특정 리액트 엘리먼트 트리를 렌더링할 수 있게 해주는 API

예컨대 ReactDOM의 진입점은 ReactDOM.render 함수

```js
ReactDOM.render(
  // { type: 'button', props: { className: 'blue' } }
  <button className="blue" />,
  document.getElementById('container')
);
```

위 코드는 "React야 domContainer 호스트를 트리를 reactElement와 같게 만들어줘." 와 같은말.

- 위 코드에서 type("button")을 보고 호스트 객체를 생성 및 속성 설정.
- 이 때 children을 가지고 있다면, 첫 렌더링에 재귀적으로 호스트 객체 생성

...

## 재조정

ReactDOM.render()가 두 번 같은 컨테이너에 호출되면?

```js
ReactDOM.render(
  <button className="blue" />,
  document.getElementById('container')
);

// ... 나중에 ...

// 호스트 객체를 교체해야 할까요
// 아니면 기존 객체에 속성만 교체하면 될까요?
ReactDOM.render(
  <button className="red" />,
  document.getElementById('container')
);
```

React의 목표는 **주어진 React 엘리먼트 트리와 호스트 트리를 일치시키는 것**
새로운 정보의 응답으로 호스트 객체 트리에 **어떤** 작업을 할지 파악하는 프로세스를 **재조정** 이라고 함

어떤 작업에는 2가지가 있다.

1. 기존트리 날리고 새로운 호스트 객체 만들기

- 근데 이 방법은 느리고 포커스, 선택, 스크롤 상태 등 중요한 정보 잃어버림.

2. (그래서) 기존트리 유지하면서 호스트 객체 변경하기

```js
// 1. 새로운 호스트 객체 생성
let domContainer = document.getElementById('container');
// 트리를 날립니다.
domContainer.innerHTML = '';
// 새로운 객체 트리를 만듭니다.
let domNode = document.createElement('button');
domNode.className = 'red';
domContainer.appendChild(domNode);

// 2. 기존 호스트 객체 변경
let domNode = domContainer.firstChild;
// 기존 호스트 객체를 변경합니다.
domNode.className = 'red';
```

위 선택을 하기 위해서는 **리액트 엘리먼트는 매번 다르지만 같은 호스트 객체라는 것을 어케 알까?**

- 엘리먼트 타입이 트리의 같은위치에 있고 이전과 일치하면 기존 호스트 객체 다시 사용

- `<button>`이 **같은위치에** 있으면 button을 다시 렌더링.
- 즉, button 호스트 객체를 가지고 있는데 다시 만들 필요 없음.
  - 여기서 type외의 속성만 바꿔치기 해주면됨.

같은 휴리스틱 알고리즘이 다음 자식들에 대해서 반복.

## 조건부 렌더링

갱신마다 동일 위치의 엘리먼트 타입이 일치할 때만 리액트가 호스트 객체를 재사용한다면.. 조건부 렌더링은 어떻게할까?
그러니까 조건부 렌더링때는 위치가 달라질 수도 있는데, 사실 동일한 컴포넌트를 렌더링하는 경우가 많다. 하지만 위치가 달라졌으므로 재사용하지 못하고 기존 호스트 객체는 버려지고 불필요하게 새로 만드는 경우가 있을거다. 이걸 리액트가 어케 해결했는지 보자.

```js
// 첫 렌더링
ReactDOM.render(
  <dialog>
    <input />
  </dialog>,
  domContainer
);

// 두 번째 렌더링
ReactDOM.render(
  <dialog>
    <p>I was just added here!</p>
    <input />
  </dialog>,
  domContainer
);
```

이걸 위 예제대로 비교해보자.

- dialog -> dialog: 재사용 가능? ㅇㅇ 타입 일치해
  - input -> p: 재사용 가능? ㄴㄴ 타입 불일치
    - input 삭제 후, p를 생성하여 추가
  - none -> input: input 호스트 객체 새로 생성

그래서 `<input>`은 다시 생성된다.

**사실 input이 p를 대체하지 않고 그냥 이동하면 된다.**
문제에 대한 해결책은 위치만 맞춰주면 된다.

```js
function Form({ showMessage }) {
  let message = null;
  if (showMessage) {
    message = <p>I was just added here!</p>;
  }
  return (
    <dialog>
      {message}
      <input />
    </dialog>
  );
}
```

JSX 객체로 살펴보자

```js
function Form({ showMessage }) {
  let message = null;
  if (showMessage) {
    message = {
      type: 'p',
      props: { children: 'I was just added here!' },
    };
  }
  return {
    type: 'dialog',
    props: {
      children: [message, { type: 'input', props: {} }],
    },
  };
}
```

children에 message와 input 타입을 가진 호스트 객체가 있다.
이렇게 하면 위치가 바뀌지 않고, 매번 동일한 위치에서 엘리먼트 타입을 비교하여 재사용 여부를 리액트가 판단할 수 있다.

## 리스트

위 방법은 자식들의 위치가 정적이고 순서를 바꾸지 않는 경우에만 제대로 동작한다.
위 예시에서는 message가 구멍이 될 수 있고, message뒤에만 input요소가 있고 다른 자식이 없다는 것을 알고 있다.

**동적리스트에서는 같은 순서인지 알 방법이 없다.**

```js
function ShoppingList({ list }) {
  return (
    <form>
      {list.map(item => (
        <p>
          You bought {item.name}
          <br />
          Enter how many do you want: <input />
        </p>
      ))}
    </form>
  );
}
```

여기서 리스트가 재정렬 된다고 해보자.
**리액트는 아이템의 name이 변경됐구나~만 알지 엘리먼트를 이동시켜야 하는지 절대 모른다.**

그래서 위 코드는 다음과 같이 동작한다.

```js
for (let i = 0; i < 10; i++) {
  let pNode = formNode.childNodes[i];
  let textNode = pNode.firstChild;
  textNode.textContent = 'You bought ' + items[i].name;
}
```

**그래서 순서 변경이 아닌 갱신을 한거다.**
이렇게 하면 버그가 발생 할 수 있다.
정렬이 되고 나서 실제로 참조해야될 객체를 사용하지 않고 다른 객체를 수정하기 때문이다.

**그래서 React는 Key prop을 요구하기로 했다.**

- key는 렌더링할 때마다 _아이템의 위치가 다른 곳에 있어_ 를 알려준다.

예컨대, `<p key="42">`를 본다면,

- 42번이 form 내부에 있었는지 검사
  - form의 자식 순서가 바껴도 동작한다.
- 같은 key를 가지는 이전 호스트 객체를 재사용하고 sibling 순서를 재정렬

> key는 동일 레벨(sibiling)내에서만 유효.
> 다른 부모의 자식과 key는 연관 없음.

## 순수성

100% 순수성을 갖지 못해도 괜찮다. React에서 멱등성이 순수성보다 훨씬 중요하다.

## 재귀

컴포넌트는 함수다. 리액트는 컴포넌트를 호출하며 string type의 엘리먼트(리액트 컴포넌트가 아닌, tag name을 가진 DOM node)를 찾을 때까지 재귀호출한다. 그래서 eslint를 사용하면 컴포넌트 이름을 대문자로 하라고 하는데, 이유는 string type의 엘리먼트와 React Component를 구분하기 위함이다.

```js
console.log(<form />.type); // 'form' 문자열
console.log(<Form />.type); // Form 함수
```

예를 들어 다음과 같은 코드를 호출한다면..

```js
ReactDOM.render(
  {
    type: Form,
    props: {
      isSubmitted: false,
      buttonText: 'OK!',
    },
  },
  document.getElementById('root')
);
```

위 코드는 Form -> Button -> button 순으로 재귀호출한다.

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

왜냐하면 타입이 컴포넌트인 트리를 최종적으로 뭘 그려야할지 알아야 하기 때문이다. 이 때 재귀호출하며 해당 위치의 엘리먼트 타입이 변경됐거나 key가 변경되면 리액트는 기존 호스트 객체를 버리고 새로 만든다.

## 제어의 역전

- **왜 직접 컴포넌트를 호출하지 않을까?**
- Form()이 아니라 <Form /> 일까?

React가 컴포넌트에 대해 알고 있는 게, 재귀적으로 호출한 결과인 React Element Tree만 보는 것보다 효율적으로 처리할 수 있다.

```js
// 🔴 React는 Layout이나 Article이 존재하는지 모릅니다.
// 컴포넌트를 직접 호출합니다.
ReactDOM.render(Layout({ children: Article() }), domContainer);

// ✅ React는 Layout과 Article의 존재를 알게 됩니다.
// React가 컴포넌트를 호출합니다.
ReactDOM.render(
  <Layout>
    <Article />
  </Layout>,
  domContainer
);
```

위 코드는 제어의 역전의 전형적인 예시다.

개발자가 아닌 React가 컴포넌트 호출 제어권을 가지게 되면 좋은점이 있다.

- 컴포넌트는 함수 이상의 역할을 한다

  - React는 상호작용에 대한 응답(prop 이나 state 변경과 같은..)으로 UI 트리를 렌더링한다.
  - 컴포넌트를 개발자가 직접 호출한다면 이 기능을 직접 구축해야한다.

- 컴포넌트 타입으로 재조정

  - 리액트가 컴포넌트를 호출한다면 트리의 개념구조를 더 많이 알려줄 수 있다.
  - `<Feed>` 컴포넌트가 다른 컴포넌트로 옮겨졌을 경우, 호스트 객체를 재사용하지 않는다.
  - 이 때 Feed의 모든 상태는 증발하고 호스트 객체가 생성된다.
  - 또한 트리의 `<input>`의 위치가 우연히 일치하더라도 <PasswordForm> 과 <MessangerChat>사이에서 입력상태 유지하고 싶진 않을거다

- 리액트가 재조정을 지연할 수 있다.
  - 브라우저가 컴포넌트 호출 사이에 일부 작업을 하게되면, 큰 컴포넌트 트리를 리렌더링하더라도 [메인스레드를 멈추지 않을 수 있다.](https://reactjs.org/blog/2018/03/01/sneak-peek-beyond-react-16.html)

## 지연 평가

```js
// (2) 나중에 계산됩니다.
eat(
  // (1) 먼저 계산됩니다.
  prepareMeal()
);
```

위와 같이 함수를 직접 호출한다면 예상 못한 문제가 발생할 수 있지만, 함수 대신 컴포넌트로 표현하면 JS 어딘가에서 사용되기 전까지 실행되지 않는다.

리액트는 비교적 순수하지만, 화면에 나타나지 않으면 실행할 필요가 없다.

```js
function Story({ currentUser }) {
  // return {
  //   type: Page,
  //   props: {
  //     user: currentUser,
  //     children: { type: Comments, props: {} }
  //   }
  // }
  return (
    <Page user={currentUser}>
      <Comments />
    </Page>
  );
}

function Page({ user, children }) {
  if (!user.isLoggedIn) {
    return <h1>Please log in</h1>;
  }
  return <Layout>{children}</Layout>;
}
```

하지만 Page 컴포넌트가 조건에 따라 함수가 일찍 종료된다면..?
`Commnets()`로 개발자가 직접 호출했다면 안그려져도 되는데, 즉시 실행될거다.

```js
// {
//   type: Page,
//   props: {
//     children: Comments() // 항상 실행됩니다!
//   }
// }
<Page>{Comments()}</Page>
```

하지만 React Element라면

```js
// {
//   type: Page,
//   props: {
//     children: { type: Comments }
//   }
// }
<Page>
  <Comments />
</Page>
```

컴포넌트로 작성시 리액트가 호출시점을 결정한다.
불필요한 렌더링을 피할 수 있고 코드의 취약성을 줄일 수 있다.

## 상태

호스트 객체는 포커스, 선택, 입력 등 모든 종류의 지역 상태를 가질 수 있다. 동일한 UI를 렌더링 하면 이 상태를 유지한다. 또한 엘리먼트가 다른 위치로 이동되었을 때 예측대로 파괴되야한다.

## 일관성

재조정은 non blocking 작업 청크로 분할하더라도, 단일 동기 흐름에 의해 호스트 트리 작업 수행해야한다. 이유는,

- 사용자가 덜 만들어진 UI를 보지 않아야함
- 사용자가 볼 수 없는 중간상태에 대해 불필요한 레이아웃/스타일 재계산 수행하지 않도록 함

위 이유 때문에 리액트는 모든 작업을 _렌더링 phase_ , _commit phase_ 로 나눈다.

- 렌더링 phase는 리액트가 컴포넌트를 호출하고 재조정한다.
  - 중단해도 안전하고 앞으로는 비동기로 동작한다
- 커밋 phase는 동기적으로 리액트가 호스트 트리를 손보는 단계다.

[lifecycle and phase](http://projects.wojtekmaj.pl/react-lifecycle-methods-diagram/)

## 가공되지 않은 모델

리액트는 세밀한 갱신을 위한 반응형 시스템을 사용하지 않는다. 최상단에 있는 모든 갱신은 영향을 받은 컴포넌트만 갱신하는게 아닌 재조정을 발생시킨다. 세밀한 수신자를 설정하는건 시간 소비가 크다.

리액트의 핵심 설계 원칙 중 하나는 로우 데이터로 동작하는 것이다. 네트워크로 JS 객체를 수신받았을 떄, 별다른 처리 없이 컴포넌트에 주입할 수 있다. 리액트 렌더링은 O(모델크기)가 아닌 O(뷰 크기) 복잡도를 가진다. 뷰 크기는 react-window 라이브러리를 통해 줄일 수 있다.(인스타 웹을 보면 이렇게 하고 있다.)

## 일괄 작업

여러 컴포넌트가 같은 이벤트에 대한 응답으로 상태를 변경하고 싶을 수 있다. 아래 예제를 보자.

```js
function Parent() {
  let [count, setCount] = useState(0);
  return (
    <div onClick={() => setCount(count + 1)}>
      Parent clicked {count} times
      <Child />
    </div>
  );
}

function Child() {
  let [count, setCount] = useState(0);
  return (
    <button onClick={() => setCount(count + 1)}>
      Child clicked {count} times
    </button>
  );
}
```

이벤트가 dispatch 되면 자식의 onClick이 먼저 호출되고, 자식의 setState 호출 -> 부모 onClick의 setState 호출.
이 때 setState는 자식 컴포넌트를 두번 렌더링 해야한다.

```js
*** React의 브라우저 클릭 이벤트 진입 ***
Child (onClick)
  - setState
  - re-render Child // 😞 불필요합니다
Parent (onClick)
  - setState
  - re-render Parent
  - re-render Child
*** React의 브라우저 클릭 이벤트 종료 ***
```

**이러한 낭비를 줄이기 위해, 이벤트 핸들러 사이에서 일괄 갱신을 한다.**
그래서 setState는 즉시 렌더링하지 않고 batch로 동작한다.

## 호출 트리

JS 엔진은 a함수가 b를 호출하고 b는 c를 호출한다면, 호출 스택에는 [a,b,c]로 쌓인다. 각 함수가 종료될 때마다 호출스택에서 제거된다. 하지만 리액트는 내부적으로 현재 렌더링하고 있는 컴포넌트를 기억하기 위해 자체 호출 스택이 있다. [App, Page, Layout, Article /** 현재 렌더링하고 있는 부분 **/]

이 자체 호출 스택은 상호작용하기 위해 계속 살아 있어야 한다. 리액트에서 이것을 호출트리라고 표현한다. 렌더링이 끝나도 호출트리는 파괴되지 않고 [어딘가에](https://medium.com/react-in-depth/the-how-and-why-on-reacts-usage-of-linked-list-in-fiber-67f1014d0eb7) 유지해야한다.

호출 트리 프레임은 재조정 규칙에서 필요할 때만 지역상태와 호스트 객체가 파괴되는데, 이 프레임은 fiber에 의해 참조되고 있다.

> fiber는 지역상태가 실제로 있는 곳이다. 지역 상태가 업데이트 될 때 React는 해당 파이버의 자식들을 재조정하고 해당 컴포넌트를 호출한다.

## Effect

리액트 컴포넌트는 렌더링 중에(특히 render phase는 부작용이 없어야 한다.) 볼 수 있는 부수효과를 가져선 안된다고 했다. 하지만 때때로 부수효과가 필요하다. 포커스를 관리하던가, 특정 데이터 소스를 구독하고 싶던가 등등..

React는 Effect를 선언하면 된다.

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

React는 브라우저가 화면을 리페인트 할 때까지 실행효과를 연기한다. 이는 [상호작용 시간](https://calibreapp.com/blog/time-to-interactive/)과 [첫번째 페인트](https://developers.google.com/web/tools/lighthouse/audits/first-meaningful-paint)를 방해하지 않기 때문에 좋다. (Layout Effect Hook은 해당 동작읋 선택 해제하고 동기식으로 작업을 수행한다.)

## Q&A

_재조정_

Q. 재조정이란?
A. 새로운 정보에 대한 응답(props나 state 변경으로 인한 re-render)으로 호스트 객체 트리에 어떤 작업을 할지 파악하는 프로세스. 왜냐하면 리액트는 주어진 React element tree와 호스트 트리를 일치시켜야 하기 때문.

Q. 재조정시 파악해야하는 어떤 작업이란?
A. 기존트리를 날리고 새로운 호스트 객체를 만들지, 기존 트리를 재활용하여 호스트 객체를 변경할지..

Q. 위 선택에 대한 기준은?
A. 이전 트리와 새롭게 받은 트리를 비교할 때 해당 위치에 동일한 엘리먼트 타입이라면 호스트 객체를 재활용. 아니면 호스트 객체 새로 생성. 왜냐하면 굳이 새로운 객체를 매번 만들어가며 큰 비용이 드는 작업을 할필요가 없기 때문에

_조건부 렌더링_

Q. 그럼 조건부 렌더링의 경우 매번 새로운 객체를 생성할 수도 있을 텐데..
A. 그래서 조건부 렌더링의 경우 변수를 통해 위치를 유지시켜줘야한다.

_리스트_

Q. 어떤 리스트가 있을 때 재정렬 되면 위의 재조정 조건대로라면.. 기존 호스트 객체에서 상태만 바꾸게된다. 이렇게 되면 올바르지 않은 객체를 참조하여 값을 바꾸게된다. 사실 호스트 객체 이동만 시키면 되는데, 리액트는 어떤 해결책을 사용했는가?
A. 컴포넌트에 unique한 키를 할당하여, 기존 호스트 객체의 위치만 변경할 수 있다.

_재귀_

Q. 리액트의 진입점인 ReactDOM.render에서부터 호출할텐데 그 이후부터는 어떤식으로 호출되는지 아는가?
A. 리액트가 최종적으로 어떤 컴포넌트 트리를 그려야할지 알아야 하기 때문에 재귀호출하며 재조정한다. 리액트의 목표는 주어진 엘리먼트 트리와 호스트 트리를 일치시키는 것이기 떄문이다.

_제어의 역전_

Q. 위에서 설명한게 제어의 역전인데, 왜 리액트가 직접 컴포넌트를 호출할까? 개발자가 Form() 이렇게 호출하면 안되는가?
A. 리액트가 컴포넌트에 대해 알고 있는 게 재귀적으로 호출한 결과인 리액트 엘리먼트 트리만 보는 것보다 효율적으로 처리할 수 있다.

- 리액트는 상호작용에 대한 응답(prop이나 state 변경)으로 UI 트리를 렌더링하는데, 개발자가 직접 호출한다면 이 응답에 대한 UI 렌더링을 직접 구축해야한다
- 리액트가 컴포넌트 호출시 트리의 개념구조를 더 많이 알 수 있는데, **어떤 컴포넌트 렌덜이을 다른 페이지로 옮길 경우**, 호스트 객체를 재사용하지 않고 새로 생성한다. 이렇게 해서 해당 컴포넌트의 상태는 증발하여 새로 사용할 수 있다.
- 지연평가를 할 수 있다. 개발자가 직접 컴포넌트를 호출한다면 안그려도 되는 컴포넌트를 호출해야한다. 하지만, 리액트 엘리먼트를 사용한다면 컴포넌트는 필요할 때 호출된다.
