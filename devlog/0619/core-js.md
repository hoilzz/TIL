# core-js

core-js는 바벨과 통합됐고 polyfilling과 관련된 babel feature의 베이스다.

- JS 표준 라이브러리의 폴리필, 지원 범위는
  - 최신 ECMAScript 표준
  - W3C 표준
- maximally 모듈러 형태다. 그래서 필요한 피처만 스코프로 로드할 수 있다.
- 글로벌 네임스페이스 오염 없이 사용될 수 있다.
- babel/preset-env와 함께 최적화 될 수 있다. 아래 글을 참조하자.

## @babel/polyfill과의 관계?

@babel/polyfill은 단순히 stable core-js 기능과 generator와 async 함수의 regenerator-runtime의 import 다.

그래서 만약 @babel/polyfill를 로드하면 ES proposal 없는 core-js의 global version을 load한거다.

@babel/polyfill은 다음과 같다.

```js
import "core-js/stable";
import "regenerator-runtime/runtime";
```

## @babel/preset-env

core-js의 글로벌 버전과 함께 동작하도록 최적화된 useBuiltIns 옵션을 가진다.

[core-js3과 바벨](https://github.com/zloirock/core-js/blob/master/docs/2019-03-19-core-js-3-babel-and-a-look-into-the-future.md#Babel)
