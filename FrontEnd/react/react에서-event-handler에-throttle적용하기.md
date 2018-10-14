# try promise debouncing

불필요한 요청을 피하기 위해 api call에 debounce를 적용한다.

__컴포넌트 인스턴스 당 single debounced (or throttled) function을 생성해야 하는 것__ 은 중요한 파트다. 매번 debounce함수를 재생성하기를 원치 않을 거고, 동일한 디바운스 함수를 공유하기 위해 여러개 인스턴스를 생성하기도 원치 않을 거다.

lodash의 debounce를 이용한 예제를 보자.

### NOT a good idea

```javascript
var SearchBox = React.createClass({
  method: function() {...},
  debouncedMethod: debounce(this.method,100);
});
```

동작안할거다. object 