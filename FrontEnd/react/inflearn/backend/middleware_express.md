# Express 앱의 미들웨어

미들웨어 함수는 req, res, 요청-응답 주기 중 그 다음의 미들웨어 함수 대한 액세스 권한을 갖는 함수이다. 그 다음의 미들웨어 함수는 일반적으로 next라는 이름의 변수로 표시된다. 미들웨어 함수는 다음과 같은 태스크를 수행한다.

- 모든 코드를 실행
- 요청 및 응답 오브젝트에 대한 변경을 실행
- 요청-응답 주기를 종료
- 스택 내의 그 다음 미들웨어 호출

현재의 미들웨어 함수가 요청-응답 주기를 종료하지 않은 경우에는 next()를 호출하여 그 다음 미들웨어 함수에 제어를 전달해야 한다. 그렇지 않으면 해당 요청은 정지된 채로 방치된다.

```javascript
var express = require('express');
var app = express();

app.get('/', function(req, res, next){
	// 미들웨어 함수에 대한 콜백 인수(일반적으로 next라 불림)
	next();
})
```

미들웨어 함수를 로드하려면 미들웨어 함수를 지정하여 `app.use()`를 호출하십시오.

```javascript

var myLogger = function(req, res, next) {
	console.log('LOGGED');
	next();
};

app.use(myLogger);

app.get('/', function(req, res){
	res.send('Hello World!')
});

```

## Response

### res.end([data][,encoding])

response process를 끝낸다. 이 메서드는 실제로 Node core에서 온다. (response.end() method of http.ServerResponse)[https://nodejs.org/api/http.html#http_response_end_data_encoding_callback]

data 없이 response를 빨리 종료하기 위해 사용한다. 만약 data에 대한 응답을 필요로 하면, 대신에 `res.send()`와 `res.json()`을 사용해라.

```javascript
res.end();
res.status(400).end();
```

### res.json([body])

JSON response를 전송한다. 이 메서드는 response(with the correct content-type)를 `JSON.stringify()`를 이용하여 JSON string으로 컨버팅 한 후 전송한다.

parameter는 object, array, string, boolean, or number 다 된다.

```javascript
res.json(null)
res.json({error:"message"})
```

### res.send([body])

body parameter는 Buffer Object, String, object or an Array다.

```javascript
res.send(new Buffer('whoop'));
res.send({ some: 'json' });
res.send('<p>some html</p>');
res.status(404).send('Sorry, we cannot find that!');
res.status(500).send({ error: 'something blew up' });
```

이 메서드는 simple non-streaming response를 위해 많은 태스크를 수행한다. 예를 들어 자동으로 `Content-Length`를 HTTP response header field에 할당한다. 그리고 automatic HEAD and HTTP cache freshness support를 제공한다.

parameter가 buffer object일 때, 메서드는 Content-Type response header field에 "application/octet-stream"을 할당한다.

```javascript
res.set('Content-Type', `text/html`);
res.send(new Buffer('<p>Some html</p>'))
```

파라미터가 String일 때, 메서드는 Content-Type을 text/html로 세팅한다.

```javascript
res.send('<p>Some html</p>')
```

파라미터가 Array or Object일 때, Express는 JSON representation으로 응답한다.

```javascript
res.send({ user: 'tobi' });
res.send([1,2,3]);
```
