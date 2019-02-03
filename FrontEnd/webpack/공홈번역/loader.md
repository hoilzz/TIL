# Loaders

웹팩 공홈의 [loader](https://webpack.js.org/concepts/loaders/)를 필요한 것만 번역했슴다.

모듈의 소스코드에 적용되는 transformation이다. (적당한 해석을 못하겠다). `import` 할 때 pre-process(전처리) 한다. 따라서, loaders 는 build tool에서 일종의 task다.

그 task들은 다음과 같다.

1. ts에서 js로 변환
2. JS module에서 `import` CSS files할 수 있도록 함
3. inline images를 data URL로 변환

예를 들어, 1,2번을 웹팩 로더에 적용한다고 해보자.

```js
module.exports = {
  module: {
    rules: [
      { test: /\.css$/, use: "css-loader" },
      { test: /\.ts$/, use: "ts-loader" }
    ]
  }
};
```

위 코드는 웹팩에게 다음과 같이 말한다.

- 모든 `.css` 파일에 대해 `css-loader`를 사용해라
- 모든 `.ts` 파일에 대해 `ts-loader`를 사용해라.

## Loader features

- Loader는 체이닝 될 수 있다. 체이닝 안에서 각 로더는 처리된 리소스를 transformation에 적용한다. 체인은 역순으로 실행된다. 아래 예제를 보자.

```js
// webpack.config.js
module.exports = {
    ...
    module: {
        rules: [{
            test: /\.scss$/,
            use: [
                "style-loader", // creates style nodes from JS strings
                "css-loader", // translates CSS into CommonJS
                "sass-loader" // compiles Sass to CSS, using Node Sass by default
            ]
        }]
    }
};
```

.scss 파일에 대해 use 배열을 역순으로 실행한다.

1. sass-loader를 통해 css로 컴파일.
2. 컴파일된 css를 commonJS로 translate
3. JS로 생성된 css를 style node로 생성.

> .scss는 브라우저가 그대로 읽을 수 없다. 보통 scss compiler를 통해 css로 컴파일된다.

- Plugin은 loader에게 더 많은 feature를 제공.

## Summary

로더는 `import *.js|.scss|.img ..`에 대해 pre-process 한다.

- ts -> js 전환 
- import CSS file을 JS module에서 가능하게 함 
- images를 data URL로 변환