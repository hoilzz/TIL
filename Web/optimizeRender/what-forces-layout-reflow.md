# layout과 reflow를 발생시키는거

아래 속성이나 메서드들이 JS에서 요청되거나 실행될 때, 브라우저에게 동기적으로 style과 layout* 을 계산하도록 트리거한다.
이거슨 reflow나 [layout thrashing](https://kellegous.com/j/2013/01/26/layout-performance/)이라고 불리고 일반적인 퍼포먼스 병목 현상이다.

[https://gist.github.com/paulirish/5d52fb081b3570c81e3a](https://gist.github.com/paulirish/5d52fb081b3570c81e3a)

