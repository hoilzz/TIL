# Iteration protocols

[Iteration protocols](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Iteration_protocols)

iterable protocol과 iterator protocol이 있다.

> protocol은 표현법이다.

## iterable protocol

iterable 프로토콜은 JS 객체들이 어떤 값들이 loop되는 것과 같은 iteration 동작을 정의하는 것을 허용한다.
Object와 같은 다른 타입은 그렇지 않은 반면에, Array, Map과 같은 것들은 built-in iterable이다.

Object가 iterable 하기 위해서는 **@@iterator** 메서드 구현해야함.
즉, object의 prototype chain중 하나가 [Symbol.iterator](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Symbol/iterator)를 가져야한다.

### Symbol.iterator

이 프로퍼티는 object를 반환하고 iterator protocol을 따르는 arguments 없는 함수다.

> built-in iterable은 Array, String, Map, Set 등이 있는데
> 이들은 prototype에 [@@iterator] 프로퍼티가 반복할 값을 미리 지정해두었다.

> Symbol.iterator
> 객체에 대응하는 기본 이터레이터를 지정한다. for..of와 함께 사용된다.

```js
const iterable1 = new Object();

iterable1[Symbol.iterator] = function*() {
  yield 1;
  yield 2;
  yield 3;
};

for (value of iterable) {
  console.log(value);
}

console.log([...iterable1]);
// expected output: Array [1, 2, 3]
```

모르는게 너무 많이 나왔다. 좀 정리해보자.

iterable protocol은 JS 객체들이 for..of와 같은 구조에서 어떤 값이 loop 되는 것을 허용한다.
예를 들어 for..of와 같은 구조에서 iteration 동작을 정의하거나 사용자 정의하는 것이다.
이 때, array, string, map, set 이런 얘들인 built-in type이고, Object는 그렇지 않다.

Object도 가능하게 하려면 **@@iterator** 메서드(프로토타입에 Symbol.iterator key의 속성)를 구현하면된다.
그냥 구현하면 안되고 함수를 구현해야한다. 이 때 이 함수는 인자가 없고 객체를 리턴한다.
반환된 iterator는 반복을 통해서 획득할 값들을 얻을 때 사용된다.

iterator 객체에 대해 알아보자.

### iterator protocol

iteration protocol을 알아봤으니 iterator protocol을 알아보자?

**iterator** protocol은 value들의 sequence를 만드는 표준 방법을 정의한다.

iterator는 객체인데 다음 조건에 해당해야한다

- next 메서드를 가진다.
- 이 메서드는
  - 인자가 없다.
  - 2개의 속성을 가진 object를 반환한다.
    - done: boolean
      - Iterator가 마지막 작업을 마치면 true
    - value: 반환되는 값

몇몇 iterator들은 iterable(반복가능)이다.

### Iteration protocol 사용 예제

built-in type 처럼 동작하기 위해 객체에 iteration 동작을 정의해보자.

```js
var obj = {};

// iterable 프로토콜을 정의: 이 함수는 인자가 없고 객체를 리턴하는 @@iterator 메서드 구현
obj[Symbol.iterator] = function() {
  // iterator protocol을 정의: value들의 sequence를 만드는 표준 방법을 제공하기 위한 iterator 객체
  // iterator 객체는 next 메서드를 가진다. 이 메서드는 인자를 받지 않고 value와 done 프로퍼티를 가진 객체다.
  return {
    next: function() {
      if (this._first) {
        this._first = false;
        return { value: 'bye', done: false };
      } else {
        return {
          done: true
        };
      }
    }
  };
};
```

iteration이 빌트인 되어있는 string도 사용해보자.

```js
var string = 'hi';

var iteration = string[Symbol.iterator]();

iteration.next();
iteration.next();
```

## Iterable 예시

@@iterator 메서드를 가진 객체인 String, Array, Map, Set은 모두 내장 iterable을 가진다.

### 사용자 정의된 iterables

```js
var myIterable = {};
myIterable[Symbol.iterator] = function* () {
  yield 1;
  yield 2;
  yield 3;
}

[...myIterable];
const iteration = myIterable[Symbol.iterator]();
iteration.next();
iteration.next();
```

## Iterable과 함께 사용되는 문법

for-of loop, spread operator, yield\*, destructuring assignment는 iterable과 함께 사용되는 구문이다.

## generator object는 iterator 일까 iterable 일까

[generator object](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Generator)는 iterator이면서 iterable 이다.

iterable과 iterator 정의 및 성립 조건을 다시 보자.

> iterable
> iterable한 객체는 [Symbol.iterator] 메서드를 구현해야한다.
> 이 메서드는 iterator protocol을 따르는 객체를 반환하고 arguments 없는 함수다.

> iterator
> value들의 sequence를 만드는 표준 방법을 정의해야한다.
> 이것을 정의하기 위해 iterator 객체는
>
> - 어떤 객체를 반환하는 next 메서드를 가진다.
> - 이 메서드는 인자가 없고 done과 value를 가진 객체를 반환한다.

```js
var generatorObj = (function*() {
  yield 1;
  yield 2;
  yield 3;
})();

typeof generatorObj.next;
// "function", next 메서드를 가지고 있기 때문에 iterator
typeof generatorObj[Symbol.iterator];
// "function", @@iterator 메서드를 가지고 있기 때문에 iterable
generatorObj[Symbol.iterator]() === generatorObj;
// true, 이 Object의 @@iterator 메서드는 자기자신(iterator)을 리턴하니까 iterable하다고 할 수 있다.
[...generatorObj];
// [1, 2, 3]
```

## Q&A

Q. generator 함수는 뭔가?
A. 제너레이터 함수는 제너레이터 객체를 반환한다. 제너레이터 객체는 iterable 프로토콜과 iterator 프로토콜을 따른다.

Q. 각 프로토클에 대해 설명해달라.
A. iterable프로토콜은 iterator 객체를 반환하는 함수다. iterable은 객체들의 어떤 값들이 loop되는 것과 같은 반복 동작을 정의하도록 한다. built-in으로 iterable이 정의된 객체는 Array, Map, Set, String 등잉 있다. 객체가 iterable 하기 위해서는 Symbol.iterator 프로퍼티를 정의해야한다. 이것은 앞에서 설명한 iterator 객체를 반환하는 함수다.

iterator 객체는 값들의 sequence를 만드는 표준 방법을 정의한다. 이 객체는 next 메서드를 가지는데 이 메서드가 반환하는 객체는 done과 value 프로퍼티를 가진다.

```js
function *genObj() {
  yield 1;
  yield 2;
  yield 3;
}

const obj = genObj();

typeof obj.next;
// function, iterator다.
typeof obj[Symbol.iterator];
// function,  iterable이다.
obj[Symbol.iterator]() === obj
// 웃긴건데 제너레이터 객체에서 iterator 객체를 반환하면, 자기자신이다. 자기자신(iterator) 을 리턴하니까 iterable
[...obj];
```
