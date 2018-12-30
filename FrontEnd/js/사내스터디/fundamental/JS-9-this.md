# this

this는 모든 함수 스코프 내에 자동으로 설정되는 특수한 식별자다. this는 가끔 정말 헷갈린다. 근데 왜 사용할까?

```javascript
function getName() {
    return this.name;
}

function sayName() {
    var saying = 'my Name is ' + getName.call(this);
    console.log(saying);
}

var me = {
    name: 'hoil'
};

var friend = {
    name: 'tmon'
}

getName.call(me);
getName.call(friend);

sayName.call(me);
sayName.call(friend);
```

getName과 sayName 두 함수는 객체별로 따로 함수를 작성할 필요 없이 다중 컨텍스트 객체인 me, friend 모두에서 재사용 가능하다. this를 안 쓰고 2개 함수에 컨텍스트 객체를 명시할 수 있다. 

```javascript
function getName(context) {
    return context.name;
}

function sayName(context) {
    var saying = 'my name is ' + getName(context);
    console.log(saying);
}

getName(friend);
sayName(me);
```

객체 레퍼런스를 함께 넘기는 this 체계가 명확하고 재사용하기 쉽다. 



this는 함수 그 자체를 가리킨다는 것은 오해다. 일단 this로 자기 참조를 할 수 없는 것을 보이기 위한 예제는 다음과 같다. foo 함수 호출 횟수를 추적하는 예제다.

```javascript
function foo(num) {
    console.log("foo: " + num);

    // foo가 몇 번 호출됐는지 추적해보자.
    this.count++;
}
foo.count = 0;
var i;
for (i=0; i<10; i++) {
    if(i > 5) {
        foo(i);
    }
}

//foo : 6
//foo : 7
//foo : 8
//foo : 9

console.log(foo.count); // 0... 이다.
```

위에 대한 우회책으로 렉시컬 스코프라는 편안한 장치를 이용할 수 도 있다. 

```javascript
function foo(num) {
    console.log("foo: " + num);

    // foo가 몇 번 호출됐는지 추적해보자.
    data.count++;
}
data.count = 0;

var i;
for (i=0; i<10; i++) {
    if(i > 5) {
        foo(i);
    }
}

//foo : 6
//foo : 7
//foo : 8
//foo : 9

console.log(foo.count); // 0... 이다.
```

this가 뭔지, 작동 원리가 뭔지 모르는 채 문제의 본질을 벗어나는 방법도 있다. this에 대해 애매하게 짐작만 하다가 뭐 좀 안된다 싶으면 렉시컬 스코프를 이용할 수도 있는데 이렇게는 발전이 없다.


foo() 함수 호출 횟수가 콘솔에 출력됐지만 foo.count 는 0이다. this.count++을 this 그대로 해석하면 헷갈릴 수 있다. `foo.count = 0` 은 foo라는 함수 객체에 count 프로퍼티가 추가된다. 하지만 this.count에서 this는 함수 객체를 바라보는 것이 아니며, 프로퍼티 명이 똑같아 헷갈리지만 바라보는 객체 자체가 다르다. 

this는 **작성시점이 아닌 런타임 시점에 바인딩 된다.** 또한, **함수 호출 당시 상황에 따라 context가 결정된다.** 함수 선언 위치와 무관하게 this 바인딩은 오로지 **어떻게** 함수를 호출했느냐에 따라 정해진다.

## this 규칙

총 4가지 규칙이 있다. 

### 1. 기본 바인딩

가장 평범한 함수 호출인 단독 함수 실행에 관한 규칙이다. 나머지 규칙에 해당하지 않을 경우 this의 기본 규칙이다. 

```javascript
function foo() {
    console.log(this.a);
}

var a = 2;
foo(); // 2;
```

var a = 2 처럼 전역 스코프에 변수 선언시 변수명과 같은 이름의 전역 객체 프로퍼티가 생긴다. 이는 서로의 사본이 아니다. 기본 바인딩이 적용 되어 this.a는 전역 객체 a다. 어떻게 기본 바인딩이 적용됐다는 것을 알 수 있을까? foo()는 있는 그대로의 함수 레퍼런스로 호출했다. 나머지 규칙을 적용핧 필요 없이 기본 바인딩이 적용된다. 

엄격 모드에서는 전역 객체가 기본 바인딩 대상에서 제외된다.

```javascript
function foo() {
    "use strict"
    console.log(this.a);
}

var a = 2;
foo(); // type error this는 undefined입니다. 
```

### 2. 암시적 바인딩

호출시 context 객체가 있는지, 즉 객체가 해당 함수를 소유 여부를 확인하는 것이다.

```javascript
function foo() {
    console.log(this.a);
}

var obj = {
    a: 2,
    foo: foo
};

obj.foo(); // 2;
```

foo() 함수를 obj에서 프로퍼티로 참조하고 있다. obj 컨텍스트로 foo()를 참조한다. obj객체는 함수 호출 시점에 함수의 레퍼런스를 소유한다고 할 수 있다. 함수 참조에 대한 context 객체가 존재할 떄 암시적 바인딩 규칙에 따르면 이 context 객체가 함수 호출 시 this에 바인딩 된다. 

### 3. 명시적 바인딩

암시적 바인딩에서 함수 레퍼런스를 객체에 넣기 위해 객체 자신을 변경해야 했다. 그런데 함수 레퍼런스 프로퍼티를 객체에 더하지 않고 어떤 객체를 this 바인딩에 이용하겠다는 것을 코드로 나타낼 수 없을까?

call(), apply() 메서드가 있다. 두 메서드는 this에 바인딩 할 객체를 첫째 인자로 받아 함수 호출 시 이 객체를 this로 세팅한다. this를 지정한 객체로 직접 바인딩 하므로 명시적 바인딩이라고 한다. 

```javascript
function foo() {
    console.log(this.a);
}

var obj = {
    a: 2
};

foo.call(obj); // 2
```

```javascript
function foo(something) {
    conosle.log(this.a, something);
    return this.a + something;
}

var obj = {
    a: 2
};

var bar = foo.bind(obj);

var b = bar (3); // 2 3
console.log( b ); // 5
```

foo.call()에서 명시적으로 바인딩 하여 함수 호출하므로 this는 반드시 obj가 된다. 이 외에 ES5 내장 유틸리티 Function.prototype.bind 메서드가 있따. bind는 주어진 this 컨텍스트로 원본 함수를 호출하기 위해 하드 코딩된 새 함수를 반환한다. 

### 4. new 바인딩

new 를 통함 함수 호출시 this가 바인딩 되는 방식에 대해 알아보자. 함수 앞에 new를 붙여 생성자 호출을 하면 순차적으로 일어나는 일은 다음과 같다.

1. 새 객체를 만든다.
1. 새로 생성된 객체의 [[Prototype]]이 연결된다.
1. 새로 생성된 객체가 this로 바인딩된다.
1. 생성자 함수가 또 다른 객체를 명시적으로 반환하지 않으면 자동으로 1번에서 만든 객체를 반환한다.

```javascript
function User(name) {
	this.name = name;
}
var user = new User('hoil');
```

## this 확정 규칙

우선순위에 따라 차례대로 정리해보자. 다음 항목을 순서대로 따져보고 그중 맞는 최초 규칙을 적용한다.

1. new로 함수를 호출 했는가? 맞으면 새로 생성된 객체가 this다.

```javascript
var user = new User();
```

1. call과 apply로 함수를 호출(명시적 바인딩), 혹은 bind를 통해 새로 바인딩된 함수를 호출하였는가? 맞으면 명시적으로 지정된 객체가 this다.

```javascript
var bar = foo.call(obj2);
```

1. 함수를 context, 즉 객체가 함수를 소유하는 형태로 호출했는가? 맞으면 이 컨텍스트가 this다.

```javascript
var bar = obj1.foo();
```

1. 그 외의 경우 this는 기본값(strict mode는 undefined, 비엄격 모드는 window)으로 세팅된다.

```javascript
var bar = foo();
```