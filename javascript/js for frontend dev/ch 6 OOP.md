# 객체 지향 프로그래밍
이장에서 다루는 내용
> 객체 프로퍼티의 이해
> 객체의 이해와 생성
> 상속의 이해

OO 언어
- 프로퍼티와 메서드를 가지는 객체를 여러개 만든다는 특징을 가짐
- ECMAScript클래스라는 개념이 없다.
  - 이에 따라 ECMAScript의 객체는 다른 클래스 기반 언어와 다르다.

객체
- "프로퍼티의 순서 없는 컬렉션이며 각 프로퍼티는 원시 값이나 객체, 함수를 포함" in ECMA-262
  - 즉, 객체가 **특별한 순서가 없는 값의 배열**이란 의미다.
  - 해시 테이블이라고 생각하면 이해하기 쉽다. (키를 값에 매핑하는 구조)
  - 즉, 이름-값 쌍의 그룹이다. 값은 데이터 or 함수가 될 수 있다.
- 모든 객체는 참조 타입을 바탕으로 생성
  - 바탕이 되는 타입 1. 네이티브 타입 2. 개발자가 정의한 타입

## 6.1 객체에 대한 이해

객체 생성시 `객체 리터럴` 패턴이 자주 쓰인다.
```javascript
var person = {
  name: "Nicholas",
  age: 29,
  job: "software Engineer",

  sayName: function() {
    alert(this.name);
  }
}
```
### 6.1.1 프로퍼티 타입

## 6.2 객체 생성
1. Object 생성자
2. 객체 리터럴
- 위 두가지의 단점은 같은 인터페이스를 가지는 객체 여러개 만들 때 중복된 코드를 많이 써야 한다는 점이다

### 6.2.1 팩터리 패턴
특정 객체를 생성하는 과정을 추상화 하는 것

```javascript
function createPerson(name, age, job){
  var o = new Object;
  o.name = name;
  o.age = age;
  ...
  return o;
}
var person1 = createPerson(...);
```

### 6.2.2 생성자 패턴
커스텀 생성자를 만들어서 원하는 타입의 객체에 필요한 프로퍼티와 메서드 정의 가능
```javascript
function Person(name, age, job){
  this.name = name;
  this.age = age;
  ...
}
var person1 = new Person("Nicholas", 29, "Software Engineer");
```
- `Person()` 함수가 팩터리 함수 `createPerson()` 역할을 대신한다.
- 팩터리함수와 다른점
  - 명시적으로 객체 생성하지 않음
  - 프로퍼티와 메서드는 `this` 객체에 직접적 할당
  - return 문이 없다.
  - 함수 Person 대문자로 시작
  - new 연산자 사용


### 6.2.3 프로토타입 패턴
모든 함수는 `prototype 프로퍼티`를 가진다.
- prototype은 해당 참조 타입의 인스턴스가 가져야 할 프로퍼티와 메서드를 담고 있는 `객체`
- 이 객체는 `생성자를 호출 시 생성되는 객체`의, 문자 그대로 프로토타입
- **프로토타입의 프로퍼티와 메서드는 객체 인스턴스 전체에서 공유**된다는 점이 프로토타입의 장점
- 객체 정보를 생성자에 할당하는 대신 다음과 같이 **직접 프로토타입에 할당 가능**

```javascript
function Person(){}
Person.prototype.name = "Nicholas";
Person.prototype.sayName = function(){
  alert(this.name);
}
```

#### 프로토타입은 어떻게 동작하는가
프로토타입은 자동으로 `constructor` 프로퍼티를 갖는데 이 프로퍼티는 해당 프로토타입이 프로퍼티로서 소속된 함수를 가리킨다.
- 위 예제에서 `Person.prototype.constructor`는 `Person`을 가리킨다.
- 다음 생성자에 따라 각종 프로퍼티와 메서드가 프로토타입에 추가
- 생성자를 호출해서 **인스턴스 생성할 때 마다 해당 인스턴스 내부에는 생성자의 프로토타입을 가리키는 포인터가 생성됨**
- 인스턴스와 직접 연결되는 것은 생성자의 프로토타입이지 생성자 자체가 아니다.

객체에서 프로퍼티를 읽으려 할 때마다 해당 프로퍼티 이름 찾으려고 검색한다
1. 검색은 객체 인스턴스 자체에서 시작
2. 인스턴스에서 프로퍼티 이름을 찾으면 그 값을 반환한다.
3. 프로퍼티를 찾지 못하면 포인터를 프로토타입으로 올려서 검색
```javascript
function Person(){}
Person.prototype.name = "Nicholas";

var person1 = new Person();
var person2 = new Person();
person1.name = "Greg";
```
- `person1.name`은 `Greg` from **instance**
- `person2.name`은 `Nicholas` from **prototype**

#### 프로토타입 대체 문법
```javascript
Person.prototype = {
  name : "Nicholas",
  age: 29
}
```

#### 프로토타입의 동적 성질
프로토타입에서 값을 찾는 작업은 런타임 검색이므로 프로토타입이 바뀌면 즉시 인스턴스에도 반영됨
```javascript
var friend = new Person();
Person.prototype.sayHi = function(){
  alert("hi");
}
friend.sayHi(); // hi 동작
```
- sayHi 없는 프로토타입을 복사한 것이 아닌 포인터이므로 동작 가능

## 6.3 상속
객체지향 언어는 메서드 시그너처만을 상속하는 `인터페이스 상속`과 실제 메서드를 상속하는 `구현 상속` 두 가지 타입 지원
- ECMAScript 함수에는 시그너처가 없으므로 인터페이스 상속 불가능
- 구현 상속만 지원 via 프로토타입 체인

### 6.3.1 프로토타입 체인
ECMA-262는 프로토타입 체인을 우선적 상속 방법으로 설명한다.
프로토타입 체인의 기본 아이디어
- 프로토타입 개념을 이용해 두 가지 참조 타입 사이에서 프로퍼티와 메서드를 상속
- 모든 생성자에는 생성자 자신을 가리키는 프로토타입 객체가 있다
- 인스턴스는 프로토타입을 가리키는 내부 포인터가 있다
- 그렇다면 프로토타입이 사실 다른 타입의 인스턴스라면..?
  - 프로토타입(A) 자체에 다른 프로토타입(B)을 가리키는 포인터가 있고
  - B에는 또 다른 생성자를 가리키는 포인터가 있을 거다.
  - 프로토타입 B 역시 다른 타입의 인스턴스라면 이런 패턴이 계속 연결되어 인스턴스와 프로토타입을 잇는 체인이 형성된다.

```javascript
function SuperType() {
  this.property = true;
}
SuperType.prototype.getSuperValue = function (){
  return this.property;
}
function SubType() {
  this.subproperty = false;
}

// SuperType을 상속
SubType.prototype = new SuperType();
SubType.prototype.getSubValue = function () {
  return this.subproperty;
}
var instance = new SubType();
alert(instance.getSuperValue()); // true
```
- SubType이 SuperType의 새 인스턴스를 생성하여 SuperType을 상속
  - 이를 SubType.prototype에 할당
  - 원래 프토토타입을 새로운 객체로 덮어쓴다.
  - SuperType의 인스턴스에 존재했을 프로퍼티와 메서드가 SubType.prototype에도 존재한다.
- 상속이 일어난 다음 SubType.prototype에 메서드를 추가하는데, SuperType에서 상속한 메서드는 그대로 유지됨
- SubType의 기본 프로토타입 대신 새 프로토타입이 할당됨
  - **새 프로토타입은 SuperType의 인스턴스 이므로** SuperType 인스턴스가 가질 프로퍼티와 메서드 외에 **SuperType의 프로토타입을 가리키는 포인터도 가진다.**
  - 즉 instance는 SubType.prototype을 가리키고 SubType.prototype은 SuperType.prototype을 가리킨다.
- `getSuperValue()` 메서드는 SuperType.prototype 객체에 남지만 **property는 SubType.prototype에 존재함을 보자**
  - 이렇게 되는 것은 getSuperValue()가 프로토타입 메서드이며 property는 인스턴스 프로퍼티이기 때문이다.
  - SubType. prototype은 SuperType의 인스턴스 이므로 property는 SubType.prototype에 저장된다.
- SubType.prototype의 constructor 프로퍼티를 덮어썼으므로 instance.constructor가 SuperType을 가리키는 것도 보자

프로토타입 체인은 검색 메커니즘을 확장
- 인스턴스에서
- SubType.prototype에서
- SuperType.prototype에서 검색하며 체인의 끝까지 올라간다.


## Summary
- 객체는 특별한 순서가 없는 값(원시값, 객체, 함수 등)의 배열
- 객체 생성
  - object 생성자
  - 객체 리터럴
- 프로토타입
  - 모든 함수는 prototype 프로퍼티를 가진다.
  - 해당 참조 타입의 인스턴스가 가져야할 프로퍼티와 메서드를 담고 있다
  - 이 객체는 생성자 호출 시 생성되는 객체
  - 프로토타입의 프로퍼티와 객체 인스턴스 전체에서 공유
  - 객체 정보를 생성자에 할당하는 대신 직접 프로토타입에 할당 가능
- 프로토타입의 동작 방식
  - 프로토타입은 자동으로 constructor 프로퍼티를 갖는다.
    - `person.prototype.constructor`는 `person`을 가리킨다.
    - 생성자 호출하여 인스턴스 생성할 때 마다 해당 인스턴스 내부에는 생성자의 프로토타입을 가리키는 포인터가 생성됨
    - 인스턴스와 직접 연결되는 것은 생성자의 프로토타입이지 생성자 자체가 아니다.
- 객체에서 프로퍼티 읽을 때 검색 순서
  1. 인스턴스
  2. 프로토타입
- 프로토타입에서 값을 찾는 작업은 런타임 검색
- 상속
  - 프로토타입 체인을 통해 `구현 상속` 가능
- 프로토타입 체인
  - 프로토타입이 다른 타입의 인스턴스라면..?
  - 프로토타입(A) 자체에 다른 프로토타입(B)를 가리키는 포인터가 있고
  - B에는 또 다른 생성자를 가리키는 포인터가 있다.
  -
