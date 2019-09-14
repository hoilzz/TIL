# 합성 컴포넌트 with hooks

[compound components with hooks](https://kentcdodds.com/blog/compound-components-with-react-hooks)

유용한 작업을 하기 위해 함꼐 동작하는 2개 이상의 컴포넌트를 가져야한다. 1개 컴포넌트는 parent고 다른건 child다. 목표는 더 표현적이고 flexible한 API를 제공하는 것이다.

```js
<select>
  <option value="value1">key1</option>
  <option value="value2">key2</option>
  <option value="value3">key3</option>
</select>
```

1개만 사용하려고 하면 작동하지 않는다. 이건 좋은 API다. 만약 compound component API를 가지지 못한다면 어떻게 해야할지 다음 코드를 보자.

```js
<select options="key1:value1;key2:value2;key3:value3"></select>
```

다른 방식도 있을 수 있지만 위 방식은 별로다. 위와 같은 API형태로 `disabled` attribute를 표현하려면 어떻게 할까? 여튼 별로다.

compound component API는 컴포넌트 간의 관계를 표현하기 좋은 방법이다.

이 컨셉ㅇ의 다른 중요한 측면은 **implicit state** 다. <select> 엘리먼트는 암시적으로 선택된 option에 대해 상태를 저장하고 children을 공유한다. 그래서 상태 기반하여 뭘 렌더링할지 정확히 알고 있다. 하지만 그 상태 공유는 암시적이다. 왜냐하면 상태에 접근할 수 있는 HTML code가 아무것도 없다.

이러한 우언칙을 이해하기 위해 합성 컴포넌트를 나타내는 리액트 컴포넌트를 보자. [예제](https://ui.reach.tech/menu-button/)인 ReachUI를 보자.

```js
function App() {
  return (
    <Menu>
      <MenuButton>
        Actions <span aria-hidden>▾</span>
      </MenuButton>
      <MenuList>
        <MenuItem onSelect={() => alert('Download')}>Download</MenuItem>
        <MenuItem onSelect={() => alert('Copy')}>Create a Copy</MenuItem>
        <MenuItem onSelect={() => alert('Delete')}>Delete</MenuItem>
      </MenuList>
    </Menu>
  );
}
```

이 예제에서 <Menu>는 공유된 암시적인 state를 수립한다. 각 컴포넌트는 state를 접근/공유할 수 있고 모두 암시적으로 수행된다. 이것이 너가 찾는 표현하는 API다.

이것을 가능하게 하는 방법은?

1. children을 React.cloneElement로 나타내기
2. React context 이용하기

여기서는 context를 이용하여 하 합성 컴포넌트 set을 만들어보자.

```js
function App() {
  return (
    <Toggle onToggle={on => console.log(on)}>
      <Toggle.On>The button is on</Toggle.On>
      <Toggle.Off>The button is off</Toggle.Off>
      <Toggle.Button />
    </Toggle>
  );
}
```

`.`을 이용했는데 이유는 이 컴포넌트들이 <Toggle> 컴포넌트의 static 프로퍼티로 추가됐기 때문이다.
합성 컴포넌트의 필수 요소는 아니라는 점을 알아두자.(위 예제 MenuComponent는 `.`안이용함) 걍 필자가 개인적으로 .으로 명시적 관계 표현하는거 좋아하는거임.

context와 hook을 이용한 합성 컴포넌트 [전체 구현체](https://codesandbox.io/s/9yp5p2z7yr?from-embed)를 보자.

상태를 저장하는 context와 상태를 업데이트하는 메커니즘을 만들었다
<Toggle> 컴포넌트는 나머지 리액트 트리에 context value를 제공하는 책임을 가진다.
