# Hoisting
: 끌어올리기

#### ex1 value 변수 선언전에 value 호출 (호이스팅)
```javascript
function hoistingExam() {
  console.log("value = " + value);
  var value = 10;
  console.log("value = " + value);
}
hoistingExam();
// 실행결과
// value = undefined
// value = 10
```

#### ex2 value 변수 선언 후에 value 호출 (일반적)
```javascript
function hoistingExam(){
  var value;
  console.log("value = " + value);
  value = 10;
  console.log("value = " + value);
}
// 실행 결과
// value = undefined
// value = 10
```
ex1의 경우 다른 프밍 언어에서는 선언문 전에 호출시 에러 발생한다. 하지만 JS의 경우 호이스팅 됨으로써 ex2와 같이 동작한다.
- 즉, 변수 선언문이 scope 안의 제일 상단부로 끌어올려진다.
- 선언문이 있던 자리에서 초기화가 이루어진다.
- 그 결과, ex1의 첫번째 value 호출에서 초기화되지 않은 undefined
- 두번째 value 호출에서 초기화된 값이 나옴

## '함수 선언문' 방식만 함수의 호이스팅 가능
ex1
```javascript
hoistingExam();
function hoistingExam(){
  ...
}
```
ex2
```javascript
hoistingExam();
var hoistingExam = function(){
  ...
}
```
ex3
```javascript
hoistingExam();
var hoistingExam = new Function("", ...)
```
ex2,3은 호이스팅 불가
- 함수 표현 식과 Function생성자를 통한 함수 정의는 변수에 함수를 초기화시킨다.
- 선언문이 호이스팅 되어 상단으로 올려지더라도 함수가 아닌 변수로써 인지된다.
- 함수명()과 같이 함수 실행이 아닌 변수명을 기재하면 undefined 결과 나온다.
