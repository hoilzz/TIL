# Hoisting

```js
console.log(zero); // 에러가 아니라 undefined
sayWow(); // 정상적으로 wow
function sayWow() {
  console.log("wow");
}
var zero = "zero";
```

함수 선언식일 때는 식 자체가 통째로 끌어올려짐. 즉, 변수 선언 및 함수 선언 전부 끌어올려짐.

```js
sayWow(); // (3)
sayYeah(); // (5) 여기서 대입되기 전에 호출해서 에러
var sayYeah = function() {
  // (1) 선언 (6) 대입
  console.log("yeah");
};
function sayWow() {
  // (2) 선언과 동시에 초기화(호이스팅)
  console.log("wow"); // (4)
}
```

```
'전역 컨텍스트': {
  변수객체: {
    arguments: null,
    variable: [{ sayWow: Function }, 'sayYeah'],
  },
  scopeChain: ['전역 변수객체'],
  this: window,
}
```

sayYeah를 실행하지 못함.
컨텍스트 생성 및 코드가 순차적으로 실행되는데 sayYeah는 값이 대입되기 전에 호출해서 에러 발생.

## summary

Q. 호이스팅이란?
A. 호이스팅은 변수 선언하고 초기화 했을 때 선언부가 최상단으로 끌어올려지는 현상이다. 함수표현식이 아닌 함수 선언식일 때는 식 자체가 통쨰로 올라간다.
