# == VS ===

`===` 은 엄격한 같음, `==`은 느슨한 같음.

|   ㅌㅈ   |   `==`   |   `===`    |
|:---------:|:-------|:-----------|
|형변환| O          |      X      |



## ===

1. 형 비교
	- 서로 다른형 : 같지 않다.
	- 같은형 : 숫자가 아닌 경우, 값 비교. 숫자면 둘 다 NaN이 아닌 같은 값이거나 +0, -0인 경우도 같다고 한다.

2. 값 비교

>`Object.is`는 삼중 등호와 같은 식으로 동작한다.
- NaN 및 -0과 +0에 대한 특별 처리로 인해 `Object.is(NaN, NaN)`은 true가 된다.



```javascript
var num = 0;
var obj = new String("0");
var str = "0";
var b = false;

console.log(num === num); // true
console.log(obj === obj); // true
console.log(str === str); // true

console.log(num === obj); // false
console.log(num === str); // false
console.log(obj === str); // false
console.log(null === undefined); // false
console.log(obj === null); // false
console.log(obj === undefined); // false
```


## ==

1. 두 값을 **공통 형으로 변환**한다.
2. 값을 비교한다. (최종 같음 비교는 `===`처럼 수행된다.)

```javascript
var num = 0;
var obj = new String("0");
var str = "0";
var b = false;

console.log(num == num); // true
console.log(obj == obj); // true
console.log(str == str); // true

console.log(num == obj); // true
console.log(num == str); // true
console.log(obj == str); // true
console.log(null == undefined); // true

// 둘 다 false, 드문 경우를 제외하고는
console.log(obj == null);
console.log(obj == undefined);
```


## Summary

1. === 비교과정
	- 형을 비교한다
	- 값을 비교한다.(숫자는 NaN이 아닌 경우 같은 값인 경우 같다.)

2. == 비교 과정
	- 강제 형변환으로 일치시킨다.
	- 값만 비교한다.
