# express framework

node js 자체는 웹서버가 아니다. 흔한 웹서버인 아파치의 경우 html 파일 경로를 지정해주고 서버를 열고 php를 실행, 세션 관리해줘야 한다. node js는 그런 설정이 없다. 그 대신에 http 서버를 직접 작성해야 한다. node js는 js 런타임이다. Express..
http 서버를 직접 구현해야 하는데, 라우팅 세션 템플릿 등

## features

- 강력한 라우팅
- HTTP helpers(redirection, caching, etc)
- View system supporting 14+ template engines
- Content negotiation












# middleware

`middleware` 도 콜백함수다.

```javascript

var myLogger = function (req, res, next) {
  console.log(req.url);
  // next 콜백함수를 실행시, 다른 미들웨어 실행하거나 라우팅 작업 실행.
  next();
}

```
app.use(myLogger);


## 기존의 미들웨어 설치 사용

**NPM으로 미들웨어 설치**

```
npm install --save morgan body-parser
```

- morgan : 로깅 미들웨어
- body-parser : JSON 형태 데이터를 리퀘스트하여 파싱하는 미들웨어
