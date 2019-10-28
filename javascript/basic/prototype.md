# 프로토타입

JS의 모든 객체는 부모 객체와 연결되어있다.
이것은 OOP의 상속처럼 객체의 프로퍼티, 메서드를 상속받아 사용할 수 있다.
이러한 부모 객체를 **프로토타입 객체** 라고 한다.

프로토타입 객체는 생성자 함수로 생성된 인스턴스의 공유 프로퍼티를 제공하기 위해 사용된다.

JS의 모든 객체는 `[[Prototype]]`을 가진다.

`[[Prototype]]`

- 모든 객체는 이 프로퍼티를 가진다.
- **proto** 프로퍼티로 접근 가능.
- 이것은 null 또는 객체이며 상속을 구현하는데 사용된다.
- 객체 생성시 프로토타입은 결정되지만 다른 객체로 변경가능하다.
- 즉, 부모 객체를 변경할 수 있다.

prototype 프로퍼티

- 함수 객체만 가지고 있는 프로퍼티
- 함수 객체가 생성자로 사용될 때 이 함수를 통해 생성될 객체의 부모 역할을 하는 객체(프로토타입 객체)를 가리킨다.

## constructor 프로퍼티

프로토타입 객체는 constructor 프로퍼티를 갖는다.
이것은 자신을 생성한 객체를 (생성자 함수)를 가리킨다.

```js
// 중간 문제

var user = { name: 'hoilzz' };

console.log(user.constructor === Object);

console.log(Person.prototype.constructor === Person);

console.log(foo.constructor === Person);

console.log(Person.constructor === Function);
```

```js
// Person() 생성자 함수에 의해 생성된 객체를 생성한 객체는 Person() 생성자 함수이다.
console.log(Person.prototype.constructor === Person);

// foo 객체를 생성한 객체는 Person() 생성자 함수이다.
console.log(foo.constructor === Person);

// Person() 생성자 함수를 생성한 객체는 Function() 생성자 함수이다.
console.log(Person.constructor === Function);
```

## 프로토타입 체인

JS에서 특정 객체의 프로퍼티 or 메소드에 접근시 [[Prototype]]이 가리키는 링크를 따라
부모 역할을 하는 프로터타입 객체의 프로퍼티나 메서드를 차례로 검색한다.

```js
var student = {
  name: 'Lee',
  score: 90
};

// Object.prototype.hasOwnProperty()
console.log(student.hasOwnProperty('name')); // true
```

student는 hasOwnProperty라는 메서드를 가지지 않는데 어떻게 호출될까?

student의 [[Prototype]]이 가리키는 링크를 따라가보자.
Object.prototype이고 이 프로토타입 객체가 해당 메서드를 가진다.

## 객체 리터럴 방식으로 생성된 객체의 프로토타입 체인

객체 생성방법 세가지

1. 리터럴
2. 생성자 함수
3. Object() 생성자 함수

객체 리터럴은 JS 엔진이 내부적으로 Object() 생성자 함수를 사용하여 객체 생성한다.

```js
var person = {
  name: 'Lee',
  gender: 'male',
  sayHello: function() {
    console.log('Hi! my name is ' + this.name);
  }
};

console.dir(person);

console.log(person.__proto__ === Object.prototype);
console.log(Object.prototype.constructor === Object);
console.log(Object.__proto__ === Function.prototype);
console.log(Function.prototype.__proto__ === Object.prototype);
```

**Object.prototype은 프로토타입 체인의 종점이다.**

## 프로토타입 객체 확장하기

프로토타입 객체도 일반 객체와 같이 추가/삭제 할 수 있다.

```js
function Person(name) {
  this.name = name;
}

var foo = new Person('Lee');

Person.prototype.sayHello = function() {
  console.log('Hi! my name is ' + this.name);
};

foo.sayHello();
```

## 프로토타입 객체 변경하기

객체 생성시 프로토타입은 결정된다.
이 프로토타입 객체를 변경하여 부모 객체인 프로토타입을 동적으로 변경할 수 있다.
이것을 이용하여 상속을 구현할 수 있다.

주의할 점은

- 프로토타입 객체 변경 시점 이후에 생성된 객체는 변경된 프로토타입 객체를 **proto**에 바인딩
- 객체 변경 시점 이전에 생성된 객체는 변경 전 프로토타입 객체를 그대로 갖는다.

```js
function Person(name) {
  this.name = name;
}

var foo = new Person('Lee');

// 프로토타입 객체의 변경
Person.prototype = { gender: 'male' };

var bar = new Person('Kim');

console.log(foo.gender); // undefined
console.log(bar.gender); // 'male'

console.log(foo.constructor); // ① Person(name)
console.log(bar.constructor); // ② Object(), 객체 리터럴은 JS 엔진이 Object 생성자로 실행한다.
```

## 프로토타입 체인 동작 조건

객체의 프로퍼티 참조하는 경우, 해당 프로퍼티가 없는 경우 프로토타입 체인이 동작.

```js
function Person(name) {
  this.name = name;
}

Person.prototype.gender = 'male'; // ①

var foo = new Person('Lee');
var bar = new Person('Kim');

console.log(foo.gender); // ① 'male'
console.log(bar.gender); // ① 'male'

// 1. foo 객체에 gender 프로퍼티가 없으면 프로퍼티 동적 추가
// 2. foo 객체에 gender 프로퍼티가 있으면 해당 프로퍼티에 값 할당
foo.gender = 'female'; // ②

console.log(foo.gender); // ② 'female'
console.log(bar.gender); // ① 'male'
```

## Summary

JS의 모든 객체는 부모 객체와 연결되어 있음.
이 부모 객체는 프로토타입 객체.

이 프로토타입 객체는 (JS의 객체의 **proto**가 가리키는 객체)

- 생성자 함수로 생성된 인스턴스의 **공유** 프로퍼티를 제공하기위해 사용됨.
- 객체 생성시 프로토타입 객체 결정됨.(변경 가능)
- 상속을 구현하는데 사용.

prototype 프로퍼티

- 함수 객체만 가지는 프로퍼티
- 함수 객체가 생성자로 사용될 떄, 이 함수를 통해 생성된 객체의 부모 역할을 하는 객체를 가리킨다.

## qna

Q. 프로토타입 체인이란?
A. 모든 객체는 프로토타입 객체를 부모로 가진다.
어떤 객체에서 프로퍼티 접근시, 객체에 할당되지 않았을 경우 **proto** 프로퍼티를 통해 해당 프로퍼티 찾을 때까지 차례로 검색한다.

Q. 객체 리터럴은 어떻게 객체가 생성되는가?
A. JS 엔진에서 리터럴을 Object() 생성자 함수를 사용하여 객체 생성한다.
그래서 리터럴 객체의 **proto** 프로퍼티는 Object.prototype 객체를 가리킨다.

Q. 프로토타입 객체는 변경가능한가? 이를 이용하여 뭘 할 수 있는가?
A. 가능하다. 이를 이용하여 상속을 구현할 수 있다. 이 때 조심할 점은, 생성자 함수의 프로토타입 객체 변경 전과 후에 생성된 객체의 **proto**가 가리키는 프로토타입 객체가 다르다.
