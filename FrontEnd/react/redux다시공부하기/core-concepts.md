# Core Concepts

app 의 상태가 plain object 로 설명된다고 해보자. 예를 들어 todo app 의 상태는 다음과 같다.

```javascript
{
  todos: [{
    text: 'Eat food',
    completed: true
  }, {
    text: 'Exercise',
    completed: false
  }],
  visibilityFilter: 'SHOW_COMPLETED'
}
```

이 객체는 setter 가 없다는 점을 제외하고 model 같다. 그래서 코드가 state 를 임의로 변경할 수 없다는 점(버그를 재생산하기 어렵다) 이 다르다.

상태에서 뭔가 바꾸기 위해, action 을 dispatch 해야한다. action 은 뭐가 일어났는지 설명하는 `plain javsscript object`다.

강제로 모든 변화를 action 으로 설명하도록 하는 것은 app 에서 무슨 일이 일어나는지 명확하게 이해하도록 한다. 만약 뭔가 변하면, 왜 변하는지 알 수 있다. state 와 action 을 연결하기 위헤, reducer 라는 함수를 작성하자. 이것은 마법같은 건 아니고 단순히 state 와 action 을 인자로 받고 app 의 다음 상태를 리턴하는 함수다. big app 에서 그런 함수를 작성하는 것을 어려울 수도 있다. 그래서 state 의 부분을 관리하는 작은 함수를 작성한다.

```javascript
function visibilityFilter(state = 'SHOW_ALL', action) {
  if (action.type === 'SET_VISIBILITY_FILTER') {
    return action.filter
  } else {
    return state
  }
}
​
function todos(state = [], action) {
  switch (action.type) {
    case 'ADD_TODO':
      return state.concat([{ text: action.text, completed: false }])
    case 'TOGGLE_TODO':
      return state.map(
        (todo, index) =>
          action.index === index
            ? { text: todo.text, completed: !todo.completed }
            : todo
      )
    default:
      return state
  }
}
```

2 개의 리듀서를 호출하여 우리의 app 의 모든 state 를 관리하는 다른 리듀서를 작성해보자.

```javascript
function todoApp(state = {}, action) {
  return {
    todos: todos(state.todos, action),
    visibilityFilter: visibilityFilter(state.visibilityFilter, action)
  };
}
```

기본적으로 이게 Redux 아이디어다. Redux API 아무것도 사용하지 않은 것을 참고하자. 이 패턴을 용이하게하기 위해 몇 가지 유틸리티가 있지만 main idea 는 **시간이 지남에 따라 action 객체에 대한 응답으로 state 가 업데이트 되는 방식을 설명** 하는 것이다. 그리고 작성되는 code 의 90%가 plain js 일거다.
