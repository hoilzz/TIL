# 참조타입

> 객체로 작업하기
> 배열 생성하고 조작하기
> 자바스크립트의 데이터 타입 이해
> 원시 데이터 및 원시 래퍼로 작업하기

### 참조 값(객체)이란
- **특정'참조 타입'의 인스턴스**
- 데이터와 기능을 그룹으로 묶는 구조
- 참조타입은 '클래스'가 아니다.
- 객체가 가져야 할 프로퍼티와 메서드를 정의한다는 점 때문에 '객체 정의'라고 불리기도 함

객체 생성
- new 연산자 뒤에 '생성자' 사용

## 5.1 Object 타입
### Object 인스턴스를 명시적으로 생성하는 방법
1 new 연산자와 Object 생성자 함께 쓰기
2 객체 리터럴 표기법

1
```
var person = new Object();
```

2
```
var person = {}
```

> 객체리터럴 표기 방법을 선호, 코드 양 줄고 관련 데이터 한눈에 알아볼 수 있으니까
```
function display (args) {
  var output = "";

  if (typeof args.name == "string") output+= "Name: " + args.name + "\n";
  if (typeof args.age == "number")  output+= "Age: " + args.age + "\n";"
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

### 5.5.4 apply()
apply 메서드는 소유자인 함수를 호출하면서 this를 넘기는데, 결과적으로는 함수 내부에서 this 객체의 값을 바꾸는 것이나 마찬가지
- 매개변수로 소유자 함수에 넘길 this와 매개변수 배열을 받는다.
- 2번째 매개변수는 Array의 인스턴스 or arguments 객체

```
  function sum(num1, num2){
    return num1 + num2;
  }

  function callSum1(num1, num2){
    return sum.apply(this, arguments);
  }
  function callSum2(num1, num2){
    return sum.apply(this, [num1, num2]);
  }

  console.log(callSum1(10,10)); // 20
  console.log(callSum2(10,10));
```
- callSum1은 자신의 this와 arguments 객체를 매개변수로 넘김
- callSum2는 arguments 객체가 아닌 매개변수 배열을 넘김
