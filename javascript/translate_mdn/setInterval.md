# setInterval()

고정된 delay 시간만큼 `setInterval()`은 반복적으로 함수나 code를 수행한다.
이것은 interval를 인식할 수 있는 `interval ID`를 리턴한다.
그래서 `clearInterval()`를 호출하여 이것을 삭제할 수 있다.
이 메서드는 `Window`와 `Worker` 인터페이스에서 제공된다.

## Syntax

```javascript
var intervalID = scope.setInterval(func, delay[, param1, param2..]);
var intervalID = scope.setInterval(code, delay);
```

### Params

func
: every delay ms 마다 실행될 함수다. 함수는 파라미터를 통과시키지 않고 리턴 되는 값도 없다.

code
: 함수 대신에 컴파일되고 every delay마다 실행될 스트링을 포함할 수 있다.  근데 이건 비추다. eval()을 이용하여 보안 문제가 일어날 수 있어서..

delay
: 실제 delay는 더 길 수 있다는 거 알아둬

param1, param2... paramN
: timer가 만료되면 함수로 전달되는 파라미터들

### Return Value

리턴 되는 timeoutID는 numeric이다. 이것은 timer를 인식하고 `setInterval()` 호출하면 생성된다. 이 값은 timeout을 취소하기 위해 `clearInterval()`에 전달된다.

...


## Examples

### ex 1

```javascript
js
```
