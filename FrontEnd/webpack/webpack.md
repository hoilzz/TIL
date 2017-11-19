# webpack

서로 연관 관계가 있는 웹 자원들을 js, css, img와 같은 스태틱한 자원으로 변환해주는 모듈 번들러

웹자원(js, js, css, scss, img1, img2)들을 스태틱한 자원으로 변환,

1. 의존성 그래프를 갖게 된다. 모듈 관리를 수월하게 할 수 있다. 
2. 이런 자원들을 최적화(미니피케이션) 와 같은 기타 압축 기법을 활용하여 웹 페이지 성능을 끌어올릴 수 있다.

## 왜 사용할까?

1. 새로운 형태의 Web Task Manager
    - 기존의 Gulp Grunt와 같은 Web Task Manager + 모듈 의존성 관리
    - 예를 들어 minification을 webpack default cli로 실행 가능

```
webpack -p
```

2. 자바스크립트 Code based Modules 관리
    - 자바스크립트 모듈화의 필요성 : AMD, common js, ES6(modules)
    - 기존 모듈 로더들과의 차이점 : 모듈 간의 관계를 chunk 단위로 나눠 필요할 때 코딩
    - 가독성 및 다수 모듈 미병행 처리 등의 약점을 보완하기 위한 Webpack 등장


> 자바스크립트 모듈화 문제?
```javascript
<script src="module1.js"></script>
<script src="module2.js"></script>
<script src="library1.js"></script>
<script src="module3.js"></script>
```

- 상기 모듈 로딩 방식의 문제점 : **전역변수 충돌**(네임스페이스 패턴과 같은 모듈화를 이용하지 않을 경우), **스크립트 로딩 순서**, **복잡도에 따른 관리상의 문제** 


## webpack 철학

1. Everything is Module

모든 웹 자원(js, css, html)이 모듈 형태로 로딩 가능하다. 사실, css나 html은 모듈로 보기 힘들다. 왜냐하면 javascript에서 css, html이 로드가 되지 않는다. 하지만 아래와 코드와 같이 모듈처럼 로드가 가능하도록 한다.

```javascript
require('base.css');
require('main.js');
```

2. Load only `What` you need and `when` you need

초기에 불필요한 것들을 모두 로딩하지 않는다. 필요할 때 필요한 것만 로딩하여 사용한다. (like `lazy load`)

