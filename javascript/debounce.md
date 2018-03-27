# debounce & throttle

## debounce

만약 웹앱이 js로 taxing tasks를 수행하는 경우, 특정 작업이 브라우저 성능을 저하시키지 않도록, 자주 작동하지 않도록 하기 위해 debounce function은 필수다.

debounce function은 어떤 함수가 fire되는 속도를 제한한다. a quick example: 몇몇 엘리먼트 치수 계산을 수행하는 윈도우의 resize listener가 있다고 하자. (그리고 몇몇 엘리먼트를 재배치 할 수도 있다). 이것은 힘든 task가 아니다. 하지만 반복적으로 실행되면 엄청 많은 resize가 site 속도를 느리게할 것이다. 함수가 fire되는 속도를 제한해야하지 않을까?

```javascript
// 함수가 계속 호출된다면 트리거 되지 않는 함수를 반환한다. ?? 코드상에서 어떤 부분이 계속 호출되면 트리거 되지 않도록 했을까?
// Nms 동안 호출되는 것을 멈춘 후에 그 함수는 호출된다.
// 만약 immiediate가 전달되면, trailing(가장 뒤에꺼)되는 것 대신에 leading(가장 앞에꺼)되는 함수를 트리거한다.

function debounce(func, wait, immediate) {
    var timeout;
    return function() {
        var context = this, args = arguments;
        var later = function() {
            timeout = null;
            if (!immediate) func.apply(context, args);
        }
        var callNow = immediate && !timeout;
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
        if (callNow) func.apply(context, args);
    }
}
```

실행할 함수와 fire 속도 제한(ms)을 debounce에 전달해보자.

```javascript
var myEfficientFn = debounce(function() {
    // all the taxing stuff you do
}, 250);

window.addEventListener('resize', myEfficientFn);
```

위 함수는 계속 트리거 되는 대신에 1/4초 동안 오직 한번 일어난다. 즉, **마지막 호출 이후 일정 밀리세컨드 이후로 지연된 호출을 하도록** 한다.

## throttle

매 밀리세컨드마다 최대 한 번만 호출될 수 있도록 Throttle된 함수를 만든다. 즉, **로직 실행 주기를 만드는 함수**라고 이해하자. 설정한 시간 동안 최대 한 번만 호출된다.


## Summary

- debounce : 마지막 호출 이후 일정 밀리세컨드 이후로 지연된 호출을 하도록 한다.
- throttle : 매 밀리세컨드마다 최대 한번만 호출될 수 있도록, 즉 로직 실행 주기를 만드는 함수.

자동완성 쿼리를 입력시마다 날리지 않고
**0.1초 정도 단위로 모아서** 쿼리를 전송.

근데 throttle쓰면 뷰가 끊겨 보일 수도 있겠다..?
0.1초 단위씩 throttle 한다고 하자. '라면' 검색시 '라며' 에서 0.1초 단위로 전송 후, 라면을 0.1초 후에 다시 보내면 뷰가 갑자기 바뀌게 될텐데.. 이건 원래 자연스러운건가..??

debounce 쓰면?
이게 제일 자연스러울거 같긴하다 '라면'을 0.1초 이내로 빠르게 입력한다면 결국엔 '라면'만 요청 보내니까

근데 스펙대로 **0.1초 정도 단위로 모아서** 라고 하면 throttle 쓰는게 맞는거 같긴하다