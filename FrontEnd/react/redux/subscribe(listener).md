# subscribe(listener)

Adds a change listener. action이 dispatch될 때마다 호출될 것이다. 그리고 state tree의 부분이 잠재적으로 변경될 것이다. 그러고나서 callback 내부에 current state tree를 읽기 위해 `getState()` 호출 해봐.

`dispatch()`를 호출할 수 있다 from a change listener.
1. 리스너는 user action에 대한 반응 or 특정 환경(store가 특정 field를 가질 때 action을 dispatch하는)에서 `dispatch()`만 호출해야만 한다. 어떤 조건 없이 `dispatch()`를 호출하는 것은 기술적으로 가능하지만, every `dispatch()`가 listener를 다시 트리거할 때 무한 루프 될 수 있다.
