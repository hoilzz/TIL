# Redux : 효율적인 React 앱의 교류
React 어플리케이션의 데이터 교류 및 state관리를 쉽고 효율적으로 할 수 있음.

## Introduction
Redux는 `data-state`와 `UI-state`를 관리
- 상태적 데이터 관리가 시간 흐름에 따라 복잡해질 수 있는 SPA에서도 유용
- **React의 데이터 흐름은 단일 방향**
  - `state`, `props`는 **parent-child 관계**를 통해 데이터 교류
- 하지만 컴포넌트 갯수가 많아진다면.. 데이터를 교류 할 컴포넌트들이 parent-child 관계가 아니라 복잡해진다.

https://velopert.com/wp-content/uploads/2016/04/01.png

- 빨강, 파랑, 초록 컴포넌트가 데이터를 교류해야한다면..?
  - **직접 데이터를 교류** 할 수 있지만 **권장하지 않음**
  - 잘못했다간 스파게티 코드가 만들어짐

## Flux
라이브러리가 아닌 **디자인패턴**
1. 어떠한 `Action`을 받았을 때
2. `Dispatcher`가 받은 `Action`들을 통제하여 `Store`에 있는 데이터 업데이트
3. 그리고 변동된 데이터 있으면 `View`에 리렌더링

`View`에서 `Dispatcher`로 `Action`을 보낼 수도 있다.
- Dispatcher는 작업이 중첩되지 않도록 한다.
- 즉, 어떤 `Action`이 `Dispather`를 통해 `store`에 있는 데이터를 처리하고
- 그 작업이 끝날 때까지 다른 `Action`을 대기 시킨다.
