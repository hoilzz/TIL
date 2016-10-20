# lexical scope (static scope)
자바스크립트는 **함수가 선언된 시점** 에서 유효범위를 갖는다.

```javascript
var i = 5;

function a(){
  var i = 10;
  b();
}
function b(){
  console.log(i);
}
a();
```
## i는 누구인가
*a() 함수 호출시 b()호출 할 때 b 선언부의 i는 누구를 가리키는가?*
```
function b(){
  console.log(i);
}
```
- console.log(i)에서 i는 누구일까
- i는 존재하지 않는다.

- **그럼 전역변수를 찾는다** `var i = 5`

## WHY
- function b()가 **선언된 시점의 전역변수** `var i = 5`가 사용됨
- b()가 **호출된 시점의 전역변수가 아니다**

## Summary
- lexical scope는 사용될 때가 아닌 정의될 때의 전역변수를 찾는다.
