# Saga

data fetching, 브라우저 캐시 접근과 같은 순수하지 않은 비동기 동작들을 쉽고 좋게 관리

사이드 이펙트만을 담당하는 별도의 쓰레드와 같은 것
- 이 쓰레드는
  - __메인 어플리케이션에서 일반적인 리덕스 액션을 통해 `실행`, `정지`, `취소` 할 수 있음__
  - 모든 리덕스 앱 상태에 접근 가능
  - 리덕스 액션 또한 dispatch 가능

비동기 흐름을 쉽게 읽고, 쓰고, 테스트할 수 있게 ES6의 generator 사용
