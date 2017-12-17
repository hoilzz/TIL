# Function Programming

함수형 프밍은 부수 효과가 없다. 즉, 들어온 인자가 같으면 동일한 값을 리턴한다. 이것을 `pure function`이라고 부를 수 있다. 또한, 모듈화를 높여서 높을 조합성을 보인다. 이것을 통해, 오류를 줄이고 안정화를 높일 수 있다. 간단한 예시를 보자.

```javascript
function add(a, b) {
    return a + b;
}
```

## Not Pure Function

pure function이 아닌 경우를 보자.

### 1. 참조하는 변수가 상수가 아닌 변화하는 값

변수 c가 변화가 있을 수 있는 변수라면 add3은 순수함수가 아니다. 하지만 c가 상수값이라면 순수함수다.

```javascript
var c = 20;
function add3(a, b) {
    c = b;
    return a + b;
}
console.log(add3(10,1));
console.log(add3(10,2));
console.log(add3(10,3));
c = 40;
console.log(add3(10,1));
console.log(add3(10,2));
console.log(add3(10,3));
```

### 2. 객체의 프로퍼티를 직접 변경

```javascript
var obj = { val : 10};
function add4(obj, b) {
    obj.val += b;
}
console.log(obj1.val);
add4(obj1, 20);
console.log(obj1.val);
```

객체의 값을 직접 변경하는 not pure function 예제다. 위와 같이 코딩하는게 틀린게 아니다. 그냥 Pure Function이 아니다. 왜냐하면 **넘어온 인자의 값을 변경**하고 있기 때문이다. 그렇다면 `순수함수는 객체의 상태를 변경할 수 없을까?` **원래 있던 값은 그대로 두고 새로운 값을 만든다. 그리고 원하는 값이 바뀌면서 새로운 값을 리턴하는 식으로 함수를 만든다.** 위 `add4` 함수와 동일한 일을 하지만 외부의 상태에 영향을 미치지 않는 함수를 만들어보자. 아래 예제는 pure function한 예제다.

```javascript
var obj1 = {};
// obj의 값을 변경하지 않으면서 b의 값을 더하
function add5(obj, b) {
    return { val: obj.val + b }
}

console.log(obj1.val);
var obj2 = add5(obj1, 20);
console.log(obj1.val);
```

obj와 동일하게 생긴 그리고 value를 변경하면서 새로운 객체를 리턴한다. **인자를 변경하지 않으면서 외부 상태도 변경하고 있지 않다.** 이제 콘솔 값이 동일하다.

## 평가 시점이 중요하지 않다.

순수함수는 **평가 시점이 중요하지 않다.** 예를 들어, add2라는 함수는 또다른 외부값을 참조한다. 항상 동일한 인자 값을 주더라도 동일한 값을 리턴하지 않는다. **어느 타이밍에 함수를 호출하느냐**에 따라 동일 인자값을 전달 하더라도 리턴 값이 달라진다. 

## 정리

순수함수는 언제나 호출해도 동일한 리턴값을 전달한다.
이것을 통해 얻는 이점은

- 함수가 굉장히 안전하고 다루기 쉽다.
- 높은 조합성으로 다양한 로직을 만들 수 있다.
  - 반면에, 순수함수가 아니면 타이밍에 따라 결과값이 달라지기 때문에 불안전하고 조합성이 낮다.

순수함수가 아닌 경우는

- 함수에서 참조하는 변수가 상수가 아닌 변화하는 값일 경우
- 넘어온 인자값의 객체 프로퍼티를 직접 변경하는 경우
- 평가 시점에 따라 값이 달라지는 경우