# box sizing
box sizing은 요소의 `width` 와 `height` 를 계산하는데 사용되는 기본적인 CSS box model을 대체하기 위해 사용된다.

| characteristic | value |
| ----------     | ----- |
| 초기값         | content-box |
| 상속 |no|

## syntax

### content-box
- CSS 표준에 의해 정의된 기본 스타일
- `width`와 `height` 속성은 오로지 콘텐츠만을 포함하며 측정되며, **`padding`, `border`, `margin` 미포함**
- 참고 : padding, border, margin은 박스 외부에 존재. 예를 들어
  ```css
    .box
    {
      width : 350px;
      border : 10px solid black;
    }
  ```

- 결과적으로 브라우저에서 렌더링 되는 것은 `.box {width : 370px}`

### padding-box
- width와 height 속성은 padding 크기를 포함한다.
- 하지만 border 및 margin 미포함

## border-box
- width와 height 속성이 padding border를 포함. margin 미포함
- 이 box model은 IE 에서 문서가 쿽스 모드일 때 사용
- 참고: padding 과  border는 박스 안에 존재한다. 이를테면 .box {width: 350px}; 인  요소에  {border: 10px solid black;} 를 적용하면 결과적으로 {브라우저에서 렌더링되는 것은} .box {width: 350px;}이다.
