## 5.5 Function 타입

### 함수가 사실 객체다.

- 모든 함수는 `Function 타입의 인스턴스`
- 다른 참조 타입과 마찬가지로 `프로퍼티와 메서드가 있음`
- 객체이기 때문에 함수 이름은 함수 객체를 가리키는 포인터일 뿐이지 함수와 결합되는게 아님

```javascript
// 함수 선언
// function sum(num1, num2){...}

// 함수 표현식
var sum = function(num1, num2){
	return num1 + num2;
}
sum.multiply = function(num1, num2){
		return num1*num2;
}
console.log("sum.multiply(10,10) : " + sum.multiply(10, 10)); // 100
```

- 변수 sum을 정의하면서 함수로 초기화
- 변수 sum으로 함수를 참조하므로 함수 이름은 필요하지 않다.

```javascript
var sum = new Function("num1", "num2", "return num1 + nu2"); // 노 권장

var anotherSum = sum;
sum = null;
anotherSum(20,10); // 30,
```

- `sum()`은 단순한 포인터이므로 `anotherSum()`과 무관하다.

- Function 생성자를 이용하여 함수 생성
- 매개변수 중 마지막은 함수 바디로 간주
- 함수는 객체고 함수 이름은 그를 가리키는 포인터를 가장 잘 나타내는 문장

### 5.5.1 오버로딩 없음

함수는 `객체`다.

즉, property와 메서드를 가질 수 있다.

함수 이름은 `pointer`다. 즉, 오버로딩이 불가능하다.

오버로딩 처럼 코드 작성하면 마지막으로 정의한 코드가 덮어쓴다.

### 5.5.2 함수 선언 VS 함수 표현식

javascript 엔진은 실행 컨텍스트에 데이터를 불러올 때,

- `함수 선언`은 어떤 코드도 실행하기 전에 모든 실행 컨텍스트에서 접근 가능
- `함수 표현식`은 코드 실행이 해당 줄까지 진행하기 전에 사용 불가능

```javascript
alert(sum(10,10));

function sum(num1, num2){
	return num1 + num2;
}
```

- 코드 실행 전에 `함수 선언 호이스팅`을 거친다.
- js엔진은 코드 평가시 `함수 선언`을 먼저 찾고 가장 위로 올린다.

```javascript
alert(sum(10,10)); // error

var sum = function (num1, num2){
	return num1 + num2;
}
```

- 위 코드는 함수 선언이 아닌 `초기화`다.
- 그러므로 `함수 선언 호이스팅`에서 배제된다.
- 즉, 해당 코드가 실행되기 전까지 변수 sum에 할당되지 않으므로 에러 발생


### 5.5.4 함수 내부 구조

함수 내부에는 `arguments`, `this`라는 특별한 객체가 있다.

`arguments`는 함수에 전달된 매개변수를 모두 포함한다.

- `callee` 라는 property : arguments 객체의 소유자인 함수를 가리키는 pointer

```javascript
function factorial(num){
	if(num <= 1) {
		return 1;
	} else {
		return num * factorial(num-1);
		// return num * arguments.callee(num-1);
	}
}

var truefactorial = factorial;

factorial = function(){
	return 0;
}

truefactorial(5); // 0 을 반환. 의도한대로 재귀함수 수행하기 위해 callee가 포함된 주코드 주석 해제해보자.

```

- 재귀 함수가 함수 이름에 의존하는 약점을 보완하기 위해 `arguments.callee(num-1)`를 사용해보자.

## this

- 함수가 실행중인 context 객체에 대한 참조
- 실행 context의 property다.

```javascript
AO={
	VO:{...},
	this: this value
}
```

- this는 context의 실행 코드 type과 직접 관련이 있다.

	1. 전역 type : 전역 코드 안의 this는 항상 전역 객체 자신이다.
	2. 함수 type
		- 함수에 정적으로 바인딩 되지 않고, context로 들어갈 때 결정된다. 그러므로 this가 가리키는 대상이 매번 다르다.

```javascript
var foo = {x:10};

var bar = {
	x:20,
	test:function(){
		console.log(this === bar);
		console.log(this.x);
		this = foo;
		console.log("this : ", this);
		console.log(this.x);
	}
}

bar.test(); // test()를 호출한 reference type의 base 객체는 bar 객체다. this는 base 객체인 bar를 가리킨다.
foo.test = bar.test;
foo.test(); // test()를 호출한 reference type의 base 객체는 foo 객체다. this는 base 객체인 foo를 가리킨다.
```

이와같이 함수 `호출 표현식의 형태`에 의해 this값이 결정된다.


### 5.5.5 함수 property와 method

모든 함수의 공통 property
- `length` : 함수가 넘겨받을 것으로 예상하는 이름 붙은 매개변수 숫자
- `prototype` : 모든 참조 타입의 인스턴스 메서드가 존재하는 곳
	- `toString()`, `valueOf()`는 prototype에 존재하며 객체 인스턴스는 이에 접근한다.


#### apply(), call()

둘 다 소유자인 함수를 호출하며 `this`를 넘긴다.

결과적으로 함수 내부에서 **this 객체 값을 바꾸는 것**과 동일하다.

**apply와 call의 핵심은 매개변수를 전달해 호출하는 것이 아닌 `this`를 바꾸는데 있다.**

```javascript
window.color = "red";
var o = {color: "blue"};

function sayColor(){
	console.log(this.color);
}

sayColor.call(this);  // this는 전역 scope에서 호출 됐으므로 window를 가리킨다. 값은 red
sayColor.call(window); // 함수의 컨텍스트를 window로 설정, red
sayColor.call(o); // 함수의 컨텍스트를 o로 설정, blue

//
```

**call이나 apply를 사용시 스코프를 바꾸면 객체마다 일일히 메서드를 등록하지 않아도 된다.**

`o.sayColor = sayColor` 이런거 안해도 된다.

call과 apply의 차이
- call : 인자를 인수로 보낸다.
- apply : 인자를 배열로 보낸다.

#### bind()

ES5에서는 `bind()`가 있다.

새 함수 인스턴스 만들 때 this는 bind()에 전달된 값이다.

```javascript
window.color = "red";
var o = {color: "blue"};

function sayColor(){
	console.log(this.color);
}

var objSayColor = sayColor.bind(o);
objSayColor(); // blue
```

objSayColor의 this는 `.bind(o)`에 의해 o에 묶여있다.

그래서 전역에서 함수 호출하더라도 항상 blue를 출력한다.





## Summar

함수가 `Function` 타입의 인스턴스다. 즉 함수도 `객체`의 일종이다.

함수는 객체이므로

	- `메서드`가 있다. 이 메서드를 통해 함수의 동작 방식을 확장할 수 있다.
	- `프로퍼티`도 있다.
	- 함수 이름은 함수 객체를 가리키는 포인터일 뿐이다.
		- 그래서 함수와 결합되는게 아니다.
		- 그래서 오버로딩도 없다.

함수에는 함수 선언과 함수 표현식이 있다.

- 함수 선언은 `함수 선언 호이스팅`을 거치므로 코드 실행 전에 모든 실행 컨텍스트에서 접근 가능하다.
- 함수 표현식은 할당될 때까지, 즉 코드 실행이 해당 줄까지 진행하기 전까지 사용 불가능하다.

함수 내부 구조에는 `arguments`, `this`라는 특별한 객체가 있다.

`arguments`는 함수에 전달된 매개변수를 모두 포함한다.

	- `callee`는 arguments 객체의 소유자인 함수를 가리킨다.

<hr>

`this`

this값을 결정하기 위해
- 실행 코드 type과 관련이 있다.
- 함수 type의 경우, `함수 호출 표현식의 형태`에 의해 this값이 결정된다.

<hr>

`apply`, `call`

`this`를 바꾸기 위한 함수다.

이것을 사용하여 스코프를 바꾸면 객체마다 일일히 메서드를 등록하지 않아도 된다.

ES5에서는 이와 비슷한 `bind`가 있다.





- 함수는 객체다
- 함수는 Function 타입의 인스턴스다.
- 함수 선언 vs 함수 표현식
  + 함수 선언시 호이스팅을 통해 코드 실행 전 실행 컨텍스트에서 접근 및 실행 가능
  + js 엔진은 코드 평가시 제일 먼저 함수 선언을 찾은 다음 이들을 맨 위로 올림
  - 함수 표현식은 선언이 아닌 초기화 문장이라 호이스팅 포함 안됨
- eval()은 매개변수를 실제 ECMAScript 문장으로 해석하여 eval()이 있던 위치에 삽입
