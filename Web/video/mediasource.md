# MediaSource

[MediaSource from MDN](https://developer.mozilla.org/en-US/docs/Web/API/Media_Source_Extensions_API)

미디어소스 확장 API(MSE)는 웹 기반 스트리밍 미디어를 가능하게 해주는 함수를 제공한다. MSE를 이용하여, 미디어 스트림은 생성되고 <video>나 <audio> 엘림너트에서 플레이된다.

## Media Source Extensions Concepts and usage

비디오와 오디오를 재생하는 것은 웹에서 플러그인 없이 가능했다. __하지만 제공된 기본 기능은 단일 전체 트랙을 플레이하는데만 유용하다.__ 예컨대, arraybuffers를 결합/분리 할 수 없다. 스트리밍 미디어는 최근까지 RTMP 프로토콜을 이용한 Flash Media Server와 같은 기술을 가진 Flash 도메인이었다. 

### MSE 표준

MSE로 위와 같은 상황은 변경됐다. MSE는 미디어 엘리먼트의 단일 트랙 `src` 값을  `MediaSource` 객체에 대한 참조값으로 변경할 수 있다. 이 객체는 플레이 될 미디어의 준비상태와 같은 정보를 위한 컨테이너다. 그리고 전체 스트림을 구성하는 미디어의 서로다른 청크를 나타내는 여러개의 `SourceBuffer` 객체에 대한 참조다. MSE는 contents를 얼마나 많이 그리고 자주 가져올지, 버퍼가 제거될 때와 같은 메모리 사용 세부사항을 제어한다. 확장 가능한 API를 기반으로 적응형 bitrate 스트리밍 클라이언트(DASH or HLS를 이용하는 것과 같은)를 위한 토대다.

MSE로 자원을 생성하는 것은 힘든 과정이다. 컨텐츠를 적절한 포맷으로 맞추기 위해 외부 유틸리티를 사용해야한다. MSE를 통한 다양한 미디어 컨테이너에 대한 브라우저 지원은 드물지만... H.265 비디오 코덱, MP4 컨테이너 포맷의 사용이 일반적인 기준이다. MSE는 컨테이너의 런타임 탐지와 코덱에 대한 API를 지원한다. 

만약 비디오 품질을 명시적으로 제어할 필요가 없는 경우, 컨텐츠를 가져오는 속도 또는 메모리가 제거되는 속도는 video element가 간단하고 적절한 솔루션일 수 있다. 