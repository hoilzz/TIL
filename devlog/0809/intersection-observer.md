# intersection observer

[Intersection Observer API from MDN](https://developer.mozilla.org/en-US/docs/Web/API/Intersection_Observer_API)

Intersection Observer API는 최상위 document viewport 혹은 조상 엘리먼트의 target 엘리먼트가 intersection(교차 되어있는지) 변경 여부를 비동기로 observe 하기 위한 방법을 제공한다.

---

유저가 페이지를 스크롤 할 떄, intersection 탐지 루틴은 스크롤 처리하는 동안에 꾸준히 발생한다.

IO API는 코드가 콜백 함수를 등록하게 한다. 모니터링을 원하는 엘리먼트가 다른 엘리먼트(or the viewport)에 enter or exit할 떄마다

## observe 하는 엘리먼트 타게팅하기

```js
var callback = function(entries, observer) {
  entries.forEach(entry => {
    // Each entry describes an intersection change for one observed
    // target element:
    //   entry.boundingClientRect
    //   entry.intersectionRatio
    //   entry.intersectionRect
    //   entry.isIntersecting
    //   entry.rootBounds
    //   entry.target
    //   entry.time
  });
};
```

콜백은 main thread에서 실행되는 것을 알아두자. 그래서 가능한 빨리 동작해야한다. 만약 시간이 소요되는 작업이라면, [window.requestIdleCallback()](https://developer.mozilla.org/en-US/docs/Web/API/Window/requestIdleCallback)을 사용하자.

## thresholds

타겟 엘리먼트가 보이는 정도에 대한 무한 변경을 모두 리포팅하는 것 대신에, IO API는 **threshold** 를 사용한다. observer를 생성할 떄, 보이는 타겟 엘리먼트늬 노출 퍼센트를 1개 이상의 숫자 값으로 제공한다. API는 **threshold 를 넘는 visibility에 대한 변경만 리포트** 한다.

예를 들어, target의 visibility가 각 25% 배수들의 이상 혹은 이하가 될 때마다 알림 받고 싶으면, `[0, 0.25, 0.5, 0.75, 1]` 배열을 통해 threshold list를 명시할 수 있다. `isIntersecting` 프로퍼티를 통해 more visible과 less visible을 구분할 수 있다.

[threshold 예제](https://codepen.io/pen/?&editable=true)

## Clipping and the intersection rectangle

브라우저는 다음과 같이 마지막 intersection rectangle을 계산한다. 정확히 intersection이 언제 일어나는지 알기 위해 아래 스텝을 이해하는게 도움 될거다.

1. 타겟 엘리먼트의 바운딩 사각형 (이것은, 엘리먼트를 구성하는 모든 컴포넌트의 바운딩 박스를 완전히 감싸는 가장 작은 사각형이다.)은 타겟에서 getBoundingClientRect()를 호출하여 얻는다. 이것은 가장큰 intersection 사각형일 거다. 남은 스텝은 intersect되지 않는 부분을 제거할 것이다.

2. 타겟의 바로 위 부모 블록에서 시작하여 바깥쪽으로 이동하면 각 블락의 clipping(이 있는 경우) intersection 사각형에 적용된다.

## Intersection change callbacks

루트 엘리먼트 내에서 보이는 target element들이 visibility thresholds 중 1개를 초과할 떄, IO 객체의 콜백이 수행된다. intersection된 threshold 값마다, 콜백은 `IOEntry` objects 배열과 IO 객체 자체에 대한 참조를 input으로 받는다

## 헷갈리는 것들

- entry.intersecting이 false가 되기 위해서는 entry.intersecting이 한번이라도 true여야 한다.
