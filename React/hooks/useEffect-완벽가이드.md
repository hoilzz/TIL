# useEffect 완벽가이드

[useEffect 완벽가이드 번역](https://rinae.dev/posts/a-complete-guide-to-useeffect-ko#tldr-too-long-didnt-read---%ec%9a%94%ec%95%bd)

내맘대로 요약해보기

## TLDR;

Q. useEffect로 componentDidMount 동작 흉내내기 가능?
A. 완전히 같진 않지만 가능 `useEffect(fn, [])`. 얘는 componentDidMount나 다른 라이프사이클 메서드와 다르다는 점을 인지하자. 생산적으로 접근하기 위해 "이펙트 기준으로 생각하기", 이 멘탈 모델은 동기화를 구현하는 것에 가깝다. 라이프사이클 메서드 이벤트에 응답하는 것과는 다르다.

Q. useEffect의 두번쨰 인자인 배열은 뭐지?
A. `[]`는 이펙트에 리액트 데이터 흐름에 관여하는 어떤 값도 사용하지 않겠다느 뜻.(그래서 한번 적용되어도 안전하다는 뜻). 잘못된 방식으로 의존성 체크를 생략하는 것보다 의존성을 필요로 하는 상황을 제거하는 몇가지 전략(`useReducer`, `useCallback`)을 익히자.

Q. 이펙트 의존성 배열에 함수 가능할까?
A. [이 글을 주목하자](https://rinae.dev/posts/a-complete-guide-to-useeffect-ko#tldr-too-long-didnt-read---%ec%9a%94%ec%95%bd). 만약 useEffect 내부에서 prop이나 컴포넌트 내부 state를 이용하여 함수를 호출하는 동작이 있다고 하자. 이 떄 useEffect의 의존성 배열이 [] 라면, 내부 prop이나 state가 변경되더라도 함수 내부에서 사용되는 prop이나 state는 절대 변경되지 않는다. 왜냐하면

요약하면,
React data flow(prop, state)에 있고 hook 내부에서 사용되는 모든 값을 포함해야한다.
그래서 이걸 해결할 방법은 두 가지다.

1. 해당 함수를 useEffect 내부로 가져와서 useEffect에 함수에서 사용하는 prop, state를 dependecy list에 추가
2. useCallback에 함수 선언하여, 함수에서 사용하는 prop, state dependency list에 추가. useEffect에서는 함수만 디펜던시로 추가.

Q. 이펙트 안에서 이전 state나 prop 참조할때
A. 보통 비동기 함수 내에서 state를 사용할 때, 비동기 호출이 일어나거나 처리 되기 전에 state가 변경되더라도, 비동기 함수내에서는 호출 당시의 state를 바라본다. 이렇게 동작하는 이유는 prop이나 state가 변경되지 않는다고 가정하여 코드로 인한 버그를 방지할 수 있기 때문이다. 여튼 우리는 최신값이 필요한데 이걸 해결할 방법은 ref를 통해 값을 직접 참조하는 것이다. 코드샌드박스에 간단히 만들어보았다. [async-fn-use-component-state](https://codesandbox.io/s/async-fn-use-component-state-642qo)
