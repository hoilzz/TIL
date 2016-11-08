# Redux : 프로젝트 준비하기

### Staring Server
`npm start`

###
eslint를 통해 오류 난 곳 출력

###
atom 에디터를 사용한다면 jshint 비활성화-eslint 사용하면 쓸만하다

###

프로젝트를 열어보면 webpack에 관한 설정은 없다
바꾸고 싶으면 nodemodule 들어가서 react-script/config 들어가면 다 있긴한데
페북에서 권장하지 않는다

그래서  eject 기능(packge.json)을 넣어놨는데
config 설정파일들을 프로젝트로 옮긴다. 그러면 설정 파일들이라 스크립트 관련 파일들이 우리 프로젝트에 다 생성되고 그 때부터 우리가 설정을 변경할 수 있다.



Redux 를 사용하기전에 프로젝트를 준비하겠습니다.
이번엔 create-react-app 이라는 페이스북에서 만든 React 프로젝트 생성 도구를 사용합니다. 복잡한 설정 없이 프로젝트를 만들어준답니다.

단점이라면, react-hot 로딩 기능은 추가되어있지 않은데. 그게 만약에 필요하다면 하단에 주어진 링크중 제가 블로그에 작성한 create-react-app 사용기 포스트를 읽어보세요.

## redux에서 필요한 모듈 설치하기
npm install --save redux react-redux
