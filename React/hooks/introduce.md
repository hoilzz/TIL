# hooks

## 왜 만들었을까?

### 컴포넌트간에 stateful 로직을 재사용하기 어렵다

리액트는 컴포넌트에게 재사용 가능한 행동을 붙이는 방법을 제공하지 않는다.
(예컨대 스토어에 컴포넌트를 연결하는 것..) 이것을 해결하기 위해 render props, HOC가 있다.

하지만 이 방법은 component를 재구성해야 하고 코드를 추적하기 어렵다.
또한, provider, consumer, hoc, render props 등 다른 추상화 레이어로 nesting되어 wrapper hell에 빠지기 쉽다.

hook을 사용하면, 컴포넌트로부터 상태 관련 로직을 추상화 할 수 있다.
이것은 독립적은 테스트 및 재사용이 가능하다.
**hook은 계층 변화 없이 상태 관련 로직을 재사용할 수 있다.**

### 복잡한 컴포넌트들은 이해하기 어렵다.

생명주기 메서드에 유지하기 힘든 상태관련 로직과 사이드 이펙트가 있는 컴포넌트를 유지해야한다.

cdm, cdu에서 데이터 가져오기, cwu에서 cleanup 수행하기. 이것으로 인해 함께 변경되는 상호 관련 코드는 분리되지만(각 라이프사이클에 맞게 분리) 연관 없는 코드들은 단일메서드로(하지만 라이프사이클에서 단일메서드로 재결합..) 결합됨.
상태 관련 로직이 모든 공간에 있기 때문에 컴포넌트들을 작게 만드는 것도 불가능.
테스트 하기 어려움

hook을 사용하면, 생명주기 메서드를 관심사 기반으로 분리할 수 있다.
또한 로직에 기반을 둔 작은 함수로 컴포넌트를 나눌 수 있다.

## Class는 사람과 기계를 혼동시킨다.

Class는 코드의 재사용과 코드 구성을 어렵게 만든다.

또한, this의 작동 방식에 대해 알아야하고, 대부분의 다른 언어와 다르게 동작.
이벤트 핸들러가 등록되는 방법을 기억해야 한다.
(constructor에서 bind메서드 혹은 [class-properties](https://babeljs.io/docs/en/babel-plugin-proposal-class-properties)를 통해 this 바인딩)
또한, 함수형/Class 컴포넌트를 언제 사용되야하는지 의견 불일치를 보임.

이러한 문제를 해결하기 위해, **Class 없이 React 기능 사용하도록 hook을 개발**

## Summary

1. 컴포넌트간 stateful 로직 재사용 어려움.

- 기존 해결책 : hoc, render prop
  - 컴포넌트 재구성해야함
    - render prop은 그 컴포넌트를 render prop에 넣어주고, 받을 prop 관련 로직 추가.
  - wrapper hell
  - 코드 추적 어려움
- hook
  - 재사용 너무나 쉬움. 그냥 hook 호출하면됨.
  - 컴포넌트 재구성 ㄴㄴ. 그냥 호출해서 리턴되는 값 사용하면됨.
  - wrapper hell 없음
  - 코드 추적 쉬움. 컴포넌트 내부에 그냥 선언되어있으니까..

2. 복잡한 컴포넌트 이해하기 어려움

- 라이프 사이클에서 여러가지 동작들이 단일 메서드로 결합됨.
- 상태 관련 로직이 모든 공간에 있기 때문에 컴포넌트 작게 만들기 불가능.
- 테스트 하기 어려움..

- hook
  - 라이프사이클 사용하지 않고 관심사별로 분리 가능.
  - 상태 관련 로직을 custom hook으로 분리하여 캡슐화 가능
  - 테스트 하기 쉬움. 관심사별로 분리 되어있으니까로

3. class..

- 이벤트 핸들러에서 this 바인딩을 위해 constructor에서 바인딩 혹은 class-properties 이용
- 함수형/class 컴포넌트 언제 사용해야 하는지 의견 불일치

이것을 해결하기 위해 Class 없이 함수형 컴포넌트 + hook으로 해결.
