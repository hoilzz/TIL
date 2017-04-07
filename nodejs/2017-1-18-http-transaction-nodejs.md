# HTTP 트랜잭션 해부

Node.js HTTP 처리 과정을 잘 이해하기 위한 node js의 [공식 문서](https://nodejs.org/ko/docs/guides/anatomy-of-an-http-transaction/)를 보고 요약한 글입니다.

이 문서를 읽기 위해, HTTP 요청 동작 방식을 알아야 합니다. 또한, Node.js의 `EventEmitters`와 `Streams`에도 익숙해야 한다. 익숙하지 않다면 미리 읽어보자.

## 서버 생성

웹 서버 객체를 먼저 만들자. `createServer`를 이용하자

```javascript
var http = require('http');

var server = http.createServer(function(req, res){
	// 여기서 작업이 진행된다.
})
```

이 서버로 
