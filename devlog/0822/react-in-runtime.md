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

React야 domContainer 호스트를 트리를 reactElement와 같게 만들어줘.

React는 reactElement.type을 보고

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
호스트 객체 트리에 어떤 작업을 해야할지 파악하는 프로세스가 `reconcilation`이다.

작업 방식은 2가지가 있다.

1. 기존 트리 날려버리고 새로운 트리 만들기

- 작업이 느리고, focus/선택/스크롤 상태 등 중요한 정보를 잃게 된다.

2. 기존 트리 재활용하여 변경하기

그래서 위 두가지 방식중 뭘해야 할지 결정해야 한다.

근데 리액트 엘리먼트는 매번 다르지만 같은 호스트 객체라는 걸 어케 알까?

**트리의 같은 위치에 있는 엘리먼트 타입이 이전 렌더링과 다음 렌더링 사이에 일치하면 기존 호스트 객체를 다시 사용한다**
(이전 렌더링의 _같은 위치에_ _엘리먼트 타입과 같다면_ 재사용한다.)

## 조건

위 말대로라면, 갱신마다 동일 위치의 엘리먼트 타입이 같을 때만 호스트 객체를 재사용한다면

조건부 컨텐츠 렌더링은 어떻게 하는걸까? (위 말대로라면 조건부 컨텐츠 렌더링은 매번 새로운 호스트 객체를 생성할거다. 그럴 필요가 없을 경우가 많을 텐데..)

## FAQ

<!-- --------------------------- reconciliation ---------------------------- -->

Q. 재조정이란?
A. 호스트 객체 트리에 어떤 작업을 해야할지 파악하는 프로세스가 `reconcilation`이다.

Q. 재조정에는 어떤 방식이 있는가?
A. 기존 트리 날리거나, 기존 트리 재활용하기

Q. 위 경우는 각각 어떤 경우에 발생하는가?
A. 같은 위치에 엘리먼트 타입이 같다면 재사용. 아니면 기존 호스트 객체를 버리고 새로 만든다.
