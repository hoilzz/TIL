# css box model

각 요소는 사각형 박스로 나타낸다. 이 박스의 크기, 특성 및 위치 결정이 렌더링 엔진의 목적이다.

<img src = "https://mdn.mozillademos.org/files/8685/boxmodel-(3).png">

### content 영역
실제 내용을 포함하는 영역이다. 거기에는 배경, 색 또는 이미지가 있다.

CSS `box-sizing` 속성이 기본으로 설정된 경우 다음 CSS 속성이 크기를 제어한다.
- `width`, `min-width`, `max-width`, `height`, `min-height`, `max-heigth`

### padding 영역
패딩을 둘러싼 보더까지 미친다.
- content 영역의 배경, 색 또는 그 위에 설정된 이미지가 있을 때 이것은 `padding` 까지 이어진다.
- 이것이 **padding을 content에 연장으로 생각할 수 있는 이유다.**

### margin
boder 영역을 이웃과 구별하기 위해 쓰이는 빈 영역
- margin collapsing 일어날 때, margin 영역은 박스 간 공유되기 때문에 분명히 정의되지 않는다. 
