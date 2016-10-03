# 객체

객체가 가진 프로퍼티 유지하는 것 외에 `프로토타입`이라고 하는 다른 객체의 프로퍼티를 상속받는다.
객체의 메서드들은 일반적으로 상속받은 프로퍼티이고, 이를 `프로토타입 상속`이라고 한다.
자바스크립트의 객체는 `정적 객체`를 흉내낼 수도 있고, 정적 타입 언어에서의 구조체처럼 사용할 수 있다.

## 모든 객체는 3가지 속성을 갖는다
- prototype은 상속받은 프로퍼티들을 가진 객체를 참조
- class는 객체의 자료형(타입)을 특정짓는 문자열
- extensible 속성은 객체에 새 프로퍼티를 추가할 수 있는지 결정
이 3가지는 ch 6에서 자세히 다룰께

## 자바스크립트 객체와 프로퍼티 종류
1 native object : Array, Function, Date
2 host object   : HTMLElement
3 user defined object

1 own property  : 객체에 직접 정의
2 inherited property : 객체의 `prototype` 객체가 정의한 프로퍼티


## 6.1 객체 생성하기
1 new 키워드
2 Object.create // ECMAScript5

### 6.1.1 객체 리터럴
{}안에, 이름과 값을 :으로 구분한 순서쌍을 쉼표로 연결한 리스트

  var point = {x:0, y:0};

- 평가될 때마다 새로운 객체 생성하고 초기화하는 표현식

### 6.1.2 new
객체를 만들고, 초기화함
- new 다음에는 반드시 함수 호출문 와야한다.
- 이것은 생성자라고 한다.

  var o = new Object();
  var k = new Array();

### 6.1.3 프로토타입
- 자바스크립트의 모든 객체는 또 다른 객체와 연관되어있다.
- 두 번째 객체는 prototype으로 알려져있고, 이 때 객체는 프로토타입으로부터 프로퍼티들을 상속받음
- 객체 리터럴로 생성된 객체 프로토타입 객체가 같으며, 자바스크립트 코드에서 이 프로토타입 객체는 Object.prototype으로 참조 가능

| 생성방식 | prototype     |
| :------------- | :------------- |
| 리터럴           | 모든 객체의 프로토타입 객체가 같다. Object.prototype으로 참조 가능       |
| new 키워드       | 생성자 함수의 프로토타입이 생성된 객체의 프로토타입이 된다.
                    - ex. new Object로 생성된 객체는 {}로 생성된 객체와 마찬가지로 Object.prototype 상속 받음
                    - new Array()로 생성된 객체는 Array.prototype을 상속받음 |

### 6.1.4 Object.create()
이 메서드의 첫번째 인자 : 프로토타입 객체

  var o1 = Object.create({x:1, y:2}); // o1은 x,y 프로퍼티를 상속받는다.

만약 {} 또는 new Object()가 만들어내는 것과 같은 일반적인 빈 객체 만들고 싶다면, 함수에 Object.prototype을 전달

  var o3 = Object.create(Object.prototype) // o3는 {} 또는 new Object()와 같은 객체다.
