# video, track, source

내가 궁금한 것만

[https://developers.google.com/web/fundamentals/media/video?hl=ko](https://developers.google.com/web/fundamentals/media/video?hl=ko)
[https://developer.mozilla.org/ko/docs/Web/HTML/Element/Video](https://developer.mozilla.org/ko/docs/Web/HTML/Element/Video)
[https://developers.google.com/web/updates/2017/06/play-request-was-interrupted](https://developers.google.com/web/updates/2017/06/play-request-was-interrupted)
[video tag from html5rocks](https://www.html5rocks.com/en/tutorials/video/basics/#toc-javascript)
[video content](https://developer.mozilla.org/en-US/docs/Learn/HTML/Multimedia_and_embedding/Video_and_audio_content)

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

- buffered

  - 미디어의 어느 시간대가 버퍼에 들어 있는지 확인 가능

- preload
  - 개발자가 생각하는 가장 좋은 사용자 경험이 어떤건지 브라우저에게 미리 알려주기
    - none : 사용자가 비디오를 보지 않거나, 서버가 최소한의 트래픽을 유지하고자 함을 의미. 비디오 no-cache
    - metadata: 비디오를 보지 않을 수도 있지만 메타데이터만 미리 가져오기

```
// 1. request video src
#EXTM3U

#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=232370,CODECS="mp4a.40.2, avc1.4d4015"
gear1/prog_index.m3u8

#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=649879,CODECS="mp4a.40.2, avc1.4d401e"
gear2/prog_index.m3u8

#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=991714,CODECS="mp4a.40.2, avc1.4d401e"
gear3/prog_index.m3u8

#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=1927833,CODECS="mp4a.40.2, avc1.4d401f"
gear4/prog_index.m3u8

#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=41457,CODECS="mp4a.40.2"
gear0/prog_index.m3u8

// 2. request metadata
#EXTM3U
#EXT-X-TARGETDURATION:10
#EXT-X-VERSION:3
#EXT-X-MEDIA-SEQUENCE:0
#EXT-X-PLAYLIST-TYPE:VOD
#EXTINF:9.97667,
fileSequence0.ts
#EXTINF:9.97667,
fileSequence1.ts
#EXTINF:9.97667,
fileSequence2.ts
#EXTINF:9.97667,
fileSequence3.ts
#EXTINF:9.97667,
fileSequence4.ts
#EXTINF:9.97667,
fileSequence5.ts
#EXTINF:9.97667,
fileSequence6.ts
#EXTINF:9.97667,
fileSequence7.ts
#EXTINF:9.97667,
fileSequence8.ts
...
```

    - auto: 사용자가 우선순위를 가진다. 사용자가 사용하지 않더라도 필요하면 전체 비디오가 다운로드 됨.
        - ts 조각을 동영상 종료 조각까지 가져온다.(m3u8기준)

> none을 사용
> 인스타, 네이버 대부분 none으로 값을 설정. on demand 로 동영상을 재생하기 때문에 불필요한 트래픽 발생하지 않으려고 그러는거 같음.

- poster
  - 동영상 재생 및 탐색 전까지 출력되는 포스터 프레임 주소
  - 이 속성이 없다면, 첫 번째 프레임이 사용 가능하게 될 때까지 아무것도 출력 안됨. 가능하면 첫번쨰 프레임을 포스터로 출력.

## Using <video>

비디오 태그를 이용하여 동영상 로드/디코딩/재생 한다.

### 시작 및 종료 시간 지정

대역폭 절감 및 사이트 반응성을 위해 **Media Fragments API** 를 사용할 수 있다.

```html
// 5~10초 사이 재생
<source src="video/chrome.webm#t=5,10" type="video/webm" />
```

iOS를 제외한 대부분의 플랫폼이 위 API 제공. 인스타그램도 위와 같이 range를 지정하여 로드.

### 어떤 형식이 지원되는지 확인

`canPlayType()`을 이용하여 동영상 지원 확인할 수 있다. m3u8 확장자를 native hls는 재생할 수 있기 떄문에 아래와 같이 확인

```js
videoRef.current.canPlayType('application/vnd.apple.mpegurl'); // maybe
```

웹뷰에서 maybe 리턴. mac os 사파리에서는 빈문자열

- 빈문자열 : 지원 ㄴㄴ
- maybe : 지원 될 수 있는데 확인을 위해 브라우저가 일부 동영상 다운로드
- probably : 지원 가능

### 동영상 크기 확인

인코딩시, 실제 동영상 프레임 크기가 동영상 요소 크기와 다를 수 있다.

인코딩 크기를 확인하려면 동영상 요소 videoWidth, videoHeight 속성을 확인한다.

### method

- load 
    - 재생하지 않고 동영상 소스 로드하거나 다시 로드(ex: js 사용하여 동영상 소스가 변경된 경우)
    - 시작으로 미디어를 리셋한다. 
    - 

### event

- canplaythorugh : 브라우저가 동영상을 중단없이 끝까지 재생할 수 있다고 판단할 만큼 데이터가 충분한 경우 재생
- error
-

## track

- track은 audio video 태그의 자식


play 중에 pause니까..

1. play를 그대로 쓸꺼면

- video element가 로드 중이면 pause 메서드 ㄴㄴ
- 로드 완료면 pause 메서드 ㅇㅇ

2. play 안쓰고 load부터 하면..
- load 중에 pause해도 괜찮은가?
