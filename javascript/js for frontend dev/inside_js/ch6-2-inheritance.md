# 6.2 상속

객체 `prototype 체인`을 이용하여 상속을 구현할 수 있다.

2가지 방식 있다.

1. 클래스 기반 전통적인 상속 방식 흉내내기
2. 클래스 개념 없이 객체의 prototype으로 상속 구현하기 (a.k.a Prototypal inheritance)
	- `객체 리터럴`을 중심으로 prototype을 이용하여 상속 구현


## 6.2.1 prototype을 이용한 상속

```javascript
var Person = {
	name: 'sample',
	getName : function(){
		return this.name;
	}
	setName : function(value){
		this.name = value;
	}
}


function create_object(parent){
	// obj는 부모 obj
	function F(){}
	F.prototype = parent;
	// parent.prototype.constructor = F;, 모든 함수는 prototype 프로퍼티를 갖는다. 객체는 생성시 __proto__ 링크를 갖는다.
	return new F();
}

var engineer = create_object(Person);
engineer.setName("hoil");
```

- `F.prototype = parent` : F 생성자를 통해 생성된 객체의 부모 역할을 하는 prototype 객체를 parent 객체로 선언하였다.(상속)


---

여기서 자식은 자신의 메서드를 `재정의` 혹은 추가로 `기능을 더 확장`시킬 수 있어야 한다.

```javascript
engineer.setAge = function(age){...}
engineer.getAge = function(){...}
```

이렇게 기능을 확장시킬 수 있다.

하지만 이렇게 하면 코드가 더러워진다.

js에서는 범용적으로 `extend()`라는 이름의 함수로 객체에 자신이 원하는 객체 혹은 함수를 추가시킨다.

jQuery의 [extend()](https://api.jquery.com/jquery.extend/) 함수를 보자.

~~자세한 건 링크를 보자..~~

extend 역할을 하는 함수를 vanilla js로 짜보자.

```javascript
...
var Person = {
	name: 'sample',
	getName : function(){
		return this.name;
	}
	setName : function(value){
		this.name = value;
	}
}

function extend(prop, obj){
	if(prop === null || typeof(prop) !== 'object') {
      return prop;
    }
	for(var attr in prop){
		obj[attr] = extend(prop[attr], {});
	}
	return obj;
}

var student = new Person();
student.setName("hoil");

console.log(student);
console.log(Person);
// 깊은 복사가 됐음을 알 수 있다.
...
```

## 6.2.2 클래스 기반 상속

**클래스의 역할을 하는 함수**로 상속을 구현하자.

```javascript

function Person(name){
	this.name = name;;
}

Person.prototype.setName = function(name){
	this.name = name;
}

Person.prototype.getName = function(){
	return this.name
}

var you = new Person("sample");


function Student(arg){}


Student.prototype = you;


var student = new Student("hoil");

console.log(student.getName());

student.setName("hoil");

console.log(student.getName());

```

위 코드는 2가지 문제가 있다.

1. student 인스턴스 생성시 부모 클래스인 `Person()` 생성자가 호출되지 않는다.

결국 student는 빈 객체다. 이를 해결하기 위해 다음 코드를 추가하여 부모 클래스 생성자 호출한다.

```javascript
functino Student(arg){
	Person.apply(this, arguments);
}
```

2. 부모클래스의 인스턴스와 자식 클래스의 인스턴스는 독립적일 필요가 있다.
	- 자식 클래스의 prototype이 부모 클래스 인스턴스를 참조한다.
	- 이것은 자식클래스의 prototype에 메소드 추가할 때 문제가 생긴다.

이를 해결하기 위해, 두 클래스 프로토타입 사이에 `중개자`를 만들자.

```javascript

Function.prototype.makeMethod = function(name, func){
	this.prototype[name] = func;
}

function Person(arg){
	this.name = arg;
}

Person.makeMethod(setName, function(name){
	this.name = name;
})

Person.makeMethod(getName, function(){
	return this.name;
})

function Student(arg){
}

function F(){}

F.prototype = Person.prototype;

Student.prototype = new F();
Student.prototype.construct = Student;
Student.super = Person.prototype;

var me = new Student();
me.setName("zzoon");
console.log(me.getName());
```

`Student.prototype = new F()`
- 자식 클래스(Student)의 prototype 객체는 빈객체이다.
- 따라서 이곳에 확장된 메서드 및 데이터가 들어갈 수 있다.
- 결론적으로, 중개자 클래스의 인스턴스로 인해 부모클래스의 객체와 자식 클래스가 독립적이다.


> 마지막으로, JS patterns의 저자 스토얀..은 상속 관계를 `즉시 실행 함수`와 `클로저`를 활용화여 최적화된 코드를 소개하였다.

```javascript
var inherit = function(Parent, Child){
	var F = function(){};
	return function(Parent, Child){
		F.prototype = Parent.prototype;
		Child.prototype = new F();
		Child.prototype.construct = Child;
		Child.super = Parent.prototype;
	}
}
```

클로저(반환되는 함수)는 `F()` 함수를 지속적으로 참조한다.

그러므로 `F()`는 가비지 컬렉션의 대상이 되지 않고 살아있다.

이를 이용해 함수 `F()`의 생성은 단 한번 이뤄지고 `inherit`함수가 계속 호출되어도 함수 F() 생성을 새로할 필요가 없다.

## Summary

지금까지 상속의 방법을 크게 2가지로 알아보았다.

1. prototype을 이용한 방법
	- extend를 활용하여 자식 클래스의 메서드 및 데이터 확장

2. 클래스 기반 상속
	- 클래스의 역할을 하는 함수로 상속을 구현.
		+ 자식 생성자 호출시, 부모 생성자 호출하지 못하는 문제를 `apply` 메서드로 해결
	- `중개자` 클래스를 이용하면 독립적인 부모,자식 인스턴스 관계 보장.
	- `클로저`로 구현하는 방법도 참고하자.
		+ 중개자 함수 `F()`의 생성은 단 한번 이뤄진다.
