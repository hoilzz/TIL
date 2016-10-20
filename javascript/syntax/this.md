# this
from mozila
A function's this keyword는 다른 언어와 약간 다르게 행동한다. strict mode와 non-strict 모드에서 약간 차이점을 가진다.
<br>
- 대부분의 경우, *this* 의 값은 함수가 호출되는 방식에 따라 결정됨
- **실행 중에 할당에 의해 세팅되지 못함**
- 그리고 함수 호출될 때마다 다르다.
- ES5는 함수 호출방법과 상관없이 function's this의 값을 세팅하기 위해 *bind* method를 소개한다.
- ECMAScript 2015는 this가 lexically scoped되도록 arrow function을 소개한다.
  - 실행 컨텍스트를 둘러싼 *this* 의 값으로 세팅된다.

## Global context
global 실행 컨텍스트에서 (outside of any func), *this*는 global object를 가리킨다. (strict든 아니든)

```javascript
console.log(this.document === document) // true
console.log(this === window);

this.a = 37;
console.log(window.a);
```

## Function context
function 내부에서, **this**의 값은 함수가 호출되는 방식에 달려있다.

### simple call
다음 코드는 strict mode가 아니기 때문에 그리고 **this** 의 값이 call로 설정되있지 않기 때문에, **this** 는 global object가 default 값이다.

```javascript
function f1() {
  return this;
}
// In a browser
f1() === window;
```

strict mode에서, 실행 컨텍스트에서 들어갔을 때, 그것이 뭘로 세팅되있든 간에 **this** 의 값은 남아있다. 따라서 다음의 경우에 **this**는 undefined가 디폴트 값이다.

## bind
ECMAScript5는 Function.prototype.bind를 소개한다.
- **f.bind(someObject)** 는 새로운 함수(with the same body and scope as f)를 생성한다. 하지만 this는 original function에서 일어난다. new function에서 그것은 bind의 첫번째 인자에 영원히 바인딩 된다. (함수가 사용된 방식 상관없이)

## Arrow functions

이것은 렉시컬리하게 세팅되어있다. execution context의 this의 값이 세팅되어있다. In global code, 그것은 global object로 세팅될 것이다.

```javascript
var globalObject = this;
var foo = (() = > this);
console.log(foo() === globalObject); // true
```

foo가 호출되는 방식은 중요하지 않다. its this는 global object로써 유지된다. 만약 apply or bind와 함께 object()의 메서드로서 호출되면 이것은 유지된다.

```javascript
// Call as a method of an object
var obj = {foo: foo};
console.log(obj.foo() === globalObject); // true

// Attemp to set this using call
console.log(foo.call(obj) === globalObject); // true

// Attemp to set this using bind
foo = foo.bind(obj);
console.log(foo() === globalObject); // true
```
