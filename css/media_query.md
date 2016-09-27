## CSS 3 Media Queries


#### CSS3 Media Queries

Media 쿼리는 CSS2 media types idea를 확장한다
- device type을 찾는 것 대신에, 그들은 device의 capability를 본다

Media 쿼리는 많은 것을 확인 하는데 사용된다
- width and height of the viewport
- width and height of the device
- orientation (is the tablet/phone in landscape or portrait mode?)
  기기의 방향, landspace (가로 모드), portrait(세로 모드)
- resolution

media 쿼리를 사용하는 것은 타블렛, 아이폰 그리고 안드로이드에 딱 맞는 style sheet을 전달하는 유명한 기법이다.

#### Media Query Syntax
- media query는 media type을 구성하고 1개 이상의 표현을 포함한다.
- 이것은 true or false로 resolve 한다.

> @media not|only mediatype and (expressions) {
  CSS-Code;
}

만약 명시된 media type과 device type이 일치한다면 쿼리 결과는 true다.
document는 dp되고 미디어 쿼리의 모든 표현은 true다.

media query가 true일 때,
상응하는 style sheet or style rules가 적용된다.
(normal cascading rule을 따르면서)

Unless you use the not or only operators,
media type은 optional 하고
*all* the type 이 implied된다.

다양한 media를 위해 다양한 stylesheet을 가질 수 있다.

<link rel="stylesheet" media="mediatype and|not|only (expressions)" href="print.css">


#### CSS3 Media type

<| Value         | Description     |
| :------------- | :------------- |
| all       | 모든 media type device       |
| print | printer |
| screen | computer screens, tablets, smart-phones|


#### Media Queries Simple Examples

media queires를 사용하는 1가지 방법은
style sheet 내부에 alternate CSS section을 가지는 것이다.

다음 예제는 만약 viewport 가 480 pixel wide or wider라면
background color를 light green으로 변경한다

> @media screen and (min-width: 480px) {
  body {
    background-color: lightgreen;
  }
}

다음 예제는 만약 viewport가 480 pixel wide or wider라면
페이지 왼쪽으로 float 된 menu를 보여줄 것이다
(만약 viewport가 480 pixel 이하라면,
  메뉴는 content의 상단에 있을 것이다)

@media screen and (min-width:480px) {
  #leftsider {width: 200px; float:left;}
  #main {margin-left:216px;}
}
