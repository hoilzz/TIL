# immutability helper - state 내부 array에 원소 삽입 제거 수정
: 데이터배열에 변화를 주는 방법

## 1 state 안의 array에 원소 삽입/제거/수정

`this.state`에 포함된 배열에 원소를 삽입/제거/수정할 때 그 배열에 직접 접근하면 안됨.
- 예를 들어, 원소를 추가 할 때 배열객체의 `push` 메서드 사용하면 원하는대로 안됨
- `this.state`가 변경된다고해서 컴포넌트가 업데이트 되지 않음
- React 컴포넌트 API인 `forceUpdate`를 통해 컴포넌트 `render()`를 다시 실행할 수 있지만 권장 ㄴㄴ
`this.setState()`를 사용하여 수정하는 것이 해결책

### 1.1 원소 삽입하기
`state` 
