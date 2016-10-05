# 참조타입

> 객체로 작업하기
> 배열 생성하고 조작하기
> 자바스크립트의 데이터 타입 이해
> 원시 데이터 및 원시 래퍼로 작업하기

### 참조 값(객체)이란
- **특정 '참조 타입' 의 인스턴스**
- 데이터와 기능을 그룹으로 묶는 구조
- 참조타입은 '클래스'가 아니다.
- 객체가 가져야 할 프로퍼티와 메서드를 정의한다는 점 때문에 '객체 정의'라고 불리기도 함

- 객체 생성
  + new 연산자 뒤에 '생성자' 사용

## 5.1 Object 타입
### Object 인스턴스를 명시적으로 생성하는 방법
1 new 연산자와 Object 생성자 함께 쓰기
2 객체 리터럴 표기법

1
```javascript
var person = new Object();
```

2
```javascript
var person = {}
```

> 객체리터럴 표기 방법을 선호, 코드 양 줄고 관련 데이터 한눈에 알아볼 수 있으니까

```javascript
function display (args) {
  var output = "";
  if (typeof args.name == "string") output+= "Name: " + args.name + "\n";
  if (typeof args.age == "number")  output+= "Age: " + args.age + "\n";
  alert(output);
}
displayInfo({
  name: "Nicholas",
  age: 29
})
displayInfo({
  name: "Greg"
})
```

### 객체 프로퍼티의 접근 방식
1 점      `person.name`
2 대괄호   `person["name"]`
  - 장점 : 변수를 써서 프로퍼티 접근 가능    
    ```
    var propertyName = "name";
    person[propertyName]
    ```
> 일반적으로 점 표기법이 좋음. 프로퍼티 이름에 변수가 필요할 때만 대괄호 쓰기

## 5.2 Array 타입

Object 타입 다음으로 많이 쓰이는 Array 타입

### 배열 생성
1 new Array()
2 new Array(30)

### 5.2.8 반복 메서드
매개변수 2개
1 배열의 각 데이터에서 실행할 함수
  - 데이터, 데이터의 인덱스, 배열 자체
2 함수를 실행할 스코프 객체
  - 스코프는 this의 값에 영향을 미친다.

- every() : 배열의 모든 데이터에서 콜백함수 호출, 반환 값이 전부 true이면 true 반환
- filter() : true인 데이터를 새 배열에 저장하여 반환ㅇ
- foreach() : 반환 값이 없다
- map() : 결과를 새 배열에 저장하여 반환
- some() : 반환 값 중 하나라도 true면 true 반환

## 5.5 Function 타입
### 함수가 사실 객체다.
- 모든 함수는 Function 타입의 인스턴스
- 다른 참조 타입과 마찬가지로 프로퍼티와 메서드가 있음
- 객체이기 때문에 함수 이름은 함수 객체를 가리키는 포인터일 뿐이지 함수와 결합되는게 아님

```
  var sum = function(num1, num2){
    return num1 + num2;
  }
```
- 변수 sum을 정의하면서 함수로 초기화
- 변수 sum으로 함수를 참조하므로 함수 이름은 필요하지 않다.

```
  var sum = new Function("num1", "num2", "return num1 + nu2"); // 노 권장
```
- Function 생성자를 이용하여 함수 생성
- 매개변수 중 마지막은 함수 바디로 간주
- 함수는 객체고 함수 이름은 그를 가리키는 포인터를 가장 잘 나타내는 문장

### 5.5.2 함수 선언 VS 함수 표현식

```
 alert(sum(10,10));
 function sum(num1, num2){
   return num1 + num2;
 }
```

#### 함수 선언
- 코드 실행하기 전엔 이미 모든 실행 컨텍스트에서 접근하고 실행 가능
- WHY ? `함수 선언 호이스팅(끌어올리다)`이란 과정을 통해 함수 선언을 읽고 실행 컨텍스트에 추가하기 때문
  - js 엔진은 코드 평가시 제일 먼저 함수 선언을 찾은 다음 이들을 맨 위로 올림
  - 즉 함수 선언이 소스코드에서 해당 함수 실행하는 부분 보다 뒤에 있다고 하더라고 `끌어올림(hoist)`
- 다음과 같이 표현 바뀌면 에러

#### 함수 표현식

```
  alert(sum(10,10));
  var sum = function (num1, num2){
    return num1 + num2;
  }
```
- 에러 이유는 함수 선언이 아닌 초기화 문장이기 때문
- 실행 전에는 변수 sum에 할당되지 않기 때문이다


### 5.3.3 값처럼 쓰는 함수
- 매개변수
- 실행결과로 다른 함수 반환하는것


# 5.7 내장된 싱글톤 객체
Object나 Array, String 같은내장 객체 이외에 Global, Math 두 가지 싱글톤 객체를 더 정의

## 5.7.1 Global 객체
- 명시적으로 접근할 수 없다.
- 전역 변수나 전역 함수라는 것은 존재 하지 않는다. 전역에서 정의한 변수와 함수는 모두 Global 객체의 프로퍼티가 된다.
  + `isNaN()`, `isFinnite()`, `parseInt()` 등 Global 객체의 메서드

### URI 인코딩 메서드
- 브라우저에 전달할 URI를 인코드하는 메서드
- encodeURI(), encodeURIComponent()
- 쿼리 스트링을 인코드하는 경우가 많으므로 encodeURIComponent() 많이 사용

### eval() 메서드
- Global 객체에서 다룰 마지막 메서드는 강력한 eval()
- ECMAScript 인터프리터 자체인 듯 동작

  ```
  eval("alert('hi')");
  alert('hi');
  ```

- 위 두 문장은 동일
- **인터프리터가 eval()을 만나면 매개변수를 실제 ECMAScript 문장으로 해석하여 eval()이 있던 위치에 삽입**
  + 인자값은 eval을 호출한 실행 컨텍스트의 일부분으로 간주되며 해당 컨텍스트와 같은 스코프 체인을 갖음

  ```
  var msg = "hello world";
  eval("alert(msg)");
  ```

- 위에서 변수 msg는 eval()을 호출한 컨텍스트 바깥에서 정의되었지만 변수의 내용이 alert를 통해 표시됨.
- 두 번째 줄이 실제 코드로 변환되기 때문.
- 마찬가지로 eval() 내부에서 함수나 변수를 정의한 후 외부에서 참조할 수 있다.

  ```
  eval("function SayHi() {alert('hi');}");
  sayHi();
  ```
- 마찬가지로 eval()이 실제 함수로 대체되므로 그 다음 줄에서 sayHi()호출 가능

## NOTE
ECMA-262에서는 Global 객체에 접근할 수 없도록 했지만 웹브라우저에서는 window 객체를 통해 Global 객체에 접근 가능




## Summary
- 함수는 객체다
- 함수는 Function 타입의 인스턴스다.
- 함수 선언 vs 함수 표현식
  + 함수 선언시 호이스팅을 통해 코드 실행 전 실행 컨텍스트에서 접근 및 실행 가능
  + js 엔진은 코드 평가시 제일 먼저 함수 선언을 찾은 다음 이들을 맨 위로 올림
  - 함수 표현식은 선언이 아닌 초기화 문장이라 호이스팅 포함 안됨
- eval()은 매개변수를 실제 ECMAScript 문장으로 해석하여 eval()이 있던 위치에 삽입
