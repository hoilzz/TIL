# Rendering Elements

엘리먼트는 React app의 가장 작은 빌딩 블록이다.

React DOM은 React element와 일치시키기 위해 DOM 업데이트에 신경 쓴다. 

> Note
> 컴포넌트 컨셉과 엘리먼트를 혼동할 수 있다. 엘리먼트는 컴포넌트가 무엇으로 "구성" 되어있냐를 의미한다.

## Updating the Rendered Element

**React Element는 immutable이다. 한 번 엘리먼트 만들면, 그것의 자식 또는 attribute를 변경할 수 없다. UI를 업데이트 할 수 있는 유일한 방법은 새로운 엘리먼트를 생성하는 것이다. 그리고 그것을 `ReactDOM.render()`에 통과시키는 것이다.**

## React Only Updates What's Necessary

**React DOM은 엘리먼트와 그 하위 엘리먼트를 이전 요소와 비교하여 DOM을 원하는 상태로 만드는 데 필요한 DOM 업데이트 만 적용합니다.** browser tool로 마지막 예제 조사하여 증명할 수 있다. (필요한 것만 업데이트 하기 증명). every tick마다 전체 UI 트리를 표현하는 엘리먼트를 생성할지라도, 오직 컨텐츠가 변경된 text node만 React DOM에 의해 업데이트 된다.

우리의 경험에서, 시간이 지남에 따라 UI를 변경하는 것이 아닌, UI가 주어진 순간에 보여져야하는 방식에 대해 생각하는 것이 버그를 없앨 수 있다.