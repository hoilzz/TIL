# 라우팅

애플리케이션 엔드 포인트(URI)의 정의, URI가 클라 요청에 응답하는 방식을 말한다.

기본적인 라우트의 예

```javascript
var express = require('express');
var app = express();

// respond with "hello world" when a GET request is made to the homepage
app.get('/', function(req, res) {
  res.send('hello world');
});
```

## 라우트 메소드

라우트 메소드는 HTTP 메소드 중 하나로 파생되며, express 클래스의 인스턴스에 연결된다.

## 라우트 경로

요청 메소드와의 조합을 통해, 요청이 이뤄질 수 있는 엔드포인트를 정의합니다. 라우트 경로는 **문자열**, **문자열 패턴** 또는 **정규식** 일 수 있다.

## 응답 메소드

**응답 오브젝트(`res`)는 응답을 클라로 전송하고 요청-응답 주기를 종료할 수 있습니다.**

**라우트 핸들러로부터 다음 메소드 중 어느 하나도 호출되지 않는 경우, 클라 요청은 정지된 채로 방치된다.**

| method    |    desc      |
| res.download() | 파일이 다운로드 되도록 프롬프트한다 |
| res.end()      | 응답 프로세스를 종료한다. |
| res.json()     | JSON 응답을 전송한다. |
| res.redirect() | 요청의 경로를 재지정 |
