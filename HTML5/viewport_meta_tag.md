## viewport_meta_tag


### Background
Mobile browser는 스크린보다 더 넓은 virtual "window" (the viewport)에서 page를 렌더링 한다. 그래서 모든 page layout을 (non-mobile-optimized site를 break하는) tiny window로 squeeze 할 필요 없다.
User는 페이지의 다른 영역을 보기 위해 pan and zoom한다

Mobile Safari는 web 개발자에게 viewport size와 scale을 제어하도록 하기 위해  "viewport meta tag"를 소개한다.

비록 *meta tag* 가 *웹 표준* 이 아니더라도, Many other mobile browsers 이 태그를 지원한다.

Apple's documentation이 web 개발자가 이 태그를 사용하는 방법에 대해 잘 설명한다. 하지만 그것이 구현되는 방식을 정확히 이해해야한다. 예를 들어, Safari 문서에서는 content 는 "comma-delimited list"다 라고 말하지만
기존의 브라우저와 웹페이지는 commas, semicolons, and space as separator의 믹스를 사용한다.

### Viewport basics

전형적인 mobile에 최적화된 사이트는 다음을 포함한다

  <meta name="viewport" content="width=device-width, initial-scale=1">

width property는 viewport 사이즈를 조절한다
width=600과 같은 pixel의 특정 숫자로 세팅되거나
device-width value와같은 특별한 값으로 세팅될 수 있다.
(100% scale에서 CSS pixel에서 device-width는 스크린의 width다.)
(상응하는 height와 device-height 값이 있다. 이것은 viewport height에 따라 position 혹은 size가 변경되는 엘리먼트를 가진 페이지에서 유용하다)
