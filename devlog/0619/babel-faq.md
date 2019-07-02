# babel-faq

## @babel/core

모든 transformation은 config file을 이용한다.

- .babelrc, .babelrc.js 와 같은 config file을 이용하여 실제로 transpile을 진행
- 그래서 아래와 같이 transform, transformFile 등과 같은 메서드를 가지고 있음.

_transform_

- code 파라미터를 transform한다
- 생성된 코드, source map, AST를 가진 object로 콜백을 호출.

```js
import * as babel from "@babel/core";

babel.transform(code, options, function(err, result) {
  result; // => { code, map, ast }
});

babel.transformFile("filename.js", options, function(err, result) {
  result; // => { code, map, ast }
});
```

_parse_

Given some code, parse it using Babel's standard behavior. Referenced presets and plugins will be loaded such that optional syntax plugins are automatically enabled.
