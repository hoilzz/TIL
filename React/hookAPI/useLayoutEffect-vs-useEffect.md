# useEffect vs useLayoutEffect

[useeffect-vs-uselayouteffect](https://kentcdodds.com/blog/useeffect-vs-uselayouteffect) 번역

## useEffect

`componentDidMount`, `componentDidUpdate`, `componentWillUnmount`를 useEffect로 대체 가능하다.

**the one catch** 는 리액트가 너의 컴포넌트를 렌더링하고 effect callback이 브라우저 페인팅을 block하지 못한다는 것을 확신한 **후에** 실행한다. 렌더링 후에 동기적으로 실행되는 클래스컴포넌트의 cmd, cmu와 다르다. 이 방식이 더 퍼포먼스적으로 좋다.

그러나 이펙트가 DOM(via DOM Node ref)을 변경시키고 effect가 그것을 변경시키고 렌더링 하는 시간사이에 DOM 변경이 DOM node의 appearance를 변경시킬거라면, **useEffect를 사용하지 마라.** 이것은 `useLayoutEffect`를 사용해야한다. 그렇지 않다면 유저는 DOM 변경이 적용될 때, 깜빡이는 것을 볼 수 있다. **useEffect를 피하고 useLayoutEffect를 사용해야한다**
