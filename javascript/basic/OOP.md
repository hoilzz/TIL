# OOP 간단 정리

## 클래스 기반 언어

클래스란 같은 종류 집단에 속하는 속성과 행위를 정의한 것이다.
인스턴스는 런타임에 그 구조 변경할 수 없다.

## 프로토타입 기반 언어

JS에는 클래스 개념이 없지만 객체 생성 방법이 존재한다.

- 객체 리터럴
- Object() 생성자 함수
- 생성자 함수

> ES6의 class가 도입되었다.
> ES6의 클래스는 새로운 OOP 모델이 아니고 Class도 사실 함수이고 기존 prototype 기반의 syntatic sugar다.

## 생성자 함수와 인스턴스 생성

```js
// 생성자 함수(Constructor)
function Person(name) {
  // 프로퍼티
  this.name = name;

  // 메소드
  this.setName = function(name) {
    this.name = name;
  };

  // 메소드
  this.getName = function() {
    return this.name;
  };
}

var me = new Person('Lee');
var you = new Person('Kim');
var him = new Person('Choi');

console.log(me); // Person { name: 'Lee', setName: [Function], getName: [Function] }
console.log(you); // Person { name: 'Kim', setName: [Function], getName: [Function] }
console.log(him); // Person { name: 'Choi', setName: [Function], getName: [Function] }
```

위 생성자 함수의 문제점은?

여러개의 인스턴스 생성시 모든 인스턴스가 중복된 메소드를 프로퍼퍼티 가진다.
메모리 낭비다.

### 프로토타입 체인으로 해결하자.

```js
function Person(name) {
  this.name = name;
}

// 프로토타입 객체에 메소드 정의
Person.prototype.setName = function(name) {
  this.name = name;
};

// 프로토타입 객체에 메소드 정의
Person.prototype.getName = function() {
  return this.name;
};

var me = new Person('Lee');
var you = new Person('Kim');
var him = new Person('choi');

console.log(Person.prototype);
// Person { setName: [Function], getName: [Function] }

console.log(me); // Person { name: 'Lee' }
console.log(you); // Person { name: 'Kim' }
console.log(him); // Person { name: 'choi' }
```

## 상속

새롭게 정의할 클래스가 기존 클래스와 유사하다면 상속을 통해 다른 점만 구현하면된다.
코드 재사용은 개발 비용을 줄이기 때문에 중요하다.

JS는 프로토타입을 통해 상속을 구현한다.
**즉, 프로토타입을 통해 객체가 다른 객체로 직접 상속된다는 의미다**

JS의 상속 구현 방식은 클래스 기반 언어의 상속 흉내내서 구현할 수 있다.

### 클래스 기반 언어의 상속 방식 흉내내기

```js
// 부모 생성자 함수
var Parent = (function() {
  // Constructor
  function Parent(name) {
    this.name = name;
  }

  // method
  Parent.prototype.sayHi = function() {
    console.log('Hi! ' + this.name);
  };

  // return constructor
  return Parent;
})();

// 자식 생성자 함수
var Child = (function() {
  // Constructor
  function Child(name) {
    this.name = name;
  }

  // 자식 생성자 함수의 프로토타입 객체를 부모 생성자 함수의 인스턴스로 교체.
  Child.prototype = new Parent(); // ②
  // new 안쓰고 Object.create로 상속 구현하기.
  // Child.prototype = Object.create(Parent.prototype);

  // 메소드 오버라이드
  Child.prototype.sayHi = function() {
    console.log('안녕하세요! ' + this.name);
  };

  // sayBye 메소드는 Parent 생성자함수의 인스턴스에 위치된다
  Child.prototype.sayBye = function() {
    console.log('안녕히가세요! ' + this.name);
  };

  // return constructor
  return Child;
})();

var child = new Child('child'); // ①
console.log(child); // Parent { name: 'child' }

console.log(Child.prototype); // Parent { name: undefined, sayHi: [Function], sayBye: [Function] }

child.sayHi(); // 안녕하세요! child
child.sayBye(); // 안녕히가세요! child

// 상속 여부 따지기.
console.log(child instanceof Parent); // true
console.log(child instanceof Child); // true
```

### 프로토타입 패턴 상속

**`Object.create` 함수를 사용하여 객체에서 다른 객체로 직접 상속 구현하기**
위 패턴보다 간단하다. 위 방식에 비해 new 연산자를 통한 prototype 교체, 생성자 링크 파괴 등이 없다.

```js
// 부모 생성자 함수
var Parent = (function() {
  // Constructor
  function Parent(name) {
    this.name = name;
  }

  // method
  Parent.prototype.sayHi = function() {
    console.log('Hi! ' + this.name);
  };

  // return constructor
  return Parent;
})();

// create 함수의 인수는 프로토타입이다.
// 전달된 인수를 __proto__로 갖는 새로운 인스턴스를 가진다.
var child = Object.create(Parent.prototype);
child.name = 'child';

child.sayHi(); // Hi! child

console.log(child instanceof Parent); // true
```

인스턴스 child의 **proto** 는 Parent.prototype이다.
프로토타입 체인에 의해 Parent.prototype에 접근가능하다.

여기서 문제를 보완하자면

- Child.prototype.constructor는 Parent다.
  - 왜냐하면 인스턴스의 contructor 프로퍼티는 자신을 생성한 생성자 함수를 바라본다.
  - Child 생성자 함수로 변경해주자.

더 보완하자면
`Child.prototype = new Parent();`에서 새 인스턴스를 만들지 않고, `Object.create(proto)`메서드로 대체할 수 있다.

이 메서드는 proto인자에 전달된 객체를 프로토타입 객체로 갖는 새로운 객체를 리턴한다.

#### Object.create

폴리필을 보면

```js
// Object.create 함수의 폴리필
if (!Object.create) {
  Object.create = function(o) {
    function F() {} // 1
    F.prototype = o; // 2ㅣ
    return new F(); // 3
  };
}
```

1. 임의의 생성자 함수 F 생성
2. 생성자 함수 F의 prototype 프로퍼티에 전달된 객체를 할당한다.
3. 생성자 함수 F의 인스턴스를 생성하여 반환.

## Summary

상속을 구현하기 위해 프로토타입을 이용하면된다.

상속 여부를 확인하기 위해서는 `insatanceof` 메서드를 사용하면 된다.
이 메서드는 생성자의 prototype 속성이 객체의 프로토타입 체인 어딘가 존재하는지 판별한다.

```js
function Car(make, model, year) {
  this.make = make;
  this.model = model;
  this.year = year;
}
var auto = new Car('Honda', 'Accord', 1998);

console.log(auto instanceof Car); // true
console.log(auto instanceof Object); // true
```

## qna

상속 구현해보자.

```js
function Parent(name) {
  this.name = name;
}

Parent.prototype.sayHi = function() {
  console.log(this.name + ' hi');
};

function Child(name) {
  Parent.call(this, name);
}

Child.prototype = Object.create(Parent.prototype);
// 위에서 Parent 인스턴스 할당하는 순간 constructor는 Parent 생성자를 바라본다.
Child.prototype.constructor = Child;

Child.prototype.bark = function() {
  console.log(this.name + ' bark!');
};
```

// without Object.create

```js
function Parent(name) {
  this.name = name;
}

Parent.prototype.sayHi = function() {
  console.log(this.name + ' hi');
};

function Child(name) {
  Parent.call(this, name);
}

Child.prototype = new Parent();
// 위에서 Parent 인스턴스 할당하는 순간 constructor는 Parent 생성자를 바라본다.
Child.prototype.constructor = Child;

Child.prototype.bark = function() {
  console.log(this.name + ' bark!');
};
```
