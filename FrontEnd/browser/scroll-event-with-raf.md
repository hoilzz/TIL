# Scroll Event with throttling using raf

[scroll_optimization_with_raf](https://developer.mozilla.org/en-US/docs/Web/API/Document/scroll_event#Scroll_optimization_with_window.requestAnimationFrame)

scroll event는 빠른 속도로 실행될 수 있기 때문에, 이벤트 핸들러는 DOM 수정과 같은 값비싼 연산을 실행하지 않아야 한다. 대신에 `raf()`, `setTimeout()` 등을 이용하여 이벤트를 쓰로틀링 해야한다.

그러나 input events와 animation frame은 동일한 속도로 실행되고 최적화는 불필요하다. 이 예제는 scroll event를 raf로 최적화한 예제다.
