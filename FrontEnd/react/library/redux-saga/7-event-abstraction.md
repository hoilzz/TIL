# 이벤트 추상화

Saga가 실제로 하는 일은
제어 흐름을 구현하기 위해 모든 이펙트들을 통합하는 것.

yield를 차례차례 넣어서 yield된 이펙트들의 순서를 지키는 것 처럼.

`takeEvery` 처럼 고레벨 API들이 결합된 `call`과 `put`같은 이펙트를 사용했을 때 redux보다 좋은점은
__테스트를 쉽게 할 수 있다는 것__

다른 장점도 다른 파트에서 아라보자.