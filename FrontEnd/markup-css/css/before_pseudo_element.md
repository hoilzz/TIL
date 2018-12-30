## before

### 정의
::before 는 매치되는 엘리먼트의 첫번째 child인 pseudo-element를 생성한다
*content* property를 이용하여 엘리먼트에 cosmetic content를 추가하기 위해 사용된다. 이 엘리먼트의 default는 inline이다.


### syntax

> CSS3 syntax
> ::before { style properties }

::before notation (with two colons) pseudo-class와 pseudo-element 간 차이를 나타내기 위해 도입되었다. Browser는 CSS2에서 :before를 허용한다

### Example

#### 1 Adding quotation marks

::before pseudo-element를 이용하는 간단한 예제는 quotation marks를 제공하는 것이다. quotation characters를 insert하기 위해 ::before와 ::after 둘다 사용해보자.

##### HTML content
  <q>Some quotes</q>, he said, <q>are better than none</q>

##### CSS content
  q::before {
    content: "<<"
    color:blue;
  }
  q::after{
    content: ">>"
    color:red;
  }
output



#### Summary
::before 선언시 기재한 엘리먼트의 첫번째 child로 pseudo-element생성.
이 엘리먼트는 *content property* 를 이용하여 컨텐츠 추가 가능.





### 해보기

http://codepen.io/cooking/pen/WGbORq?editors=1100

<p data-height="265" data-theme-id="0" data-slug-hash="VKYzvg" data-default-tab="html,result" data-user="cooking" data-embed-version="2" class="codepen">See the Pen <a href="http://codepen.io/cooking/pen/VKYzvg/">VKYzvg</a> by cooking (<a href="http://codepen.io/cooking">@cooking</a>) on <a href="http://codepen.io">CodePen</a>.</p>
<script async src="//assets.codepen.io/assets/embed/ei.js"></script>

##### Issue
1 ::before의 element와 ::before의 부모 element를 table화 해야함
  - 현재상황 : table과 관련된 모든 엘리먼트 block 으로 변경
  - block 엘리먼트 안의 ::before(inline) 엘리먼트를 테이블의 행,열 처럼 보여야함
  - td 안의 컨텐츠 자체는 ::before 엘리먼트와 같은 레벨? 이라서 움직일 수 없음
  - td의 padding-left를 통해 ::before와 td 컨텐츠를 동시에 오른쪽으로 옮긴다.
  - ::before 엘리먼트만 옮기기 위해 부모 엘리먼트를 relative, ::before를 absolute로 변경



2 display:none이 아닌 잠깐 숨겨야할때..?
thead tr {
    position: absolute;
    top: -9999px;
    left: -9999px;
  }
