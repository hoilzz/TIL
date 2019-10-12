# HLS

Http Live Streaming

HLS는 http 기반

live and on-demand audio and video를 iPhone, iPad, Mac 등에 Http Live Streaming 기술로 보낸다. HLS는 ordinary web server를 이용하여 컨텐츠를 배포할 수 있도록 한다. HLS는 신뢰성과 유무선 연결의 사용 가능한 속도에 맞게 재생을 최적화하여 네트워크 상태에 dynamic하게 적응한다.

클라이언트는 Edge, firefox, 크롬에서 이용가능하다.

HLS는 MPEG-DASH와 비슷하다. 전체 스트림을 일련의 small HTTP-based file 다운로드로 분할하여 작동하는 점에서 비슷하다. 각 다운로드는 잠재적으로 제한되지 않는 전체 전송 스트림의 짧은 조각을 로드한다.

이용 가능한 스트림의 리스트를 M3U playlist를 확장하여 클라이언트에게 보낸다.

표준 HTTP 트랜잭션 기반인 HLS는 표준 HTTP traffic을 통해 proxy server를 순회할 수 있다.

## hls.js

hls.js는 HTTP Live Streaming을 구현한 JS 라이브러리다.

play를 위해 [html5](https://www.html5rocks.com/en/tutorials/video/basics/)와 [mediaSource extension](http://w3c.github.io/media-source/)에 의존한다.

MPEG-2 전송 스트림을 ISO BMFF (MP4) Fragments로 변환하여 동작한다. 이 변환과정은 가능하다면 Web worker를 사용하여 동작한다.

hls.js는 플레이어가 필요없다. HTML 표준 `<video>` element에서 동작한다.

## Compatibility

hls.js는 video/mp4 입력으로 MediaSource 확장(MSE)을 지원하는 브라우저와 호환된다.

미디어소스 API는 다음 [링크](https://developer.mozilla.org/en-US/docs/Web/API/MediaSource)에서 확인하자.

현재 지원 범위는

- 안드 크롬 34+
- 사파리 Mac 8+ (beta)

> iOS Safari "Mobile"은 MediaSource API를 지원하지 않는다. plain video tag source URL을 통해 사파리 브라우저는 내장 HLS 가진다.
> 그래서 플랫폼이 MediaSource나 native HLS 지원을 하지 않는다면, HLS로 플레이할 수 없다.

## FAQ

- native HLS를 지원하면 hls.js 사용할 필요가 없다.
  - 예컨대 hls를 만든 애플.. 
- native HLS를 지원하지 않을 경우에 hls.js를 통하여 동영상을 로드하자.
  - 
- m3u8은 왜 video tag에서 재생되지 않을까?
  - video tag가 지원하지 않는 확장자여서
