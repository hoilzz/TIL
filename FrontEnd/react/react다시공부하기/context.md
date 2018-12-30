# Context

## React.createContext

```javascript
const {Provider, COnsumer} = React.createContext(defaultValue);
```

`{ Provider, Consumer }` 쌍을 생성하자. 리액트가 context `Consumer`를 렌더링할 때, 트리에서 가장 가깝게 매칭되는 `Provider`에서 현재 context 값을 읽는다.

*뭔트리?*

매칭되는 Provider를 가지고 있지 않을 때 `defaultValue` 인자는 Consumer에 의해 사용된다. `defaultValue`는 컴포넌트를 감싸지 않고 컴포넌트를 테스트할 때 도움이 된다. Note: `undefined`를 Provider 값으로 전달하면, `Consumer`는 `defaultValue`를 사용하지 않는다.

## Provider

```javascript
<Provider value={/* some value*/}>
```

consumer가 context change를 구독하도록 허용하는 react component.

`value` prop을 Provider의 자손인 Consumer가 전달받도록 허용한다. One Provider는 많은 Consumer에 연결된다. (1대다 관계인듯). Provider는 더 깊게 중첩된 값을 오버라이드 하기 위해 트리 내부에서 중첩될 수 있다.

## Consumer

```javascript
<Consumer>
  {value => /* context value로 뭔가 render */}
</Consumer>
```

context 변화를 구독하는 리액트 컴포넌트

Consumer 자식으로 함수가 필요하다. 함수는 현재 context value를 받고 React node를 리턴한다. 함수에 전달된 `value` 인자는 가장 가까운 Provider의 `value` prop과 동일할 것이다.