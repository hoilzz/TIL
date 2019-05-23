# Static VS Unit VS Integration Testing for Frontend Apps

_이것들이 의미하는 것, 왜 중요한지, 왜 안중요한지 알아보자._

Testing Practice에서 J.B. Rainsberger의 인터뷰에서 그는 내가 좋아하는 메타포를 들려주었다.

> 벽에 페인트를 던질 수 있다. 결국 벽의 대부분을 차지할 거지만 브러시로 벽을 올라갈 때까지 절대로 코너에 도달할 수 없다.

- Integration: 몇몇 유닛들이 함께 동작하는 것을 증명
- Unit : 개별적이고 고립된 부분이 예상대로 동작하는지 증명
- Static : typos와 타입에러를 캐치

## Integration

full app을 렌더링한다. 이것이 통합 테스트의 필수는 아니고 대부분의 통합 테스트가 full app을 렌더링 하지 않는다.

그러나 app에서 사용되는 Proviers와 함꼐 렌더링 될 것이다. (til-client-test-utils라는 모듈 만든 이유가 이때문이다)

통합테스트의 아이디어는 가능한 모킹하는 것이다. 필자는 거의 다음의 것들만 모킹한다.

1. Network request(axiosMock)
2. animation을 맡고 있는 Components

## Why do we test again?

매번우리는 왜 테스트를 작성할까? 테스트가 없으면 PR이 리젝당해서..? 테스트는 너의 workflow를 향상시켜주니까?

가장 중요한 이유는 **CONFIDENCE** 다.
내가 작성한 코드가 미래에 app(현재 production에서 잘 작동하는) 을 break하지 않을거라는 자신감을 가질 수 있다.
