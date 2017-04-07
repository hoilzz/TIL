# RESTful API

REST 서버는 클라로 하여금 HTTP 프로토콜을 사용해 서버의 정보에 접근 및 변경을 가능케 한다. 여기서 정보는 text, xml, json 등 형식으로 제공된다.

## HTTP 메서드

HTTP/1.1 에서 제공되는 메소드는 여러개가 있다.
REST 기반 아키텍처에서 자주 사용되는 4가지 메소드는 다음과 같다.

1. GET - 조회
2. PUT - 생성 및 업데이트
3. DELETE - 제거
4. POST - 생성

## 디비 생성

JSON 기반 사용자 디비를 만들어보자.

<hr>

# 내가 궁금한 것들 알아보기

## res
> `res` object는 HTTP request를 받을 때 Express app이 보내는 HTTP response를 나타낸다.

### res.end([data] [, encoding])
> ends the response process.

- 사실 Node core의 메소드다. `http.ServerResponse`의 메소드다.
- 데이터 없이 response를 빨리 끝낼 때 사용한다.
	- 만약 data로 respond하고 싶다면, `res.send()`나 `res.json()`을 사용해라.

## res.send([body])
> Sends the HTTP response.

`body parameter`는 Buffer Object, a String, an object, or an Array가 될 수 있다.

```javascript
res.send(new Buffer('whoop'));
res.send({ some: 'json'});
res.status(404).send('sorry we cannot find that');
```


- non-streaming response에 유용한 도구다.
*non-streaming response* 란
	- 자동으로 `Content-Length`를 HTTP response header field에 할당한다.
	- automatic HEAD and HTTP cache freshness support를 제공한다. (*이 줄 자체* 가 뭔소리일까..)

- parameter는 Buffer Object일 때, 메서드는 response header field인 `Content-Type`에 `"application/octet-stream"`을 설정한다. 만약 아래와 같이 정의하지 않았다면:

*application/octet-stream* 이란..

```javascript
res.set('Content-Type', 'text/html');
res.send(new Buffer('<p>some html</p>'));
```

- 파라미터가 `String`일 때 `Content-Type`이 `"text/html"`로 설정된다.

- 파라미터가 `Array` or `Object`일 때, Express는 JSON으로 응답한다.
