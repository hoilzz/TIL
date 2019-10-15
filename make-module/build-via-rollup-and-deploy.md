# webpack and rollup

## webpack

SPA 빌드시 생기는 큰 문제점을 해결함. 이 중 2가지 특징을 주목하자.

1. Code Splitting
   - 필요할 때만 로드될 수 있는 청크로 앱을 쪼개는게 가능.
     - 이는 유저가 전체 앱을 다운받고 파싱할동안 기다리지 않고 더 빨리 사이트와 인터랙션 가능하게함
2. Static Assets
   - image와 CSS는 앱에 import 될 수 있고 의존성 그래프에서 다른 노드로 다뤄질 수 있음
     - 더이상 file들을 올바른 폴더에 위치시키는 것에 신경쓸 필요 없고
     - file의 URL에 hash를 추가하기위해 hacked-together scripts를 추가할 필요 없음. 웹팩이 다 알아서 해줌

Rollup은 위와 다른 이유 때문에 생김

- 효율적으로 배포 가능한 javascript 라이브러리들을 flat하게 빌드하기 위해

webpack을 포함한 다른 모듈 번들러들은 함수 내에서 각 모듈을 래핑하여 동작한다. (`require` 로 bundle을 불러오면서 1개씩 평가한다). 만약 on-demand loading과 같이 필요하다면 이 방법은 훌륭하다. 하지만 그렇지 않으면 이것은 낭비다. 많은 모듈을 가지고 있다면 상황은 악화된다.

Rollup이 사용하는 방식인 ES2015 모듈은 다른 접근이 가능

- 모든 코드는 동일한 위치에 놓이고 한번에 평가됨
- 그래서 더 빨리 시작할 수 있는 간단한 코드가 생성됨

하지만 trade-off가 있다.

- `code-splitting`은 hairer problem이다.
  - 그 당시엔 롤업은 이를 지원하지 않음
- 비슷하게, Rollup은 HMR을 지원하지 않음

## 그래서 뭘 사용해야할까

- Use webpack for apps, and Rollup for libraries

코드스플리팅 필요, static assets이 많거나 CommonJS 의존성을 많이 가진 것을 빌드하면 웹팩이 쵝오

코드 베이스가 ES2015 module이고 다른 사람들이 사용하는 뭔가 만드면 Rollup 고고
