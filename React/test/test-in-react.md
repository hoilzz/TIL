# FE 테스트

[testing 시리즈](https://jbee.io/react/testing-3-react-testing/)를 읽고

## 1. 무엇을 테스트 할 것인가?

동작을 테스트하고, 동작은 사용자로부터 발생한 이벤트의 부수효과를 의미

**그리고 이 부수효과들이 발생하게 되는 조건과 결과** 를 테스트한다.
이것은 Store의 `selector`, `reducer`, `middleware 함수`가 된다.

## 무엇을 테스트하지 않을것인가

1. 컴포넌트들이 제대로 합성되는가
2. 화면에 제대로 렌더링 되는가
   -> 디자인 변경시 컴포넌트의 계층 구조가 변경되면서 깨지기 쉬운 테스트가 됨.
3. 컴포넌트에 어떤 동작을 했을 떄, 무엇인가 트리거가 되는가
   -> 브라우저, 리액트를 믿자. ROI가 좋지 않다.

## 2. 어떻게 테스트할까?

- 테스트의 결과는 외부에 있는 어떤 요소에 의해 결정되는 부분이 없어야한다.
- 오로지 **가정에 의해서만** 결정되어야 한다.
- **가정은 테스트의 의도를 포함하여, 각 테스트 케이스 하나 당 하나의 의도만을 포함해야 한다.**

### TC 만들기

#### Given-When-Then pattern

```js
test('should $1', () => {
  // Given : 데이터 혹은 payload 혹은 mocking하는 state object가 될 수 있음
  const data = $4;

  // When : 주어진 데이터를 기반으로 어떤 행동을 취했을 때 검증해야 하는 값. 어떤 함수 호출했을 때 반환값
  const result = $3;

  // Then
  expect(result).toEqual($2);
});
```

1. TC의 **목적** 을 작성
2. **예상하는 값** 을 작성
3. 어떠한 **flow** 를 검증할지 작성
4. 3번 검증을 위해 어떤 가정이 필요한지 작성.

## 비즈니스 로직과 UI 렌더링의 분리

컴포넌트 렌더링과 관련된 단위테스트는 작성하지 않기로 했다.
컴포넌트에 비즈니스 로직이 포함되지 않도록 `custom hooks`, `middleware`, `selector`, `reducer`로 옮긴다.
컴포넌트는 그저 화면만 그린다.

몇가지 예외사항이 있다.

- 사용자 동작에 대해 alert 띄우기
- anchor 태그 클릭시 외부 페이지 이동

하지만 hook을 이용하여 비즈니스 로직을 분리할 수 있다.

- 특정 버튼 클릭시, 어떤 조건에 따라 팝업 노출
- api 호출시, 에러 발생했을 때 알맞은 에러 메시지 노출
- 특정 조건에 따라 버튼이 활성화/비활성화 됨.

## 3. Store와 비즈니스 로직 테스트

1. 액션 생성 함수가 액션을 의도한대로 생성하는가?
   -> FSA 구조를 따라 액션 정의시 불필요한 테스트

2. 리듀서가 상태를 의도한대로 변경하는가?
3. (만약 미들웨어가 있다면) 액션이 미들웨어에 적용되는가?
   -> 리덕스에서 특정 action만 건너뛸 리 없고 라이브러리를 믿자.
4. 미들웨어는 잘 동작하는가?
5. selector를 사용한다면 그 selector는 store의 상태에 따라 제대로 된 값을 반환하는가?

### Store 단위테스트

#### reducer, selector

두 경우 A라는 인풋에 대해 항상 동일한 output을 반환하는 순수함수라서 테스트 코드 작성하기 쉽다.

```js
test('should return', () => {
  // Given
  const state = {};
  const action = {
    type: '',
    payload: ''
  };

  // When
  const results = reducerFunction(state, action);
  // or When
  const results = selectorFunction(state, action);

  // Then
  const expected = {};
  expect(results).toEqual(expected);
});
```

두 경우, state에 대한 mocking만 잘해주면 발생 가능한 모든 상황에 대해 테스트 코드 작성가능하다.

#### redux-saga

미들웨어 테스트는 **리덕스 환경 바깥에서** 진행해야 한다.

## Summary

**무엇을 테스트할까?**

이벤트의 부수효과만 테스트한다.

- selector
- reducer
- middleware 함수

무엇을 테스트하지 않을까?

- 제대로 렌더링 되는지 (컴포넌트 스냅샷 테스트)
- 컴포넌트에 어떤 동작을 했을 때, 무엇인가 트리거 되는가 (storybook이라면 action을 통한 이벤트 트리거 여부)

---

**어떻게 테스트할까?**

- 테스트 결과는 외부 요소에 의해 결정되는 것이 없어야 한다.
- 오로지 가정에 의해서 결정되어야 한다.
- 가정은 테스트의 의도다. TC 1개당 1개의 의도만을 포함해야한다.

**Given-When-Then pattern**

- Given : 데이터 혹은 payload, mocking state object
- When : 어떤 행동을 취했을 때 검증해야 하는 값(함수 호출시 반환값)
- Then : expect(result).toEqual(expectedResult)

비즈니스 로직과 UI 렌더링의 분리

- 컴포넌트에 비즈니스 로직이 포함되지 않도록 `custom hook`, `middleware`, `selector`, `reducer`로 이동

---

**Store와 비즈니스 로직 테스트**

- action creator
  -> FSA 구조를 따른다면 불필요.

1. 리듀서
2. 셀렉터
3. 미들웨어가 잘 동작하는지
