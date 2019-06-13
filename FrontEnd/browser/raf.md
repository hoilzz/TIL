# raf

[animation with raf](https://www.html5rocks.com/en/tutorials/speed/animations/)

raf는 렌더링과 애니메이션을 처리하도록 설계되었다. 브라우저는 거의 적절한 시간에 그것을 스케줄링할 수 있고, 초당 60프레임을 부드럽고 매끄러운 화면을 보여줄 수 있다.

이 아티클에서는 animation code에서 최대 이득을 얻을 수 있도록 도와줄 것이다. `raf`를 이용하면 애니메이션에서 bottleneck을 끝낼 수 있다.

브라우저에게 수행할 animation을 알리고 다음 리페인트 실행 전에 애니메이션을 업데이트하는 함수를 호출한다.

- raf의 콜백은 다음 리페인트 전에 실행된다.
- 다음 리페인트에서 그 다음 프레임을 animate하려면 콜백 루틴이 스스로 `raf()`를 호출해야 한다.

콜백의 수는 보통 1초에 60회다.

콜백 메서드에는 raf()에 대기된 콜백을 실행하는 시점을 나타내는 단일 인자 `DOMHighResTimeStamp`가 전달된다. 모든 이전 콜백의 작업 부하를 계산하는 동안 시간이 지났음에도 단일 프레임에서의 다중 콜백은 각각 동일한 timestamp를 받는다.
