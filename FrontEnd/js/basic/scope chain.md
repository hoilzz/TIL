# scope chain

[https://github.com/hoilzz/hoilzz.github.io/blob/f966ccf6c7162ca6714f89d581a773d6fc61e47b/\_posts/2017-6-12-scope-chain.md](https://github.com/hoilzz/hoilzz.github.io/blob/f966ccf6c7162ca6714f89d581a773d6fc61e47b/_posts/2017-6-12-scope-chain.md)
[zero초님 scope](https://www.zerocho.com/category/JavaScript/post/5740531574288ebc5f2ba97e)

## lexical Scope

**자바스크립트 스코프는 함수 호출이 아닌 선언 때 생긴다.**

> 스코프는 함수를 호출할 때가 아닌 선언할 때 생긴다! 그래서 정적 스코프다.

```js
var name = "zero";
function log() {
  console.log(name);
}

function wrapper() {
  name = "nero";
  log();
}
wrapper(); // -> nero
```

```js
var name = "zero";
function log() {
  console.log(name);
}

function wrapper() {
  var name = "nero";
  log();
}
wrapper();
```

두 번째 예시에서 nero가 출력된다고 답하면, 렉시컬 스코프를 제대로 이해 못한거다. **다시 말하지만 스코프는 함수 실행이 아닌 함수 선언때 생성된다.**

함수를 처음 선언하는 순간, 함수 내부 변수는 자기 스코프로부터 가장 가까운 곳에 있는 변수를 참고한다. log 안의 name은 wrapper의 name을 참조하는게 아닌 window의 name을 참고한다. 왜냐하면 log의 스코프체인은 자신이 생성된 EC의 스코프체인위에 자신의 스코프체인을 쌓기 때문이다. 즉, log의 스코프체인에 wrapper가 없다.

## Summary

Q. 자바스크립트의 유효 범위는?
A. C나 자바처럼 블록 스코프가 아닌, 함수 스코프가 기준이 된다.

Q. 스코프체인이란?
A. 자바스크립트는

- 각 사각형은 실행 컨텍스트임
- 내부 컨텍스트는 스코프 체인을 따라 상위(외부) 컨텍스트에서 변수나 함수를 검색할 수 있다
- 상위 컨텍스트는 내부 컨텍스트를 따라 내려 가며 검색 불가능
