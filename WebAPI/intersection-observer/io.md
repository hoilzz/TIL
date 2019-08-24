# intersection observer

[observeation is better](https://developers.google.com/web/updates/2019/02/intersectionobserver-v2)

[io into view](https://developers.google.com/web/updates/2016/04/intersectionobserver)

[lazy-load-guide](https://developers.google.com/web/fundamentals/performance/lazy-loading-guidance/images-and-video/)

[io-with-react](https://www.robinwieruch.de/react-intersection-observer-api/)

위 4개 글을 읽고 맘대로 정리

엘리먼트가 viewport에서 보이는 시점을 추적한다고하자. image lazy load시 필요한 정보다. 보통은 해당 엘리먼트를 스크롤 이벤트 핸들러에서 getBoundingClientRect()를 통해 위치를 파악한다. 이것은 [브라우저가 전체 페이지를 re-layout](https://gist.github.com/paulirish/5d52fb081b3570c81e3a) 하므로 굉장히 느리다.

## IO를 생성하는 방법

io 콜백은 entries와 observer를 파라미터로 전달한다. entries는 IntersectionObserverEntry의 배열인데, boundingClientRect의 결과물을 가진다.

IntersectionObserver는 데이터를 비동기로 전달하고, 콜백은 메인스레드에서 실행할 것이다. spec에서 구현체는 [requestIdleCallback()](https://developer.mozilla.org/ko/docs/Web/API/Window/requestIdleCallback)을 이용한다. 제공된 콜백은 우선순위가 낮고 idle time동안 브라우저가 호출한다.

## 모든 엘리먼트를 intersect 하는 것은 bad..
