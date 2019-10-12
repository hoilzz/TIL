# useReducer로 useState 구현하는 방법

[useState를 useReducer로 구현하기](https://kentcdodds.com/blog/how-to-implement-usestate-with-usereducer)

TL;DR:

```js
const useStateReducer = (prevState, newState) =>
  typeof newState === 'function' ? newState(prevState) : newState;

const useStateInitializer = initialValue =>
  typeof initialValue === 'function' ? initialValue() : initialValue;

function useState(initialValue) {
  return React.useReducer(useStateReducer, initialValue, useStateInitializer);
}
```

## But Kent.. why기

재구현하는 건 동작 방법을 배우기 위한 좋은 방식이다.
