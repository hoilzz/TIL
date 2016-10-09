# React Project 만들기 | NPM, WEBPACK

1. Webpack : 브라우저 위에서 import(require) 를 할 수 있게 해주고 자바스크립트 파일들을 하나로 합쳐줍니다

2. webpack-dev-server : 별도의 서버를 구축하지 않고도 static 파일을 다루는 웹서버를 열 수 있으며 hot-loader 를 통하여 코드가 수정 될 때마다 자동으로 리로드 되게 할 수 있습니다.

## 프로젝트 생성
package json이라는 파일 생성. 이 파일이 프로젝트 정보를 담고 있다.

## Dependency 및 Plugin 설치

--save 이 키워드가 있어야 package.json파일에 추가함
--save-dev : 개발 과정에서 필요한 패키지

바벨은 es6문법을 프로젝트에서 사용 가능하도록
babel-preset-react JSX 문법 사용하도록
react-hot-loader 실행 중에 특정 컴포넌트가 업데이트되면 해당 컴포넌트만 업뎃, 개발서버가 리액트를 호환하지 않기 때문에 따로 설정해줘야함. (이거 설정 안하면 새로고침만 해야함.)

## Webpack 설정
webpack.config.js를 한줄씩 뜯어보자

```javascript
var webpack = require('webpack');
```
- require로 불러오기

```javascript
module.exports = {
  entry: ['react-hot-loader/patch', './src/index.js'],
...}
```
- 이 객체를 모듈로 내보내겠다
- entry : 웹팩의 핵심 기능,
  + require 기능을 클라이언트에서 사용하여 코드를 1개 파일로 합치기
  + 해당 파일에서부터 require한 파일을 불러오고 그 과정에서 require한거 불러오고 이렇게 재귀적으로 불러와서 필요한 모듈 모두 불러오기

```javascript
  output: {
    path: __dirname + '/public/',
    filename: 'bundle.js'
  },
```
- 합친 파일들을 bundle js로 저장

```javascript
  devServer: {
    hot: true,
    inline: true,
    host: '0.0.0.0',
    port: 4000,
    contentBase: __dirname + '/public/'
  }
```
- 개발서버의 설정
- hot는 파일이 수정될때마다 리로
- 인라인은 hot reloading에서 필요한 웹팩 데브서버를 번들에 같이 넣어주는 것
- 호스트는 서버를 리슨할 주소

```javascript
module: {
  loaders: [
    {
      test: /.js$/,
      loader: 'babel',
      exclude: /node_modules/,
      query: {
          cacheDirectory: true,
          presets: ['es2015', 'react'],
          plugins: ["react-hot-loader/babel"]
      }      
    }
  ]
}
```
- module : 웹팩의 핵심 기능
  + babel : es2015, es6을 일반 자바스크립트로 변경
  + less, sass -> css로 변경과 같은 기능
- loader를 2개 이상 적용하기 위해 s붙이기
- 값을 배열로 받음

```javascript
  plugins: [
      new webpack.HotModuleReplacementPlugin()
  ]
```
- 자동으로 리로딩해주는 hot 모듈 reload도 플러그인을 통해서 함
- 자바스크립트 압축하는 uglify, 서드파티 플러그인 많음

### Summary
- 이와 같이 웹팩은 할 수 있는게 많다-그런트,걸프 대체 가능


## 개발서버 실행 스크립트
dev-server라는 스크립트 만들어보자
- script라는 곳에 key값 : dev-server, 값 : webpack-dev-server로 설정


## App.js

```javascript
export default App;
```
- App.js 클래스를 사용할 수 있도록 export
