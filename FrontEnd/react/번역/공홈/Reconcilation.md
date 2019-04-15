# Reconcilation

React diffing 알고리즘을 설명할거다. 충분히 퍼포먼스가 좋은 app으로 만들면서 컴포넌트 업데이트는 예측 가능해질거다.

## Motivation

next state or props update 될 떄, `render()` 함수는 React elements의 다른 tree를 리턴한다. 그리고 나서 React는 가장 최신 트리를 일치시키려고 UI 를 어떻게 효율적으로 업데이트할지 이해한다.

1개의 트리를 다른 트리로 변환하기 위한 최소 연산수를 생성하는 알고리즘이 있다. 그러나 이 알고리즘은 n^3 시간복잡도를 필요로 한다.(n은 트리에 있는 엘리먼트 갯수다.)

만약 React에서 이것을 사용한다면 1000개의 엘리먼트를 나타내는데 10억 번 비교가 필요하다. 이것은 굉장히 높은 비용이고 대신에 리액트는 다음 2가지 가정을 기반으로 O(n) 알고리즘으로 구현했다.

1. 다른 타입의 2개 엘리먼트는 다른 트리를 생성할 것이다.
2. 개발자는 `key` prop이 있는 다른 renders에서 어떤 자식요소가 안정적(stable)인지 알 수 있다.

## Diffing Algorithm

2개의 트리의 차이점을 알아볼 때, 리액트는 2개의 루트 엘리먼트를 비교한다. 이 비교 동작은 root elements의 타입에 따라 다르다.

### Elements Of Different Types

root elements가 다른 타입을 가질때마다, 리액트는 old tree를 버리고 처음부터 새로운 tree를 만든다.
Going from <a> to <img>, or from <Article> to <Comment>, or from <Button> to <div> - any of those will lead to a full rebuild.

tree를 버릴 때, old DOM nodes는 파괴된다. Component instances receive componentWillUnmount(). When building up a new tree, new DOM nodes are inserted into the DOM. Component instances receive componentWillMount() and then componentDidMount(). Any state associated with the old tree is lost.

root 아래의 어떤 컴포넌트든 unmount되고 해당 컴포넌트가 가진 state는 파괴돈다. 예를 들어, when diffing,

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

old `Counter`는 파괴될 것고 새로운 것이 remount된다.

### DOM elements of the same type

동일한 타입의 2개의 React DOM elements를 비교할 때, 리액트는 2가지 attributes를 보고, 동일한 기본 DOM node를 유지하고 변경된 attribute만 업데이트한다.

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

2개의 엘리먼트를 비교하여, 리액트는 `className`만 수정해야 할 것을 알고 있다.

When updating style, React also knows to update only the properties that changed. For example:

```js
<div style={{color: 'red', fontWeight: 'bold'}} />

<div style={{color: 'green', fontWeight: 'bold'}} />
```

When converting between these two elements, React knows to only modify the color style, not the fontWeight.

After handling the DOM node, React then recurses on the children.

DOM node를 처리한 후에, React는 children에서 recurse한다.

### Component Elements of the same type

동일 타입의 컴포넌트가 업데이트 할 떄, 인스턴스는 동일한 것으로 유지한다. 그래서 state는 렌더 간에 유지된다.
React는 기존 컴포넌트의 props를 새로운 엘리먼트와 매칭시키기 위해 업데이트한다. and calls componentWillReceiveProps() and componentWillUpdate() on the underlying instance.

`render()` 메서드는 호출되고 diff 알고리즘은 이전 결과와 새로운 결과를 recurse한다.

### Recursing On Children

기본적으로 DOM node의 자식에서 recursing할 떄, React는 자식 리스트를 동시에 이터레이트 하고 차이가 있을 때마다 변경(mutation)을 생성한다.

예컨대, children 마지막에 엘리먼트 추가할 때 2개의 트리 사이의 변환은 잘 수행된다.

```js
<ul>
  <li>first</li>
  <li>second</li>
</ul>

<ul>
  <li>first</li>
  <li>second</li>
  <li>third</li>
</ul>
```

React will match the two <li>first</li> trees, match the two <li>second</li> trees, and then insert the <li>third</li> tree.

만약 단순하게 구현하면, 처음에 element 추가하는 것은 성능상 좋지 않다. 예를 들어 2개의 트리간 변환은 제대로 작동하지 않는다.

```js
<ul>
  <li>Duke</li>
  <li>Villanova</li>
</ul>

<ul>
  <li>Connecticut</li>
  <li>Duke</li>
  <li>Villanova</li>
</ul>
```

리액트는 `<li>Duke</li>`, `<li>Villanova</li>` 하위트리를 그대로 유지할 수 있다는 사실을 깨닫지 않고 모든 child를 변경시킬 것이다. 이 비효율은 문제가 된다.

## Keys

위 이슈를 해결하기 위해, 리액트는 `key` attribute를 지원한다. key를 가지고 리액트는 기존 트리에서 subsequent 트리의 children과 매치시키기 위해 key를 이용한다. 예를 들어, `key`를 추가하는 것은 비효율적인 위 예제를 효율적인 tree conversion으로 만들 수 있다.

```js
<ul>
  <li key="2015">Duke</li>
  <li key="2016">Villanova</li>
</ul>

<ul>
  <li key="2014">Connecticut</li>
  <li key="2015">Duke</li>
  <li key="2016">Villanova</li>
</ul>
```

React는 `2014` key를 가진 엘리먼트가 새로운 건줄 알고 2015, 2016 엘리먼트만 옮기면 되는 것을 알게된다.

---

```js
<li key={item.id}>{item.name}</li>
```

키는 보통 hash로 생성하거나 서버에서 내려준 unique ID를 할당한다.

이 키는 globally unique할 필요는 없고 sibling간에 unique 하면 된다.

key를 배열 인덱스로 전달할 수 있는데, 재정렬 될일이 없으면 잘 작동한다.( 재정렬 하는 것이 굉장히 느리다. )

Reorders can also cause issues with component state when indexes are used as keys. Component instances are updated and reused based on their key. If the key is an index, moving an item changes it. As a result, component state for things like uncontrolled inputs can get mixed up and updated in unexpected ways.

[Here](https://reactjs.org/redirect-to-codepen/reconciliation/index-used-as-key) is an example of the issues that can be caused by using indexes as keys on CodePen, and here is an updated version of the same example showing how not using indexes as keys will fix these reordering, sorting, and prepending issues.

## Tradeoffs

It is important to remember that the reconciliation algorithm is an implementation detail. React could rerender the whole app on every action; the end result would be the same. Just to be clear, rerender in this context means calling render for all components, it doesn’t mean React will unmount and remount them. It will only apply the differences following the rules stated in the previous sections.

일반적인 use case를 더 빠르게 만들기 위해 heuristics을 정기적으로 수정하고 있다. 현재 구현에서 subtree가 형제 컴포넌트 간에 이동했다는 것을 표현할 수 있지만, 다른 어딘가로 이동한 것을 말할 수 없다. __알고리즘은 full subtree를 리렌더 할거다__

리액트는 heuristics에 의존하기 때문에, 만약 다음 가정이 충족되지 않는다면 퍼포먼스가 안좋게 될 것이다.

1. 알고리즘은 다른 컴포넌트 타입의 subtree를 매치시키려고 하지 않는다. 매우 유사한 output을 가진 2가지 컴포넌트 유형을 번갈아 사용하는 경우,  동일한 유형으로 만들 수 있다. 실제로 이 문제는 없었다.

2. Keys는 안정되고 있고, 예측 가능하고 unique 해야된다. Unstable Keys(`Math.random()`)은 많은 컴포넌트 인스턴스와 DOM node가 불필요하게 재생성되는 것을 유발한다. (이것은 퍼포먼스 저하와 child component의 상태를 잃어버리도록 만든다.)

## 요약

state나 props이 업데이트되면 render는 different tree를 리턴한다.
그리고 나서 React는 가장 최신 트리와 일치시키기 위해 UI를 어떻게 효율적으로 업데이트할지 이해한다.

__Diffing 알고리즘__

1. 다른 타입 엘리먼트
- old tree를 버리고 처음부터 새로운 tree를 만든다.

2. 동일 타입 DOM 엘리먼트

- 변경된 attribute만 수정한다. 그리고 _자식 노드를 recurse한다._

3. 동일타입 COmponent element

- 인스턴스는 동일한 것으로 유지. 그래서 state는 렌더간에 유지된다.
- React는 기존 컴포넌트의 props를 새로운 엘리먼트와 매칭시키기 위해 업데이트한다.
- render 메서드는 호출되고 diff 알고리즘은 이전 결과와 새로운 결과를 _recurse한다._

_recurse 한다 on Children_

- DOM node 자식에서 recurse할 때, React는 자식 리스트를 iterate 하고 차이가 있을 때마다 mutation한다.
- 이때 자식 노드의 형제 노드에 엘리먼트가 추가되면
  - 추가가 마지막에 엘리먼트를 추가하면 트리 변환 잘 진행됨.
  - 근데 맨 처음에 추가하게 되면 2개의 트리간 변환은 제대로 작동하지 않는다.
  - 왜냐하면 기존 알고리즘을 기반으로
  - 기존 하위트리 그대로 유지할 수 있다는 사실을 모르고 모든 child를 변경시킨다.
  - 이것은 굉장히 비효율

- 이것을 해결하기 위해 key attribute 지원.
- key를 지원하여 React가 새로운 key를 가진 엘리먼트를 알고, 기존 key를 가진 엘리먼트만 이동시키면 된다는 것을 알게됨.
