# mocha + chai

## mocha - getting started

모카는 러너를 포함한 테스트 프레임워크다. 모카는 assertion을 지원하지 않는다. 그걸 지원하는 chai 라이브러리와 함께 사용한다.

mocha는 BDD 기반 라이브러리다.

## syntax

- describe
  - 이름 지정
  - 중첩 사용시 section 구분 용도

### hook

테스트 코드가 실행되기 전과 후에 실행되는 함수다.

- before
- beforeEach
- afterEach
- after


## chai - getting started

차이는 Assertion Library다. 3가지 스타일의 Assertion을 제공한다.

- assert
  - node에서 제공하는 Assert와 유사
- expect
  - BDD 스타일로 제공되는 인터페이스 중 하나로 `chaining`을 제공
- should
  - BDD 스타일로 제공되는 인터페이스 중 하나로 `chaining`을 제공

## enzyme

리액트 테스트 유틸리티.
- 얕은 렌더링, 정적 렌더링된 마크업 또는 DOM 렌더링을 사용하는 편리한 유틸리티
- 엘리먼트를 찾고, props 등을 읽는 것이 jQuery API와 유사


## JSDOM

realistic testing 환경을 생성하기 위해 사용되는 headless 브라우저 기반 자바스크립트다.

enzyme의 mount API는 (mount를 이용하기 위해 필요한) DOM, JSDOM을 필요로 한다.

