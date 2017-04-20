# passport-http-bearer

이 모듈은 bearer token을 이용하여 HTTP 요청을 인증한다.

## 사용

The HTTP Bearer authentication strategy authenticates users using a bearer token. The strategy requires a verify callback, which accepts that credential and calls done providing a user. Optional info can be passed, typically including associated scope, which will be set by Passport at req.authInfo to be used by later middleware for authorization and access control.

### 환경 설정하기

HTTP bearer 인증 전략은 유저를 bearer token을 이용하여 인증한다.

이 전략을 유저에게 제공한 `done`을 호출하도록 허용하는 콜백을 호출해야한다.

`info` 인자를 보낼 수도 있다.

```javascript
passport.use(new BearerStrategy(
  function(token, done) {
    User.findOne({ token: token }, function (err, user) {
      if (err) { return done(err); }
      if (!user) { return done(null, false); }
      return done(null, user, { scope: 'all' });
    });
  }
));
```

## 요청 인증하기

`bearer` strateget를 명시하면서, 요청을 인증하기 위해  `passport.authenticate()`를 사용해라.

bearer 토큰을 포함하는 요청은 세션 지원을 필요로 하지 않는다.

그래서 session option은 false다.

예를 들어, 익스프레스 어플리케이션에서 라우트 미들웨어를 보자

```javascript
app.get('/profile',
  passport.authenticate('bearer', { session: false }),
  function(req, res) {
    res.json(req.user);
  });
```
