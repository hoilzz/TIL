# 참조타입

> 객체로 작업하기
> 배열 생성하고 조작하기
> 자바스크립트의 데이터 타입 이해
> 원시 데이터 및 원시 래퍼로 작업하기

### 참조 값(객체)이란
- **특정 '참조 타입' 의 인스턴스**
- **데이터와 기능을 그룹으로 묶는 구조**
- 참조타입은 '클래스'가 아니다.
- 근데 객체가 가져야 할 프로퍼티와 메서드를 정의한다는 점 때문에 '객체 정의'라고 불리기도 함

- 객체 생성
  + new 연산자 뒤에 '생성자' 사용

## 5.1 Object 타입

### Object 인스턴스를 명시적으로 생성하는 방법

1. new 연산자와 Object 생성자 함께 쓰기
2. 객체 리터럴 표기법

```javascript
var person = new Object();
```

```javascript
var person = {}
```

> 객체리터럴 표기 방법을 선호, 코드 양 줄고 관련 데이터 한눈에 알아볼 수 있으니까

```javascript
function displayInfo (args) {
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

- `args`를 통한 매개변수 접근


## 5.2 Array 타입

`Object 타입` 다음으로 많이 쓰이는 `Array 타입`

다른 언어의 배열과 달리, ECMAScript는 어떤 데이터 타입이든 다 넣을 수 있다.

첫번쨰에는 문자열, 두번째에는 숫자, 세 번쨰는 객체 이렇게 넣을 수 있다.

### 배열 생성

1. `new Array()`

2. `new Array(30)`
	- 배열에 데이터가 몇 개 들어갈지 알고 있다면, 위와 같이 `length` 프로퍼티가 30인 배열을 만들 수 있다.
	- 길이를 미리 알고 있다면 이 방법을 사용

3. `new Array("Greg")`
	- 문자열 "Greg"만 있는 배열 생성

4. `= ["red", "blue"], []`
	- `배열 리터럴` 표기 방법

<br>

`length` property 는 RDONLY가 아니다.

**이 값을 바꾸면** 배열 길이가 그에 맞게 바뀌면서 **데이터를 제거하거나 빈 슬롯을 추가한다**.

```javascript
var colors = ["red", "black", "green"];

colors.length = 1;

colors[2] // undefined;

colors // ["red"]

colors[colors.length] = "purple";

colors // ["red", purple]
```


### 5.2.1 배열 감지

전역 스코프가 하나뿐인 단순한 웹 페이지에서는 `instanceof` 연산자를 쓰면 된다.

```javascript
if(value instanceof Array){
	// ..
}
```

instanceof의 문제는, 실행 컨텍스트가 하나 뿐이라고 가정한다는 점이다.

웹페이지에 프레임이 여러 개 있다면(iFrame 같은걸 끼얹어보자) 전역 실행 컨텍스트가 두 개이다. 따라서 Array 생성자도 두 개다.

배열을 한 프레임에서 다른 프레임으로 전달했다면 전달한 배열은 전달 받은 프레임에서 직접 생성한 배열과는 다른 생성자 함수를 가진다.

ES5에서는 이 문제를 우회하기 위해 `Array.isArray()`메서드를 제공한다.


### 5.2.2 변환 메서드

```javascript

var colors = ["red", "blue", "green"];

colors.toString(); // "red,blue,green"
colors.valueOf(); // ["red", "blue", "green"];

```

`toString()`은 쉼표로 분리된 문자열 반환
`valueOf()`는 특정 객체의 원시값 반환


### 5.2.5 정렬 메서드

`sort()` 메서드 그대로 쓴 결과에 만족할 수 없을 때, `비교 함수`를 넘겨서 순서를 조절할 수 있다.

비교 함수는 매개변수 2개를 받아서

<!-- - 첫 번째 매개변수(a)가 두 번째 매개변수(b)보다 앞에 있어야 한다면 음수를
	- 1,15 순으로 오름차순일 경우
	- `A(0번쨰)<B(1번째) : -1`

- 두 매개변수의 순서가 같다면 0을
- 첫 번째 매개변수가 두 번째 매개변수보다 뒤에 있어야 한다면 양수를 반환한다.
	- 15,1 순으로 내림차순일 경우
	- `A(0번쨰)<B(1번째) : 1` -->

sort함수는 아래의 값 중 하나를 반환한다.

	1. 첫번째 인수가 두 번째 인수보다 작을 경우 : -1
	2. 두 인수가 같을 경우 : 0
	3. 첫번째 인수가 두 번째 인수보다 큰 경우 : 1

```javascript
var arr = [10,5,12,22,1];

function compare(A, B){
	if(A<B) return -1;
	else if (A>B) return 1;
	else return 0;
}

function compare2(a,b){
	return a-b;
}
function compare3(a,b){
	return b-a;
}

arr.sort(compare);
```





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


## summary

js 객체는 참조 값이라 불리고, 다음과 같이 내장된 참조 타입을 통해 특정한 타입의 객체를 만들 수 있다.

- 모든 참조 타입은 Object 타입의 작동방식을 상속한다.
- Array 타입은 데이터의 순서 있는 목록이며 포함한 값을 조작하고 변환하는 기능 제공
	- `length` property를 통해 데이터 제거 및 빈 슬롯 추가 가능
	- `Array.isArray()`로 배열 감지 가능
