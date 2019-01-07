# How should I split my logic between reducers and action creators? Where should my “business logic” go?

정답은 없다.
- 누구는 fat action creater를 선호한다. reducer는 단순히 action에서 데이터만 받고 blindly merge 한다.
- 딴사람은 action을 가능한 작게 유지하고, action creator에도 `getState()` 사용을 최소화한다.

reducer로 로직을 더 넣는 것은 잠재적인 이득이 있다. action type은 좀 더 __semantic__ 해야하고 의미 있어야 한다.
(예를 들어 `SET_STATE` 대신에 `USER_UPDATED`).
게다가 리듀서에서 더 로직을 적용하면 time travel debugging이 더 많은 영향을 받는다.

아래 코멘트는 이분법을 멋지게 요약했다:

> 문제는 action creator에, 리듀서에 무엇을 넣는지다.
> 선택지는 fat and thin action object다.
> 1. 만약 모든 로직이 action creator에 있다면, state를 업데이트 하기위한 fat action objects를 가질거다.
> 대신 리듀서는 pure, dumb, add-this, remove that update these function이 될 것이다.
> 리듀서는 구성하기 쉬워진다. 하지만, 비즈니스 로직은 그곳에 많지 않다.
> 2. 만약 reducer에 로직이 많아진다면, nice, thin action object를 가진다.
> 한 장소에서(리듀서) 데이터 로직이 대부분이고, 리듀서는 구성하기 어려워진다. 왜냐하면 다른 브랜치의 정보가 필요하기 때문이다.
> large reducer or 추가 인자를 갖는 리듀서를 가지게 된다.

## 요약

2가지 극단에서 밸런스를 찾아라.