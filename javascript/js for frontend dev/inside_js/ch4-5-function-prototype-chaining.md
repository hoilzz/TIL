## 4.5.1 함수와 프로토타입 체이닝

### 프로토타입 체이닝

OOP 상속의 근간이 되는 prototype과 prototype chaining을 알아보자.

### OOP

JAVA에서 class가 있다.

JS에서는 class가 없다.

객체를 생성할 때, `객체 리터럴`, `생성자 함수`를 이용한다.

이 때, 생성된 객체의 부모 객체가 `prototype` 객체다.

javascript의 **모든 객체는 자신의 부모인 prototype 객체를 가리키는 참조 링크 형태의 숨겨진 property가 있다.**

`[[prototype]]` 프로퍼티 혹은 링크라고 불린다.

> NOTE
`함수 객체의 prototype 프로퍼티`와 `객체의 숨은 프로퍼티[[prototype]] 링크`는 다르다.

## 4.2.3.2 모든 함수는 prototype 프로퍼티를 갖는다.

`[[prototype]]` : 객체 입장에서 자신의 부모 역할을 하는 prototype 객체

`함수 객체가 가지는 prototype 프로퍼티` : 이 함수가 생성자로 사용될 떄, 이 함수를 통해 생성된 객체의 부모 역할을 하는 prototype 객체.

`함수의 prototype 프로퍼티`는 `함수명.prototype 객체`를 가리킨다.

`함수명.prototype 객체`의 유일한 `constructor`프로퍼티는 자신과 연결된 함수를 가리킨다.


---

다시 ch4.5.1로 돌아와서 돌아와서

---

> javascript에서 객체를 생성하는 건 생성자 함수
But, 생성된 객체의 실제 부모 역할을 하는 건, 생성자 자신이 아닌 생성자의 prototype 프로퍼티가 가리키는 prototype 객체다.


## 4.5.4 프로토 타입 체이닝의 종점

js에서 `Object.prototype` 객체는 프로토타입 체이닝의 종점이다.

생성된 객체에서 생성자 함수를 이용한 방식이에 상관없이 js 객체는 Object.prototype 객체가 가진 프로퍼티와 메서드에 접근 가능하다.

## 4.5.5 기본 데이터 타입 확장

js의 숫자, 문자열, 배열 등에서 사용되는 표준 메서드의 경우

이들의 prototype인 `Number.prototype`, `String.prototype` 등에 정의되어 있다.

물론 이러한 기본 내장 prototype 객체 또한 `Object.prototype`을 자신의 prototype으로 가지고 있다.


## 4.5.6 프로토타입도 js 객체다.

함수 생성시 자신의 prototype 프로퍼티에 연결되는

프로토타입 객체는 default로 constructor 프로퍼티만을 갖는 객체다.


## 4.5.7 prototype 메서드와 this 바인딩

프로토타입 체이닝을 통해 메서드를 찾았어도 `this`는 호출한 객체에 바인딩 된다.


## 4.5.8 default prototype은 다른 객체로 변경 가능하다

생성자 함수의 prototype이 바뀌면,

변경되기 전에 생성된 객체는 기존의 객체를 가리킨다.

변경된 후에 생성된 객체는 `[[prototype]]` 링크를 변경된 prototype 객체로 가리킨다.

```javascript
function Person(name){
	this.name = name;
}

var foo = new Person("foo");

console.log(foo.country); // undefined

Person.prototype = {
	country:'Korea'
}

var bar = new Person("change");

console.log(bar.country); // Korea
console.log(Person.prototype.country); // Korea
console.log(foo.country); // undefined
console.log(Person.prototype);
console.log(foo.constructor); // 프로토타입 체이닝 발생으로 [[Prototype]]이 연결된 변경되기 전 constructor를 가진 프로토타입 객체
console.log(bar.constructor); // 변경된 후 프로토타입 체이닝이 발생하지만 constructor 객체를 찾지 못하므로 다시 프로토타입 체이닝 발생하여 Object.prototype의 constructor를 가리키게 된다.

```

- `foo` 객체는 Person.prototype 객체를 자신의 `[[prototype]]`으로 연결한다.
	- `foo.country` 때, `foo`에는 country가 없으므로, 프로토타입 체이닝이 일어난다.
	- `Person.prototype`, `Object.prototype`에도 없으므로 undefined 생성.

- Person.prototype을 객체 리터럴 방식으로 생성하여 coutry 프로퍼티를 가진 일반 객체로 변경하였다.
	- 변경 후, `Person.prototype.constructor`는 어떤 값일까?
	- 변경한 프로토타입 객체는 단지 country 프로퍼티만 있다.
	- 똑같이 프로토타입 체이닝이 발생하는데, 프로토타입 객체는 객체 리터럴 방식으로 생성하였으므로 `Object.prototype`을 `[[Prototype]]`링크로 연결한다.
	- 이 때, `Object.prototype`은 `Object()` 생성자 함수와 연결된 빌트인 프로토타입 객체다.
	- 그래서 `Object()`새엉자 함수를 constructor에 연결하고 있다. 따라서 `Person.prototype.constructor`는 `Object()` 생성자 함수다.

## 4.5.9 객체의 프로퍼티 읽기나 메서드를 실행할 때만 프로토타입 체이닝이 동작한다

> 즉, 특정 프로퍼티에 값을 쓰려고 하면 프로토타입 체이닝 발생하지 않는다.
자바스크립트는 객체에 없는 프로퍼티에 값을 `쓰려고` 할 경우 동적으로 객체에 프로퍼티를 추가한다.

```javascript

function Person(name){
	this.name = name;
}

Person.prototype.country = 'Korea';

var foo = new Person('foo');
var bar = new Person('bar');

console.log(foo.country);
console.log(bar.country);

foo.country = 'USA'; // 이떄 country를 찾기 위해 프로토타입 체이닝 발생하지 않는다. 이유는, 읽기가 아닌 쓰기니까

console.log(foo.country);
console.log(bar.country);
```

## Summary

- 객체를 생성할 땐, `객체 리터럴`, `생성자 함수`를 이용한다.
	- 이 때 생성된 객체의 부모 객체가 `prototype` 객체다.

- JS의 모든 객체는 자신의 부모인 prototype 객체를 가리키는 **참조 링크 형태의 숨겨진 property** (`[[Prototype]]`, `__proto__`)이 있다.

	- `[[Prototype]]`은 객체 입장에서 자신의 부모 역할을 하는 prototype 객체다.

- 구분지어야 할게, `함수의 prototype` 프로퍼티는 `함수명.prototype` 객체를 가리킨다.

- 프로토 타입 체이닝의 종점은 `Object.prototype` 객체다.
	- 이 객체도 동일하게 `constructor` 프로퍼티를 가지고 있고, 이것은 생성자 함수 `Object()`를 가리킨다.

- `protytpe 체이닝`을 통해 메서드를 찾았어도 `this`는 호출한 객체에 바인딩 된다.

- default prototype은 다른 객체로 변경 가능하다.

- 프로토타입 체이닝은 다음에서 발생한다.
	+ 프로퍼티 읽기
	+ 메서드 실행하기

- 프로토타입 체이닝은 객체에 없는 값을 `쓰려고` 할 경우 프로토타입 체이닝이 발생하지 않는다.
	- 대신 동적으로 객체에 프로퍼티를 추가한다.
