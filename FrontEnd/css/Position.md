# Position


## Summary

| charateristic  |  value |
|----------------| -------|
| initial value  |  static |
| inherited      | no     |

- **position element**는 position property가 `relative`, `absolute`
, `fixed`, `stickty`로 된 엘리먼트다

  - relatively positioned element : `relative`
  - absolutely positioned element : `absolute` or `fixed`
  - stickily positioned element   : `sticky`

- `top`, `right`, `bottom`, `left` 프로퍼티는 positioned element의 포지션을 명시한다.

## Values

*static*
: `top`, `right`, `bottom`, `left`, `z-index` 프로퍼티 **do not apply**

*relative*
- 모든 엘리먼트가 positioned 안된 것처럼 보인다.
- 그리고 layout 변경 없이(따라서** positioned되지 않은 요소의 간격을 남겨둔다**.)
- element의 positon을 조정한다. `table-*-group`, `table-row, column, cell, caption`에서 정의되지 않는다.

*absolute*
- **element를 위한 space를 남기지 않는다** (`relative`와 차이점)
- 대신에 가장 가까이 포지셔닝된 ancestor의 특정 position에 그것을 positioning 해라.
-  Absolutely positioned boxes는 margin을 가질 수 있고 그것들은 다른 마진과 collapse 되지 않는다.
- **다른 엘리먼트와 놓일 때 공간을 차지 않는다**(`relative`와 차이점)
- positioned absolutely is taken out of the flow
- The absolutely positioned element is positioned relative to nearest positioned ancestor (non-static).
- otherwise relative to the initial containing block.

## 참고
[position from mozilla](https://developer.mozilla.org/en-US/docs/Web/CSS/position)
