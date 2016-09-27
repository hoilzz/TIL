# 언어의 기초
자바스크립트의 핵심은 ECMAScript라는 가상언어로 정의. 웹 브라우저에서 가장 널리 구현된 ECMASCript 버전은 ECMA-262 3판 (지금은 5판?)

## 3.1.4 스트릭트 모드
ECMAScript 5에서는 '스트릭트 모드'라는 개념 도입. 스트릭트 모드는 기존과는 다른 방식으로 js를 파싱하고 실행하라고 지시하는 것

> use strict  // 전체 스크립트에 스트릭트 모드 적용

이 문법은 ECMAScript 3과 호환됨

함수 단 하나만 스트릭트 모드로 실행하려면 다음 선언을 함수 본문 맨 앞에 추가

> function doSomething() {
  "use strict"
  // 함수 본문
}

## 3.3 변수

var 연산자는 변수를 로컬 스코프에서 정의, 즉 함수 종료시 즉시 파괴

  function test() {
    var msg = "hi" // 로컬 스코프에서 정의됨
  }
  test();
  alert(msg); // 에러

var 연산자 생략시 전역 변수 선언

  function test() {
    msg = "hi" // 로컬 스코프에서 정의됨
  }
  test();
  alert(msg); // 출력


## 3.4 데이터 타입

ECMAScript에는 5가지 기본적인 타입이 있다. (primitive data type이라고 불림)
1 Undefined
2 Null
3 Boolean
4 숫자
5 문자열
+ 객체 (이름-값 쌍의 순서 없는 목록)

### 3.4.1 typeof 연산자
ECMAScript는 느슨한 타입을 채택했으므로 변수의 데이터 타입을 알아내야 할 때가 있다.

값(변수)에 typeof 연산자를 적용하면 다음 문자열 중 하나를 반환
- 정의되지 않은 변수 : "undefiend"
- 불리언 : "Boolean"
- 문자열 : "string"
- 숫자 : "number"
- 함수를 제외한 객체 또는 null : "object"
- 함수 : "function"

  var msg = "some string";
  alert(typeof msg);  // **typeof는 함수가 아닌 연산자이므로 괄호 쓰지 않아도 된다.**

### 3.4.2 undefined 타입
undefined는 특별한 값. var를 써서 변수 정의했지만 초기화하지 않았다면 undefined가 할당됨

  var msg;
  alert(msg == undefined) // true

*Note*
변수를 초기화하지 않으면 자동으로 undefined가 할당된다. 하지만 초기화를 권장한다
WHY? typeof에서 undefined 반환시 해당변수가 초기화되지 않은 것인지, 정의되지 않은 것인지 바로알 수 있다.


### 3.4.3 Null 타입
빈 객체를 가리키는 포인터. 즉 typeof 하면 object 반환

  var car = null;
  alert(typeof car); // "object"

undefined는 null에서 파생했으므로 두 값이 표면적으롣 ㅗㅇ일

  alert(null == undefined) //true

true인 이유는 연산자가 피연산자 비교시 암시적 타입변환함

변수의 값에 undefined는 할당하면 안되지만 null은 다르다.
**객체를 사용해야하지만 해당 객체를 이용할 수 없을 때 항상 그 자리에 null이 와야함**


## 3.4.4 불리언 타입

| 데이터 타입 | true     | false |
| :------------- | :------------- |
| 불리언       | true       |  false |
| 문자열       | 비어있지 않은 문자열 | " "(빈 문자열) |
| 숫자        | 0이 아닌 모든 숫자 | 0, NaN |
| 객체 | 모든 객체 | null |
| undefined | 해당 없음 | undefined|

**Note**

var msg = "HelloWorld"
if (msg) {
  alert("Value is true");
}

이 때 msg 값이 실수로 객체를 쓰면 (항상 true) 흐름이 완전히 바뀌기 때문에 조심.

## 3.4.5 숫자 타입
### NaN

Not a Number라는 특별한 값.
- 숫자를 반환할 것으로 의도한 조작이 실패했을 때 반환하는 값
- 예를 들어, 어떤 숫자를 0으로 나누려 하면 ECMAScript에서는 NaN을 반환

- Nan == Nan // false
- **isNaN()** 함수 따로 제공, 숫자로 변환 할 수 없는 값을 넘기면 true 반환

  isNan(NaN)      // true
  isNan(10)       // false - 10은 숫자
  isNan("10")     // false - 숫자 10으로 변경 가능
  isNan("blue")   // true - 숫자로 바꿀 수 없다
  isNan(true)     // false - 1로 바꿀 수 있다.

### 3.4.6 문자열 타입

### 3.4.7 객체 타입

ECMAScript에서 객체는 데이터와 기능의 집합
- 객체는 new 연산자 다음에 객체 타입의 이름을 써서 만듬
- Object 타입의 '인스턴스'를 만들고 프로퍼티나 메서드를 추가하여 객체 생성

  var o = new Object();

**Object 인스턴스 자체는 유용하지 않지만 개념은 매우 중요** 하다.
ECMAScript의 Object 타입은 자바의 java.lang.Object 처럼 이 타입에서 파생되는 모든 객체의 원형

- Object 타입의 인스턴스는 Object 타입의 프로퍼티와 메서드를 전부 상속
- Object의 인스턴스는 다음 프로퍼티와 메서드를 가진다
  - constructor : 해당 객체를 만드는 데 쓰인 함수. 위 예제는 Object() 함수가 생성자
  - hasOwnProperty (propertyName) : 해당 프로퍼티가 객체 인스턴스에 고유하며 프로토타입에서 상속하지 않았음을 확인. 프로퍼티 이름은 반드시 문자열
                                    예를 들어 o.hasOwnProperty("name") 같은 형식
  - isPrototypeOf(object) : 해당 객체가 다른 객체의 프로토타입인지 확인 (5장에서 프로토타입 설명할께)
  - toLocaleString() : 객체를 지역에 맞게 표현한 문자열 반환
  - toString() : 객체를 문자열로 변환 후 반환
  - valueOf() : 객체를 나타내는 문자열이나 숫자, 불리언을 반환 toString과 같은 값 반환할 때가 많다


## 3.5 연산자

  var b = false;
  b++ // 숫자 1

## 3.7 함수
- 꼭 값을 반환하지 않아도 된다.
- return 문 뒤에 반환 값 써서 반환 가능


### 3.7.1 매개변수의 이해
ECMASCript 함수는 매개변수 숫자를 따지지 않고, 데이터 타입도 체크하지 않는다. **매개변수를 2개 받도록 만들었더라도 반드시 2개 전달해야 하는 것 아니다** 이렇게 되는 이유는 **매개변수가 내부적으로는 배열로 표현** 되기 때문이다. 함수는 arguments라는 객체를 갖는데, 이 객체를 통해 매개변수값 접근 가능. length 프로퍼티 혹은 arguments[0]과 같은 형태로 접근 가능하지만 Array의 인스턴스는 아니다.

function SayHi() {
  alert("Hello " + arguments[0] + ", " +  arguments[1]);
}

ECMASCript함수의 중요한 특징을 묘사하는 예제다. 이름 붙은 매개 변수는 편리하지만 반드시 필요한 건 아니다. 다른 언어와 달리 ECMAScript에서는 매개변수의 유효성 검사를 하지 않는다.

**ECMASCript 매개변수는 모두 값으로 넘겨야 한다** 매개변수를 참조 형식으로 전달할 수는 없다.

  "use strict"
  function doAdd(num1, num2) {
    arguments[1] = 10;
    console.log(num1, num2);
    console.log(arguments);
    // arguments = {100, 10} // 에러
  }

  doAdd(10)     // 10, undefined
                // [10]
  doAdd(20,30)  // 20, 30
                // [20, 10]


### 3.7.2 오버로딩 없음
ECMAScript 함수에는 오버로딩이 없다. ECMAScript 함수에는 시그니처 (매개변수의 타입과 개수)가 없고 매개변수는 그저 배열일 뿐이고 값에 제한이 없기 때문이다.

## 3.8 요약
- ECMAScript 기본 데이터 타입은 Undefined, Null, boolean, 숫자, 문자열
- ECMAScript는 정수와 부동소수점 숫자를 구분하지 않는다. 숫자 데이터 타입이 두가지 모두를 나타낸다.
- 복잡한 데이터 타입인 Object 타입도 있으며, 이 타입은 js의 모든 객체의 기반
- 스트릭트 모드는 js에서 에러가 자주 생기는 부분에 몇 가지 제약을 가한다

- 함수든 언제든, 무슨 값이든 반환할 수 있으므로 함수 반환값 미리 명시할 필요 없다.
- **값을 반환하지 않는 함수는 undefined 를 반환**
- ECMAScript 함수에는 시그너처 성질이 없다. (매개변수가 어떤 값이든 가질 수 있기 때문)
- 함수에 넘기는 매개변수 숫자 제한 없다. arguments 객체로 접근 가능
