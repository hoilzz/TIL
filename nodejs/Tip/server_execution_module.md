# 서버 실행 모듈

```
$ npm install -g supervisor
$ npm install -g forever
```

파일 내용 변경시 현재 실행 중인 스크립트에 영향을 미치지 못한다.

그래서 서버를 종료 후 다시 실행해야 한다.

하지만 supervior 모듈 사용시 파일의 변경 사항을 자동으로 인식하고 실행을 종료 후 재실행한다.
