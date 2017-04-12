# 5.4 클로저

먼저 `[[scope]]`의 개념에 대해 알아보자.

- 각 함수 객체는 `[[scope]]` 프로퍼티로 현재 context의 scope chain을 참조한다.

- 한 함수가 실행되면, 새로운 실행 context를 만든다.
	+ 현재 실행되는 함수 객체의 `[[scope]]` 프로퍼티 복사 (현재 실행되는 함수 객체는 실행 컨텍스트 생성될 당시에 scope 프로퍼티를 가지고 있다.)
	+ 새롭게 생성된 변수객체를 해당체인의 제일 앞에 추가.

요약하면,

스코프체인 = 현재 실행 컨텍스트의 변수 객체 + `상위 context`의 scope chain

## 5.4.1 클로저란

> 이미 생명주기가 끝난 외부 함수의 변수를 참조하는 함수

- 클로저로 참조되는 외부변수는 자유변수라고 한다.

js가 클로저를 구현하는 전형적인 패턴을 보자.

```javascript
function outerFunc(){
	var x = 1;

	function innerFunc(){
		console.log(x);
	}

	return innerFunc;
}

var func = outerFunc();
func();
```

outerFunc()가 실행되면서 생성되는 VO가 스코프 체인에 들어간다.

이 스코프 체인의 innerFunc의 스코프체인 프로퍼티에 참조된다.

즉, outerFunc() 함수가 종료되었지만

innerFunc()의 `[[scope]]`으로 참조 되므로 가비지 컬렉션의 대상이 되지 않고 여전히 접근 가능하다.

클로저는 이러하다.

> 클로저는 스코프 체인에서 뒤쪽에 있는 객체에 자주 접근한다.
그러므로 성능 저하 문제가 있다. 그렇다고 클로저를 쓰지 않는 것은 JS의 강력한 기능을 무시하고 사용하는 것과 다름 없다. 따라서 클로저를 영리하게 사용하는 지혜가 필요하다. 다음 절에서 알아보자.

---


## 5.4.2 클로저의 활용

클로저는 성능적인 면과 자원적인 면에서 약간 손해를 볼 수 있다.

그래서 무차별적인 사용은 안된다.

일단 클로저의 전형적인 예제 코드를 알아보자.


### 5.4.2.1 특정 함수에 사용자가 정의한 객체의 메서드 연결하기

```javascript
function HelloFunc(func){
  this.greeting = "hello";
}


HelloFunc.prototype.call = function(func){
  func ? func(this.gretting) : this.func(this.greeting);
}

var userFunc = function(greeting){
  console.log(greeting);
}

var objHello = new HelloFunc();
objHello.func = userFunc;
objHello.call();
```

이 예제에서 `HelloFunc()`는 greeting 만을 인자로 넣어 사용자가 인자로 넘긴 함수를 실행시킨다.

그래서 사용자가 정의한 함수도 한 개의 인자를 받는 함수를 정의할 수 밖에 없다.

원하는 인자를 더 넣어서 `HelloFunc()`를 이용하여 호출하려면 어떻게 해야할까?

---

```javascript
function saySomething(obj, methodName, name){
  return (function(greeting){
    return obj[methodName](greeting, name);
  });
}

function newObj(obj, name){
  obj.func = saySomething(this, "who", name);
  return obj;
}

newObj.prototype.who = function(greeting, name){
  console.log(greeting + " " + (name || "everyone"));
}


var obj1 = new newObj(objHello, "hoil");

obj1.call();
```

새로운 함수 `newObj()`를 선언해보자.

이 함수는 `HelloFunc()` 객체를 좀 더 자유롭게 활용하기 위한 함수다.

첫번쨰 인자의 obj는 HelloFunc()의 객체다.

두 번째 인자는 출력을 원하는 사람의 이름이다.



```javascript
obj.func = saySomething(this, "who", name);
return obj;
```

`new newObj(objHell, "hoil")` 실행시, 위 코드가 실행된다.

결국 `obj(objHello)` 객체에서 func 프로퍼티에 참조된 함수만 바뀐 객체가 리턴된다.

```javascript
obj1.call()

function saySomething(obj, methodName, name){

  return (function(greeting){
    // obj, methodName, name으로 클로저를 활용하여 함수 호출 하고 있다.
    return obj[methodName](greeting, name);
  });
}
```

- 위에서 반환된 함수가, HelloFunc가 원하는 function(greeting){} 형식의 함수가 된다.
- 이것이 HelloFunc 객체의 func로 참조된다.
- 여기서 클로저는 saySomething()에서 반환되는 function(greeting){}이 된다.
- 이 클로저는 자유 변수 obj, methodName, name을 참조한다.

이와 같은 방식으로 자신의 객체 메서드인 who 함수를 HelloFunc에 연결시킬 수 있다.

---

앞 예제는 정해진 형식의 함수를 콜백해주는 라이브러리가 있을 경우,

그 정해진 형식과는 다른 형식의 사용자 정의 함수 호출시 유용하게 사용된다.

예를 들어, 브라우저에서 onClick, onmouseover와 같은 프로퍼티에 해당 이벤트 핸들러를

사용자가 정의할 수 있다.

이 이벤트 핸들러는 event 인자만 전달받는다. 이 외에 원하는 인자를 더 추가하고 싶을 때,

앞과 같은 방식으로 클로저를 적절히 뢀용할 수 있다.

---

`setTimeout(callback, ms)`는 함수 객체 참조를 첫번째 인자로 넘겨준다.

근데 실제 실행될 때 함수에 인자를 줄 수는 없다. 인자를 주려면 클로저로 해결 가능하다.

```javascript
var sumObj = {sum : 0};

function getSum(obj, a, b){
	return (function(){
		sumObj['sum'] = a + b;
	})
}

var fn = getSum(sumObj, 10, 20);

setTimeout(fn, 1000);

```


## 5.4.2.2 함수의 캡슐화

"I am XXX. I live in XXX. I am XX years old" 라는 문장을 출력해보자. XX는 인자 값이다.

```javascript
var buffAr = [
	'I am',
	'',
	'. I live in ',
	'',
	'. I am',
	'',
	' years old.'
]

function getCompletedStr(name, city, age){
	buffAr[1] = name;
	buffAr[2] = city;
	buffAr[3] = age;

	return buffAr.join('');
}
var str = getCompletedStr('hoil', 'seoul', '11');
console.log(str);
```

buffAr은 전역 변수로 외부에 노출되어있다.

클로저를 이용하여 buffAr을 스코프에 넣고 사용하자.

```javascript
var getCompletedStr = function(){
	var buffAr = [
		'I am',
		'',
		'. I live in ',
		'',
		'. I am',
		'',
		' years old.'
	];

	return (function(name, city, age){
		buffAr[1] = name;
		buffAr[2] = city;
		buffAr[3] = age;

		return buffAr.join('');
	})
}
```

변수 `getCompletedStr`에 즉시 실행 함수를 통해 익명 함수 반환한다.

이 반환된는 함수는 클로저가 되고, 자유변수 `buffAr`을 스코프 체인에서 참조할 수 있다.


## 5.4.3 클로저 활용시 주의사항

### 5.4.3.1 클로저의 프로퍼티 값이 쓰기 가능하므로 여러 번 호출로 항상 변할 수 있음에 유의하자.

### 5.4.3.2 하나의 클로저가 여러 함수 객체의 스코프 체인에 들어가 있는 경우도 있다.

### 5.4.3.3 루프 안에서 클로저 활용시 주의하자

단골 예제다.

```javascript
function coundSeconds(howMany){
	for (var i = 1; i <= howMany; i++){
		setTimeout(function() {
			console.log(i);
		}, i * 1000);
	}
}
countSeconds(3);
```

1,2,3이 아닌 4가 3번 출력된다.

setTimeout 함수의 인자로 들어가는 함수는 자유 변수 i를 참조한다.

하지만 이 함수가 실행되는 시점은 coundSeconds()함수의 실행이 종료된 이후다.

원하는 결과를 얻기 위해, `루프 i값 복사본`을 함수에 넘겨주자

```javascript
function coundSeconds(howMany){
	for (var i = 1; i <= howMany; i++){
		(function(currentI){
			setTimeout(function() {
				console.log(currentI);
			}, currentI * 1000);
		}(i));
	}
}
countSeconds(3);
```

즉시 실행 함수를 실행시켜 루프 i값을 currentI에 복사한다.

**클로저에 의해 각기 다른 환경에서 서로 다른 currentI가 생성된다.**


## summary

클로저는 `이미 생명주기가 끝난 외부 함수의 변수를 참조하는 함수`다.

클로저로 참조되는 외부변수는 `자유변수`다.

클로저는 성능적인 면과 자원적인 면에서 약간 손해를 볼 수 있다.

그래서 무차별적인 사용은 안된다.

활용 예제를 보자

1. 특정 함수에 사용자가 정의한 객체의 메서드 연결하기

	- onClick, onmouseover와 같은 이벤트는 function(event)와 같이 1개의 인자만 받을 수 있다.
	- 클로저를 통해 클로저와 외부함수의 자유변수를 통해 event외에 여러개의 인자를 받도록 구현할 수 있다.

2. 함수의 캡슐화
	- 즉시 실행 함수를 통해 익명 함수를 반환한다.
	- 이 때 반환되는 익명함수는 클로저 외부함수의 자유변수를 통해 캡슐화를 할 수 있다.
