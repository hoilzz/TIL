# setTimeout

setTimeout은 native JS 함수다. (jQuery와 같은 라이브러리에서 함께 사용되기도 한다.) 이것은 특정 딜레이 (in ms) 후에 함수를 호출하거나 코드를 실행한다.

예를 들어, 방문자가 특정 시간 동안 웹사이트를 구경한 후에 팝업을 보이고 싶을 때 유용하다. 혹은, element의 hover effect를 없애기 전에 약간의 딜레이를 원할 때 유용하다. (유저가 우연히 마우스 아웃할 때)

## Syntax

```javascript
var timeoutID = window.setTimeout(func, [delay, param1, param2])
var timeoutID = winwdow.setTimeout(code, [delay]);
```

- `timeoutID`는 숫자 id다. timer를 취소하기 위해 `clearTimeout()`을 사용할 때 필요하다.

## The Problem With "this"

setTimeout에 의해 실행된 코드가 실행 될 때 분리된 실행 컨텍스트를 가진다. `this` keyword의 컨텍스트가 중요할 때 문제가 생긴다.

```javascript
var person = {
	firstName: "Jim",
	introduce: function(){
		console.log("Hi, I'm " + this.firstName);
	}
};
person.introduce();
// outputs : Hi, I'm Jim
setTimeout(person.introduce, 50);
// outputs : Hi, I'm undefined
```

- `setTimeout(person.introduce, 50);` 여기서 `this`는 `window`를 가리킨다.

### this 값 명시적으로 설정하기

`bind()`를 사용하여 `person` object로 `this`를 설정한다.

```javascript
setTimeout(person.introduce.bind(person), 50);
```

### Use a Library

많은 라이브러리에 이 이슈를 해결하기 위한 함수가 내장되어있다. 예를 들어, jQuery의 `$.proxy()` method가 있다.

이것은 함수를 가지고 특정 컨텍스트를 가진 새로운 함수를 리턴한다.

```javascript
setTimeout($.proxy(person.introduce, person), 50);
```

### canceling Timer

`setTimeout`의 리턴 값은 숫자 id 값이다. 이것은 timer를 취소할 수 있는 `clearTimeout()` 함수에 같이 사용된다.

## wrapping up

`setTimeout`은 비동기다. 그것은 함수 참조를 큐안에 넣는다.
현재 호출 스택이 실행하는 것을 끝내면 실행되도록 수신한 함수 참조 대기열에 넣는다. 그러나 동시에 실행되거나 별도의 스레드로 운용되지 않는다.(JS는 싱글 스레드니까)

```javascript
console.log(1);
setTimeout(function(){
	console.log(2);
},0);
console.log(3);
```

native JS `setTimeout`과 jQuery의 `delay` 사용에 약간의 혼란이 있다.

`delay` method는

## summary

- 함수 호출을 지연하기 위한 `setTimeout` 사용 방법
- setTimeout에 파라미터 전달하는 방법
- 콜백 내부에서 `this` value 유지하는 방법
- timer 취소하는 방법
