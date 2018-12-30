# 객체

OOP에서 객체의 기본 개념은 데이터와 그 데이터에 관련되는 동작을 포함하고 있는 개념이다. 자바스크립트에서 객체는 `프로퍼티`와 `메서드`를 가진다. 

## Property

객체의 속성을 나타낸다. 이 속성을 통해 해당 객체가 가진 정보에 직접 접근할 수 있다 (`proto`와 같이 직접 접근할 수 없는 프로퍼티가 있기도 하다). 

```javascript
var obj = {};
obj.name = 'hoil';
```

프로퍼티에 값을 할당하지 않으면 어떻게 될까? JS 엔진이 강제적으로 `undefined`를 할당한다. 또한, 프로퍼티는 `undefined`나 `null`을 할당해도 삭제되지 않는다. 프로퍼티의 삭제는 `delete` keyword를 사용해야 한다.

```javascript
var obj = {};
obj.name = 'hoil';

obj.name = null;
console.log(obj.name); // null

delete obj.name;
console.log(obj.name); // undefined
```

## method

객체게 가진 동작을 나타낸다. 함수와 메서드는 다른 의미를 가진다. 공통점은 어떤 동작을 실행한다는 점이다. 둘의 차이점은 보자. **메서드는 객체를 통해서 호출된다.** 즉, 동작 주체가 객체다. 함수는 객체를 통해 호출되지 않는다. 함수자체가 그 동작을 정의한 함수객체이기 때문에 자기 자신을 호출하지 않아도 된다.  


```javascript
var obj = {};
obj.age = 20;
obj.year = 2017;

obj.printBirthYear = function() {
    console.log(obj.year - obj.age);
}
```

## JS 객체 구성

객체는 크게 3가지로 구분된다.

1 Built-in Object
2 Native Object
3 Host Object

### Built-in Object 

Object, String, Number, Boolean, Date, Array, Math, RegExp, Error 등 의 내장객체가 있다. 자바스크립트 엔진이 구동되는 시점에서 바로 제공된다. 어디서든 사용 가능하다.

### Native Object

자바스크립트가 구동되는 시점에서 바로 사용 가능한 객체 들이다. 하지만 이 객체들은 JS 엔진이 구성하는 기본객체라고 하기 보다는 브라우저에서 빌드되는 객체들이다. BOM과 DOM이 대표적이다. Built-in Object와 마찬가지로 내장 객체다. 구분하여 이름을 부르는 이유는 브라우저에 따라 객체 구성이 달라지기 때문이다.

### Host Object 

사용자 정의 객체다. `constructor` 또는 객체리터럴을 통해 사용자가 객체를 정의하고 확장시킨 객체다. 이 때 객체리터럴은 단일 객체로만 활용되고, `constructor`는 동일 구성을 가진 객체를 여러개 만들 수 있는 차이점이 있다. 


## Object 객체

Object객체는 Built-in 객체다. 그 중에서도 최상위레벨의 객체다. 즉 모든 객체는 이 Object 객체에서 파생되어 나온 확장형태다. Object 객체로 파생된 객체들은 Object 객체가 가진 기본적인 구성요소를 상속 받는다. 자바스크립트의 모든 객체가 자유롭게 확장될 수 있는 이유도 Object객체가 가진 프로퍼티 및 메서드 때문이다. Object객체가 가진 `constructor`, `prototype` 이라는 프로퍼티가 대표적이다. 
