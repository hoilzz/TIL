# wrapping dispatch() to recognize Promise

`receiveTodos` action creator는 꽤 유용하지 않다. 왜냐하면 호출할때마다, `todos`를 먼저 fetch해야 하기 때문이다. **그니까 receiveTodos는 무조건 fetch를 해야하기 때문에 굳이 아래코드와 같이 하지 말고 쟤네처럼 동작하는 actionCreator를 하나 만들자**라는 취지인거같다.
fetchTodos와 receiveTodos는 동일한 인자를 받기 때문에, 이 코드를 단일 action creator로 그루핑하는 것이 좋을거 같다.

*기존 fetchData()*
```javascript
fetchData() {
  const { filter, receiveTodos } = this.props;
  fetchTodos(filter).then(todos =>
    receiveTodos(filter, todos)
  );
}
```

## Action creator를 리팩토링하기

`fetchTodos`라는 비동기 action creator를 추가했다. filter를 인자로 받고, API의 fetchTodos 메서드를 호출한다.

`import * as api from '../api'`

이름이 `fetchTodos`인 비동기 action creator 추가하자. `filter`를 인자로 받고 API의 `fetchTodos`메서드를 호출한다.

filter와 response가 주어진 `receiveTodos`에 의해 성생된 action object에 `response`의 Promise 결과를 변경하기 위해 Promise `then` method를 사용할거다.

*src/actions/index.js*

```javascript
export const fetchTodos = (filter) =>
  api.fetchTodos(filter).then(response =>
    receiveTodos(filter, response)
  );
```

## Updating VisibleTodoList

`connect`가 주입해준 `fetchTodos` prop을 사용할 수 있다. 이것은 새로운 비동기 `fetchTodos` action creator와 일치한다.

`import {fetchTodos} from '../api'`를 삭제하자. 왜냐하면 지금부터 우리는 `fetchTodos` action creator를 사용할거다.

```javascript
fetchData() {
  const { filter, fetchTodos } = this.props;
  fetchTodos(filter);
}
```

## Recaping what we just did

redux는 promise가 아닌 plain object만 dispatch하는 것을 허락한다. 그래서 `configure.js`에서 dispatch를 가지는 함수를 새로 만들어서 Promise일 경우 따로 처리하는 코드를 작성하자.

## Adding Promise Support

`configure.js`에서, `dispatch`와 `store`를 가지고 promise를 지원하는 `addPromiseSupport()` 함수를 만들자.

첫째로, `store`에서 정의된 `rawDispatch` 함수를 쥐고 있을 것이다. 그래서 그걸 나중에 호출할거다. dispatch function처럼 동일 API를 가진 함수를 리턴할거다.

```javascript
const addPromiseSupportToDispatch = (store) => {
  const rawDispatch = store.dispatch;
  return action => {
    if (typeof action.then === 'function')  {
      return action.then(rawDispatch)
    }
    return rawDispatch(action);
  }
}
```

`action`이 real action 인지 promise인지, `then` 메서드를 가졌는지 판단하면, 우리는 그게 promise인지 알 수 있다. action이 promise라면 우리는 action 객체를 resolve할 때까지 기다린다.

promise가 아니면, rawDispatch를 action과 함께 즉시 호출한다.

... 중략

