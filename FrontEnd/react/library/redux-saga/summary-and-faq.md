# 1-8 summary

- 이펙트 : 미들웨어에 의해 수행되는 명령을 담고있는 JS 객체.

- takeEvery는

  - 여러 개의 fetchData 인스턴스 **동시에 시작** 하게 함.
  - 종료되지 않은 여러개 fetchData task가 있다면 새로운 fetchData task로 시작 가능

- takeLatest

  - **마지막으로 발생된 리퀘스트의 응답만 얻고 싶다면** 얘 사용

- put

  - action을 dispatch

- call

  - 미들웨어에게 `args`를 파라미터로 전달하여 `fn`를 실행하라고 명령
  - 비동기 호출, 동기 호출 등 액션생성자 호출

- take

  - 특정한 액션을 기다리기 위해 미들웨어에게 알려주는 명령 오브젝트
  - Pull 접근법을 통해 동기적 flow로 로직 작성가능 (로그인-로그아웃)
  - **yield take(pattern)의 결과 값은 dispatch된 action object**

- select(selector, ...args)

  - 미들웨어가 현재 store의 상태에서 제공된 셀렉터를 호출하도록 명령

- fork

  - non-blocking 태스크 수행

- cancel

  - fork된 태스크 취소

- cancelled

  - 태스크 취소됐을 경우 finally에서 cancled 이펙트를 통해 청소 로직 ㄱㄱ

- all

  - 병렬 태스크 수행

- race

  - task를 병렬로 수행하지만 특정 조건을 통해 종료

- eventChannel(subscribe, [buffer], [matcher])
  - subscribe 메서드를 이용하여 이벤트 소스를 구독하는 채널을 생성.
  - 다가오는 이벤트는 interested taker가 등록될 때까지 채널 내부의 큐에 쌓인다.
  - 보통 setInterval을 구독하는 이벤트 채널 예제 많음.
