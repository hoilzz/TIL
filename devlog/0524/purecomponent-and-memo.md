# pure component and memo

회사에서 React.memo를 통해 컴포넌트를 메모이징 하거나, useCallback, useMemo를 통해 콜백함수, 컴포넌트 등을 메모이징 하고 있다. 너무 무분별하게 메모이징 하는거 아닌가 싶은 와중에 해당 트윗에 대해 발견했다.

[note about pure component and memo](https://twitter.com/ryanflorence/status/1131976648159424512)

PureComponent와 memo를 사용할 때 트레이드오프에 대해 알아야 할점.

1. boot time과 첫 렌더가 느려진다.
2. 업데이트가 필요한 모든 인터랙션이 느려진다.

(소수의) 느린 인터랙션을 최적화 하자, 나머지를 무의식적으로 최적화 하지 말자.

---

Q. boot-time tradeoff란? 첫 렌더 때 shallow compare는 없지 않아?
A. (Dan) : 기술적으로 useMemo와 useCallback에서 값을 저장할 노드를 생성하고 내부 트리에 그것들을 attach할 때 시간을 사용한다.

**그 시간이 많이 사용되지 않지만 불필요할 때 필요 이상으로 작업시간이 많이 소요된다는 거다.**

Q. 그래서 useEffect 밖에서 그것들을 정의하기 위해 useCallback에 함수를 감싸는 것은 좋지 않은 아이디어인가?
[omit functions from list of dependencies](https://reactjs.org/docs/hooks-faq.html#is-it-safe-to-omit-functions-from-the-list-of-dependencies)

A. (Dan) : 나는 그것이 "좋지 않다" 라고 말한 적이 없다. over-analyze하지 말자. 정당한 이유가 있으면 꼭 사용해라!

Q. PureComponent의 trade-off 란? 기본적으로 shallow prop 비교는 하지 않니?
A. (Ryan) : (PureComponent의 trade-off는) 더 할 게 많잖아 ? 적어도 새로운 함수에 대해 메모리에 할당해야 하니까

?. 렌더 내에서 함수를 생성하는데 측정가능한 오버헤드가 있다는 잘못된 생각에 대해 1년 동안 경고 했었는데, now you say this with a straight face?

A. (Ryan) : 정확히 내가 말하고 싶은거다. 너가 boot time or render time에 할 수 있는 중요하지 않은 두가지..(?)

---

대화 뒤쪽의 Ryan이 말하는게 뭔말인지 잘 모르겠다..

PureComponent 나 React.memo를 자식 컴포넌트의 불필요한 리렌더를 막기 위해 사용했다.
