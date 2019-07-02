# babel 7.4.0

추가 지원

- TS 3.4
- proposal for patial application in function calls
- static private method
- @babel/preset-env 와 @babel/tranform-runtime이 core-js@3을 지원함
- @babel/template이 sweet new syntax를 가진다.

자세한 사항은 [Github 참조](https://github.com/babel/babel/releases/tag/v7.4.0)

## Highlights

### core-js 3

@babel/polyfill, @babel/runtime, @babel/preset-env에 의해 로드되는 polyfills을 전부 제공한다.

core-js@3 은 릴리즈 되었다. 자세한건 [core-js@3, babel and a look into the future](https://github.com/zloirock/core-js/blob/master/docs/2019-03-19-core-js-3-babel-and-a-look-into-the-future.md)

@babel/plugin-transform-runtime을 사용하여 **instance** method를 폴리필하여 전역 환경을 오염시키지 않으면서 기존 브라우저에서 사용할 수 있다.

```js
// 'foo' could be either a string or an array, or a custom object
foo.includes("a");

// ⮕

import _includesInstanceProperty from "@babel/runtime-corejs3/core-js-stable/instance/includes";

_includesInstanceProperty(foo).call(foo, "a");
```

@babel/preset-env 와 @babel/plugin-transform-runtime은 proposal polyfill을 지원한다. `corejs: 3` 대신에 `corejs: { version: 3, proposals: true}`를 이용해야 한다. (ECMAScript proposal은 unstable 하다는걸 알아두자.)

### core-js@2에서 마이그레이션
