# Organizing State

## 모든 state를 redux에 넣어야만 할까? `setState()`를 사용해야만 하는지?

1. Redux에서 전부 데이터를 관리하기
2. non-critical or UI state는 component 내부 state에서 관리하기

리덕스에서 관리되어야 하는 데이터 종류 결정하기
- application의 다른 부분이 해당 데이터에 대해 신경 쓸 때
- original data를 기반으로 파생 데이터를 추가로 생성해야 할 때
- 여러개의 컴포넌트에서 사용될 때
- 주어진 시점으로 상태를 복원 하는 기능 이용할 때 가치가 있는 데이터일 때
- 데이터 캐싱할 때(재요청 보내는 거 대신에 기존 state가 있으면 요청 안보냄)
