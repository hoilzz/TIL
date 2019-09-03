## useSelector와 reselect

```js
const result : any = useSelector(selector : Function, equalityFn? : Function)
```

셀렉터는 connect의 mapStateToProps와 개념적으로 어느정도 비슷하다.

- 함수형 컴포넌트가 렌더 될 때 마다 셀렉터는 실행된다.
- action이 디스패치 될 때마다 셀렉터는 실행된다.

useSelector와 mapState 함수의 차이

- 셀렉터(useSelector)는 객체가 아닌 모든 값을 result로 리턴 가능하다.
  - 셀렉터의 리턴 값은 useSelector의 리턴 값으로 사용된다.
- action이 dispatch 될 떄, useSelector는 **이전 셀렉터 결과 값과 현재 결과 값의 참조값 비교를 한다.** 만약 다르다면, 컴포넌트는 무조건 리렌더한다. 같으면 컴포넌트는 리렌더 하지 않는다.
- 셀렉터 함수는 ownProps 인자를 받지 않는다. props은 클로저나 커링된 셀렉터를 이용하여 사용될 수 있다.
- **메모이징된 셀렉터를 이용할 때 추가적인 주의사항이 필요하다.** (아래 예제 참고)
- useSelector는 === 참조값 비교를 한다. 즉, 얕은 비교가 아닌 깊은 비교를 한다.

단일 함수형 컴포넌트에서 useSelector는 여러번 호출 될 수 있다. useSelector는 개별 구독을 생성한다. **리액트 리덕스 v7에서 배치 업데이트 때문에, 여러개의 useSelector가 새로운 값을 리턴하도록 유발하는 디스패치된 액션은 단일 리렌더 내에서 결과를 반환해야만 한다.**

## Equality 비교와 업데이트

함수 컴포넌트가 렌더할 때, 제공된 셀렉터 함수는 호출 될 거고 결과 값은 useSelector로부터 리턴될 것이다. (만약 셀렉터가 실행되고 변경되지 않았다면 캐시된 결과값을 리턴할 거다.)

그러나, 액션이 디스패치 될 때 useSelector는 셀렉터 결과 값이 최근 결과값과 다르다면 강제 리렌더 할거다. 7.1.0-alph.5에서는 strict (===) 참조값 비교를 한다. connect와 다른점인데, 리렌더 여부를 결정하기 위해 mapState의 결과와 얕은 비교를 한다. 이것은 useSelector를 사용해야 하는 이유중 하나다.

mapState로 개별 필드가 결합된 객체로 리턴될 수 있다. 만약 리턴된 오브젝트가 새로운 참조값인지 아닌지가 중요하지 않다. 왜냐하면 connect는 개별필드를 비교한다.

useSelector에서 매번 새로운 객체를 반환하면, 기본적으로 강제 리렌더링한다. store에서 여러번 값을 가져온다면, 다음을 수행해야 한다.

- 즉, useSelector() 여러번 호출하는데, 이 때 각 호출은 단일 필드 값을 반환한다.
- 객체 내의 여러개의 값을 리턴하는 메모이징 셀렉터를 생성하기 위해 reselect를 사용해라. 하지만 값일 1개라도 바뀔 때만 새로운 객체를 리턴해라.
- useSelector()의 인자인 `equalityFn`의 `shallwEqual` 함수를 사용해라. 다음과 같이

```js
import { shallowEqual, useSelector } from 'react-redux';

// later
const selectedData = useSelector(selectorReturningObject, shallowEqual);
```

옵셔널 비교 함수는 또한 Lodash의 `_.isEqual()`이나 immutable.js의 비교 함수를 사용할 수 있다.

### useSelector예졔

```js
// basic usage
const CounterComponent = () => {
  const counter = useSelector(state => state.counter);
};
```

꺼내올 것을 결정하기 위해 클로저를 통한 prop 이용하기.

```js
import React from 'react';
import { useSelector } from 'react-redux';

export const TodoListItem = props => {
  const todo = useSelector(state => state.todos[props.id]);
  return <div>{todo.text}</div>;
};
```

**셀렉터를 메모이징해서 사용하기**

위와 같이 inline selector로 useSelector를 사용하면, 컴포넌트가 렌더링될 때마다 selector의 새 instance가 생성된다.
selector가 상태를 유지하지 않으면 잘 동작될 거다. 그러나, `reselect`의 `createSelector`를 통해 생성된 메모이즈된 셀렉터는 내부 상태를 갖는다. 그래서 사용될 떄 주의를 기울여야 한다. 메모이즈된 셀렉터를 사용하는 전형적인 방법이 아래에 있다.

셀렉터가 상태에만 의존할 때, 컴포넌트 밖에서 선언해야 하고 그래서 동일 셀렉터 인스턴스는 렌더링 될 때마다 사용된다.

```js
import React from 'react';
import { useSelector } from 'react-redux';
import { createSelector } from 'reselect';

// 밖에서 선언하여 메모이징된 셀렉터를 생성하자.
const selectNumOfDoneTodos = createSelector(
  state => state.todos,
  todos => todos.filter(todo => todo.isDone).length
);

export const DoneTodosCounter = () => {
  const NumOfDoneTodos = useSelector(selectNumOfDoneTodos);
  return <div>{NumOfDoneTodos}</div>;
};

export const App = () => {
  return (
    <>
      <span>Number of done todos:</span>
      <DoneTodosCounter />
    </>
  );
};
```

만약 셀렉터가 컴포넌트의 prop에 의존해도 마찬가지다. 하지만 단일 컴포넌트의 단일 인스턴스에서만 사용될 수 있다.

```js
// 메모이징 셀렉터
const selectNumOfTodosWithIsDoneValue = createSelector(
  state => state.todos,
  (_, isDone) => isDone,
  (todos, isDone) => todos.filter(todo => todo.isDone === isDone).length
);

// props.isDone을 셀렉터에서 이용하기 때문에
export const TodoCounterForIsDoneValue = ({ isDone }) => {
  const NumOfTodosWithIsDoneValue = useSelector(state =>
    selectNumOfTodosWithIsDoneValue(state, isDone)
  );

  return <div>{NumOfTodosWithIsDoneValue}</div>;
};

export const App = () => {
  return (
    <>
      <span>Number of done todos:</span>
      <TodoCounterForIsDoneValue isDone={true} />
    </>
  );
};
```

---

## summary

useSelector는

- 이전 셀렉터 결과 값과 현재 결과 값의 참조값 비교를 한다.
  - 다르면 리렌더, 같으면 낫 리렌더
- connect의 shallow compare가 아닌 strict compare를 한다.
  - connect는
    - 개별 필드가 결합된 객체를 리턴한다
    - 리턴된 오브젝트가 새로운 참조값인지가 비교하는게 아닌 개별필드를 비교한다.
- 개별 구독을 생성한다.
- useSelector 여러번 호출하는데, 이 때 각 호출은 단일 필드 값을 반환
- 객체 내의 여러개의 값을 리턴하는 메모이징 셀렉터를 생성하기 위해 reselect를 사용

connect는

connect와 비교했을 때 useSelector는

- 객체뿐만 아니라 어떤 값이든 리턴할 수 있다.
- ownProps API 사용 ㄴㄴ. 함수형 컴포넌트로 props를 단순히 전달받기 때문에 클로저를 통해 사용할 수 있음
- equlality 함수는 수정가능하다. Lodash의 isEqual이나 immutable의 matcher 같은걸로..
