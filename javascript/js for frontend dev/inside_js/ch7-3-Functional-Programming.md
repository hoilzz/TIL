# 7.3 JS에서의 FP를 활용한 주요 함수

`Function.prototype.apply` 함수로 함수 호출 수행할 수 있다.

근데 왜 이름이 apply 일까

함수 적용`applying function`은 FP에서 사용되는 용어다.

FP에서는 특정 데이터를 여러 가지 함수를 적용시키는 방식으로 작업을 수행한다.

여기서 함수는 단순히 입력을 넣고 출력을 받는 기능을 수행 하는 것뿐만 아니라,

*인자 혹은 반환 값으로 전달된 함수를 특정 데이터에 적용시키는 개념* 으로 이해해야 한다.

따라서 `func.apply(Obj, Args)`와 같은 함수 호출을

`func 함수를 Obj 객체와 Args 인자 배열에 적용시킨다` 라고 표현 가능하다.

## 7.3.2 커링


## 7.3.4 래퍼

래퍼란 특정 함수를 자신의 함수로 덮어쓰는 것이다.

물론 여기서 사용자는 원래 함수 기능을 잃어버리지 않은 상태로 자신의 로직을 수행할 수 있어야 한다.

객체지향 프밍에서 다형성의 특성을 살리려면 오버라이드를 지원하는데, 이와 유사하다고 보면 된다.

```javascript
function wrap(obj, method, wrapper){
	var fn = obj[method];
	return obj[method] = function(){
		return wrapper.apply(this, [ fn ]. concat(
		//return wrapper.apply(this, [ fn.bind(this) ].concat(

		Array.prototype.slice.call(arguments)));
	}
}

Function.prototype.original = function(value){
	this.value = value;
	console.log("value : " + this.value);
}

var mywrap = wrap(Function.prototype, "original", function(orig_func, value){
	this.value = 20;
	orig_func(value);
	console.log("wrapper value : " + this.value);
});

mywrap("hoil");

// value : hoil
// wrapper value : 20
```
