# OOP

> 1 OOP
> 2 상속
> 	- 클래스 기반 전통 상속 방식
>	- 객체의 prototype으로 상속 구현하기
> 3 캡슐화
> 4 OOP 응용 예제 : 클래스의 기능을 가진 subClass 함수


> ECMA-262는 `객체`를 "프로퍼티의 순서 없는 컬렉션이며, 각 property는 원시 값, 객체, 함수를 포함한다."

즉, 객체는 특별한 순서가 없는 배열이다.

프로퍼티와 메서드는 이름으로 구별하고 값에 대응한다.

이래서 ECMAScript 객체를 hash table로 이해하면 쉽다.

모든 객체는 `참조 타입`을 바탕으로 생성된다.

`참조 타입`은 native 거나 개발자가 정의한 type이다.

---

JS는 `함수 객체`로 많은 것을 구현한다.

왜냐하면 클래스, 생성자, 메서드 모두 함수로 구현한다.

---

생성자 함수 호출시 `this 바인딩`
- 모든 함수에 `new`를 붙여 호출하면, 해당 함수는 생성자 함수가 된다.
- 이를 이해하기 위해 생성자 함수가 호출 됐을 때, 동작 방식을 알아보자.

1. 빈 객체 생성 및 `this 바인딩`
    - 생성자 함수 코드가 실행되기 전에 빈 객체가 생성된다.
    - 근데 엄밀히 말하면 빈객체 아니다. `[[Prototype]]` 링크가 생성자 함수의 `prototype` 객체와 연결되어있다.
    - 이 객체는 `this`로 바인딩 된다.

2. `this`를 통한 동적 property 생성

3. 생성된 객체 리턴
    - 리턴값이 명시될 경우, 명시된 리턴값을 준다.

> 생성자 함수를 호출시 new 유무에 따른 차이
> - `new Person()` : `this`는 빈객체, 생성자 함수의 prototype 객체를 `[[Prototype]]` 객체로 설정
> - `Person()` : `this`는 함수 호출자.

## 6.1 클래스, 생성자, 메서드

공통으로 사용할 수 있는 `getter`, `setter` 함수를 따로 생성하여 불필요하게 중독된다. 이로인해 메모리 낭비하는 예시를 보자.

```javascript
function Person(arg){
    this.name = arg;

    this.getName = function(){
        return this.name;
    }

    this.setName = function(value){
        this.name = value;
    }
}
```

함수 객체의 `prototype`을 활용하여 반복을 줄이자.

```javascript
function Person(arg){
    this.name = arg;
}

Person.prototype.setName = function(value){
    this.name = value;
}

Person.prototype.getName = function(){
    return this.name;
}
```

## Summary

객체의 공통된 메서드 생성시 생성자의 `prototype` 프로퍼티를 활용하자.
