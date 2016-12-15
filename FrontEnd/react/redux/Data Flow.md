# Data Flow

Redux 아키텍처는 strict unidirectional data flow로 회전한다.

data life Cycle은 4 step을 따른다.

1. You call `store.dispatch(action)`
  **action은 plain object** describing what happend :

  ```javascript
    {type : 'LIKE_ARTICLE', articleId: 42}
    {type : 'FETCH_USER_SUCCESS', response: {id: 3, name: 'Mary'} }
    {type : 'ADD_TODO', text: 'Read the Redux docs.'}
  ```

  "Mary liked article 42" or "'Read the Redux docs' was added to the list of todos".

  **너의 앱 어디에서든 (components와 XHR callback or even at scheduled intervals을 포함하여)**`store.dispatch(action)`를 호출할 수 있다.

2. Redux store calls the reducer function you gave it.

  **store는 reducer에 2개의 인자를 보낸다:**
  1. current state tree
  2. action

  예를 들어, todo app에서 `root reducer`는 다음과 같이 받는다

  ```javascript
    // The current application state (list of todos and chosen filter)
    let previousState = {
      visibleTodoFilter: 'SHOW_ALL',
      todos: [
        {
          text: 'read the docs',
          complete: false
        }
      ]
    }

    // The action being performed (adding a todo)
    let action = {
      type: 'ADD_TODO',
      text: 'Understand the flow.'
    }

    // Your reducer returns the next application state
    let nextState = todoApp(previousState, action);
  ```

  reducer는 pure function이다.
  - It only computes the next state.
  - 완벽하게 예측 가능해야 한다 : calling(same input) many times 동일한 결과 생산해야한다.
  - API calls or router transition과 같은 side effect를 수행하지 않아야 한다
  - 이러한 것들은 action이 dispatch되기 전에 일어나야 한다.

3. root reducer는 single state tree에 multiple reducer 아웃풋을 combine한다.

  root reducer의 구성 방식은 완전히 너한테 달려있다. Redux ships with a `combineReducers()` helper function (root reducer를 separate function(각 함수는 state tree의 1개 branch를 관리한다)으로 나누는 것을 위한 helper다.)


  다음은 `combineReducers()`가 동작하는 방식이다. 2개의 리듀서를 가지고 있다고 해보자. 하나는 list of todos, and another for the currently selected filter setting.

  ```javascript
  function todos(state = [], action) {
    // Somehow calculate it...
    return nextState
  }

  function visibleTodoFilter(state = 'SHOW_ALL', action) {
    // Somehow calculate it...
    return nextState
  }

  let todoApp = combineReducers({
    todos,
    visibleTodoFilter
  })
  ```

  action을 생략했을 때, `combineReducers`에 의해 리턴된 `todoApp`은 reducer 둘 다 호출할 것이다.

  ```javascript
    let nextTodos = todos(state.todos, action)
    let nextVisibleTodoFilter = visibleTodoFilter(state.visibleTodoFilter, action)
  ```

  그리고나서 single state tree에 결과 set을 을 결합할 것이다.

  ```javascript
  return {
    todos: nextTodos,
    visibleTodoFilter: nextVisibleTodoFilter
  }
  ```

  While `combineReducers()` is a handy helper utility, you don't have to use it; feel free to write your own root reducer!

  4. Redux store는 root reducer에 의해 리턴된 완전한 state tree를 저장한다.

  `store.subscribe(listener)`로 등록된 every listener는 이제 호출될 것이다. listener는 아마 현재 state를 얻기 위해 `store.getState()`를 호출할 것이다.

  Now, UI는 new state를 반영하기 위해 업데이트 될 것이다. 만약 너가 React Redux처럼 binding을 사용한다면, `component.setState(newState)`호출될 시점이다.
