# tour 서비스에서 폴리필 관련 이슈.

```js
defineIteratorMethods(AsyncIterator.prototype);

AsyncIterator.prototype[asyncIteratorSymbol] = function() {
  return this;
};

exports.AsyncIterator = AsyncIterator;
```

**오류 내용**

Error: asyncIteratorSymbol이 문자열이 아닙니다. (IE 9~11에서)

[ES7 asyncIterator](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Symbol/asyncIterator)

tour_customview의 바벨 관련 패키지 버전

```json
// 해당 이슈 이해를 돕는 패키지 외에 전부 생략
{
  "devDependencies": {
    "@babel/core": "^7.0.0",
    "@babel/plugin-transform-regenerator": "^7.4.5",
    "@babel/plugin-transform-runtime": "^7.4.4",
    "@babel/preset-env": "^7.0.0"
  },
  "dependencies": {
    "@babel/polyfill": "^7.0.0",
    "@babel/runtime": "^7.4.5",
    "core-js": "^2.4.1"
  }
}
```

```js
// babel.config.js, 해당 이슈 이해를 돕는 패키지 외에 전부 생략
module.exports = {
  presets: [
    [
      '@babel/preset-env',
      {
        targets: '> 0.25%, not dead',
        modules: false,
        debug: true,
        useBuiltIns: 'usage', // 'usage(experimental)',
      },
    ],
    ['@babel/preset-react'],
  ],
  plugins: ['@babel/plugin-transform-regenerator'],
};
```

## 해결방안 찾아가기

### 1. 바벨 폴리필 통째로 집어넣기

ES7의 asyncIterator를 지원하지 않는 거 같아 빠른 해결을 위해

- `useBuiltIns: 'entry'`로 변경하여 모든 polyfill 집어넣기

결론 : 똑같은 오류내용 보여주면서 안됨.

### 2. 근데 저 문법을 투어에서 쓰고 있나요..?

아니요.. 그렇다면 라이브러리에서 사용하는건데..

> babel-loader가 권장한대로 node_modules은 제외하고 트랜스파일함.
> 권장 이유는 트랜스파일이 굉장히 느려질거고.. 대부분 라이브러리는 트랜스파일을 거쳐서 나오기때문..(대신 브라우저 지원 범위가 다름)

이 때, 모든 node_modules을 트랜스파일 하면 될 것 같았지만 시간 여유가 있어서 다른 방법 찾아봄

### 3. 시간도 많으니까 걍 바벨 설정 첨부터 다 까보자.

첨부터 다 까다가 생각해보니 문제되는 syntax에 대해 polyfill을 추가하면 되겠네 라고 생각해서 해결했다.

```js
// in config/polyfill.js
import 'core-js/modules/es7.symbol.async-iterator';
```

### 이런 일이 없도록 하려면..?

#### babel/preset-env의 useBuiltIns를 entry로 하여 모든 폴리필을 집어넣자.

1번 해결책에서 봤듯이 모든 폴리필이 들어가는거 같지 않았다. 이유는..

entry 옵션만 넣었다고 polyfill이 전부 추가되지 않는다.
entry 는 말 그대로 개발자가 import문을 작성한 폴리필만 transpile때 추가한다.
(entry 옵션으로 해놓고, 폴리필을 import하지 않으면 어떠한 polyfill도 포함되지 않는다.)

이 때 아래와 같이 작성하면 3가지 polyfill만 추가된다. (투어 에서 아래와 같이 작성되있었다.)
4번째 라인만 import해야 모든 폴리필이 추가된다.

```js
import 'core-js/es6/map';
import 'core-js/es6/set';
import 'core-js/fn/array';
// import "core-js/stable"

var promise = new Promise(resolve => {
  resolve(5);
});
```

결론은 entry로 한다고 해서 모든 폴리필이 추가되는게 아닌, 개발자가 직접 모든 폴리필을 import하는 코드를 작성해줘야 한다.

하지만, 불필요한 폴리필이 포함되므로 좋지 않은 방법이다.

---

```js
import 'core-js';

var promise = new Promise(resolve => {
  resolve(parsed);
});

promise().then(val => console.log(val));
```

위 코드를 바벨로 트랜스파일 하면.. 아래와 같이 전부 import 된다.

왜냐하면 나는 promise만 필요한데, 아래와 같이 모든 폴리필이 불필요하게 추가되기 때문이다.

```js
require('core-js/modules/es6.array.copy-within');

require('core-js/modules/es6.array.fill');

require('core-js/modules/es6.array.find');

require('core-js/modules/es6.array.find-index');

require('core-js/modules/es7.array.flat-map');

require('core-js/modules/es6.array.from');

require('core-js/modules/es7.array.includes');

require('core-js/modules/es6.array.iterator');

require('core-js/modules/es6.array.of');

require('core-js/modules/es6.array.species');

require('core-js/modules/es6.date.to-primitive');

require('core-js/modules/es6.function.has-instance');

require('core-js/modules/es6.function.name');

require('core-js/modules/es6.map');

require('core-js/modules/es6.math.acosh');

require('core-js/modules/es6.math.asinh');

require('core-js/modules/es6.math.atanh');

require('core-js/modules/es6.math.cbrt');

require('core-js/modules/es6.math.clz32');

require('core-js/modules/es6.math.cosh');

require('core-js/modules/es6.math.expm1');

require('core-js/modules/es6.math.fround');

require('core-js/modules/es6.math.hypot');

require('core-js/modules/es6.math.imul');

require('core-js/modules/es6.math.log1p');

require('core-js/modules/es6.math.log10');

require('core-js/modules/es6.math.log2');

require('core-js/modules/es6.math.sign');

require('core-js/modules/es6.math.sinh');

require('core-js/modules/es6.math.tanh');

require('core-js/modules/es6.math.trunc');

require('core-js/modules/es6.number.constructor');

require('core-js/modules/es6.number.epsilon');

require('core-js/modules/es6.number.is-finite');

require('core-js/modules/es6.number.is-integer');

require('core-js/modules/es6.number.is-nan');

require('core-js/modules/es6.number.is-safe-integer');

require('core-js/modules/es6.number.max-safe-integer');

require('core-js/modules/es6.number.min-safe-integer');

require('core-js/modules/es6.number.parse-float');

require('core-js/modules/es6.number.parse-int');

require('core-js/modules/es6.object.assign');

require('core-js/modules/es7.object.define-getter');

require('core-js/modules/es7.object.define-setter');

require('core-js/modules/es7.object.entries');

require('core-js/modules/es6.object.freeze');

require('core-js/modules/es6.object.get-own-property-descriptor');

require('core-js/modules/es7.object.get-own-property-descriptors');

require('core-js/modules/es6.object.get-own-property-names');

require('core-js/modules/es6.object.get-prototype-of');

require('core-js/modules/es7.object.lookup-getter');

require('core-js/modules/es7.object.lookup-setter');

require('core-js/modules/es6.object.prevent-extensions');

require('core-js/modules/es6.object.to-string');

require('core-js/modules/es6.object.is');

require('core-js/modules/es6.object.is-frozen');

require('core-js/modules/es6.object.is-sealed');

require('core-js/modules/es6.object.is-extensible');

require('core-js/modules/es6.object.keys');

require('core-js/modules/es6.object.seal');

require('core-js/modules/es7.object.values');

require('core-js/modules/es6.promise');

require('core-js/modules/es7.promise.finally');

require('core-js/modules/es6.reflect.apply');

require('core-js/modules/es6.reflect.construct');

require('core-js/modules/es6.reflect.define-property');

require('core-js/modules/es6.reflect.delete-property');

require('core-js/modules/es6.reflect.get');

require('core-js/modules/es6.reflect.get-own-property-descriptor');

require('core-js/modules/es6.reflect.get-prototype-of');

require('core-js/modules/es6.reflect.has');

require('core-js/modules/es6.reflect.is-extensible');

require('core-js/modules/es6.reflect.own-keys');

require('core-js/modules/es6.reflect.prevent-extensions');

require('core-js/modules/es6.reflect.set');

require('core-js/modules/es6.reflect.set-prototype-of');

require('core-js/modules/es6.regexp.constructor');

require('core-js/modules/es6.regexp.flags');

require('core-js/modules/es6.regexp.match');

require('core-js/modules/es6.regexp.replace');

require('core-js/modules/es6.regexp.split');

require('core-js/modules/es6.regexp.search');

require('core-js/modules/es6.regexp.to-string');

require('core-js/modules/es6.set');

require('core-js/modules/es6.symbol');

require('core-js/modules/es7.symbol.async-iterator');

require('core-js/modules/es6.string.anchor');

require('core-js/modules/es6.string.big');

require('core-js/modules/es6.string.blink');

require('core-js/modules/es6.string.bold');

require('core-js/modules/es6.string.code-point-at');

require('core-js/modules/es6.string.ends-with');

require('core-js/modules/es6.string.fixed');

require('core-js/modules/es6.string.fontcolor');

require('core-js/modules/es6.string.fontsize');

require('core-js/modules/es6.string.from-code-point');

require('core-js/modules/es6.string.includes');

require('core-js/modules/es6.string.italics');

require('core-js/modules/es6.string.iterator');

require('core-js/modules/es6.string.link');

require('core-js/modules/es7.string.pad-start');

require('core-js/modules/es7.string.pad-end');

require('core-js/modules/es6.string.raw');

require('core-js/modules/es6.string.repeat');

require('core-js/modules/es6.string.small');

require('core-js/modules/es6.string.starts-with');

require('core-js/modules/es6.string.strike');

require('core-js/modules/es6.string.sub');

require('core-js/modules/es6.string.sup');

require('core-js/modules/es7.string.trim-left');

require('core-js/modules/es7.string.trim-right');

require('core-js/modules/es6.typed.array-buffer');

require('core-js/modules/es6.typed.int8-array');

require('core-js/modules/es6.typed.uint8-array');

require('core-js/modules/es6.typed.uint8-clamped-array');

require('core-js/modules/es6.typed.int16-array');

require('core-js/modules/es6.typed.uint16-array');

require('core-js/modules/es6.typed.int32-array');

require('core-js/modules/es6.typed.uint32-array');

require('core-js/modules/es6.typed.float32-array');

require('core-js/modules/es6.typed.float64-array');

require('core-js/modules/es6.weak-map');

require('core-js/modules/es6.weak-set');

require('core-js/modules/web.timers');

require('core-js/modules/web.immediate');

require('core-js/modules/web.dom.iterable');

require('regenerator-runtime/runtime');
```

그래서 이건 좋지 않은 방법이다.

#### 라이브러리를 사용하기 전에 어디까지 지원하는지 확인하자.

예를 들어 [쿼리스트링 라이브러리](https://github.com/sindresorhus/query-string#install)을 보면, 친절하게 **IE** 는 지원하지 않는다고 알려줬다.

코드를 까보면 const, let을 사용하고 있다.

#### 근데 지원 범위를 라이브러리에서 알려주지 않아요.. ㅂㄷㅂㄷ

개발자가 IE 에서 test를 해보거나,

QA 분이 IE에서 안된다고 할 때,

해당 syntax 에러와 관련된 패키지를 직접 추가해주는 방법밖에 없는 거 같다.

아래와 같이..

```js
// in config/polyfill.js
import 'core-js/modules/es7.symbol.async-iterator';
```

#### 의심되는 혹은 폴리필이 필요한 라이브러리는 뭔지 알겠어요

babel-loader의 include 옵션에 해당 모듈만 포함시켜서 같이 트랜스파일 시키자.

#### 어떤 라이브러리가 문제인지도 모르겠고, 어떤 폴리필이 필요한지도 모르겠고.. 제가 시간이 없거든요..

```js
// babel config를 entry 로 설정 후,
import 'core-js';
```

이외에 좋은 해결 방법이나 틀린 내용이 있다면 알려주세요.. 해결방법을 찾고 공식 문서 읽어가며 작성한 내용입니다.
