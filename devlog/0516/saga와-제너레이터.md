
## 제너레이터 함수 - Caller와 Callee

- 제너레이터 함수는 Callee, 이를 호출하는 함수는 Caller
- Caller는 Callee가 반환한 제너레이터를 가지고 로직 수행
- Caller는 Callee의 yield 지점에서 다음 진행 여부/시점을 제어

Caller는 Callee를 호출하는 책임 뿐 아니라, Callee 내부 로직 수행에 대한 제어권을 갖는다.

Saga 입장에서 보면 미들웨어는 Caller, 우리가 작성한 Saga는 Callee