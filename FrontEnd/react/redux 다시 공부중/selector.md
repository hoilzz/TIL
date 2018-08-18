# Selectors in Redux are a MUST

redux selector가 해결할 수 있는 것은 많다.

crazy search page 작업했었다. normal text query외에 user는 filter의 개수를 선택할 수 있다. 필터는 모든 종류와 모양으로 나온다: 몇몇은 checkbox 집합, 일부는 중첩된 체크박스 트리이며 일부는 텍스트 상자로 필터링할 수 있다. 그것 뿐만 아니라, AND와 OR를 결합하여 복잡한 쿼리를 만들 수 있다.

겁나 빡센 스펙이었고, 개발하던 중에 selector는 도움이 되었다.

## Keeping state flat

프로젝트 개발 초기에 아래와 비슷한 store 모양을 가지고 있었다.

```javascript
const store = {
  filters: {
    locations: [],
  }
}
```

`locations`은

```javascript

```

## separating concerns

`locationByPath`는 너무 많은 정보를 담고 있다. 양쪽 도메인(id, value, heierarchy and UI data)을 다 가지고 있다. 대부분의 경우 도메인과 UI 데이터는 서로 다른 니즈와 라이프사이클을 가지고 있기 때문에 잘못된 설계다. 예를 들어, 나의 경우에는 필터가 스토어에서 한 번 로드되면 절대 업데이트 되지 않는다. 반대로, `checked` 프로퍼티는 checkbox의 상태가 바뀔 떄마다 토글된다. 그러므로, 2개를 분리하기로 했다.

```javascript
const locationsByPath = {
  1: {
    id: 1,
    value: 'Europe',
  },
  '1/2': {
    id: 2,
    value: 'Central Europe',
  },
  '1/2/3': {
    id: 3,
    value: 'Italy',
  },
  // ...
}

const checkedLocationsPaths = ['1', '1/2', '1/2/3']
```

이케 하면 좋은 거는 엄청 쉽게 노드를 확인할 수 있다.

```javascript
const newCheckedLocations = checkedLocationsPaths.includes('1/2/3') ?
  checkedLocationPaths: checkedLocationPaths.concat('1/2/3')
```

또한, `checkedLocationsPaths`와 `locationsByPath`는 독립적이다. 즉, 얘네는 다른 라이프사이클을 따를 수 있다. 예를 들어, `checkedLocationsPaths`는 `locationsByPath`가 로딩되기 전에 스토어에서 보여질 수 있다.

불행히도, flat state로 리팩토링 하는 것은 reducer 부분은 쉬웠지만 컴포넌트 부분은 어려웠다. initial nested shape은 컴포넌트가 처리하기에 더 쉬웠다.

```javascript
const Component = ({ value, checked, children }) =>
  <div>
    <input type='checkbox' value={value} checked={checked} />
    {children.map(({ value, checked, children }) =>
      <Component
        value={value}
        checked={checked}
        children={children}/>
    }
  </div>
```

flat state를 다루기 위해 컴포넌트에 로직을 추가했다. 하지만 그것이 올바른 위치였을까? 그렇게 생각하지 않는다. 그렇게 하면 컴포넌트에 state의 모양을 연결하는 것을 의미한다.

## selector to the rescue

reducer는 상태를 특정 모양으로 작성하는 역할을 한다. 그러므로, reading part를 처리하기 위해 가능한 가까이 배치하는 것이 좋다. 그것이 selector의 역할이다.

동일한 곳에 `initialState`를 갖는 것은 R/W 측면에서 올바른 장소다.

```javascript

```

---

## selector pattern 요약하자면

셀렉터 패턴은 어플리케이션이 state 값을 가져와야하는 방법의 문제를 해결한다. 기존에 state 가져오는 방법은 직접 참조를 통해 접근하는 것이다.

```javascript
const thePieceOfStateMyAppNees = store.someStateDomain.someProperty[somekey];
```

이 접근의 문제는 어플리케이션이 store의 모양을 정확히 알아야한다. store의 모양이 바뀌면 변경된 데이터를 읽는 코드를 모두 업데이트 해야한다. 셀렉터 패턴은 어플리케이션 스토어를 쿼리로 조회할 수 있는 정규화한 추상화다. 간단한데, 앱이 접근하고 싶은 스토어의 어떤 부분을 위해, 전체 스토어를 받아서, 스토어의 원하는 부분을 리턴하는 함수를 정의하는 것이다.

```javascript
const thePieceOfStateMyAppNeeds = getMyNeeds(state);
```

연관된 업데이트를 필요로 하는 참조 양은 최소화된다.

장점 요약
- selector 없으면
  - state 모양 바뀌면 관련해서 fetch하는 view코드 전부 수정
  - 동일한 데이터를 가져오는 컴포넌트가 많을 텐데, 재사용성 떨어짐

- selector 있으면 selector만 수정하면 됨

더 나아가서
- reselect의 createSelector와 함꼐 selector 사용하면 불필요한 재계산을 피하기 위해 메모이제이션 사용가능
- 만약 퍼포먼스 이슈가 없다면 createSelector는 필요하지 않다.

