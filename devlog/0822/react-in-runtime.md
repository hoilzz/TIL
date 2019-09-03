# react in runtime

리액트는 시간이 지남에 따라 변화할 수 있는 트리를 출력한다. 보통 이 트리는 UI를 표현하는데 쓰인다. 이것은 `호스트 트리`.

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

## 조건

## 배운거

## FAQ
