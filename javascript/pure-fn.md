# What is a Pure function?

[pure fn이란?](https://medium.com/javascript-scene/master-the-javascript-interview-what-is-a-pure-function-d1c076bec976)

순수함수는 FP, 안전한 동시성, react + reddux app을 포함한 다양한 목적에 필수적이다.
하지만 "pure function"이란 무엇일까?

## What is a function?

function은 **argument** 라는 input을 받고 **return value** 라 불리는 output을 만든다. 함수는 다음 목적을 제공한다.

- **Mapping** : 주어진 input을 기반으로 output을 만든다. 함수는 input 값과 output 값을 **매핑** 한다.

- **Procedures** : 함수는 일련의 스템을 수행하기 위해 호출된다. 이 시퀀스는 절차로 알려져있고, 절차형 프밍 스타일이다.

- I/O : 몇몇 함수는 스크린, 스토리지, 시스템 로그, 네트워크와 같은 시스템의 다른 부분과 소통하기 위해 존재한다.

## Mapping

함수는 input 인자와 return value를 매핑한다. 함수는 input을 가지고 상응하는 output을 리턴한다.

## Pure Function

> 함수가 순수하지 않다면, 반환 값을 사용하지 않고 호출하는 것이 합리적이다.
> 순수 함수만이 반환 값을 사용하는 것이 합리적이다.

```js
const double = x => x * 2;
```

- input이 같으면 **항상** 동일 output을 리턴한다
- FP의 기초를 형성한다.
  - 외부 상태에 대해 완전히 독립적이다.
  - 공유가능한 mutable state를 다룰 때 생기는 버그에 영향을 받지 않는다.
- 극도로 독립적
  - 이동하기 쉬움
  - 리팩터링 쉬움
  - 코드 재구성하기 쉬움
  - 유연하고 변화하는 요구사항 대응하기 쉬움
  - **테스트 하기 쉬움**
- side effect가 없다.
- **불변성**

## 불변성

JS 객체 인자는 참조값이다. 이것은 함수가 객체나 배열 파라미터에 대해 프로퍼티를 변경할 수 있다는 것이다.
이것은 함수 외부에서 접근 가능한 상태를 변경한다는 의미다.
순수 함수는 외부 상태를 변경하지 않아야 한다.

```js
// impure addToCart mutates existing cart
const addToCart = (cart, item, quantity) => {
  cart.items.push({
    item,
    quantity,
  });
  return cart;
};

// Pure addToCart() returns a new cart
// It does not mutate the original.
const addToCart = (cart, item, quantity) => {
  const newCart = lodash.cloneDeep(cart);

  newCart.items.push({
    item,
    quantity,
  });
  return newCart;
};
```

순수 함수의 대표적인 사례는 리덕스의 리듀서다.
리덕스는 각 리듀서 내부의 전체 앱 상태를 처리하지 않고 리듀서를 구성할 수 있다. (with `combineReducer()`)
전체에서 가장 작은 부분만 업데이트해야하는데, 리덕스는 전체 앱을 매번 deep clone deep 할 필요가 없도록 해준다.
대신에, non-destructive 배열 메서드를 사용하거나 Object.assign() 을 사용하여 앱의 작은 부분을 업데이트할 수 있다.

- 참조 투명성을 원하면, 순수 함수를 사용해야 한다.

## qna

Q. 순수함수란?
A. 언제든 동일한 input으로 호출할 떄, 동일 output을 리턴해주는 함수다

Q. 순수함수를 사용하면 뭐가 좋은가?
A. 사이드 이펙트에 대해 걱정하지 않아도 된다. 즉, 이 함수는 언제호출하든 동일 input 동일 output이라는 신뢰를 가질 수 있다. 사이드 이펙트를 가지지 않기 때문에, 리팩터링과 같은 변화에 대응하기 쉽다. 또한 독립된 상태라 테스트하기도 쉽다.
