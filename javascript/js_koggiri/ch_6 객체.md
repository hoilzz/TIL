# CH 6 객체 지향 프로그래밍
> 객체 프로퍼티의 이해
> 객체의 이해와 생성
> 상속의 이해

객체지향 언어
- 클래스를 통해 같은 프로퍼티와 메서드를 가지는 객체를 여러개 만듬
- 하지만 ECMAScript에는 클래스라는 개념이 없다.

ECMAScript 객체를 해시 테이블이라고 생각하자
- 객체를 `프로퍼티의 순서 없는 컬렉션이며 각 프로퍼티는 원시 값이나 객체, 함수를 포함`한다고 정의 by ECMA-262

## 6.1 객체에 대한 이해

### 6.2.3 프로토타입 패턴

모든 함수는 prototype 프로퍼티를 가진다.
- 이 프로퍼티는 해당 참조 타입의 인스턴스가 가져야 할 프로퍼티와 메서드를 담고 있는 객체
- **이 객체는 생성자를 호출할 때 생성되는 객체의, 문자 그대로 프로토타입**
- **프로토타입의 프로퍼티와 메서드는 객체 인스턴스 전체에서 공유된다는 점이 프로토타입의 장점**
- **객체 정보를 생성자에 할당하는 대신 직접 프로토타입에 할당**

```javascript
function Person(){
}

Person.prototype.name = "Nicholas";
Person.prototype.age = 29;
Person.prototype.job = "Software Engineer";
Person.prototype.sayName = function() {
  alert(this.name);
};

var person1 = new Person();
person1.sayName(); // "Nicholas"

var person2 = new Person();
person2.sayName(); // "Nicholas"

alert(person1.sayName == person2.sayName) // true

```

- **생성자 함수가 비어있지만, 생성자를 호출해 만든 객체에도 프로퍼티와 메서드 존재**

*프로토타입은 어떻게 동작하는가*
- 모든 프로토타입은 자동으로 `constructor 프로퍼티`를 갖는다.
  + 이 프로퍼티는 해당 프로토타입이 프로퍼티로서 소속된 함수를 가리킨다.
  + ex. Person.prototype.constructor 는 Person을 가리킨다.

- **인스턴스와 직접 연결되는 것은 생성자의 프로토타입이지 생성자 자체가 아님을 이해해야함**
- person.prototype은 프로토타입 객체를 가리키지만
- Person.prototype.constructor는 Person을 가리킨다.

객체에서 프로퍼티 읽을 때 마다 해당 프로퍼티 이름을 찾으려고 검색한다.
- 검색은 객체 인스턴스 자체에서 시작.
- 못찾으면 포인터를 프로토타입으로 올려서 검색

- 객체 인스턴스에서 프로토타입 값 읽기 가능 / 수정 불가능
- **프로토타입과 같은 이름의 프로퍼티를 인스턴스에 추가하면 해당 프로퍼티는 인스턴스에 추가되며** 프로토타입까지 올라가지 않는다.
- 인스턴스에 프로퍼티 추가시 해당 프로퍼티는 프로토타입에 존재하는 같은 이름의 프로퍼티 가린다
- delete 연산자로 인스턴스 프로퍼티 삭제하여 prototype에 다시 접근 가능

```javascript
Person() {}
Person.prototype.name = "Nicholas";

var person1 = new Person();
person1.name = "kkk";

delete person1.name
```


*프로토타입 in 연산자*
- 주어진 이름의 프로퍼티를 객체에서 접근할 수 있을 때
- 프로퍼티가 인스턴스든 프로토타입이든 존재하면 true 반환

```javascript
var person1 = new Person();
alert("name" in person1);
```

*프로토타입 대체 문법*
이전 예제에서 Person.prototype을 매 프로퍼티와 메서드마다 기입해야 했다.
- 다음과 같이 프로퍼티오 메서드를 담은 객체 리터럴로 프로토타입을 덮어써서 반복을 줄이고 프로토타입에 기능을 더 가독성 있게 캡슐화 하는 패턴 유행

```javascript
function Person(){}

Person.prototype = {
  name : "Nicholas",
  age : 29,
  sayName : function() {
    alert(this.name);
  }
};
```
- 이 예제는 Person.prototype 프로퍼티에 객체 리터럴로 생성한 객체를 덮어씀
- 위와같이 하면 constructor 프로퍼티가 Person을 가리키지 않는다는 점만 차이
- 결과적으로 constructor 프로퍼티는 함수 자체가 아닌 완전히 새로운 객체 생성자(Object)와 같다.

*프로토타입 동적 성질*

프로토타입에서 값을 찾는 작업은 런타임 검색이므로 프로토타입 바뀌면 즉시 인스턴스에도 반영됨. 심지어는 프로토타입이 바뀌기 전에 빠져나온 인스턴스도 바뀐 내용 반영

```javascript
var friend = new Person();

Person.prototype.sayHi = function(){
  alert("hi");
}
friend.sayHi(); // hi 동작
```
- Person 인스턴스 생성하여 friend에 저장
- sayHi()라는 메서드를 Person.prototype에 추가
- friend 인스턴스는 sayHi() 추가 되기 전에 만들어졌는데 이 메서드에 접근 가능
  + 인스턴스와 프로토타입의 느슨한 연결 때문
  + friend.sayHi() 호출시 인스턴스의 sayHi 프로퍼티 검색
  + 찾을 수 없으면 검색 범위를 프로토타입으로 옮김
  + **인스턴스와 프로토타입은 포인터를 통해 연결되었을 뿐 인스턴스 생성시 sayHi없는 프로토타입을 복사한것이 아니다.**
- **인스턴스는 프로토타입을 가리키는 포인터를 가질 뿐 생성자와 연결된 것이 아님**

*프로토타입의 문제점*
- 초기화 매개변수를 생성자에 전달할 수 없으므로 모든 인스턴스가 디폴트로 같은 프로퍼티 값을 가진다
- 더 큰 문제는 공유라는 성질
  + 인스턴스 프로퍼티에 값을 할당하면 프로토타입 프로퍼티 값을 가릴 수 있음

```
function Person(){
}
Person.prototype = {
  constructor: Person,
  name : ...,
  friends : ["Shelby", "Court"]
}
var person1 = new Person();
var person2 = new Person();

Person1.friends.push("van");

person1.friends; // shelby, court, van
person2.friends; // shelby, court, van
```

## Summary
- 인스턴스와 prototype은 포인터를 통해 연결되어있을 뿐이다.
- 인스턴스는 prototype을 가리키는 포인터를 가진 것이다.
- 프로토타입의 프로퍼티와 메서드는 객체 인스턴스 전체에서 공유된다는 점이 프로토타입의 장점
- 객체 정보를 생성자에 할당하는 대신 직접 프로토타입에 할당


### 6.2.4 생성자 패턴과 프로토타입 패턴 조합
### 6.2.5 동적 프로토타입 패턴
### 6.2.6 기생 생성자 패턴
### 6.2.7 방탄 생성자 패턴
## 6.3 상속
### 6.3.1 프로토타입 체인
### 6.3.4 프로토타입 상속
## Summary
