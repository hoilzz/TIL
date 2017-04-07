# body-parser

Parse incoming request bodies in a middleware before your handlers, available under the `req.body`property

- 요청 스트림의 body를 추출하고 `req.body`로 이용가능하다.
- 이거 원래 직접할 수 있는데, `body-parser` 이용하면 여러모로 편해

## API

```javascript
var bodyParser = require('body-parser')
```

`bodyparser` 객체는 middleware를 생성하기 위해 다양한 factories를 드러낸다.

### bodyParse.json(options)

`json` 만 파싱하는 미들웨어를 리턴한다. 이 파서는 body의 어떤 unicode든 상관없고 `gzip`의 자동 인플레이션과 deflate encoding을 지원한다.

파싱된 데이터를 포함하는 `body` 객체는 `request` 객체에 포함되어있다.


## bodyParser.urlencoded(options)

`urlencoded` body만 파싱하는 미들웨어를 리턴한다. 이 파서는 UTF-8 만 허용한다. 그리고 `gzip`과 `deflate` 인코딩을 지원한다.

이 객체는 key-value 쌍을 포함한다. value는 string or array (when `extended` is `false`), any type(when `extended` is `true`)다.


## summary

body-parser는 incoming request data를 unzip하기 위해 `nodejs/zlib`을 사용하는 미들웨어다. 만약 zipped


## examples

이 예제는 all incoming 요청들의 body를 파싱하는 일반적인 JSON과 URL-encoded parser를 top-level middleware로 설명한다.

```javascript
var bodyParser = require('body-parser');

var app = express();

// parse application/x-www-form-urlencoded
app.use(bodyParser.urlencoded({ extended: false }))

// parse application/json
app.use(bodyParser.json())

app.use(function (req, res) {
  res.setHeader('Content-Type', 'text/plain')
  res.write('you posted:\n')
  res.end(JSON.stringify(req.body, null, 2))
})

```

express와 함께 body-parser를 이용하는 가장 좋은 방식

```javascript
var express = require('express')
var bodyParser = require('body-parser')

var app = express()

// create application/json parser
var jsonParser = bodyParser.json()

// create application/x-www-form-urlencoded parser
var urlencodedParser = bodyParser.urlencoded({ extended: false })

// POST /login gets urlencoded bodies
app.post('/login', urlencodedParser, function (req, res) {
  if (!req.body) return res.sendStatus(400)
  res.send('welcome, ' + req.body.username)
})

// POST /api/users gets JSON bodies
app.post('/api/users', jsonParser, function (req, res) {
  if (!req.body) return res.sendStatus(400)
  // create user in req.body
})
```
