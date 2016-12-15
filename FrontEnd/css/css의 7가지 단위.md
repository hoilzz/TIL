## rem
- `em`은 현재의 font-size
-
```css
body {
  font-size: 14px;
}
div {
  font-size: 1.2em; // calculated at 14px * 1.2, or 16.8px
}
```

이 때, 폰트 사이즈를 각각의 자식에 선언하면..?
부모의 폰트 사이즈를 상속받아 점점 커진다.
```html
  <body>
      <div>
          Test <!-- 14 * 1.2 = 16.8px -->
          <div>
              Test <!-- 16.8 * 1.2 = 20.16px -->
              <div>
                  Test <!-- 20.16 * 1.2 = 24.192px -->
              </div>
          </div>
      </div>
  </body>
```

## rem
이런경우엔 `rem`
- `rem` 은 *root em* 이라는 뜻으로, HTML 문서의 root 요소인 `<html>`을 가리킨다.

```css
  html {
      font-size: 14px;
  }
  div {
      font-size: 1.2rem;
  }
```

### WHEN ? 그리드 시스템

- `rem`의 r은 root 즉, `<html>` element를 뜻한다 (not the parent element)

rem은 폰트에서만 사용하지 않는다.
- 그리드 시스템
  - `rem`을 이용한 기본 폰트 사이즈 기반으로 만든 UI 스타일, 그리고 `em`을 이용해 **특정 위치에 특별한 사이즈를 지정**

```css
  .container {
    width: 70rem; // 70*14px = 980px
  }
```

## NOTE
호환성 체크 [caniuse.com](caniuse.com)

## vh와 vw
- 반응형 웹 디자인은 상당히 `퍼센트`에 의존.
  - 하지만 CSS의 `퍼센트`가 모든 문제 해결하기엔 좋지 않음.
- **CSS의 너비 값은 가장 가까운 부모요소에 상대적인 영향을 받음**.
- 만약 너비와 높이를 `뷰포트`에 맞게 사용할 수 있다면..?

`vh`는 **높이값의 100분의 1단위**. 즉, **뷰포트의 너비와 높이값에 상대적인 영향을 받는다**.


### when?

최대 높이값이나 그의 유사한 높이값의 슬라이드 제작시 아주 간단한 CSS


## vmin과 vmax
`vh`와 `vw`가 뷰포트의 너비값과 높이값에 상대적인 영향을 받는다면 `vmin`과 `vmax`는 너비값과 높이값에 따라 최대, 최소값을 지정할 수 있다.
- 예를 들어, 브라우저 1100px X 700px일 때
- `1vmin`은 7px이 되고 `1vmax`는 11px이 됨

### when?

양 변에 가득차는 정사각형 요소를 만들고 싶을 때

```css
  .box {
    height : 100vmin; // 전체 브라우저의 1/100
    width : 100vmin;
  }
```

만약 커버처럼 뷰포트 화면에 보여야하는 (모든 네 변이 스크린에 꽉 차 있는) 경우 같은 값을 `vmax`로 적용



## ex와 ch

`ex`와 `ch`는 `em`과 `rem`과 유사
- ex와 ch는 **폰트의 특정 수치에 기반**
- em과 rem은 **font-family에 의존**

## ch
- 0의 너비값의 "고급 척도"로 정의
- width : **40ch는 40개의 문자열을 포함**

## ex
- 현재 폰트의 `x-높이` 값 (`x-높이값`은 소문자 x의 높이값이기도 한다)
- 또는 em의 절반값

### when ?
- **폰트의 중간 지점을 알아내기 위해 자주 사용하는 방법**
- 타이포그래피에서 세밀한 조정을 할 때 많이 사용
- 예를 들어 위첨자 태그인 sup에게 position을 relative로 하고 botoom 값을 1ex라고 하면 위로 올릴 수 있다.

<p data-height="265" width="100%" data-theme-id="0" data-slug-hash="LRjRAm" data-default-tab="css,result" data-user="cooking" data-embed-version="2" class="codepen">See the Pen <a href="http://codepen.io/cooking/pen/LRjRAm/">Demo of vw Unit</a> by cooking (<a href="http://codepen.io/cooking">@cooking</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="//assets.codepen.io/assets/embed/ei.js"></script>




# 그밖에..

## px

이미지에 맞춰 정확히 배치해야할 때 사용하면 좋다

## pt

pt는 포인트를 의미한다.
