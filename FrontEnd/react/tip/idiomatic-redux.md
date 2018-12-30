# idiomatic-redux 중 일부 발췌

출처:[idiomatic-redux](https://blog.isquaredsoftware.com/2017/01/idiomatic-redux-thoughts-on-thunks-sagas-abstraction-and-reusability/)

## TL;DR:

redux-thunk와 redux-saga 라이브러리는 redux의 "side-effects"를 위한 가장 널리 이용되는 라이브러다. 둘 다 AJAX request, multiple action dispatch, current store state 접근, 다른 복잡한 로직 제공를 만들 장소를 제공한다. 이와 같은 것을 제공하기 위해, `redux-thunk`는 `dispatch()`에 함수를 전달하도록 하고, `redux-saga`는 비동기 로직을 실행하기 위해 ES6 generator를 이용할 수 있다.

## The problem at Hand

몇가지 source들이 이 포스트에 영감을 제공했다:

### Dan Abramov - Don't use getState in thunks

...

### State Tracing

__Related concerns:__
- action에 대한 값의 source로 store state를 이용하는 것은 data 출처를 모호하게 한다.
- dispatched action trail에서 thunk를 사용하는 것은 잠재적으로 less visible하게 되는 결과를 낳는다.