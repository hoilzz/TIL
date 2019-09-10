# prerequisite concept

Redux 리듀서 함수는 "pure" 해야한다. 리듀서는

- side effect를 수행하지 않는다.(API 호출 or non-local object or variable 수정하기)
- non-pure 함수 호출하지 않기(Date.now, Math.random)
- 인자 변경하지 않아야한다.
  - 리듀서가 state를 업데이트 한다면, **기존 state** 를 수정하지 않아야 한다.대신 변경사항을 포함한 **new object** 를 생성해야한다.

> immutability, side effects, and mutation
> react redux의 `connect` 함수와 time-travle debugging을 깨드리기 때문에 Mutation은 하지 않아야한다.
> `connect`는 컴포넌트가 업데이트가 되야하는지 확인하기 위해 `mapStateToProps` 함수에서 리턴된 prop이 변경되었는지 체크한다. 퍼포먼스를 개선하기 위해, `connect`는 immutable한 상태에 의존하는 일부 shortcut을 사용하고 변경여부를 알기 위해 shallow reference 비교를 사용한다. 이것은 **직접 변경된 object나 배열의 변경은 알지 못하고, 컴포넌트는 리렌더링 하지 않는 다는 것을 의미한다**

## Redux Reducer Key Concepts

- state와 state 모양의 관점에서 생각하기
- update 책임을 slice of state에게 위임하기(reducer composition)
- Higher Order Reducers
- 초기 상태 리듀서 정의하기

## Basic State Shape

- Domain data: 어플리케이션이 show, use, or modify 해야하는 데이터(서버에서 가져온 Todo 전부)
- App State: 앱의 특정 행위에 대한 데이터(Todo #5는 현재 선택되었슴다, todos를 fetch하기 위해 진행중인 요청이 있다.)
- UI State: UI가 현재 보여지는 방식에 대한 데이터(EditToddo modal dialog가 현재 open되어있다)

**store는 어플의 핵심을 나타내기 때문에, state 모양은 UI component 트리가 아닌 도메인 데이터와 app 상태의 관점에서 정의해야한다**
예를 들어, `state.leftPane.todoList.todos`는 별로다. 왜냐하면 todos는 UI의 부분이 아닌 전체 앱의 중심이기 때문이다. 대신 `todos` slice는 state tree의 최상단에 위치해야한다.

전형적인 app 상태 모양은 다음과 같다:

```js
{
    domainData1 : {},
    domainData2 : {},
    appState1 : {},
    appState2 : {},
    ui : {
        uiState1 : {},
        uiState2 : {},
    }
}
```
