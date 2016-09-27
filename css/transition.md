## CSS transition

CSS 속성 변경할 때 애니메이션의 속도를 조절한다. 속성 변경이 즉시 영향을 미치게 하는 대신, *그 속성의 변화가 일정 기간에 걸쳐 일어나도록* 할 수 있다. 예를 들어, 흰->검 으로 변경시 즉시 일어난다. 하지만 트랜지션 이용시, 커스터마이즈 가능한 어떤 가속도 곡선을 따르는 시간 주기마다 변화가 일어난다.

https://developer.mozilla.org/files/4529/TransitionsPrinciple.png

- 어떤 속성을 움직이게 할지
- (딜레이를 설정해서) 언제 애니메이션이 시작할지
- (지속 시간을 설정해서) 트랜지션을 얼마나 지속할지
- (선형이거나 초기 빠름, 종료 느림과 같은 타이밍 함수를 정의해서) 어떻게 트랜지션을 실행할지


### 트랜지션 정의에 사용한 CSS 속성
트랜지션은 시작에서 종료까지 어떤 속성의 변화만을 시각화한다.
어떤 변화의 루프를 시각화하려면 [**CSS animation**](https://developer.mozilla.org/en-US/docs/Web/CSS/animation) 속성을 보자.

1 transition-duration         트랜지션 일어나는 지속시간
2 transition-timing-function  속성의 중간값을 계산하는 방법을 정의하는 함수 명시
3 transition-delay            속성이 변한 시점과 트랜지션이 실제로 시작하는 사이에 기다리는 시간 정의


### NOTE
1 CSS 트랜지션 속성은 prefix 제공자 없이 사용 가능
  - 하지만 최근에야 안정되어서.. 벤더 프리픽스 필요하다.


### 다수의 애니메이션이 적용된 속성 예제

- width, height : from 100 to 200
- background    : #0000FF to #FFCCCC

HTML

  <body>
    <div class="box"></div>
  </body>

CSS

  .box {
    width  : 100px;
    height : 100px;
    background-color : #0000FF;
    -webkit-transition: width 2s, height 2s, background-color 2s, -webikit-transform 2s;
    transition:width 2s, height 2s, background-color 2s, transform 2s

  }



### 트랜지션 완료 감지하기

### 메뉴 하이라이팅에 트랜지션 사용

### 트랜지션을 이용하여 Javascript 기능 부드럽게 하기




### 걍해본거
<iframe height='265' scrolling='no' src='//codepen.io/cooking/embed/kkPNNo/?height=265&theme-id=0&default-tab=css,result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/cooking/pen/kkPNNo/'>kkPNNo</a> by cooking (<a href='http://codepen.io/cooking'>@cooking</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>
