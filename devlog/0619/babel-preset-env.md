# babel-preset-env

@babel/preset-env는 타겟 환경에 필요한 구문(및 선택적으로 브라우저 폴리필)을 세세하게 관리할 필요 없이 최신 JavaScript를 사용할 수 있는 똑똑한 preset이다.

## 어케 작동하니?

browserlist와 같은 오픈소스가 없었으면 얘는 동작 못한다.

위 데이터를 활용하여 JS 구문 또는 브라우저 기능을 지원한다. 이러한 구문 및 기능을 바벨 transform plugin과 core-js polyfill과 매핑한다.

> 중요한 점은 babel/preset-env 는 `stage-x` 플러그인을 지원하지 않는다.

@babel/preset-env는 명시된 타겟 환경을 모두 가져와서 매핑 목록과 비교하여 플러그인 목록을 컴파일하고 이를 babel에 전달한다.
