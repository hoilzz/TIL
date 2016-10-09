# React Project 만들기 | NPM, WEBPACK

1. Webpack : 브라우저 위에서 import(require)를

## 프로젝트 생성
package json이라는 파일 생성. 이 파일이 프로젝트 정보를 담고 있다.

## Dependency 및 Plugin 설치

--save 이 키워드가 있어야 package.json파일에 추가함
--save-dev : 개발 과정에서 필요한 패키지

바벨은 es6문법을 프로젝트에서 사용 가능하도록
babel-preset-react JSX 문법 사용하도록
react-hot-loader 실행 중에 특정 컴포넌트가 업데이트되면 해당 컴포넌트만 업뎃, 개발서버가 리액트를 호환하지 않기 때문에 따로 설정해줘야함. (이거 설정 안하면 새로고침만 해야함.)

## Webpack 설정

## 개발서버 실행 스크립트
