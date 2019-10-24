# 어떤 상태에 대해 redux state에 둘지 component state로 둘지의 기준은?

[https://github.com/reduxjs/redux/issues/1287](https://github.com/reduxjs/redux/issues/1287)

Use React for ephemeral state that doesn't matter to the app globally and doesn't mutate in complex ways. For example, a toggle in some UI element, a form input state. Use Redux for state that matters globally or is mutated in complex ways. For example, cached users, or a post draft.

Sometimes you'll want to move from Redux state to React state (when storing something in Redux gets awkward) or the other way around (when more components need to have access to some state that used to be local).

The rule of thumb is: do whatever is less awkward.

글로벌하게 앱에 중요하지 않고 짧게 지속되는 상태는 React에서 유지하자. 복잡한 방식으로 변경하지 말자.
예를 들어, UI element를 토글한다거나 form input state 같은거가 해당된다.

글로벌하게 중요하거나 복잡한 방식으로 변경되는 상태는 리덕스를 사용하자.. 예를 들어 캐시된 유저 or draft post하기

가끔 리덕스 상태를 리액트 상태로 옮기고 싶을거다.(리덕스에서 무언가를 저장하는게 어색할 경우) or the 다른 방법을 하고싶은 경우 (많은 컴포넌트가 로컬에서 사용되는 상태에 접근해야 할 때)

경험의 규칙은 다음과 같다 : 어색하지 않은걸로 뭐든 해라.
