# callback Func

> 특정 함수에 매개변수로서 전달된 함수, 그리고 그 Callback Func는 그 함수를 전달받은 함수 안에서 호출되게 된다.

다음 jQuery에서 사용된 callback func를 보자.

```javascript

// 보시면, click 메소드의 인수가 변수가 아니라 함수이죠?
// click 메소드의 인수가 바로 Callback 함수입니다.
$("#btn_1").click(function() {
  alert("Btn 1 Clicked");
});

```

## Blocking Code
: 어떤 작업을 실행하고 기다리면서 코드가 `막히`게 된다.

## Non-Blocking Code
: 콜백 함수를 통해 프로그램이 함수가 끝날 때까지 기다리지 않고 바로 코드를 실행한다.


# Summary

Callback 함수를 사용하여 프로그램의 흐름을 끊지 않음으로써, **`Non-Blocking` 코드를 사용하는 서버** 는 Blocking 코드를 사용하는 서버보다 **더 많은 양의 요청을 빠르게 처리할 수 있다.**
