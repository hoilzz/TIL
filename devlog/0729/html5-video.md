# video, track, source

## video

- 동영상 콘텐츠를 포함하기위해 사용
- src속성이나 `<source>` 를 이용하여 여러개의 동영상 노출 가능

```js
<video controls width="250">
    <source src="/media/examples/flower.webm"
            type="video/webm">

    <source src="/media/examples/flower.mp4"
            type="video/mp4">

    Sorry, your browser doesn't support embedded videos.
</video>
```

**properties**

- autoplay
  - 데이터 로딩이 완료되지 않더라도 재생가능한 시점에 자동 재생
- buffered
  - 미디어의 어느 시간대가 버퍼에 들어 있는지 확인 가능
- controls
  - 소리조절, 동영상 탐색, 일시정지/재시작을 할 수 있는 컨트롤러 제공
- height
  - 비디오의 출력 영역 높이
- loop
  - 반복재생
- crossorigin
  - 관련 이미지 가져오기에서 CORS 사용 여부
- preload
  - 개발자가 생각하는 가장 좋은 사용자 경험이 어떤건지 브라우저에게 미리 알려주기
    - none : 비디오 no-cache
    - metadata: 메타데이터만 미리 가져오기
    - auto: 사용자가 우선순위를 가진다. 사용자가 사용하지 않더라도 필요하면 전체 비디오가 다운로드 됨.
    - poster: 동영상 재생 및 탐색 전까지 출력되는 포스터 프레임 주소
    -

## track

- track은 audio video 태그의 자식

**properties**

- default:
  - 활성화될 자막 가리키기
- kind
  - 자막 사용 방법
- label
  - 자막 텍스트의 제목들
- src
  - 자막의 주소
- srclang
  - 자막 텍스트 데이터의 언어.

## source

다중 미디어 리소스 지정하기 위해 사용.
일반적으로 다른 브라우저에서 지원하는 여러 포맷들을 통해 같은 미디어를 제공하기 위함.
(걍 여러가지 확장자의 동영상 지원시 필요)
