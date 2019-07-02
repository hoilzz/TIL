# @babel/runtime

바벨 모듈러 런타임 헬퍼와 `regenerator-runtime` 버전을 포함하는 라이브러리다.

## Usage

`@babel/plugin-transform-runtime`과 함께 runtime `dependency`로 사용된다.

## Why

바벨은 어떤 동일한 코드를 output에 삽입하여 잠재적으로 재사용될 수 있다.

예를 들어,

loose mode 없이 class transform 예제를 보자.

```js
class Circle {}
```

다음과 같이 컴파일된다.

```js
function _classCallCheck(instance, Constructor) {
  //...
}

var Circle = function Circle() {
  _classCallCheck(this, Circle);
};
```

class를 포함하는 모든 파일은 `_classCallCheck` 함수가 반복된다.

@babel/plugin-transform-runtime을 사용하면, 함수에 대한 참조값을 @babel/runtime version으로 대체할 수 있다.

```js
var _classCallCheck = require("@babel/runtime/helpers/classCallCheck");

var Circle = function Circle() {
  _classCallCheck(this, Circle);
};
```

@babel/runtime은 단순히 모듈러 방식으로 함수 구현을 포함하는 패키지다.
