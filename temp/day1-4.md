# day1-4

## 열거 가능한 값, 콜렉션

FP에서는 컬력센을 많이 다룬다. 컬렉션을 다루는 대표적인 함수인 `map, filter, reduce , find`에서 사용할 수 있는 값들을 아래와 같이 정할 수 있다. iterator 혹은 generator를 실행한 결과 값을 이용하면 무한 수열도 표현 가능하다.

JS에는 콜렉션이라는 클래스가 없다. 그러면 무엇을 콜렉션으로 볼까?

1. JSON 데이터 타입 내의 object
2. Array, Map, Set ...
3. 그 외 `[Symbol.iterator]()`가 구현된 모든 iterable과 iterator
4. Generator를 실행한 결과 값

map :: Coll a => Coll b // collection인

[10]이 collection이라면
[10] => [20]을 만드는게 map이라고 하자. 그러면 [10].map(a => a + 10)이다. 그러니까 map을 규정할 때 위와 같은 코드로 한다고 하고, collection은 1~4로 정의한다고 하자. 그러면 array like 와 같은 값은 들어오지 못한다.

순회를 위한 로직에서 1~4는 for를 쓸 수 있다.

## 컬렉션 순회

`for, while, i++, j++, length` 등을 이용하면 루프는 명령적이고 코드가 복잡하다. i++ 등을 직접 다루거나 순회하는 객체의 값을 변경하면 영향을 받기도 한다. 스코프와 실행 컨텍스트와 관련된 실수도 일어날 수 있다. 또한 비동기 상황 등을 고려하면 파편화가 심해진다. *그렇다고 `head, tail`로 추상화하기에는 성능 이슈가 만만치 않다.*

```javascript
const coll = [1,2,3,4];
const [head, ...tail] = coll;
// for문이 아닌 재귀로 돌릴 수 있다.
// 재귀가 호출 될 때마다 쓸데없는 배열이 계속 생성된다.
```


ES6의 `for..of`를 사용하면 이런 문제를 최소화 할 수 있고 `for..of`는 선언적이다. `for..of`문은

- Iterable/Iterator 프로토콜을 따르기 때문에 다형성이 높다.
- 비동기 상황에서 재귀 등의 복잡한 로직을 파편화 없이 구현할 수 있다.

따라서 JS에서 순회를 해야할 경우 `for..of`를 사용하면 좋다. 이렇게하면 상대적으로 안전한 명령형 프로그래밍을 할 수 있다. 또한, FP에 사용될 함수들을 간결한 코드로 구현할 수 있다.

## 불변성

불변성은 값을 변경하는 성질하는 막는것. `Object.freeze`와 같이 값이 변하지 않도록 하는 것은 아니다. 이것은 일부다. 값의 변화를 줄 때 원본값을 변경시키지 않겠다가 불변성이다.

### 불변적으로 배열 변경하기

```javascript
const list = [1,2];
console.log([...list, 3]);
console.log(list);
```

### 불변적으로 객체 변형하기

```javascript
const object = { a: 1, b: 2 };
const object2 = {...object, ...{b: 3}};

const object3 = Object.assign({}, object, { a: 2})
```

## 영속성 혹은 존속성