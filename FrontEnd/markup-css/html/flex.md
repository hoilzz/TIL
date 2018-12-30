## flex

### background

`Flexbox Layout` (flexible Box) 모듈은 layout에 대한 더 효율적인 방식을 제공한다. layout의 사이즈가 알려져있지 않고 dynamic (thus the word "flex")할 때 컨테이너 내부의 아이템 간에 space를 정렬하고 분배 한다.

flex layout 의 main idea는 컨테이너에게 *available space의 best fill을 만들기 위해 items' width/height를 변경할 수 있는 능력을 준다* 는 것이다. (대개 모든 종류의 display device와 screen size에게 적합하도록 함)

 flex container는 *available free space를 채우기 위해 아이템을 확장* 시킨다. (*or overflow를 막기위해 item을 shrink*)

flexbox layout은 regular layout과 대조된다.

> regular layout
vertically-based인 `block`과 horizontally-based인 `inline` 으로 잘 작동하지만, large or complex application에선 regular layout은 유연성이 부족하다. (특히 orientation이 변경, 리사이징, 스트레칭, shirinking 등과 같은 상황 일 때)

<br>

> Note : Flexbox layout은 application의 *component, small-scale layout* 에 적합하다. 반면에 Grid layout은 larger scale layout 때문에 만들어졌다.


### Basic & Terminology

flexbox는 whole module이고 single property는 아니기 때문에, 그것은 set of properties 를 포함한다. 프로퍼티의 몇몇은 container에 세팅 컨테이너에서 세팅된다.
(컨테이너는 parent element, known as "flex container") 반면에 `flex item`이라 불리는 children도 있다.

만약 regular layout이 block과 inline flow direction 기반이라면,
flex layout은 "flex-flow direction" 기반이다.

https://cdn.css-tricks.com/wp-content/uploads/2011/08/flexbox.png

기본적으로, 아이템은 main axis 혹은 cross axis를 따라 펼쳐진다.
(main axis from main-start to main-end, cross axis from cross-start to cross-end)

#### properties for the Parent ( flex container )

##### display

- flex container를 정의
- inline or block
- 그것의 direct children의 flex context 를 허용한다.

```css
  .container {
    display:flex;
  }
```

##### flex-direction

- 이것은 main-axis를 만든다. 따라서 *direction of flex item을 정의하는 것은 flex container 안에 위치* 해야 한다.
- Flexbox는 single direction layout concept이다. (aside from optional wrapping)
- flex item은 주로 horizontal rows or vertical column에서 놓인다.

```css
  .container {
    flex-direction : row | row-reverse | column | column-reverse
  }
```

##### flex-wrap

기본적으로, flex item은 one line에 fit하려 할 것이다. 그것을 변경할 수 있고 아이템이 필요에 따라 wrap하도록 허용한다. Direction은 stacked in 한 new line direction을 결정하는 역할을 한다.

```css
  .container {
    flex-wrap : nowrap | wrap | wrap-reverse;
  }
```

  - `nowrap` (default) : single-line / left to right in `ltr`; right to left `rtl`, *라인이 2개 이상 안됨(1줄)*
  - `wrap` : *multi-line* / left to right in `ltr`; right to left in `rtl`

#### justify-content
main axis를 따라 alignment를 정의
- extra free space를 분배


### Properties for the children (flex item)

#### 1 order

#### 2 flex-grow
: 필요시 flex item이 grow할 수 있는 능력.
- 비율에 따라 제공하는 unitless value 허용
- flex container 내부에 available space의 양을 나타낸다.

##### 3 flex-shrink
: flex item이 필요하다면 감소할 수 있는 능력


### Summary
flex css 프로퍼티는 이용가능한 공간을 채우는 dimension을 변경하기 위해 flex item의 ability를 명시하는 속성이다. Flex items는 flex grow factor로 공간을 비율로 이용할 수 있다. 혹은 over flow를 막기 위해 flex shrink factor를 사용할 수 있다.


<br>

*화면 비율에 따라 layout이 바뀌는 레이아웃 via flex*
<iframe height='442' width="100%" scrolling='no' title='qaOpzJ' src='//codepen.io/cooking/embed/qaOpzJ/?height=442&theme-id=0&default-tab=result&embed-version=2' frameborder='no' allowtransparency='true' allowfullscreen='true' style='width: 100%;'>See the Pen <a href='http://codepen.io/cooking/pen/qaOpzJ/'>qaOpzJ</a> by cooking (<a href='http://codepen.io/cooking'>@cooking</a>) on <a href='http://codepen.io'>CodePen</a>.
</iframe>
