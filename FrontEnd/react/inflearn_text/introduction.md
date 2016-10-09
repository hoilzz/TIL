# introduction
## React ?
- 재사용 가능한 UI를 생성하도록 도와줌
- 페북, 인스타, 야후, 넷플릭스, 에어비엔비에서 사용중
- Virtual DOM 개념을 사용하여 상태가 변함에 따라 **선택적 UI 렌더링**
  + 최소한의 DOM 처리로 컴포넌트들을 업데이트 하도록 도움

## Virtual DOM의 작동 방식
### DOM 알기
- Document Object Model, 즉 객체를 통해 구조화된 문서를 표현하는 방법
  + XML, HTML로 작성됨
- 웹 브라우저는 DOM을 활용하여 객체에 JS와 CSS를 적용
- DOM은 *트리 형태* 로 구성됨
  + 특정 Node 찾기, 수정, 제거, 추가 가능

### DOM의 문제점
- 동적 UI에 최적화되지 않음
  + HTML은 정적임, 이를 javascript나 jQuery로 제어 가능
**하지만** 큰 규모의 웹 서비스(페북)에서 스크롤시 많은 데이터 로딩됨
- 각 데이터를 표현하는 엘리먼트가 몇백 몇천개 됨
- 페북 같은 곳에서 DOM에 직접 접근하여 변경하면 성능상 이슈 발생

> NOTE
> DOM 자체는 빠르다. DOM을 읽고 쓸 때의 성능은 js 객체를 처리 할 때의 성능과 비교해서 다를게 없다. 단 브라우저 단에서 DOM 변화 발생시, 브라우저가 CSS를 다시 연산, 레이아웃 구성, 웹 페이지 리페인트하는데 시간이 오래걸림

### 해결책
일단, HTML 마크업을 시각적인 형태로 변환 하는 것이 브라우저의 주 역할이기 때문에 이 때 사용되는 리소스는 어쩔 수 없다. 따라서, 이 문제 해결하기 위해 DOM 조작을 안할 수는 없으니까 **최소한의 DOM 조작을 통해 개선** 해야한다. 예를 들어보자.
- DOM 업데이트를 4번 하면 브라우저에서 redraw과정이 4번 발생, 개선방법은
  1. 이를 묶어서 처리
  2. 원하는 최종 결과에는 영향을 미치지 않아 불필요한 업데이트 생략

- React는 **Virtual DOM** 을 사용하여 효율적 진행
  + DOM 업데이트 추상화
  + DOM 처리 횟수 최소화

## Virtual DOM
- 실제 DOM에 접근하여 조작하는 대신, 추상화 시킨 js 객체를 구성하여 사용
- 실제 DOM의 가벼운 사본과 비슷

React에서 데이터 변경시 브라우저상의 실제 DOM 업데이트 할때 3가지 절차
1. 데이터가 업데이트되면, 전체 UI를 Virtual DOM에 리렌더링
2. 이전 Virtual DOM에 있던 내용과 현재의 내용을 비교
3. 바뀐 부분만 실제 DOM에 적용

### 오해
Virtual DOM은 무조건 빠르지 않다. React 매뉴얼을 보자.
> 지속해서 데이터가 변화하는 대규모 애플리케이션을 구축하기

즉,
- 단순 라우팅 정도만 있는 정적인 웹페이지는 React 사용하지 않는 것보다 더 나은 성능을 보임

반면에,
- UI를 업데이트하는 과정에서 생기는 복잡함 모두 해소
- 업데이트에 더욱 쉽게 접근 가능 및 간결함

## 특징
- Virtual DOM을 사용
- JSX
  + javascript 확장 문법
  + DOM 엘리먼트 생성시 Javsscript 형식으로 작성해야 하는 것을, XML과 비슷한 형태로 작성할 수 있게 해준다. 이를 사용하는 것은 권장
- components
  + React는 Component에 대한 것
  + React 개발시 모든 것을 Component로 생각할 것

## 장점
- Virtual DOM을 사용한 서비스 성능 향상
- 클라, 서버 둘 다 렌더링 될 수 있음
  + 이를 통해 브라우저측 초기 렌더링 딜레이 줄이고, SEO 호환도 가능
- Component의 가독성 매우 높고 쉬운 유지보수 가능
- 프레임워크 아닌 라이브러리다. 다른 프레임워크와 사용 가능
  + React에선 UI만 신경 쓰기
  + 빠진 부분은 내가 좋아하는 라이브러리 사용하여 내 입맛대로

## 제한
- View만 다루기 떄문에 그 외의 부분 다른 기술 사용
  + Ajax, Router 등의 기능 직접 구현 or 다른 모듈 설치

## 해보자-

```javascript
import React from 'react';
```
- 모듈을 require 하기
  + 보통 클라에서 (html 태그에서) script를 통해 여러 파일 불러옴
- **bundling** : webpack을 이용하여 import(혹은 require)한 모듈을 한 파일로 합침

```javascript
function HelloWorld() {
  return (
    <h1>Hello World</h1>
  )
}
```
- stateless Function을 통해 Hello World 컴포넌트 선언
- `return (<h1>hello world</h1>)`
  + `'`나 `"` 없이 그냥 적힘
  + 이것은 JSX 코드
  + 이 코드는 webpack의 번들링 과정 거치면서 babel-loader를 통해 javascript로 변환
### 변환 결과
```javascript
return React.createElement(
  "h1",
  null,
  "Hello World!"
)
```

## main.js
```javascript
import React from 'react';
import {render} from 'react-dom';
import HelloWorld from './Helloworld.js'

render(<HelloWorld/>, document.getElementById('app'));
```

- HelloWorld.js에서 만든 컴포넌트를 페이지에 렌더링
- 위 파일은 webpack의 entry파일이다.
  + import한 파일을 재귀적으로 불러와서 하나의 파일로 합치기
  + react 컴포넌트를 페이지에 렌더링 할 때 react-dom 모듈을 불러와서 render 함수를 통해 처리
- <컴포넌트이름/> : 컴포넌트 만들기




## Summary
- React는 재사용 가능한 UI 생성하도록 도와준다
- Virtual DOM 개념 사용하여 상태가 변함에 따라 **선택적 UI 렌더링** 함
  + 실제 DOM에 접근하여 조작하는 대신, 추상화 시키 js 객체를 구성하여 사용
  + 실제 DOM의 가벼운 사본과 비슷

- React에서 데이터 변경시 3가지 절차
  1. 전체 UI를 Virtual DOM에 리렌더링
  2. 기존 Virtual DOM의 내용을 현재와 비교
  3. 바뀐 부분만 DOM에 적용
  + DOM 업데이트 추상화
  + DOM 처리 횟수 최소화

- 특징
  1. Component, Component, Component
  2. JSX
  3. 클라, 서버 둘 다 렌더링 됨

- `import React from 'react'` from hellworld.js
  + bundling : webpack을 이용하여 import(or require)한 모듈 한 파일로 합침

```javascript
import React from 'react';
import {render} from 'react-dom';
import HelloWorld from './Helloworld.js'
```
- webpack의 entry 파일
  + import한 파일을 재귀적으로 불러와서 1개 파일로 합치기
