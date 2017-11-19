# counter 만들면서 배우기

velopert 카운터 만들기를 보며 배운것 정리

## Presentational and Container Component

### presentational Component

presentational component는 Dumb component라고도 불린다.

- 오직 뷰만을 담당
- DOM 엘리먼트, 스타일 가진다.
- presentational component or container component 가질 수 있다
- state를 갖지 않는다.
  - 가지게 될 경우 데이터가 아닌 UI에 관련된 것
- 주로 함수형 컴포넌트로 작성
- **state를 갖고 있어야 하거나, 최적화를 위해 LifeCycle이 필요해질 때 Class형 컴포넌트로 작성됨**

### Container Component

- presentaional or container 컴포넌트들을 관리
- 내부에 DOM엘리먼트가 직접적으로 사용되는 경우는 없다.
  - 사용되는 경우 감싸는 용도로만 
- 스타일 가지지 않음
  - 스타일들은 모두 프리젠테이셔널 컴포넌트에서 정의되야 한다.
- 상태를 가질 때가 많다. 리덕스에 직접적으로 접근 가능하다.

주로 페이지, 리스트, 헤더, 사이드바, 내부의 컴포넌트 때문에 props가 여러 컴포넌트 거쳐야 하는 경우에 사용.

### 이 구조의 장점

UI와 Data가 분리되어 프로젝트 이해도 용이, 컴포넌트 재사용률도 높여준다.


