# 8 express module

## 8.2 기본 응답 메서드

- `response.send([body])` : 매개변수의 자료형에 따라 적절한 형태로 응답합니다.
- `response.json([body])`
- `response.jsonp`
- `response.redirect([status,]path)` : 웹페이지 경로 강제 이동

`response.status(status code)`

- XMLHttpRequest 객체로 Ajax 요청시 이러한 응답 코드를 확인하면 적절한 처리 수행 가능

## 8.3 기본 요청 메서드

- `params` : 라우팅 매개변수 추출
- `query` : 요청 매개변수를 추출
- `headers` : 요청 헤더를 추출
- `header()` : 헤더 속성 지정 및 추출
- `accepts(type)` : Accept 곳성 확인
- `is(type)` : 헤더의 Content-Type 속성 확인

요청 헤더 다 추출가능

User-Agent 속성 추출해서, 브라우저에 따라 다른 화면 보여주자.


## 8.4 미들웨어 개요

http 모듈과 express 모듈로 만든 서버의 차이점은

express 모듈은 req 이벤트 리스너 연결시 `use()` 메서드를 사용한다.

왜 `http`와 다른걸까

우선,
	- use() 메서드는 여러 번 사용 가능
	- 그리고 `use()` 메서드의 매개변수에는 `function(req, res, next) {}` 형태의 함수 입력한다.
		- `next`는 다음에 위치하는 함수

그래서, `use()` 메서드의 매개변수에 입력하는 함수를 `미들웨어` 라고 부른다.

요청의 응답을 완료하기 전까지 요청 중간중간 여러 일을 처리할 수 있다.

## 8.5 router 미들웨어

라우팅을 지원한다. 페이지 라우팅 기능은 express 모듈에 내장되어 있는 미들웨어의 기능이라 보통 자동으로 사용할 수 있게 설정되어있어서 미들웨어 사용하는 느낌 안받는다.

http 모듈 사용시 if문으로 페이지 라우팅 구현했지만, express 모듈의 router 미들웨어는 다음 메서드를 이용하여 쉽게 라우팅 구현 가능.

	1. get(path, callback)
	2. put(path, callback)
	3. delete(path, callback)
	4. post(path, callback)

> router 모듈화
express 모듈은 페이지 라우팅을 모듈로 분리하는 기능을 제공한다.


## 8.6 static 미들웨어

express 모듈 자체에 내장되어 있는 미들웨어다.

그래서 웹 서버에서 손쉽게 파일 제공 가능하다.

이미지 제공해준다고 해보자.

```javascript
app.use(express.static(__dirname + '/public'));

app.use(function(req, res){
	response.end('<img src="/chriskdm.jpg">');
})
```

- static 미들웨어 사용시 지정한 폴더에 있는 내용 모두 웹 서버 루트 폴더에 올린다.
- 따라서,

## 8.9 body parser middleware

POST 요청 데이터를 추출하는 미들웨어다.

이 미들웨어 사용시, req 객체에 body 속성이 부여된다.

body parser 미들웨어는 `application/x-www-form-urlencoded`라는 인코딩 방식만 지원한다.

이외의 인코딩 방식(파일 전송을 위한 `multipart/form-data` 인코딩은 다음 절에서 살펴보는

multipart 미들웨어를 사용해야 한다.

cookie parser 미들웨어와 body parser 미들웨어를 사용하여 로그인을 구현해보자.



## summary

**기본 응답 메서드**
`response.*`
- `.send` : 매개변수 자료형에 따라 적절한 형태로 응답
- `.json([body])`
- `.jsonp`
- `.redirect([status,]path)`: 웹페이지 경로 강제 이동
- Ajax 요청시 응답 코드 확인하여 적절한 처리 수행 가능


---


**기본요청메서드(req)**
- `params`
- `query`
- `headers`
- `header()` : 속성 지정
- `accepts(type)` : accept 속성 확인

걍 요청 헤더 다 추출가능


---


**미들웨어**
- express모듈은 req 이벤트 리스너 연결시 `use()` 메서드 사용

```javascript
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
```

- body-parser는 POST request 데이터를 추출하는 미들웨어다.
- req 객체에 body 속성이 생겨서 데이터 추출하기 왕편함

---

**router middleware**

http 모듈 사용시 if문으로 페이지 라우팅 구현 했지만, express의 router 미들웨어는 다음 메서드를 이용하여 쉽게 라우팅 가능

`router.get(path, callback)`

- get대신, put,delete,post도 가능


---


**static middleware**

static middleware 사용시 지정 폴더(보통 public)에 있는 내용 모두 웹서버 루트 폴더에 올린다.

보통 다음과 같이 사용한다.

```javascript
app.use(express.static(__dirname + '/public'));
```

---

**body parser middleware**

POST 요청 데이터 추출하는 미들웨어

req 객체에 body 속서 ㅇ부여

- `application/x-www-form-urlencoded` 인코딩만 지원
- 즉, 파일전송을 위한 `multipart-form-data` 지원 안함


## issue
- *jsonp란*
- `application-x-www-form-urlencoded`와 같은 인코딩
