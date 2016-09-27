## Responsive Web design

#### What is the viewport?

viewport는 web page의 visible area다.

viewport는 device에 따라 다양하고

모바일 폰이 computer screen보다 작다

tablets and mobile phone이전에,
web page는 computer screen을 위해 디자인 됐다.
그리고 web pages가 static design과 fixed size를 갖는 것이 일반적이다.

이것을 고치기 위해, 그러한 장치의 브라우저는
전체 웹페이지를 스크린에 맞추기 위해 scaled down했다.


#### 활용
>
> <meta name="viewport" content="width=device-width, user-scalable=no">
>

width
- 뷰포트의 크기 조정
- 특정 숫자 사용 (width = 600) or device-width와 같은 특정한 값 사용 가능
- device-width는 100% 스케일에서 CSS 픽셀들로 계산된 화면의 폭을 의미

initial-scale
- 페이지가 처음 로드될 때 줌 레벨 조정
- maximum-scale, minimum-scale, 그리고 user-scalable 속성들은
  사용자가 얼마나 페이지를 줌-인, 줌-아웃 할 수 있는지 조정.
