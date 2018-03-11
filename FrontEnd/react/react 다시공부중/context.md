# Context

몇몇 경우에, 모든 단계마다 메뉴얼대로 props를 전달하는 것 없이 component 트리를 통해 데이터를 통과시키고 싶을거다. `context` API로 이걸 할 수 있다.

## Context를 사용하지 않는 이유

대다수의 프로그램은 컨텍스트를 사용할 필요가 없다. 

만약 application이 안정되기를 원하면 context를 사용하지 마라. 실험적인 API고 React의 미래에 