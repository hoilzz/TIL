# @babel/plugin-transform-runtime

[@babel/plugin-transform-runtime](https://babeljs.io/docs/en/babel-plugin-transform-runtime) 요약

**코드사이즈를 절약하기 위해 바벨에서 주입해준 helper를 re-use하도록 해주는 플러그인**

> 'foobar'.includes('foo') 와 같은 인스턴스 메서드는 동작하지 않을 것이다. 왜냐하면 기존에 내장된 거의 수정을 필요로 하기 때문이다.(동작하도록 하기 위해 @babel/polyfill를 사용할 수 있다.)

얘는 @babel/runtime을 production 의존성을 갖는다. (왜냐하면 **runtime** 에서 동작해야 하니까.)

transformation plugin은 development 에서만 사용된다. 하지만 runtime은 배포된 코드에 의존성을 갖는다. 뭔말이지?

## Why?

바벨은 \_extend 와 같은 공통 함수를 위한 small helper를 사용한다. 이것을 필요로하는 모든 파일에 헬퍼가 추가될거다. 이러한 중복은 불필요하다. 특히 어플리케이션이 여러개의 파일로 쪼개진 경우에..

이거슬 위해 @babel/plugin-transform-runtime 플러그인이 있다. 모든 헬퍼는 컴파일된 ouput에서 중복을 피하기 위해 @babel/runtime을 참조할 거다. runtime은 빌드에 컴파일 될거다.

transformer의 다른 목적은 코드에 대한 샌드박스 환경을 만드는거다. 만약 Promise, Set, Map과 같은 것을 제공하는 빌트인과 @babel/polyfill을 사용한다면, global scope를 오염시킬거다. app이나 CLI에서는 괜찮은 반면에 만약 너의 코드가 라이브러리라면 혹은 너의 코드가 실행되는 환경에 문제가 될 수 있다.

transformer는 built-ins을 `core-js`로 별칭을 지정한다. 그래서 polyfill 없이도 완벽하게 사용할 수 있다. (??)

```json
// defaults
{
  "plugins": [
    [
      "@babel/plugin-transform-runtime",
      {
        "absoluteRuntime": false,
        "corejs": false,
        "helpers": true,
        "regenerator": true,
        "useESModules": false
      }
    ]
  ]
}
```

[`corejs`](https://babeljs.io/docs/en/babel-plugin-transform-runtime#corejs) option은 명시해주자.

## Technical details

`transform-runtime` transformer plugin은 3가지 일을 한다.

- generator/async 함수를 사용할 때 자동으로 `@babel/runtime/regenerator` 를 요구한다.
- 필요한 경우 `core-js` 옵션을 사용할 수 있음
- 자동으로 inline babel helers를 지우고 `@babel/runtime/helpers` 모듈을 대신 사용한다.

위 3가지 일은 실제로 뭘 의미할까?

기본적으로 promise, set, symbol 과 같은 빌트인 기능을 사용할 수 있다.
뿐만 아니라, global 오염 없이 완벽하게 polyfill을 필요로 하는 모든 바벨 feature를 사용하여 라이브러리에 매우 적합하다.

**`@babel/runtime`을 dependency로 포함하는 것을 잊지마라**

예제를 보자.

다음 제너레이터 함수를 사용할 때 마다

```js
function* foo() {}
```

```js
"use strict";

var _marked = [foo].map(regeneratorRuntime.mark);

function foo() {
  return regeneratorRuntime.wrap(
    function foo$(_context) {
      while (1) {
        switch ((_context.prev = _context.next)) {
          case 0:
          case "end":
            return _context.stop();
        }
      }
    },
    _marked[0],
    this
  );
}
```

위와 같이 코드가 생성될텐데, 이상적이지 않다. 왜냐하면 regenerator runtime을 의존하기 때문이다. 이것은 global scope를 오염시킨다. `runtime` transformer로 다음과 같이 컴파일 할 수 있다.

```js
"use strict";

var _regenerator = require("@babel/runtime/regenerator");

var _regenerator2 = _interopRequireDefault(_regenerator);

function _interopRequireDefault(obj) {
  return obj && obj.__esModule ? obj : { default: obj };
}

var _marked = [foo].map(_regenerator2.default.mark);

function foo() {
  return _regenerator2.default.wrap(
    function foo$(_context) {
      while (1) {
        switch ((_context.prev = _context.next)) {
          case 0:
          case "end":
            return _context.stop();
        }
      }
    },
    _marked[0],
    this
  );
}
```

너의 현재 환경을 오염시키지 않고 regenerator runtime을 사용할 수 있다.

## Summary

코드사이즈 절약하기 위해 바벨에서 주입해준 helper를 re-use하도록 해주는 플러그임

사용하는 이유?

- 공통 헬퍼 함수 중복 사용을 피하기 위해 사용
- global scope 오염을 피하기 위해 사용.

주의할 점

- @babel/runtime 을 dependency로 포함해야한다.
  - 컴파일된 output에서 중복을 피하기 위해서는 @babel/runtime이 필요하다.
  - transformation plugin인 자체는 development에서만 사용된다.
