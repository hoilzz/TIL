# 3.5.9 유사 배열 객체

`배열`의 length 프로퍼티는 배열의 동작에 있어서 중요한 프로퍼티다.

만약 `일반 객체`가 length를 가지고 있다면?

length 프로퍼티를 가진 객체를 유사 배열 객체(array-like objects)라고 한다.

유사 배열 객체의 가장 큰 특징은 JS의 표준 배열 메서드 사용 가능 하다는 점이다.

```javascript
var arr = ['bar'];
var obj = {
	name:'foo',
	length:1
};
arr.push('baz');
console.log(arr); // ['bar', 'baz'];

obj.push('baz'); // error
```

유사 배열 객체의 경우, `apply()` 메서드를 사용하면 **객체지만 `표준 배열 메서드` 활용하는 것이 가능**하다.

결과값을 보면 obj 객체의 '1' 프로퍼티에 'baz'가 추가되었고,

length는 2로 증가한 것을 확인할 수 있다.

```javascript
Array.prototype.push.apply(obj, ['baz']);
console.log(obj); // {'1':'baz', name:'foo', length:2}
```

## summary

`유사 배열 객체`

	- length 프로퍼티를 가진 객체
	- 배열 메서드 사용하는 것이 가능하다.
