# React

1 Declarative
2 Component-Based
3 Learn Once, Write Anywhere

## npm으로 React 사용하기

browserify, webpack 같은 CommonJS 모듈 시스템과 함께 React를 사용하자
`react`, `react-dom` npm 패키지를 사용하자











## NOTE
1 CommonJS
범용적인 목적으로 JS를 사용하기 위해 필요한 조건은 모듈화이다. Node.js도 이런 모듈화 작업때문에 탄생할 수 있었다. 이러한 모듈화의 선두주자는 `CommonJS`와 `AMD`이다.
- 브라우저, 서버사이드 애플리케이션, 데스크톱 애플리케이션에서도 사용하려고 조직한 자발적 워킹 그룹
- 'Common'은 JS가 브라우저 뿐만 아니라 일반 범용 언어로 사용할 수 있다는 의지

2 browserify
브라우저에서 모든 dependencies를 빌드하여 너가 require('modules')를 하도록 한다.
- 브라우저는 정의된 `require`  메서드를 가지지 않는다. 하지만 Node.js는 가진다.
- Browserify로 Node에서 사용한 방식 그대로 `require`를 사용할 수 있는 코드 작성할 수 있다.
- `require('경로')`는 .js 파일 기준으로 상대 경로에 위치한 js 가져올 수 있음
- main js의 dependencies의 모든것과 함께 main.js라 불리는 simple file을 bundle up하기 위한 명령어를 보자.

  main.js along with all of its dependencies
  > var unique = require('uniq');
  > var data = [1,2,3,4,5,5,5,5];
  > console.log (unique(data));

  Install the uniq module with npm:
  > npm install uniq

  recursively bundle up all the required modules starting at main.js into a single file called bundle.js with the browserify command:
  > browserify main.js -o bundle.js

  **요약하자면 main.js에서 시작하는 필요한 모듈을 bundle.js라 불리는 1개 파일로 recursively bundle up 해보자.**

  Browserify는 require() 호출이 너의 프로젝트 전체 dependency를 traverse하도록 AST(추상 syntax tree)를 파싱한다.

  ><script src="bundle.js"> </script>

  it's done!
