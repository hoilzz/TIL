# Should I dispatch multiple actions in a row from one action creator?

특별한 규칙은 없다. thunk와 같은 async middleware를 사용하는 것은 __multiple distinct but related action in a row를 dispatch__ 할 수 있다. (AJAX 요청의 진행을 나타내는 action dispatch, state 기반 조건부 action dispatch, update된 state 즉시 확인하기 등)

일반적으로 이러한 action들이 관련있지만 독립적인지, 실제로 1개의 action으로 표현되어야 하는지 물어봐라. 너의 상황에 맞춰서 만들어야하지만 reducer의 가독성과 action log의 가독성에 균형을 맞춰라. 예를 들어, 전체 new state tree를 포함하는 action은 reducer를 1줄짜리로 만들지만, 단점은 변경사항이 발생한 이유에 대한 history가 없으므로 디버깅이 어려워진다. 반면에, 만약 루프에서 action을 발생시켜서