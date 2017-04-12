3# 6.4 OOP 응용 예제

## 6.4.1 클래스의 기능을 가진 subClass 함수

말 그대로 클래스의 기능을 가진 `subClass 함수`를 만들어보자.

	- 부모 클래스의 프로퍼티를 상속받는 생성자 함수를 만들거다.
	- 생성자 함수를 통해 인스턴스 생성시 모든 부모 생성자 호출 후, 자신의 생성자를 호출할 수 있다.

[프로토타입을 이용한 상속](https://github.com/seaunseen/TIL/blob/master/javascript/js%20for%20frontend%20dev/inside_js/ch6-2-inheritance.md#621-prototype을-이용한-상속)
, [클래스 기반 상속](https://github.com/seaunseen/TIL/blob/master/javascript/js%20for%20frontend%20dev/inside_js/ch6-2-inheritance.md#622-클래스-기반-상속) 을 바탕으로 기존 클래스와 같은 기능을 하는 js 함수를 만들어보자.

이 함수는 다음 3가지를 활용하여 구현한다.

	1. 함수의 프로토타입 체인
	2. extend 함수
	3. 인스턴스 생성시 생성자 호출(여기서는 `_init` 함수로 정한다.)


### 6.4.1.1 subClass 함수 구조

subClass는 상속받을 클래스에 넣을 변수 및 메서드가 담긴 객체를 인자로 받는다.

그리고 부모 함수를 상속 받는 자식 클래스를 만든다.

여기서 부모 함수는 `subClass()` 호출시 `this` 객체를 의미

```javascript
var SuperClass = subClass(obj); // 여기서 부모 함수는 Function
var SubClass = SuperClass.subClass(obj);
```

SuperClass를 상속받는 SubClass 만들고자 할때, `SuperClass.subClass()` 형식으로 호출하게 구현한다.

(참고로 최상위 클래스는 Function을 상속받음)

함수 `SubClass`의 구조를 보자.

```
function subClass(obj){

	1 자식 클래스 (함수 객체) 생성
	2 생성자 호출
	3 프로토타입 체인을 활용한 상속 구현
	4 obj를 통해 들어온 변수 및 메서드를 자식 클래스에 추가 (extend)
	5 자식 함수 객체 반환
}
```

### 6.4.1.2 자식 클래스 생성 및 상속

```javascript
function subClass(obj){
	...
	var parent = this;
	var F = function(){};

	/* 매개자 함수를 가진 프로토타입 체이닝으로 상속 */
	F.prototype = parent.prototype;
	child.prototype = new F();
	child.prototype.constructor = child;
	child.parent = parent.prototype;
	child.parent_constructor = parent;

	return child;
}
```

자식 클래스는 `child`라는 이름의 `함수 객체`를 생성하여 만들어졌다.

부모 클래스를 가리키는 parent는 `this`를 그대로 참조한다.

(만약, global에서 호출했을 시, this는 `Function`이 된다.)

프로토타입 체인 구성은 [앞서 설명 한 것](https://github.com/seaunseen/TIL/blob/master/javascript/js%20for%20frontend%20dev/inside_js/ch6-2-inheritance.md#621-prototype을-이용한-상속) 과 비슷하지만, 한가지가 다르다.

`child.parent_constructor`에 부모의 생성자를 참조 시킨점이다.


### 6.4.1.3 자식 클래스 확장

사용자가 인자로 넣은 객체를 자식 클래스에 넣어 자식 클래스를 확장해보자.

```javascript
for (var i in obj){
	if(obj.hasOwnProperty(i)){
		child.prototype[i] = obj[i];
	}
}
```

`extend()` 함수의 역할을 하는 코드(shallow copy)를 넣어봤다.

```javascript
function extend(propObj, targetObj){
	if(propObj === null || typeof propObj !== 'object')
	for(var attr in propObj){
		targetObj[attr] = extend(propObj[attr], {});
	}
	return propObj;
}
```



### 6.4.1.4 생성자 호출

클래스의 인스턴스가 생성될 때, 다음 2가지가 호출되어야 한다.

	1. 클래스 내에 정의된 생성자
	2. 부모 클래스의 생성자

이를 **자식 클래스 안에** 구현하자.

이것은 [클래스 기반 상속](https://github.com/seaunseen/TIL/blob/master/javascript/js%20for%20frontend%20dev/inside_js/ch6-2-inheritance.md#622-클래스-기반-상속) 에서 언급 되었으므로 설명은 코드로 대체하겠다.

```javascript
var child = function(){
	if (parent._init){
		parent._init.apply(this, arguments);
	}
	if(child.prototype._init){
		child.prototype._init.apply(this, arguments);
	}
}
```

위 코드는 **한가지 문제점**이 있다.

`parent._init`, `child.prototype._init` 찾을 때, `_init` 프로퍼티가 없으면

프로토타입 체인으로 상위 클래스의 `init` 함수를 찾아서 호출하게 된다.

이를 방지하기 위해 `hasOwnProperty` 함수를 활용해야 한다.

```javascript
var child = function(){
	if (parent.hasOwnProperty("_init")){
		parent._init.apply(this, arguments);
	}
	if(child.prototype.hasOwnProperty("init")){
		child.prototype._init.apply(this, arguments);
	}
}
```

근데 한 가지 더 고려해야한다.

앞 코드는 단순히 부모-자식 한 쌍을 이루었을 때만 제대로 동작한다.

만약 자식을 또 다른 함수가 다시 상속 받았을 때는 어떻게 될까?

```javascript
var SuperClass = subClass();
var SubCLass = SuperClass.subClass();
var Sub_SubClass = SubClass.subClass();

var instance = new Sub_SubClass();
```

마지막 코드에서 instance 생성시, 상위의 상위 클래스인 SuperClass의 생성자가 호출되지 않는다.

즉, **재귀적으로** 코드를 구현해야 한다.

```javascript

var child = function(){
	var _parent = child.parent
	// 여기서 child.parent는 parent 생성자 함수다.
	// parent는 함수 호출이 재귀적으로 부모를 찾을 수 있게 도움을 주는 역할만 한다.
	// 즉, 기존의 parent._init 처럼 parent를 통해 함수 호출을 하지 않는다.
	if(_parent && _parent !== Function)
		_parent.apply(this, arguments);
	}
	if(child.prototype._init){
		child.prototype._init.apply(this, arguments);
	}
}
```

```javascript
if (parent.hasOwnProperty("_init")){
	parent._init.apply(this, arguments);
}
```

```javascript
if(_parent && _parent !== Function)
	_parent.apply(this, arguments);
}
```

- 부모의 부모.. 부모 함수가 `Function`이 아닐 때까지 부모 생성자를 찾기위해 재귀적 호출을 한다.
- 기존에는 부모 함수에서 직접 `_init`을 호출했다.
- 2번째 코드와 같이 재귀적으로 부모 함수를 찾는 역할로 바꾼다.
- `_init` 함수 호출하는 것을 `child.prototype._init`이 하는 것으로 변경한다.


---

### 6.4.1.5 subClass 보완

parent를 단순히 this.prototype으로 지정하면 안된다.

왜냐면, 처음에 최상위 클래스를 `Function` 상속 받는 것으로 정했기 때문이다.

그래서 다음 코드를 `parent=this`

```javascript
var parent = this === global ? Function : this
```

또 하나 빠진 부분이 있다.

subClass 안에서 생성하는, 자식 클래스의 역할을 하는 함수는 subClass 함수가 있어야 한다.

```javascript
function subClass(){
	...
	child.subClass = arguments.callee; // prototype이 아닌 이유는, 각 child가 가진 property(함수, 객체)가 다르다. 또한, 생성자 함수이기 때
	// 문이다. 마지막으로, child.prototype.subClass 하면 부모 생성자, 부모의 부모 생성자 찾으러 다닐 때 프로토타입 체이닝을 할 수 없다.
	...

}

var SuperClass = subClass();
var subClass = SuperClass.subClass(); // err, SuperClas.subClass() is not a function
```


### 6.4.1.6 subClass 활용

최종 완성 코드를 보자

```javascript
function subClass(obj){
  var parent = this === window ? Function : this;
  var F = function(){};

  var child = function(){
    var _parent = child.parent;
    if(_parent && _parent !== Function){
      _parent.apply(this, arguments);
    }
    if(child.prototype._init){
	  // child는 new 생성자로 만들어진 객체가 아닌 생성자 함수이기 때문에 프로토타입 체인이 형성될 수 없다. 그러므로 _init 함수 앞에 prototype을 명시해줘야 한다.
      child.prototype._init.apply(this, arguments);
    }
  };

  F.prototype = parent.prototype;
  child.prototype = new F();
  child.prototype.constructor = child;
  child.parent = parent;
  child.subClass = arguments.callee;

  for(var i in obj){
    if (obj.hasOwnProperty(i)){
      child.prototype[i] = obj[i];
    }
  }

  return child;

}

var person_obj = {
  _init : function(){
    console.log("person init");
  },

  getName: function() {
    return this.name;
  },

  setName: function(name){
    this.name = name;
  }
}

var student_obj = {
  _init : function(){
    console.log("student init");
  },
  getName: function(){
    return "Student Name : " + this.name;
  }
}

var children_obj = {
  kidergarten: true
}

var Person = subClass(person_obj);
console.log(Person);
var person = new Person();

var Student = Person.subClass(student_obj);

var hoil = new Student();

var Children = Person.subClass(children_obj);

var baby = new Children();
```

다음 내용을 확인해보자

	- 생성자 함수가 호출되는가?
	- 부모의 메서드가 자식 인스턴스에서 호출되는가?
	- 자식 클래스가 확장 가능한가?
	- 최상위 클래스인 Person은 Function을 상속받는가?


---



## 6.4.1.7 SubClass 함수에 클로저 적용

subClass 함수에 클로저를 적용해보자.

사실 프로토타입 체이닝하려고 만든 임시 함수 객체 F가 되게 거슬린다.

```javascript
var F = function() {};
```

이 함수 객체는 subClass 함수가 호출될 때마다 생성된다.

**클로저로 단 한 번만 생성되게 해보자**

```javascript
var subClass = function(){
	var F = function() {};

	var subClass = function(obj){
		...
	}
	return subClass;
}();
```

**즉시 실행 함수로 새로운 컨텍스트를 만들었다.**

그리고 F() 함수 객체 생성하였다.

이 F() 함수 객체를 참조하는 안쪽의 `subClass()` 함수를 반환 받는다.

이렇게 하면 F() 함수 객체는 클로저에 엮여서 가비지 컬렉션의 대상이 되지 않고, subClass() 함수 호출할 때마다 사용된다.


### 6.4.2 subClass 함수와 모듈 패턴을 이용한 객체지향 프밍

[6.3 캡슐화](https://github.com/seaunseen/TIL/blob/master/javascript/js%20for%20frontend%20dev/inside_js/ch6-3-capsulation.md) 에서 잠시 언급된 모듈 패턴은 OOP와 관계가 없어 보인다.

하지만 캡슐화의 중요 개념인 정보 은닉을 하려면, 모듈 패턴은 상당히 유용하다.

모듈 패턴으로 캡슐화 하여 앞절의 subClass() 함수로 상속을 구현해보자

```javascript
var person = function(arg){
	var name = undefined;

	return {
		_init:function(arg){
			name = arg ? arg : "zzooon"
		},
		getName : function(){
			return name;
		}
		setName function(arg){
			name = arg;
		}
	}
}

Person = subClass(Person());
```



## Summary

다음 3가지 활용하여 클래스의 기능을 가진 subClass 함수 만들기

	1. 함수의 프로토타입 체인
	2. extend 함수
	3. 인스턴스 생성시 생성자 호출(여기서는 `_init` 함수로 정한다)

	```javascript
	var SuperClass = subClass(obj); // 여기서 부모 함수는 Function
	var SubClass = SuperClass.subClass(obj);
	```

그냥 위와 같이 호출 하여 부모 클래스를 상속 받는 자식 클래스를 만드는 코드가 있다고 가정하자.

그리고 코드를 짜보자.

아래와 같은 코드가 돌아가게끔

```javascript
var person_obj = {
  _init : function(){
    console.log("person init");
  },

  getName: function() {
    return this.name;
  },

  setName: function(name){
    this.name = name;
  }
}

var student_obj = {
  _init : function(){
    console.log("student init");
  },
  getName: function(){
    return "Student Name : " + this.name;
  }
}

var children_obj = {
  kidergarten: true
}

var Person = subClass(person_obj);
var person = new Person();

var Student = Person.subClass(student_obj);
var hoil = new Student();

var Children = Person.subClass(children_obj);
var baby = new Children();
```

위 subClass 함수에 `클로저`를 적용해보자

왜냐하면 프로토타입 체이닝 하려고 만든 임시 함수 객체 F가 되게 거슬려서

```javascript
var subClass = function(){
	var F = function() {};

	var subClass= function(obj){
		...
	}
	return subClass();
}();
```

- 즉시 실행 함수로 새로운 컨텍스트 생성.
- 그리고 F() 함수 객체를 참조하는 내부 `subClass()` 함수를 반환한다.
- 이렇게 하면 F() 함수 객체는 클로저에 엮여서 가비지 컬렉션의 대상이 되지 않는다.
- 또한, subClass() 함수 호출할 때마다 사용한다.


`subClass 함수`와 `모듈 패턴`을 이용하여 **객체지향 프밍**을 해보자.

캡슐화의 중요 개념인 정보 은닉을 하기 위해, 모듈 패턴은 유용하다.

```javascript
var person= function(arg){
	var name = undefined;

	return {
		_init:function(arg){
			name = arg ? arg : "zzooon"
		}
	}
}

Person = subClass(person());
```

Person 함수 객체는 **name의 정보를 캡슐화 시킨 객체**를 반환하는 역할을 한다.

이렇게 반환 받은 객체는 subClass() 함수의 인자로 들어가 **클래스의 역할을 하는 Person 함수 객체**를 완성 시킬 수 있다.


## 결론

실습을 해보자.

1. 클래스의 기능(클래스의 인스턴스 생성시, 클래스 내에 정의된 생성자와 부모 클래스의 생성자도 호출)을 가진 subClass() 함수를 만들어보자.
2. 위 subClass()를 클로저를 이용하여 구현해보자
3. 모듈 패턴(캡슐화)으로 클래스 역할을 하는 특정 함수의 정보 은닉을 구현해보자.
