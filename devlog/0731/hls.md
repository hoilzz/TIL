# HLS

Http Live Streaming

HLS는 http 기반

live and on-demand audio and video를 iPhone, iPad, Mac 등에 Http Live Streaming 기술로 보낸다. HLS는 ordinary web server를 이용하여 컨텐츠를 배포할 수 있도록 한다. HLS는 신뢰성과 유무선 연결의 사용 가능한 속도에 맞게 재생을 최적화하여 네트워크 상태에 dynamic하게 적응한다.

클라이언트는 Edge, firefox, 크롬에서 이용가능하다.

HLS는 MPEG-DASH와 비슷하다. 전체 스트림을 일련의 small HTTP-based file 다운로드로 분할하여 작동하는 점에서 비슷하다. 각 다운로드는 잠재적으로 제한되지 않는 전체 전송 스트림의 짧은 조각을 로드한다.

이용 가능한 스트림의 리스트를 M3U playlist를 확장하여 클라이언트에게 보낸다.

표준 HTTP 트랜잭션 기반인 HLS는 표준 HTTP traffic을 통해 proxy server를 순회할 수 있다.
