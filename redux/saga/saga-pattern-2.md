# 리덕스 사가 패턴이 정신건강에 도움을 줄 것이다.

이 포스팅 보는 사람들은 기본적인 라이브러리 지식이 있다고 생각한다.

## Take And Fork

패턴 리스트 중 가장 일반적이다. ~~앵귤러1의 watcher와 listener를 사용한거 기억하니?~~

이 패턴은 action이 dispatch된 후에 어떤 프로세스를 트리거하는데 사용한다.

```js
/* this is the saga you are going to register */
export function* aListenerOnlySaga() {
  const somePossibleData = yield take('SOME_ACTION');
  yield fork(someOtherSagaProcess);
}

function* someOtherSagaProcess() {
  /* Any process calculation you need to do */
}
```

### use case

다양한 정보를 보여주고 현재 선택에 따라 action을 취해야하는데 필요한 브랜치/상태를 지원해야한다.

드롭다운으로 브랜치를 선택할 수 있고 그것과 관련된 정보를 쿼리할 수 있어야한다.

```js
/* Some ugly react component*/
class CompanyDropDown extends React.Component {
  state = { company: null, branches: [] };
  componentDidUpdate({ company, branches }) {
    this.setState(({ company }) => ({ company, branches }));
  }
  onChangeCompany(company) {
    this.props.dispatch('company_change', company);
  }
  render() {
    /* omitted for convenience */
  }
}

const mapStateToProps = ({company, branches}) => ({company, branches})

export connect(mapStateToProps)(CompanyDropDown)
```

렌더 메서드와 리듀서와 같이 어떤 지점에 직접접근해야 하는 코드는 생략한다.

```js
/* somewhere in your code... */
export function* listenForChangeCompany() {
  /* this variable holds the argument passed */
  const company = yield take('company_change');
  yield fork(changeCompanySaga, company);
}

function* changeCompanySaga(company) {
  const branchesPerCompany = yield call(getBranchesByCompany, company);
  yield put({ type: 'company_change_success', payload: branchesPerCompany });
}
```

UI와 비즈니스 로직을 분리할 수 있다.

main 이득은 특정 기능을 분리시키고 임의로 재량에 따라 팀에 공개하는 프로세스 카탈로그를 만들 수 있는점이다.(나중에 더 자세히 얘기하자).

하지만 이 패턴에 약간의 문제가 있다. **딱 한번 동작한다는 점이다**
다음 패턴은 간단하게 이 문제를 해결한다.

## Watch and Fork

Take and Fork 패턴의 문제 중 하나는 딱 한번 실행한다는 점이다.

더 나은 fir-for-purpose 케이스는 login or logout 프로세스가 될 수 있다.

마르타가 원할 때마다 회사를 변경할 수 있다고 해보자.
**watch and fork** pattern을 보자.

```js
export function* listenForChangeCompany() {
  while (true) {
    const company = yield take('company_change');
    yield fork(changeCompanySaga, company);
  }
} /* eh viola! */
```

```js
/* Where you register the sagas */ function* rootSagas() {
  yield [takeEvery('company_change', changeCompanySaga)];
}
```

회사 인자는 changeCompanySaga로 전달된다.
이 패턴을 좋아한다. 특히, 수많은 프로세스를 다루는 큰 어플리케이션이라면 더더욱
너는 단지 단일 액션에 대해 응답한다는 점만 알아두면 된다.

## Put and Take

이 패턴도 유용하다. 전에 말했듯이, 다양한 사가들로 동작을 구성할 수 있다.
teams/people/units간에 모든 것을 공유할 수 있는 서비스 사가를 만들 수 있다.

각 서비스는 상태를 변경시키는 유한한 기능을 가질 수 있다는 뜻이다.

재사용할 수 있는 복잡한 서비스가 만들어져있다고 생각해보자.
`fetchDataOverFiveDifferentLocations` 라고 불리는 게 있다. 많은 암시적인 역할을 할거 같다. 그러나 결국에는 파싱하고 소비할 준비가 된 모든 정보게 제공된다.

팀에서 다음과 같이 이름을 정하기로 했다.
`{service_name}_{microservice}_{status}`

- `fetchSomeData_events` 사가를 시작한다.
- `fetchSomeData_events_start` 시작하자마자 서비스에 디스패치되는 액션이다.
- `fetchSomeData_events_success` 종료됐을 때 디스패치되는 액션
- `fetchSomeData_events_error` 처리 중에 에러가 있다면 디스패치되는 액션

```js
export function* fetchDataOverFiveDifferentLocations() {
  while (true) {
    yield put({
      type: 'fetchSomeData_events_start',
    }); /*         computing stuff...       */
    yield put({ type: 'fetchSomeData_events_success' });
  }
}

function* rootSagas() {
  yield [
    takeEvery('fetchSomeData_events', fetchDataOverFiveDifferentLocations),
  ];
}
```

만약 위 함수를 확장해야한다면?

```js
/* We create a manager saga */
function* fetchDataManager() {
  /* we need to start the service/saga */
  yield put({
    type: 'fetchSomeData_events',
  });

  /* we need to wait/listen when it ends...*/
  yield take('fetchSomeData_events_success');
  /*      fork another process,     query info from the state,     do imperative stuff,     whatever you need to do when the previous saga finishes, the sky is the limit...    */
}

/* We create an orchestrator saga */
function* orchestratorSaga() {
  while (true) {
    yield fork(fetchDataManager);
  }
}
```

```js
/* your root saga then looks like this */
function* rootSagas() {
  yield [takeEvery('other_action_trigger', orchestratorSaga)];
}
```

## for/of collection

위 방법으로 대부분의 문제를 해결하지 않는다.

어떤 곳에서 collection 데이터를 가져온다고 해보자. 100개의 객체를 받고 각각에게 operation/service를 적용해야한다. 즉, 1개 잇아의 액션을 각 엘리먼트에 디스패치 해야한다. 보통, 리듀서에서 다룰 수 있지만, service catalog의 spirit을 유지하자(?)

saga에서 다음 행동을 할 수 없다.

```js
function* someSagaName() {
  /* code omitted for convenience */
  const events = yield call(fetchEvents)
  events.map((event) => {
    /* this is syntactically invalid */
    yield put({type: 'some_action', payload: event})
  })
}
```

```js
function* someSagaName() {
  /* code omitted for convenience */
  const events = yield call(fetchEvents);
  for (event of events) {
    yield put({ type: 'some_action', payload: event });
    /* ?? */
    /* or maybe something like: */
    yield fork(someOtherSagaOrService, event); /* ?? */
  }
}
```

---

## summary

- watch and fork pattern

  - 특정 기능을 분리시킬 수 있다.

- put and take

  - 다양한 사가들로 동작을 구성 가능
  - 비동기 API 호출이 있다면 `{service_name}_{microservice}_{status}`
    - `fetchSomeData_events` 사가를 시작한다.
    - `fetchSomeData_events_start` 시작하자마자 서비스에 디스패치되는 액션이다.
    - `fetchSomeData_events_success` 종료됐을 때 디스패치되는 액션
    - `fetchSomeData_events_error` 처리 중에 에러가 있다면 디스패치되는 액션

- 위 사가를 확장해야한다면?

```js
/* We create a manager saga */
function* fetchDataManager() {
  /* we need to start the service/saga */
  yield put({
    type: 'fetchSomeData_events',
  });

  /* we need to wait/listen when it ends...*/
  yield take('fetchSomeData_events_success');
  /*      fork another process,     query info from the state,     do imperative stuff,     whatever you need to do when the previous saga finishes, the sky is the limit...    */
}

/* We create an orchestrator saga */
function* orchestratorSaga() {
  while (true) {
    yield fork(fetchDataManager);
  }
}
```
