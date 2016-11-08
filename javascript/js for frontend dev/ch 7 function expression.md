# 함수 표현식
> 함수 표현식의 특징
> 함수와 재귀
> 클로저를 이용한 고유 변수

함수 선언에서 가장 뚜렷한 특징 `호이스팅`
- 함수 선언부를 다른 코드보다 먼저 읽고 실행하기

함수를 정의하는 2가지 방법
1. function 키워드 다음에 함수 이름 쓰기
```javascript
function functionName(arg0){

}
```
2. 함수 표현식
```javascript
var functionName = function(arg0, arg1) {
}
```
- 함수 표현식은 일반적인 변수 할당과 비슷
- 함수를 생성하고 이를 functionName에 할당
- 이렇게 생성된 함수는 function 키워드 다음에 함수 이름이 없으므로 익명함수로 간주
  - 때때로 `람다함수` 라고도 한다
- 함수 표현식은 다른 표현식과 마찬가지이므로 반드시 호출하기 전에 할당해야 한다.
```javascript
sayHi();
var sayHi = function(){

}
```
이것은 에러를 일으킨다. 호이스팅을 이해해야 함수 선언과 함수 표현식 사이의 차이 이해 가능
```javascript
// 이렇게 절대 하지마
if (condition) {
  funtion sayHi(){
    alert("hi");
  }
} else {
  function sayHi(){
    alert("yo");
  }
}
```
**위 패턴은 대부분의 브라우저에서 두번째 선언을 사용한다.**

```javascript
// 이건 괜춘
var sayHi;
if(condition) {
  sayHi = function(){
    alert(hi);
  }
} else {
  sayHi = function(){
    alert(yo);
  }
}
```
**condition에 따라 sayHi에 각각 다른 표현식을 할당**

#### 함수 표현식을 사용하면
다른 함수에서 사용할 수 있도록 **함수를 반환**하는 형태도 가능
```javascript
function createComparisonFunction(propertyName) {
  return function(object1, object2){
    var value1 = object1[propertyName];
    var value2 = object2[propertyName];
    return 1;
  }
}
```
`createComparisonFunction` 함수는 `익명함수`를 반환한다. 이렇게 **값처럼 쓰이는 함수**를 `함수 표현식`이라고 한다.

## 7.2 클로저
`익명 함수`와 `클로저`는 잘못 혼용된다.
클로저 : 다른 함수의 스코프에 있는 변수에 접근 가능한 함수
```javascript
function createComparisonFunction(propertyName) {
  return function(object1, object2){
    // 요기서부터
    var value1 = object1[propertyName];
    var value2 = object2[propertyName];
    // 요까지
    return 1;
  }
}
```
주석 사이의 부분은 `내부 함수(익명함수)` 이면서 `외부 함수의 변수(propertyName)`에 접근한다.
- **내부 함수가 반환 되어 다른 컨텍스트에서 실행되는 동안에도 propertyName에 접근 가능**
  - **내부 함수의 스코프 체인에 createComparisonFunction()의 스코프가 포함되기 때문**
위를 더 잘 이해하기 위해 처음 호출시 무슨일이 일어나는지 보자.
- 먼저, 스코프 체인이 어떻게 생성되고 사용되는지 자세히 알아야 한다
  - 함수 호출시, 실행 컨텍스트와 스코프 체인이 생성된다.
  - 함수의 활성화 객체는 arguments 및 이름 붙은 매개변수로 초기화 된다.
  - 외부 함수의 활성화 객체는 스코프 체인의 두 번째 객체다.
- 이 과정이 포함 관계에 있는 함수에서 계속 발생하여 스코프 체인이 전역 실행 컨텍스트에서 종료될 때까지 이어진다.
- 함수를 실행하면 값을 읽거나 쓸 변수를 스코프 체인에서 검색

```javascript
function compare(value1, value2){
  if (value1 < value2) {
    return -1;
  } else if (value1 > value2) {
    return 1;
  } else {
    return 0;
  }
}
var result = compare(5,10);
```
이 코드는 **전역 실행 컨텍스트에서 호출하는** compare()라는 함수를 생성
- compare()를 처음 호출시 arguments, value1, value2를 포함한 활성화 객체 생성
- 전역 실행 컨텍스트의 변수 객체는 `this`와 `result`, `compare`를 포함하는 compare 실행 컨텍스트의 스코프 체인의 다음에 위치

---노트---

클로저는 이와 다르게 동작
- 다른 함수 내부에 존재하는 함수는 외부 함수의 활성화 객체를 자신의 스코프 체인에 추가
- 따라서
