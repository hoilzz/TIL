# saga with pattern

비동기 로직(API 호출)을 처리하기 위한 패턴.

API 호출은 요청-성공|실패 로 이어진다.

이 때, thunk든 saga든 다음 패턴을 주로 이용한다.

- REQUEST ACTION을 dispatch
  - 로딩 관련 UI 노출
- api 호출

- 성공시
  - SUCCESS ACTION을 dispatch
- 실패시
  - FAILURE ACTION을 dispatch

saga에서 위 비동기 로직을 컨트롤 하기 위해 다음과 같이 추상화 함수를 생성할 수 있다.

```js
function fetchEntity(entityActions, api) {
  return function *(...arg) {
    try {
      yield put(entityActions.request());
      const data = call(api, ...arg);
      yield put(entityActions.success(data));
    } catch {
      yield put(entityActions.failure());
    }
  }
}
```
