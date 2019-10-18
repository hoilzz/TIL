# babel

바벨은 JS 컴파일러다. ES2015+ 코드를 내가 명시한 타겟 브라우저에 맞게 변경해준다.

```js
// Babel Input: ES2015 arrow function
[1, 2, 3].map(n => n + 1);

// Babel Output: ES5 equivalent
[1, 2, 3].map(function(n) {
  return n + 1;
});
```

이제 create-tmon-webapp에 포함된 바벨 설정을 보자.

```json
{
  "devDependencies": {
    "@babel/core": "^7.4.5",
    "@babel/plugin-transform-runtime": "^7.4.4",
    "@babel/preset-env": "^7.4.5",
    "@babel/preset-react": "^7.0.0"
  },
  "dependencies": {
    "@babel/runtime": "^7.4.5",
    "core-js": "^3.1.4"
  }
}
```

- @babel/core
  - babel config 파일을 이용하여 실제로 transpile을 진행.
- @babel/preset-env
  - 똑똑한 프리셋, 타겟환경에 필요한 구문([browserlist](https://github.com/browserslist/browserslist))을 개발자가 관리할 필요 없이 알아서 transform plugin과 core-js polyfill과 매핑한다.
  - **주의할 점은 stage-x 플러그인을 지원하지 않는다!!**

> preset, plugin?
> plugin은 특정 syntax에 대한 것이다.
> @babel/plugin-transform-arrow-functions
> preset은 plugin들의 모음집.
> stage별로 (stage-X) 혹은 react, typescript와 같은 것들을 transpile 하기 위한 모음집들.

- @babel/preset-react

  - react 관련 코드를 변형하기 위한 프리셋. 대표적으로 jsx -> React.createElement

- @babel/plugin-transform-runtime

  - 코드 사이즈를 절약하기 위해 바벨에서 주입해준 helper 함수 재사용해도록 도와주는 플러그인. (inline babel hleper -> @babel/runtime/helper 모듈 대신 사용.)
  - 그래서 @babel/runtime을 dependency로 포함해야한다.
  - global scope 오염을 피하기 위해 사용
  - 예제를 보고 싶으면 [이동](https://babeljs.io/docs/en/babel-plugin-transform-runtime#regenerator-aliasing)

- core-js
  - 잘 알려진 @babel/polyfill은 core-js와 regenerator-runtime을 import한다.
  - babel 7.4.0부터 polyfill은 deprecated 됐고, core-js와 regenerator-runtime을 각각 import 해야한다. [참고](https://github.com/zloirock/core-js/blob/master/docs/2019-03-19-core-js-3-babel-and-a-look-into-the-future.md#babelpolyfill)

```js
module.exports = {
  presets: [
    [
      '@babel/preset-env',
      {
        modules: false, // webpack이 import문을 통해 최적화된 dependengy graph를 그릴 수 있음.
        useBuiltIns: 'usage', // 서비스 코드에서 필요한 polyfill(core-js)만 포함.
        corejs: 3,
      },
    ],
    ['@babel/preset-react'],
  ],
  plugins: [
    [
      '@babel/plugin-transform-runtime',
      {
        corejs: 3,
      },
    ],
  ],
};
```
