# Reducers

Actions는 일어날 어떤 것을 나타낸다. 하지만 application's state가 response에서 변화하는 방식에 대해 명시하지 않는다. 이것을 reducer가 한다.

## Designing the state shape

What's the minimal representation of your app's state as an object?

todo app에서, 2가지 다른 것을 저장할꺼다

1. The currently selected visibility filter
2. The actual list of todos

어떤 데이터 혹은 UI State in the state tree를 저장해야할 때가 있다. 하지만 UI State로부터 분리된 데이터를 유지하려고 시도해봐.

```javascript
{
  visibilityFilter: "SHOW_ALL",
  todos: [
    {
      text: 'Consider using Redux',
      completed : true,
    },
    {
      text: 'Keep all state in a single tree',
      completed: false
    }
  ]
}
```

> Note On Relationships
> 더 복잡한 app에서, 서로 참조하는 다양한 엔티티가 있다. nesting 없이 가능한 normalized로 state를 유지해라. key를 ID로 하는 object에서 모든 entity를 유지해라. 그리고 다른 entity로부터 그것을 참조하기 위해 ID를 사용해라. app's state를 database로 생각해라. 이러한 접근은 [normalizr's](https://github.com/paularmstrong/normalizr) documentation에 더 자세히 적혀있다. 예를 들어, `todosById : {id -> todo}` and `todos: array<id>`를 state 내부에서 유지하는 것은  real app에서 더 나은 idea다. 하지만 우리는 예제를 간단하게 유지해야 한다.
>

#### Summary
1. Designing the state shape
2. 더 복잡한 app에서, 서로 참조하는 다양한 엔티티
  - nesting 없이 가능한 normalized로 state를 유지해라.

## Handling actions
앞에서 state object의 shape을 결정했다. reducer를 작성할 준비 완료됐다. Reducer 는 `pure function`이다.
- `previous state`와 `action`을 가진다.
- returns `next state`

```javascript
(previousState, action) => newState
```

It's called a reducer because it's the type of function you would pass to [`Array.prototype.reduce(reducer, ?initialValue)`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/Reduce).
reducer를 pure로 유지하는 것이 굉장히 중요하다. 리듀서에서 너가 절대 하지 말아야 할것을 알려줄께

- 인자값 변경하기
- API 호출 and routing transition과 같은 side effect 수행하기
- non-pure function 호출하기, e.g `Data.now()` or `Math.random()`

[advanced walkthrough](https://github.com/reactjs/redux/blob/master/docs/advanced/README.md) 에서 side effect수행하는 방식을 알아보자.

## reducer stay pure

- **동일한 argument가 주어지고**
- **그것은 next state를 계산하고**
  - **그것을 리턴한다.**
- **no surprise. no side effect. no api calls. no mutation. Just a calculation**

## write reducer

1. initial state를 작성하자
  - Redux는 처음에 reducer를 `undefined` state로 호출할 것이다.
  - app의 initial state를 리턴할 좋은 chance다

```javascript
import { VisibilityFilters } from './actions'

const initialState = {
  visibilityFilter: VisibilityFilter.SHOW_ALL,
  todos: []
}

function todoApp(state, action){
  if (typeof state === 'undefined') {
    return initialState
  }

  // For now, don't handle any actions
  // and just return the state given to us.
  return state
}
```

es6 default arguments syntax를 이용하여 짧게 하기

```javascript
function todoApp(state = initialState, action) {
  // For now, don't handle any actions
  // and just return the state given to us.
  return state
}
```

이제 `SET_VISIBILITY_FILTER` 를 처리하자. 필요한건 state에서 `visibilityFilter`를 변경하는 것이다.
```javascript
function todoApp(state = initialState, action) {
  // 스토어는 루트 리듀서에 액션과 현재 상태 트리를 보낸다
  // 이 때 모든 리듀서에 보내기 때문에 switch를 통해 action.type 분기를 가져야함
  switch (action.type) {
    case SET_VISIBILITY_FILTER:
      return Object.assign({}, state, {
        visibilityFilter: action.filter
      })
    default:
      return state
  }
}
```
Note that:
  1. **`state`를 변경하지 않는다. **
    - `Object.assign()`으로 copy본 생성
    - `Object.assign(state, {visibilityFilter: action.filter})` 또한 틀렸다.
      - 첫번째 인자를 변경한다.
      - empty object를 첫번째 인자에 넣어야 한다.
    - `{...state, ...newState}`를 작성하기 위해 object spread operator proposal 활성화해야 한다.

  2. **`default`로 `previous state`를 리턴한다.** unknown action에서 `previous state`를 리턴하는 것은 중요하다.

> **`Object.assign`**
> `Object.assign()`은 ES6다. 하지만 대부분 브라우저에서 구현이 되어있지 않다. use a polyfill, a Babel plugin or a helper from another library like `_.assign()`
>
> **`switch` and BoilerPlate**
> `switch` statement는 real boilerplate가 아니다. real boilerplate of Flux는 conceptual: the need to emit an update, the need to register the Store with a Dispatcher, the need for the Store to be an object.
>
> It's unfortunate that many still choose a framework based on whether it uses switch statements in the documentation. If you don't like switch, you can use a custom createReducer function that accepts a handler map, as shown in “reducing boilerplate”.

## Handling More actions

우리가 처리해야 할 2개의 action이 더 있어. `ADD_TODO`를 처리할 리듀서를 만들어보자.

```javascript
function todoApp(state = initialState, action){
  switch(action.type) {
    case SET_VISIBILITY_FILTER:
      return Object.assign({}, state, {
        visibilityFilter : action.filter
      })

    case ADD_TODO:
      return Object.assign({}, state, {
        todos: [
          ...state.todos,
          {
            text: action.text,
            completed: false
          }
        ]
      })
    default:
      return state
  }
}

```
Just like before, `state` or its field에 직접 작성하지 않았다. 대신에 new object를 리턴했다. new `todos`는 끝에 new item과 합친 old `todos`와 동일하다. fresh todo는 action의 데이터를 이용하여 생성된다.

Finally, `TOGGLE_TODO` handler의 구현 shouldn't come as a complete surprise:

```javascript
case TOGGLE_TODO:
  return Object.assign({}, state, {
    todos: state.todos.map((todo, index) => {
      if (index === action.index) {
        return Object.assign({}, todo, {
          completed: !todo.completed
        })
      }
      return todo
    })
  })
```

mutation의 resorting 없이 array안에 특정 item을 update하기를 원하기 때문에, index에서 item 없이 동일한 item을 가진 new array를 생성해야 한다. immutability helper, updeep, or other library 사용해. 만약 그것을 복제하지 않을 꺼라면 `state`내부에 어느것도 할당하지 말아야 해.

## Splitting Reducers
이제 다 합친거 봐보자. 근데 좀 장황하다 그치?

```javascript
function todoApp(state = initialState, action) {
  switch (action.type) {
    case SET_VISIBILITY_FILTER:
      return Object.assign({}, state, {
        visibilityFilter: action.filter
      })
    case ADD_TODO:
      return Object.assign({}, state, {
        todos: [
          ...state.todos,
          {
            text: action.text,
            completed: false
          }
        ]
      })
    case TOGGLE_TODO:
      return Object.assign({}, state, {
        todos: state.todos.map((todo, index) => {
          if(index === action.index) {
            return Object.assign({}, todo, {
              completed: !todo.completed
            })
          }
          return todo
        })
      })
    default:
      return state
  }
}
```

이해하기 쉽게 표현할 수 있을까? **`todos`와 `visibilityFilter`는 완전히 독립적으로 업데이트 된다.** state field는 서로 의존하고 more consideration is required, 하지만 쉽게 updating `todos`를 function 분리할 수 있다.
```javascript
function todos(state = [], action) {
  switch (action.type) {
    case ADD_TODO:
      return [
        ...state,
        {
          text: action.text,
          completed: false
        }
      ]
    case TOGGLE_TODO:
      return state.map((todo, index) => {
        if (index === action.index) {
          return Object.assign({}, todo, {
            completed: !todo.completed
          })
        }
        return todo
      })
    default:
      return state
  }
}

function todoApp(state = initialState, action) {
  switch (action.type) {
    case SET_VISIBILITY_FILTER:
      return Object.assign({}, state, {
        visibilityFilter: action.filter
      })
    case ADD_TODO:
    case TOGGLE_TODO:
      return Object.assign({}, state, {
        todos: todos(state.todos, action)
      })
    default:
      return state
  }
}
```

`todos` 또한 `state`를 허용한다. 하지만 그것은 배열이다! `todoApp`은 관리할 상태 조각을 준다. 그리고 `todos`는 그 slice를 업데이트하는 방법을 알고 있다. **This is called reducer composition, and it's the funamental pattern of building Redux Apps.**

reducer composition을 더 알아보자. `visibilityFilter`만 관리하는 리듀서 추출할 수 있니?
```javascript
function visibilityFilter(state = SHOW_ALL, action) {
  switch (action.type) {
    case SET_VISIBILITY_FILTER:
      return action.filter
    default:
      return state
  }
}
```

state의 부분을 관리하는 리듀서를 호출하는 function으로 main reducer를 재작성할 수 있다. 그리고 single object로 그것들을 combine한다. 완전한 initial state를 더이상 알 필요가 없다.
만약 `undefined`가 처음에 주어졌을 때, child reducer는 initial state를 리턴하는 것으로 충분하다.

```javascript
function todos(state = [], action) {
  switch (action.type) {
    case ADD_TODO:
      return [
        ...state,
        {
          text: action.text,
          completed: false
        }
      ]
    case TOGGLE_TODO:
      return state.map((todo, index) => {
        if (index === action.index) {
          return Object.assign({}, todo, {
            completed: !todo.completed
          })
        }
        return todo
      })
    default:
      return state
  }
}

function visibilityFilter(state = SHOW_ALL, action) {
  switch (action.type) {
    case SET_VISIBILITY_FILTER:
      return action.filter
    default:
      return state
  }
}

function todoApp(state = {}, action) {
  return {
    visibilityFilter: visibilityFilter(state.visibilityFilter, action),
    todos: todos(state.todos, action)
  }
}
```

**리듀서 각각은 global state에서 자신의 부분만 관리한다. `state` 파라미터는 every reducer마다 다르다. 그리고 그것이 관리하는 state의 부분에 상응한다**

app이 커질 때, reducer를 file로 분리하고 완전히 독립적으로 유지할 수 있고 다양한 data domain을 관리할 수 있다.

finally, Redux는 `combineReducers()` utility를 제공한다.

```javascript
import { combineReducers } from 'redux'

const todoApp = combineReducers({
  visibilityFilter,
  todos
})

export default todoApp
```

this is equivalent to :

```javascript
export default function todoApp(state = {}, action) {
  return {
    visibilityFilter: visibilityFilter(state.visibilityFilter, action),
    todos: todos(state.todos, action)
  }
}
```

subreducer들에게 다양한 key로 설정하거나 함수들을 다르게 호출할 수 있다. 이러한 combined reducer를 작성하는 2가지 방식은 완전히 동일하다.

```javascript
const reducer = combineReducers({
  a: doSomethingWithA,
  b: processB,
  c: c
})
```

```javascript
function reducer(state = {}, action) {
  return {
    a: doSomethingWithA(state.a, action),
    b: processB(state.b, action),
    c: c(state.c, action)
  }
}
```

`combineReducers()`가 하는 모든 것은 **key에 따라 선택된 state의 조각으로 리듀서를 호출하는 함수를 생성하는 것** 그리고 결과를 single object로 combining 하는 것이다. 만약 모든 리듀서가 state를 변경하지 않는다면 다른 reducer와 같이 `combineReducers()`는 new object를 생성하지 않는다.


각 these reducers는 global state의 부분을 관리한다. the `state` parameter는 리듀서마다 다르다. 그리고 그것을 관리하는 state 부분과 일치한다.

finally, Redux는 `todoapp` `combineReducers()` 라는 유틸을 제공한다.

```javascript
import { combineReducers } from 'redux'

const todoApp = combineReducers({
  visibilityFilter,
  todos
})

export default todoApp
```
