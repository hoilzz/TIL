# Changes are made with pure function

action이 state tree를 어떻게 만드는지 명시하기 위해, pure reducer를 작성해야 한다.

리듀서는 이전 상태와 action을 받는 pure function이다. 그리고 다음 상태를 리턴한다. 이전 상태를 변경하는 것 대신에 new state object를 반환하는 것을 기억하자.

single reducer로 시작할 수 있고 app이 커지면서 state tree의 특정 부분을 관리하는 더 작은 리듀서로 쪼갤 수 있다. 왜냐하면 리듀서는 단순한 함수이기 때문이다. 그것들이 호출되는 순서를 제어할 수 있고, 추가 데이터를 전달 할 수 있다. 혹은 pagination과 같은 common task를 위해 재사용 가능한 리듀서를 만들 수 있다.
