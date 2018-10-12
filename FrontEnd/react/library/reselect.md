# Reselect

## creating a memoized selector

`createSelector`
- input-selectors의 배열을 받는다. 배열의 값은 함수로 변형시킨다.
- 만약 redux state tree가 input-selector의 값을 변경시키는 방식으로 변경되면, 셀렉터는 input-selector의 값을 인자로 사용하여 변형 함수를 호출하고 결과를 리턴할 것이다.
- 만약 input-selector의 값이 selector에게 이전에 호출했던 것과 똑같다면, 변경된 함수를 호출하는 대신 이전에 계산된 값을 리턴할 것이다.

```javascript
import { createSelector } from 'reselect'

const getVisibilityFilter = (state) => state.visibilityFilter
const getTodos = (state) => state.todos

export const getVisibleTodos = createSelector(
  [ getVisibilityFilter, getTodos ],
  (visibilityFilter, todos) => {
    switch (visibilityFilter) {
      case 'SHOW_ALL':
        return todos
      case 'SHOW_COMPLETED':
        return todos.filter(t => t.completed)
      case 'SHOW_ACTIVE':
        return todos.filter(t => !t.completed)
    }
  }
)
```

input-selector
- getVisibilityFilter
- getTodos

getVisibleTodos만 memoized selector, input-selector는 non-memoized selector.

## Composing Selectors

memoized selector가 input-selector가 될 수 있다. getVisibleTodos가 input-selector가 된 것을 볼 수 있다.

```javascript
const getKeyword = (state) => state.keyword

const getVisibleTodosFilteredByKeyword = createSelector(
  [ getVisibleTodos, getKeyword ],
  (visibleTodos, keyword) => visibleTodos.filter(
    todo => todo.text.includes(keyword)
  )
)
```