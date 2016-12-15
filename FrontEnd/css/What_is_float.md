# What is "float"

float css는 엘리먼트가 normal flow를 쓰지 않고 컨테이너의 left or right side에 놓여진다.
- 이 때, 컨테이너는 text와 inline element로 wrapping 될 것이다.
- floating element는 float 값이 none이 아닌 것이다.
- float는 inherit 안된다.

### applies to
`all elements` but has no effect if the value of `display is none`

- **float는** **`block`** **layout 사용** 하기 때문에, 가끔 display 값을 수정한다.

#### 4가지 valid value
1. Left
2. right
3. None
  - 엘리먼트는 float하지 않을 것
4. Inherit
  - 부모 엘리먼트에서 float value를 상속 받는다.

## **1. text wrap**
Float 는 CSS positioning property다. text가 wrapping하고 있는 아래 이미지를 보자. 이것은 일반적으로 **`text wrap`** 이라고 불린다.

<img src = "https://css-tricks.com/wp-content/csstricks-uploads/web-text-wrap.png">

- Floated 엘리먼트는 web page의 flow의 부분으로 남아있다.
- 이것은 `absolute positioning`을 사용하는 page element와 다르다.
  - Absolutely positioned page elements는 웹페이지의 flow에서 제거된다.
  -  **Absolutely positioned page element는 다른 엘리먼트간 닿든 안닿든 간에 다른 엘리먼트와 다른 엘리먼트 위치에 영향을 주지 않는다.**, float 제대로 동작 안한다.



## What are floats used for?

### **2. 전체 웹 레이아웃을 생성**

<img src = "https://css-tricks.com/wp-content/csstricks-uploads/web-layout.png" />

2. smaller instance 내에서 **레이아웃 잡는데 도움**이 된다. 웹 페이지의 작은 영역을 예시로 들어보자. 만약 우리가 작은 avatar image를 사용한다면, **그 이미지의 사이즈가 변경 될 때 박스 안의 텍스트는 accomodate하기 위해 reflow**된다.

<img src = "https://css-tricks.com/wp-content/csstricks-uploads/reflow-example-1.png">

4. 컨테이너에서 relative positioning과 absolute positioning을 이용하여 동일한 레이아웃이 완성될 수 있다. 이러한 방식으로 하면, 텍스트는 아바타에 영향을 받지 않고 size 변화에 reflow할 수 없다.

<img src = "https://css-tricks.com/wp-content/csstricks-uploads/reflow-example-2.png">


## Clearing the Float

Float's sister property is `clear`. `clear` property를 갖는 엘리먼트는 float가 바라는대로 float에 인접한 곳으로 이동하지 않을 것이다. 하지만  float를 지나 움직일 것이다.

<img src = "https://css-tricks.com/wp-content/csstricks-uploads/unclearedfooter.png" />

위 예제에서, sidebar는 오른쪽으로 floated되고 main content area보다 작다. footer는 float에 의해 필요한 만큼 이용가능한 공간으로 점프 될 필요가 있다. 이러한 문제를 해결하기 위해 footer가 floated columns 아래에 stay하도록 cleared되어야 한다.

```css
#footer {
  clear : both;
}
```

clear는 4가지 값을 가진다.
1. `both`
  - commonly used, either direction에서 오는 float를 clear한다.

2. `left`와 `right`
  - 각각 한 방향만 clear할 수 있다.

3. `None` 은 default.
  - 만약 cascade로부터 clear 값을 제거하지 않는다면 which is typically unnecessary

4. `inherit` would be the fifth
  - but IE에서 지원하지 않는다.
  - left or right float만 Clearing. 실무에서 보기 힘들지만 확실히 쓰긴 쓴다.

### summary
- `float`를 지우는 것은 `clear`다.


**## The Great Collapse**

float로 작업시 당황스러운 점 중 하나는 "parent" element에 영향을 미치는 방식이다. 만약 아무것도 포함하지 않은 parent element but floated elements, 그것의 height는 문자 그대로 collapse to nothing. 만약 parent가 비주얼적으로 알아볼 수 있는 background를 포함하지 못한다면 이것은 항상 obvious 하지 않다. 하지만 이것을 아는 것은 중요하다.

<img src = "https://css-tricks.com/wp-content/csstricks-uploads/collapse.png" />

As anti-intuitive as collapsing seems to be, the alternative is worse.


## Technique for Clearing Floats

엘리먼트에 **`clear : both`** 적용하기.. no fancy hack and no additional element (완벽하게 semantic) 이 2가지 상황을 필요로 하지 않는게 이상적이다.

- **The Empty Div Method**는 말그대로 empty div다. `<div style = clear : both;></div>`. element or some other random element used, but div is the most common. (왜냐하면 어떤 브라우저도 div에 대해 default style을 갖지 않기 때문이다). 맥락상 의미도 없기 때문에  semantic purist는 이걸 겁나 경멸한다.

- **Overflow Method** 는 parent element에 overflow CSS를 세팅하는 것. 만약 이 프로퍼티가 `auto` or `hidden`으로 세팅 되있다면, parent는 **float 포함하기 위해 expand**할 것이다.(succeeding element를 위해 그것을 효과적으로 clearing 하면서). 추가 element를 필요 하지 않기 때문에 이 메서드는 semantic하다. 그러나 만약 이것을 적용하기 위해 new div를 추가한다면 empty div method처럼 non-semantic이다. 또한, overflow property는 특별히 clearing float를 하지 않는다. content를 숨기지 않거나 unwanted scrollbar가 트리거 되지 않도로고 조심해라

- **Easy Clearing Method** 는 float를 지우기 위해 clever CSS pseudo selector(:after)를 사용한다. parent에 overflow 세팅하는 것보다 `clearfix`와 같은 클래스를 추가하는게 낫다.

```css
.clearfix:after {
  content : ".";
  visibility : hidden;
  display: block;
  height : 0;
  clear : both;
}
```
  - 위 코드는 뷰에서 숨겨진 small bit of content에 적용할 것이다. (after float를 clear한 parent element). 이게 전부가 아냐. older browser를 위해 추가 코드가 더 필요해.
