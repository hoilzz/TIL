# Store에 접근하기

리액트 리덕스는 컴포넌트가 action을 dispatch 하고 store에서 데이터 업데이트를 subscribe하도록 허용한다.

react-redux는 너가 사용하고 있는 스토어의 디테일한 부분과 그 스토어와 상호작용에 대해 세부사항을 추상화한다. 컴포넌트는 스토어의 디테일한 부분을 신경 쓸 필요가 없다. 또한 스토어를 직접 참조할 필요도 없다. react-redux는 스토어와 state가 connected component에 전파되는 디테일한 방식을 내부적으로 처리해준다. 그래서 예상한대로 동작한다.

그러나, connected component에 store와 state가 전파되는 방식을 커스터마이징 해야하거나 store에 직접 접근해야할 use case도 있을 것이다.

## Context 사용 이해가ㅣ

내부적으로, react-redux는 깊게 중첩된 connected component에 접근 가능한 리덕스 스토어를 만들기 위해 [context](https://reactjs.org/docs/context.html)를 사용한다. 리덕스 버전 6에서는, `React.createContext()`로 생성된 단일 context object(`ReactReduxContext)`로 처리된다.
