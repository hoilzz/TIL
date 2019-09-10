# React as a ui runtime

[react as a ui runtime](https://overreacted.io/ko/react-as-a-ui-runtime/)을 읽고..

위 글은 React를 Runtime 관점으로 이야기한 것이다. 이 글을 통해 React 프밍 모델을 깊이 있게 이해할 수 있다.

몰랐던 거, 인상깊었던 거(어떤게, 그리고 왜)를 작성해보고자한다.

## 호스트 트리

리액트는 **시간이 지남에 따라 변화할 수 있는 트리** 를 출력한다. 이 트리는 UI를 표현하는데 쓰인다. 이것은 '호스트 트리'다. 이 호스트 트리는 appendChild와 같은 명령형 API를 가진다.

React는 외부 상호작용, 네트워크 응답, 타이머 등 외부 이벤트에 대한 응답으로 복잡한 호스트 트리를 예측할 수 있게 조작하는 프로그램 작성시 유용하다.

## 호스트 객체

호스트 트리는 노드(호스트 객체)로 구성된다. 이 노드는 DOM 노드 같은거다.

## 렌더러

리액트 렌더러는 특정 호스트 환경과 통신하고 호스트 객체(such as 노드)를 관리.

렌더러는 2가지 모드를 가진다.

1.

## React Element

호스트 환경에서 호스트 객체(such as DOM Node)는 제일 작은 구성요소.
React에서 제일 작은 요소를 **React Element** 라고 한다.

리액트 엘리먼트는 호스트 객체를 그릴 수 있는 JS 객체다.

```js
// JSX는 아래 오브젝트를 만들기 위한 편의구문입니다.
// <button className="blue" />
{
  type: 'button',
  props: { className: 'blue' }
}
```

그리고 싶은 정보가 들어있음.

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

React 엘리먼트는 영속성을 가지지 않는다. 매번 새로 만들어지고 버려진다.
즉, React 엘리먼트는 불변이다. React 엘리먼트는 영화의 프레임이라 생각하자. 매 순간 어떻게 보여야되는지 파악하고 변하지 않는다.

## 조건

매번 갱신할 때마다 type이 일치할 때만 react가 호스트 객체를 재활용한다.

그럼 조건부 렌더링은..?
