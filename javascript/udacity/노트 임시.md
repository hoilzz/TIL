# images with markup

# 1 performance

mobile networking의 의미는 file요청은 요청 size만큼 중요하다. 즉, image 요청 줄이는 목표는 image file의 사이즈가 아니다. 이러한 문제를 latency라 부른다. 이것은 요청과 응답의 delay다. 너의 브라우저가 website 로부터 이미지를 retrieve 한다. 이 방식의 모든 스텝에서 디바이스와 website 서버 간  potential delay가 있다.

많은 모던 웹 페이지, bandwidth는 latency만큼 중요하지 않다.

여튼 **file size**와 **file request 수** 를 줄여야한다.

image bytes를 줄이는 좋은 방법은
1 **compress them**
2 **reduce number of images**

## Note

latency는 new bottleneck이다. *High performance Browser Networking* 에서 [how reducing latency continues to improve page load times](http://chimera.labs.oreilly.com/books/1230000000545/ch10.html) 반면에 bandwidth는 평평해지고 있다.

image download 양을 줄이기 위해, 다음을 사용할 수 있다.
1 [CSS image sprite](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Images/Implementing_image_sprites_in_CSS)
2 [responsive sprites](http://brianjohnsondesign.com/responsive-background-image-sprites-css-tutorial/)

[sprite sheet image](https://www.google.co.uk/images/nav_logo195.png) 는 많은 이미지를 결합한다. 이것은 sprite sheet을 background to the element로써 세팅하여 개별적으로 dp된다. 그리고 나서 CSS로 background position으로 조정된다. 이러한 테크닉은 특히 icon, 반복되는 grphic에서 유용하다.

**latency를 피하기 위해 사용하는 기법이 뭐든, HTTP/2의 변화를 알아둬라**

In a nutshell, HTTP/2는 다음을 의미한다; 많은 file의 요청은 costly less다(**spriting, concatenating** 사용을 멈출 준비를하고 other HTTP/1 hacks!)

[HTTP2 for front-end web dev를 확인해봐..](https://mattwilcox.net/web-development/http2-for-front-end-web-developers)




# Text Problems

# CSS techniques

shadow는 모든 모던 브라우저에서 지원된다. (이미지 hack보다 더 낫다)
- rounded corners, gradient, and animation 다 된당
- 그러나 processing and **rendering cost** to using CSS shadows, rounded corners, and so on
- rendering cost는 모바일에서 중요하다
- [use CSS effects sparingly](https://www.smashingmagazine.com/2013/04/build-fast-loading-mobile-website/)


# CSS background images

background images는 많은 responsive effect를 성취하는데 사용된다.

[using images when don't know the size of the viewport](http://udacity.github.io/responsive-images/examples/2-06/backgroundSizeCover/)

[this image display whole image if viewport more than 500 px wide, or a smaller crop otherwise, add CSS transition, there is not too much of jolt if you resize the window]

- smaller koala crop is displayed, downloaded when the window is small. and then if you resize the window larger, the larger crop is downloaded and displayed.


With background images, you can also use the CSS Image Set to choose a background image depending on screen resolution.

이 예제는 high resolution dp에서 2x color image를 dp한다
otherwise a 1x monochrome image를 dp한다

### reference

[Div with background image](http://udacity.github.io/responsive-images/examples/2-06/divWithBackgroundImage/)
[CSS background-size: cover](http://udacity.github.io/responsive-images/examples/2-06/backgroundSizeCover/)
[body with background image](http://udacity.github.io/responsive-images/examples/2-06/bodyWithBackgroundImage/)
[body with elaborate background using only css](http://udacity.github.io/responsive-images/examples/2-06/bodyWithElaboratePatternPureCSS/)

[Using CSS background images for conditional image display](http://udacity.github.io/responsive-images/examples/2-06/backgroundImageConditional/)

[Using CSS background images for alternative images](http://udacity.github.io/responsive-images/examples/2-06/backgroundImageAlternative/)

[iamge-set()](http://udacity.github.io/responsive-images/examples/2-06/imageSet/)


# CSS background image techniques

### example
- compare between background-size value's cover AND contain

cover : 컨테이너를 완전히 채우는 동안 가능한 사이즈 작게함.
contain : 컨테이너 내부에서 완전히 visible 될만큼 가능한 사이즈 커진다


# Unicode Trble Clef

- char set to utf-8 inside your meta tag.
- meta tag에 utf-8 명시해
> <meta http-equiv="Content-Type" content="text/html; charset=utf-8">

# icon fonts

[icon fonts](http://weloveiconfonts.com)

- icon font characters는 CSS before selector를 이용하여 추가된다.
- CSS text shadow를 포함한 formatting을 추가

  @import url(http://weloveiconfonts.com/api/?family=zocial);

  [class*="zocial-"]:before {
    display: inline-block;
    font-family : 'zocial', sans-serif;
    text-shadow: 3px 3px 3px #aaa;
    width: 20vw;
  }

class name 기반 selector (like zocial-flicker etc)

[icon fonts](https://css-tricks.com/examples/IconFont/)


# inlining images with SVG and data urls

SVG and image element with a data URI source

1 SVG
- inline SVG support on mobile and desktop browsers
- optimization tools can significantly reduce SVG size.


SVG와 data URI source는 동일하게 보인다. 하지만 1개는 3K고 다른 1개는 2K다.

SVG is incredibly powerful.
[Trajan's Column SVG example](https://upload.wikimedia.org/wikipedia/commons/6/6c/Trajans-Column-lower-animated.svg)
- responsive interactivity for less than 160kb

Data URIs
- provide a way to include a file such as image inline as a base64 encoded string using the format

Data URI and SVG 둘다 mobile지원 좋고
CSS에서 인라인될 수 있다.
