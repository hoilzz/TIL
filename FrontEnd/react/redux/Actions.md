# Actions
[Actions](https://github.com/reactjs/redux/blob/master/docs/basics/Actions.md)를 참고하여 작성하였습니다.

action은

- 너의 application에서 스토어로 데이터를 전송하는 정보의 payload다.
	+ (action이 실질적인 적화물 위키피디아의 payload를 참고하자)

- action들은 오직 store를 위한 정보의 source다.
	- store는 `받은 action`과 `현재 application 상태 트리`를 루트 리듀서에 보낸다.
	- `store.dispatch()`를 이용하여 action을 전송할 수 있다.

new todo item을 추가하는 것을 나타내는 action 예제가 여기있다.

```javascript
const ADD_TODO = 'ADD_TODO';
```

```javascript
{
  type : ADD_TODO,
  text : 'Build my first Redux App'
}
```

- Action은 plain JS object다.
- Action은 수행될 action의 type을 가리키는 **`type` property를 반드시 가져야 한다**.
- string constants(`const`)로 정의되어야 한다.
- app이 충분히 커지면, 그것들을 separate module로 옮기고 싶을거다.


```javascript
import {ADD_TODO, REMOVE_TODO} from '../actionTypes';
```

> **NOTE on BoilerPlate**
> action type constant를 separate file에서 정의할 필요 없다.
> small project의 경우에, action type을 string literal로 사용하는게 더 쉽다.
> 그러나, larger codebase에서 명시적으로 constant로 선언하는 것이 이점이 많다.
> [Reducing BoilerPlate](https://github.com/reactjs/redux/blob/master/docs/recipes/ReducingBoilerplate.md) 읽어봐

action object의 구조는 너한테 달려있다. 만약 흥미가 있다면 (Flux Standard Action)[https://github.com/acdlite/flux-standard-action]에서 action이 구성되는 방식을 확인해봐.

완료 했을 때 todo를 터치아웃하는 유저를 describe 하기 위해 1가지 더 action type을 필요로 한다. `index`로 특정 todo를 참조한다.  왜냐하면 배열에 그것들을 저장하기 때문이야. real app에서 every time something new is created, unique ID를 생성하는 것이 더 현명해

```javascript
{
  type: TOGGLE_TODO,
  index: 5
}
```

각 action에 little data 인자로 보내는거 좋은 생각이야. 예를 들어 전체 todo object 보다 `index`를 통과시키는 게 더 나아

Finally, 현재 visible todo를 변경하기 위한 action 추가하자
```javascript
{
  type: SET_VISIBILITY_FILTER,
  filter: SHOW_COMPLETED
}
```

## Action Creators
Action creator는 action을 생성하는 함수다. `action`과 `action creator`라는 용어를 합치는 것은 쉽다.

action creator는 action을 리턴한다

```javascript
function addTodo(text){
  return {
    type: ADD_TODO,
    text
  }
}
```
이것은 portable하고 테스트하기 쉽다.

action creator가 dispatch를 trigger한다.

Redux에서 dispatch를 initiate하기 위해, `dispatch()` function에 result를 인자로 넣어라

```javascript
dispatch(addTo(text))
dispatch(completeTodo(index))
```

Alternatively, **자동으로 dispatch하는 bound action creator**를 생성할 수 있다.

```javascript
const boundAddTodo = (text) => dispatch(addTodo(text))
const boundCompleteTodo = (index) => dispatch(completeTodo(index))
```

이제 직접 action을 호출할 수 있다.
```javascript
boundAddTodo(text)
boundCompletyeTodo(index)
```

`dispatch()` function은 `store.dispatch()`로 store에서 직접 접근될 수 있다. 하지만 react-redux의 `connect()`와 같은 헬퍼를 이용하여 접근할 수도 있다. 자동으로 많은 action creator를 bind하는 `bindActionCreators()`를 사용할 수 있다.

Action creators 비동기고 부작용이 많다. advanced tutorial에서 [async action](https://github.com/reactjs/redux/blob/master/docs/advanced/AsyncActions.md)을 읽어봐. (**AJAX response와 action creator를 async control flow로 구성하는 방식에 대해 배울 수 있다.**) basic tutorial 완전히 끝낼때까지 async action로 절대 스킵하지마. as it covers other important concepts that are prerequisite for the advanced tutorial and async actions.

## Source Code
<hr>
**`action.js`**

```javascript
/*
 * action types
 */

export const ADD_TODO = 'ADD_TODO'
export const TOGGLE_TODO = 'TOGGLE_TODO'
export const SET_VISIBILITY_FILTER = 'SET_VISIBILITY_FILTER'

/*
 * other constants
 */

export const VisibilityFilters = {
  SHOW_ALL: 'SHOW_ALL',
  SHOW_COMPLETED: 'SHOW_COMPLETED',
  SHOW_ACTIVE: 'SHOW_ACTIVE'
}

/*
 * action creators
 */

export function addTodo(text) {
  return { type: ADD_TODO, text }
}

export function toggleTodo(index) {
  return { type: TOGGLE_TODO, index }
}

export function setVisibilityFilter(filter) {
  return { type: SET_VISIBILITY_FILTER, filter }
}
```
