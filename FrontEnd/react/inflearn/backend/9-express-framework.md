# express framework

``` javascript
// 서버가 읽을 수 있도록 HTML의 위치를 정의해준다.
app.set('views', __dirname + '/views');

// 서버가 HTML 렌더링할 때, EJS 엔진을 사용하도록 설정한다  .
app.set('view engine', 'ejs');
app.engine('html', require('ejs').renderFile);
```

## static file 다루기

js, css, image 파일 등이 정적파일이다.

```javascript
app.use(express.static('public'));
```

- public 폴더 내의 파일들을 정적 파일로 다루겠다.
