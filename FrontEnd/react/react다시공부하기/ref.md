# ref

ref가 뭔지 언제 어떻게 사용하면 좋을지 몰라서 번역해본다.

React data flow에서, `props`는 부모 컴포넌트가 자식 컴포넌트와 상호작용할 수 있는 유일한 방법이다. 자식 컴포넌트를 수정하기 위해, new props로 re-render할 수 있다. 근데, 일반적인 dataflow 말고 자식 컴포넌트를 수정해야 하는 경우가 있다. 수정될 자식 컴포넌트는 리액트 컴포넌트의 인스턴스가 될 수도 있고, DOM element일 수도 있다. 이 경우 둘다, 리액트는 escape hatch를 제공한다.

## when to use Refs

ref 사용하기 좋은 케이스

- focus, text selection, or 미디어 재생 관리하기
- 필수 애니메이션 트리거하기
- 서드파티 DOM library 통합하기

선언적으로 할 수 있는 작업에는 ref 사용을 피하자. 예를 들어, Dialog 컴포넌트에서 `open()`, `close()`, 메서드를 두는 대신 `isOpen` prop을 전달할 수 있다.

