# useRef는 hook의 디펜던시로 사용하면 안된다.

[ref.current를 디펜던시로 사용할 때 이슈](https://github.com/facebook/react/issues/14387)

요약하자면,

렌더링 전에 실제로 변경되었는지 (ref.current와 같은 mutable 값은 렌더링을 유발할 수 있다.) 보장할 수 없기 때문에 [ref.current](or any mutable field)를 디펜던시에 포함하는 것은 문제가 될 수 있다. React의 ref의 경우, 렌더링 후에 수정되므로 항상 뒤처진다.

hook의 Dependency는 top-down 리액트 데이터 플로우에 포함되는 값이어야한다. 예컨대 props, state, 이러한 값들을 통해 계산한것들.. Ref container도 괜찮다. (왜냐하면 얘들도 데이터 플로우를 통해 top-donw된 얘니까)

근데 ref.current를 디펜던시로 추가하는 건 말이 안된다. 동일한 이유로, window.myVaraible도 안된다. 이것이 업데이트 될 때, 리액트는 그것에 대해 모른다. 그리고 컴포넌트를 업데이트 하지 못한다.
