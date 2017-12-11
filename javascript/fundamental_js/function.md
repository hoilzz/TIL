# Function

- es3, 5
- es6

## Basic

자바스크립트에서 함수는 다른 객체처럼 속성(property) 및 메서드를 가질 수 있는 일급 객체다. 다른 객체와 구별되는 점은 함수는 **호출**될 수 있다는 것이다. (함수는 `Function` 객체다.)

함수는 2가지 방식으로 호출된다. `new`를 사용하여 호출 또는 `new` 없이 호출할 수 있다. `new` 키워드로 호출되는 `생성자`의 경우, return되는 기본값(기본 값이란 return문을 작성하지 않을 경우)은 자신의 `this` 매개변수 값이다. `new` 없이 호출되는 경우, 기본 반환 값은 undefined다.

일단, 자바스크립트 함수가 생성되는 3가지 방식을 알아보자.

1. 함수 선언식
2. 함수 표현식
3. Function() 생성자 함수

## 함수 정의

### 1. 함수 선언식₩₩

JS에서 함수는 일반 객체 처럼 값으로 취급된다. 때문에 객체 리터럴 방식으로 일반 객체 생성하는 것처럼 `함수 리터럴`을 이용해 함수를 생성할 수 있다.

```javascript
function add(x, y){
	return x + y;
}
```

### 2. 함수 표현식

JS에서 함수는 `하나의 값`이다. (`함수는 일급 객체다`) 따라서 함수도 숫자나 문자열처럼 변수에 할당하는 것이 가능하다.

```javascript
var add = function (x, y){
	return x + y;
}

var plus = add;
```

함수 변수 add는 함수의 참조값을 가진다. 그래서 plus 변수에도 그 값을 할당할 수 있다.

C의 포인터처럼 add와 plus는 동일한 익명함수를 가리킨다.

### 3. Function() 생성자 함수를 통한 함수 생성하기

JS의 함수도 `Function()`이라는 **기본 내장 생성자 함수로부터 생성된 객체**다.
함수 선언문, 함수 표현식은 `Function()` 생성자가 아닌 함수 리터럴 방식으로 함수를 생성한다. 하지만 결국엔 `Function()` 생성자 함수로 함수가 생성된다고 볼 수 있다.

```
new Function (arg1, arg2, ..., functionBody)
```

위의 예제를 `Function()` 생성자를 이용하여 add 함수를 생성 해보자

```javascript
var add = new Function('x', 'y', 'return x + y');
```

> 함수 호이스팅
`더글라스 크락포드의 JS good parts` 에서 함수 표현식만을 사용할 것은 권하고 있다. 그 이유 중 하나가 함수 호이스팅 때문이다.
```javascript
add(2,3);
function add(x, y){
	return x + y;
}
add(3, 4)
```
1번 라인에서 add() 함수가 정의되지 않았음에도 add 함수를 호출 할 수 있다. **함수가 자신의 위치에 상관 없이 함수 선언문 형태로 정의한 함수의 유효 범위는 코드의 맨 처음부터 시작한다.** 이것이 함수 호이스팅이다.
더글락스 크락포드는 함수 사용 전에 반드시 함수 선언해야 하는 규칙을 무시하므로 구조를 엉성하게 만든다고 지적하며, `함수 표현식`을 사용할 것을 권장했다.


## 함수도 객체다.

- 일반 객체처럼 `property`들을 가질 수 있다.


### 함수는 값으로 취급된다.

다시 말하자면, 함수도 일반 객체처럼 취급될 수 있다.

- 리터럴에 의해 생성
- 변수나 배열의 요소, 객체의 프로퍼티 등에 할당 가능
- 함수의 인자로 전달 가능
- 함수의 리턴값으로 리턴 가능
- 동적으로 프로퍼티를 생성 및 할당 가능

이와 같은 특징 때문에 자바스크립트에서 함수는 `일급 객체(First Class)`다. 일급 객체라는 말은 앞에서 나열한 기능이 모두 가능한 객체를 일급 객체라고 부른다. 이 때문에 함수형 프로그래밍이 가능하다.


## this

자바스크립트에서 함수 호출시 매개변수로 전달되는 인자값, `arguments` 객체 및 `this` 인자가 함수 내부로 암묵적으로 전달된다. this는 **함수가 호축ㄹ되는 방식**에 따라 this가 다른 **객체를 참조(this 바인딩)**한다.

### 1. 객체의 메서드 호출할 떄 this 바인딩

```javascript
var myObj = {
  name: 'hoil',
  sayHello: function () {
    console.log('hello '+this.name)
  }
}

var otherObj = {
  name: 'doodoo'
}

otherObj.sayHello = otherObj.sayHello

myObj.sayHello(); // hello hoil
otherObj.sayHello(); // hello doodoo
```

sayHello() 메서드에서 this.name 값을 출력하는 간단한 함수다. myObj, otherObj객체로부터 각각 호출 된다. sayName에서 this는 자신을 호출한 객체에 바인딩 된다. 

### 2. 함수 호출시 this 바인딩

자바스크립트에서 함수 호출시, 해당 함수 내부 코드에서 사용된 this는 전역 객체에 바인딩된다. 브라우저에서는 전역 객체 window에 바인딩된다. 

```javascript
var name = 'hoil';

console.log(name);
console.log(window.name);
```

전역변수 name을 정의하고 출력하는 코드다. 이제 함수 호춝시 this 바인딩이 어떻게 되는지를 보자.

```javascript
var introduce = 'i am hoil';
console.log(window.introduce); // i am hoil

var sayHello = function() {
  console.log(this.introduce);
}

sayHello(); // i am hoil
```

함수 호출에서의 this 바인딩 특성은 **내부 함수을 호출했을 경우**에도 그대로 적용된다. 



## ES6

### generator 함수



```javascript
function* sayHello(name) {
  yield "1. hello " + name;
  yield "2. second called";
  if (name.startsWith("N")) {
    yield "3-a. N " + name;
  }
  yield "3-b. third called";
}
```

`function*` 선언은 generator function을 정의한다. 이 함수는 `Generator` 객체를 반환한다. 위 코드에서 기존의 함수와 제너레이터 함수와의 다른 점을 2가지 정도 발견할 수 있다. 

- `function*` 키워드
- `yield` 구문이 존재한다. return과 비슷하다. 차이점은 함수에서 return은 단 한 번 실행된다. 하지만, 제너레이터 함수의 yield는 **여러번** 실행된다. **`yield`는 제너레이터의 실행을 멈췄다가 다음에 다시 시작할 수 있게 만든다.**

이제 실행해보자.

```javascript
var iteratorObj = sayHello('hoil');
// [object Generator]
iteratorObj.next();
// { value: '1. hello hoil', done: false}
iteratorObj.next();
// { value: '2. second called', done: false }
iteratorObj.next();
// { value: '3-b. third called', done: false }
iteratorObj.next();
// { value: undefined, done: true}
```

일반적인 함수의 동작 방식은 호출하면 바로 실행된다. 그래서 return 문을 만나거나 예외(exception) 발생할 때까지 실행된다. 위 코드에서 `sayHello('hoil')`은 일반 함수를 호출하는 코드 같아 보인다. 하지만 제너레이터 함수는 호출시 즉시 시랳ㅇ되지 않는다. 그 대신 *generator 객체*를 리턴한다. (iteratorObj 변수) 이 제너레이터는 실행이 얼어붙은 함수라고 표현할 수 있다. 첫번째 줄 바로 앞에서 실행이 얼어붙은 함수이기 때문이다.

제너레이터 객체의 `.next()`메소드 호출시 스스로 해동되어 다음 `yield`까지 실행된다. 그래서 `iteratorObj.next()` 마다 다른 문자열 값을 얻을 수 있었다. 

`.next()`의 호출에서, 마지막에 도달시 `done` 프로퍼티가 `true`가 된 것을 확인할 수 있다. 그래서 `value`도 `undefined`다.


### Arrow Function

자신의 this, arguments, [super](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Operators/super) 또는 new.target을 바인딩 하지 않는다. 화살표 함수는 항상 익명이다. 이 함수 표현은 메소드 함수가 아닌 곳에 적당하다. 그래서 생성자로써 사용할 수 없다. 

#### 바인딩 되지 않는 this

화살표 함수 나오기 전까지, 모든 함수는 자신의 `this` 값을 정의했다. OOP 스타일 프로그래밍에서 귀찮은 작업이 항상 필요했다.

> this는 생성자 함수의 경우 새로운 객체를 가리킨다. `strict mode`에서 함수 호출은 `undefined`, 함수가 객체 메서드로써 호출된 경우 해당 객체를 가리킨다. 

```javascript
function User() {
  // new 키워드를 통하여 호출시 this는 자신의 인스턴스
  // new가 아닐 경우 전역변수
  this.name = 'noname';
  setInterval(function sayName() {
    // sayName() 함수는 this를 전역객체에서 찾는다.
    // 이는 User() 생성자에 정의된 this와 다르다.
    console.log(this.name);
  }, 1000);
}

var user = new User();
```

위와 같은 문제를 해결하기 위해 this를 참조하는 변수를 선언한다.

```javascript
function User() {
  var self = this;
  self.name = 'noname';

  setInterval(function sayName(){
    console.log(self.name);
  }, 1000)
}
```

하지만 위와 같이 하는 대신에, 바인딩한 함수는 적절한 `this` 값이 `sayName()` 함수에 전달될 수 있도록 할 수 있다. 화살표 함수는 자신만의 this를 생성하지 않는다. **this는 자신을 감싸고 있는 컨텍스트의 의미를 갖는다.** 즉, this는 렉시컬 컨텍스트를 가진다. 

```javascript
function User(){
  this.name = 'noname';
  
  setInterval(() => {
    console.log(this.name);
  }, 1000);
}
```

### 바인딩 되지 않은 arguments

`arguments` 객체를 바인딩 하지 않기 때문에, 단순히 scope내 이름에 대한 참조다.


### 메소드로 사용되는 화살표 함수


서브루틴(메서드가 아닌 함수), 

```javascript
var obj = {
  myMethod: function(){
    setTimeout(function(){...}, 0);
  }
}
```

함수는 호출될 때마다 2가지 scope를 가진다. 여기서 lexiocal scope는 코드를 둘러싸고 있는 구문 구조를 가리킨다. 즉, 코드가 작성된 그 문맥에서 결정된다는 말이다. dynamic scope는 런타임 도중 실행 컨텍스트나 호출 컨텍스트에 의해 결정된다. 


