# Portals

Portal은 부모 컴포넌트의 DOM 계층 밖에 존재하는 DOM node 에 children을 렌더링하는 first-class 방식을 제공한다.

```javascript
ReactDOM.createPortal(child, container)
```

첫번쨰 인자 `child`는 렌더링 가능한 React child(element, string or fragment)다. 두번째 인자는 DOM element다.

## 예제

보통 컴포넌트의 render 메서드에서 요소 반환시, 근처 부모 노드의 자식으로써 DOM이 마운트된다.

```javascript
render() {
    // React는 new div를 마운트하고, 그거 안에 children을 렌더링한다.
    render() {
        return (
            <div>
                {this.props.children}
            </div>
        )
    }
}
```

근데 DOM 내의 다른 위치(DOM의 자식 ㄴㄴ)에 자식 넣는 것이 유용하다.

```javascript
render() {
    // React는 new div를 생성하지 않는다. 이것은 children을 'domNode' 안에 렌더링한다.
    // 'domNode'는 유효한 DOM node다.
    return ReactDOM.createPortal(
        this.props.children,
        domNode,
    );
}
```

여기서 domNode는 React에서는, `<ReactPortal target="~~Element{...}">`로 표현된다. 말 그대로 DOM element가 된다.

portals의 일반적인 사용 사례는 부모 컴포넌트가 `overflow: hidden`이나 `z-index`를 가지지만, 자식이 컨테이너에서 시각적으로 **이탈해야 하는** 경우다. 예를 들어 **Dialog, hovercard, tooltip**이 있다.

## Portal을 통한 이벤트 버블링

portal은 DOM tree의 어디에나 존재할 수 있다. 또한, 일반 React 자식처럼 동작한다. context 같은 기능은 DOM 트리의 위치에 상관없이 **portal이 여전히 트리 내에 존재하기 때문에 동일하게 동작**한다. 이벤트 버블링도 마찬가지로 트리 내에 포함되기 때문에 동일하게 동작한다. **portal 내부에서 시작된 이벤트는 DOM 트리에서 조상이 아니더라도 React 트리에 있는 조상에 전달된다.**

[![Edit mozk8p1nlx](https://codesandbox.io/static/img/play-codesandbox.svg)](https://codesandbox.io/s/mozk8p1nlx)


**상위 컴포넌트의 portal에서 이벤트 버블링을 캐치하면 portal에 본질적으로 의존하지않는 보다 유연한 추상화 개발을 할 수 있습니다.** 예를 들어 <Popup /> 컴포넌트를 렌더링하면 **상위에서 portals를 사용하여 구현하였는 지 여부에 관계없이 이벤트를 캡쳐할 수 있습니다.**

## Summary

Portal은 부모 컴포넌트의 DOM 계층 밖에 존재하는 DOM node 에 children을 렌더링하는 first-class 방식을 제공한다. 예를 들어 Dialog, hover-card, tooltip에 주로 사용된다.

## ..

이걸 팝업에 활용한다고 생각해보자. 팝업을 띄워야하는 인터랙션을 가진 컴포넌트에서 portal로 생성된 컴포넌트를 로드한다. 동시에 그 컴포넌트의 props.children으로 전달할 팝업 내용을 가진 컴포넌트를 로드한다. 즉, `<Popup />`은 추상화된 모달 컴포넌트다. 그 안의 들어갈 내용은 props를 통해 분기를 하든, 다른 컴포넌트를 부르든 방법을 통해 유연하게 컴포넌트를 사용하면 될거 같다.
