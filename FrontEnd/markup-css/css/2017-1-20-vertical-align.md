# vertical-align

`vertical-align`이 넘나 헷갈려서 정리하는 그링ㅂ니다.

## Summary

> vertical-align은 `inline` or `table-cell box`의 수직 정렬을 명시한다.

## Values

baseline
: 엘리먼트의 baseline을 부모의 baseline으로 정렬한다. `textarea`와 같은 replaced element의 baseline은 HTML 스펙에 명시되어 있지 않다. 이 말은 브라우저에 따라 키워드의 baseline이 다 다르다는 것을 의미한다.

middle
: baseline을 가진 element의 중앙 + 부모의 x-height의 절반을 더한 값으로 정렬한다.

top
: element의 top과 자손의 전체 라인의 top에 맞춰 정렬한다.

bottom
: element의 bottom과 자손의 전체 라인의 bottom에 정렬한다. 

text-top
: element의 top을 부모 엘리먼트 폰트의 top에 정렬한다.

# 발췌 1
[http://christopheraue.net/2014/03/05/vertical-align/](http://christopheraue.net/2014/03/05/vertical-align/)

레이아웃을 위해 `vertical-align`을 사용하는 것은 hack이다. 왜냐면 레이아웃 잡으라고 개발된건 아니기 때문이다. text와 text 옆에 있는 엘리먼트를 정리 할 수 있다.

Nonetheless, very flexible and 세밀하게 엘리먼트를 정렬하기 위해  `vertical-align`을 다양한 맥락에서 사용할 수 있다. 엘리먼트의 사이즈는 알필요가 없다. 엘리먼트는 flow에서 유지되서 다른 엘리먼트가 다양한 dimension에 반응한다.


## vertical-align 사용시 필요한 것

`vertical-align`은 `inline-level element`를 정렬할 때 사용한다. `display` property가 다음 세가지 값이어야 한다.

- inline
- inline-block
- inline-table

`inline elements`는 기본적으로 text를 감싸는 태그다.

`inline-block elements`는 이름 그대로, inline으로 사는 block element다. 얘들은 width와 height(자체 컨텐츠로 정의될 수도 있다.)를 가질 수 있다. 뿐만아니라 padding, a border and margin도 가질 수 있다.


**inline element의 outer edges** 는 자신의 `line-height`의 top and bottom edge에 자신을 정렬한다. 만약 `line-height`가 font의 height보다 작으면 이건 안중요하다. 그래서 outer edges는 red line이다.



**inline-block element의 baseline** 은 element가 in-flow content 소유 여부에 달려있다.

	- in-flow의 경우 inline-block의 baseline은 normal flow에서 가장 마지막 컨텐츠의 baseline이다.

	- in-flow에서 `overflow` property가 visible외의 것으로 설정되어있을 경우, baseline은 margin-box의 bottom edge다. 그래서 baseline은 inline-block element's bottom egde와 동일하다.


> NOTE : *in-flow* 는 flow에서 벗어나지 않는 엘리먼트를 뜻한다.
>		 *out of flow* 는 float, absolutely positioned 된 엘리먼트다. margin edge 는 box margin을 둘러싼다. 만약 margin이 0 width를 갖는다면 margin edge는 border edge와 동일하다. 4가지 margin edge는 box의 margin box를 정의한다.



### Line box

> inline element는 서로 나란히 배치된다. line box의 text box의 top and bottom 과 baseline을 보자. 현재 라인에 더 많은 엘리먼트가 들어오면 그 아래에 새로운 라인이 생성된다. 모든 라인은 **line box** 를 가진다. 이것은 라인의 모든 내용을 묶는다. 다양한 사이즈를 가진 컨텐츠는 다양한 height를 가진 line box를 의미한다. 다음 일러스트레이션은 line boxes의 top과 bottom이 red line으로 나타내고 있다.

그림

line box 내부의 요소들의 property `vertical-align`은 개별 요소를 정렬한다.

그림

이번엔 line box의 text box의 top and bottom 을 그려보자. text element의 영역엔 회색을 칠해놨수다.

line box의 base라인은 보이지 않기 때문에 어딨는지 확실히 알 수 없다. 하지만 쉽게 보이게할 수 있다. `x`라는 단어 추가해라. 만약 이 문자가 정렬되어있지 않다면, baseline을 default로 갖는다.

baseline 주변의 line box는 **text box** 라 불리는 것을 갖는다. **text box는 어떠한 정렬이 없는 line box 내부의 inline element로 간주된다.** 그것의 높이는 부모 엘리먼트의 font-size와 동일하다. 그러므로 text box는 line box의 포맷팅 되지 않은 text를 둘러싼다. box는 위 그림에서 green line을 가리킨다. **이 text box는 baseline에 묶여있기 때문에, baseline이 움직일 때 움직인다**. **이 부분 개 어렵다..**

자 이제 요약해보자

	- *line box* 라고 불리는 영역이 있다. 이것은 vertical alignment가 일어나는 영역이다. 이것은 `baseline`, `text box` and `top` and `bottom edge`를 가진다.
	- *inline-level* element가 있다. 정렬된 object가 있다. 얘들은 `baseline` and `top` and `bottom edge`를 가진다.


## vertical-align의 값


## Movement of the Line Box's Baseline

line box의 baseline position은 라인 안의 모든 엘리먼트에 영향을 받는다. 엘리먼트가 정렬되어 line box의 baseline이 움직여야한다고 가정해보자. 대부분의 vertical alignment가 (except top and bottom) baseline에 상대적이기 때문에, 결과는 그 라인에 있는 모든 엘리먼트의 조정된 포지션이다.

Some Examples,

- 전체 높이보다 높은 tall element가 있다면 `vertical-align`은 효과가 없다. tall element의 top 위로 bottom의 아래로 공간이 없다. line box의 baseline 기준으로 정렬하기 위해, line box의 baseline은 움직여야한다. short box는 `vertical-align:baseline`을 가진다. 왼쪽 예제의 경우, tall box는 `text-bottom`이다. 오른쪽 예제는 `text-top`으로 정렬되었다.


## Inline-level element 아래에 약간의 Gap
