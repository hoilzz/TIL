# babel

## with jest

`node_modules` 를 트랜스파일 하기 위해 babel.config.js 를 사용하려면 다음 문서를 보자.

babel은 자동으로 root 디렉토리 `babel.config.js` 찾음

- 혹은 명시적인 `configFile`값을 사용할 수 있음, default config file search 행동을 오버라이드 하기 위해

## file-relative 설정

바벨은 디렉토리 구조를 검색하여 `.babelrc`를 로드 함

file-relative 설정은 최상단 config value와 머지됨.

- 특정 오버라이드를 하게 될 경우 유용

근데 몇가지 단점 있음

- `package.json`이 포함된 디렉토리가 찾아지면 검색 멈춤
- 그래서 relative config는 오직 single package에서만 적용됨.

## Monorepos

모노레포에서, 핵심은 바벨은 working directory를 logical `root`로 취급하는 것

- 만약 바벨이 전체 repo에 적용되는 경우, 특정 sub-package내에서 실행된다면 이것은 문제를 일으킬 수 있음

위와 별도로 `.babelrc`를 사용할지, 중앙의 `babel.config.js`만 사용할지 결정해야함

- babelrc 파일은 babel6에서 하위폴더별 설정을 위해 필수가 아님 (babel7의 babel.config.js도 마찬가지)

### Root babel.config.js files

모노레포에서 첫번째로 할 일은 루트에 `babel.config.js` 만드는 거

- 얘는 저장소의 base directory의 core concept을 정의
- **만약 특정 package를 구성하기 위해 `.babelrc`를 사용한다면, repo-level option을 설정해줘야하는게 중요**

- repo 구성을 root `babel.config.js`로 지정할 수 있음
- `override`로, 저장소의 subfoler에 적용할 수 있음
  - 이것은 레포에 수많은 `.babelrc` 만드는것보다 더 쉬움

첫번째 이슈

- 바벨은 `babel.config.js`를 `root`로 설정된 dir에서 로드하려고 함
  - 이것은 만약 너가 babel.config.js 파일을 만들었다면
