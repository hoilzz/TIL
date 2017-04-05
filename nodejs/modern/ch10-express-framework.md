# 10 express framework

project 구조를 살펴보자

|foler or file name|desc|
|:-----------:|:------------------------------|
|bin/| program 실행과 관련된 파일, `www` file을 실행하여 framework 실행|
|public/| express 모듈의 static middleware를 사용해 서버에 올라가는 folder(js, css, img 등 리소스 파일)|
|routes/| page 라우트와 관련된 모듈, routes 폴더에는 index.js와 routes file이 있다.

---

## 10.3.1 서버 생성

`app.js` 에는 다음과 같은 내용이 있다.

1. 모듈추출
2. 서버 객체 생성 (`var app = express()`)
3. 서버 및 미들웨어 설정

```javascript
// 서버.set
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// 미들웨어 사용
// 서버.use(모듈들);
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// 라우터 미들웨어 설정
app.use('/', index);
app.use('/users', users);
app.use('/products', products);
```

---

## 10.3.4 모듈화

|module 만들기|모듈 사용하기|
|:----:|:----:|
|exports.key = 객체 / 함수| require('./모듈이름').key 형태로 객체 or 함수 사용 가능|
|module.exports = 객체/함수| require('./모듈이름')|

2번째 방식으로 모듈 생성 및 추출하면, 해당 객체나 함수 바로 사용가능

## 10.4.1 page render

express는 fs 모듈을 이용하여 page 제공하는 render 메서드 제공

## 10.5 layout page

`ejs`에서는 layout 기능이 없다. `include`를 활용하여 대체할 수 있다.
