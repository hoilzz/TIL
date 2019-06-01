# 리마운트를 막아보자!

[https://codesandbox.io/s/unmount-test-with-keys-sl0o3](https://codesandbox.io/s/unmount-test-with-keys-sl0o3)

회사에서 리마운트 될 필요가 없는 컴포넌트가 있는데 자꾸 리마운트가 되서..

Test1 컴포넌트는 리마운트 될 필요가 없는 얘다. 리액트 diff 알고리즘상 Test1은 Test2가 append되서 새로운 컴포넌트로 판단된다.
그래서 key를 이용하여 얘는 동일 컴포넌트입니다? 라는걸 알려줘서 리마운트 안되도록 해결.

사실 key가 동일 컴포넌트입니다? 라고 말하는 건지 모르겠지만 일단 적어놓고 나중에 조사해야지..

### 요약의 요약

Diff 알고리즘을 O(N^3)에서 O(N)으로 줄이기 위한 2가지 가정

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성한다
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 리액트에게 알려줄 수 있다.

3. 2개의 다른 타입 엘리먼트

- 루트 엘리먼트가 다를 경우

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

기존 컴포넌트 언마운트되고 새로운 컴포넌트 마운트되서 DOM이 추가된다.(기존 컴포넌트의 상태 사라짐)

- (반대로) 동일한 타입의 DOM 엘리먼트

DOM노드를 유지하며 (리마운트 하지 않고) 변경된 속성만 업데이트 한다.(이로 인해 기존 컴포넌트 상태 유지)

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

2. key를 이용하여 stable한 컴포넌트 알려주기

리액트는 뒤에 추가되는 컴포넌트에 대해서만 효율적으로 동작한다.
즉, 1,2번 컴포넌트 뒤에 3번 컴포넌트가 추가된 경우
"1,2번 컴포넌트 뒤에 3번이 추가됐으니까 1,2번은 그대로 두고 3번 컴포넌트만 추가하면 되구나"라는 걸 안다.

하지만 1번 컴포넌트 앞에 3번 컴포넌트가 추가된 경우 모든 트리를 언마운트 후 리마운트 한다.
이를 해결하기 위해 key를 이용한다.

- key는 가급적 유니크 ID를 이용
  - 재정렬 할 컴포넌트가 아니라면 인덱스로 사용해도됨.
- 만약 재정렬되는 컴포넌트에 index를 사용할 경우, 문제 발생한다.
  - 문제는 컴포넌트 인스턴스는 키에 따라 업데이트되거나 리마운트 되거나 재사용되기 때문이다.

## FAQ

Q. Diffing 알고리즘이란?
A. 2개의 트리의 차이점을 비교하는거다. 리액트는 먼저 2개의 root element를 비교한다. diffing 동작은 루트 엘리먼트의 타입에 따라 다르다.

---

## React의 Diff 알고리즘 요약

디프 알고리즘을 알고나면 컴포넌트 업데이트가 예측 가능하다.

리액트 해본사람은 다 알고 있는 사실은

state나 prop의 업데이트마다, `render()` 함수는 다른 리액트 엘리먼트 트리를 리턴할 것이라는 점이다.

그러고나서 리액트는 가장 최근의 트리와 일치하도록 UI를 효율적으로 업데이트하는 방법을 찾는다.

UI를 효율적으로 업데이트하기 위해 (하나의 트리를 다른 트리로 변환하기 위해) 최소 O(n^3)이 소요된다.
[the state of art algorithm](https://grfia.dlsi.ua.es/ml/algorithms/references/editsurvey_bille.pdf)

리액트에서는 다음 2가지 가정을 기반으로 O(n)으로 개선했다.

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성할 것이다.
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 알려줄 수 있다.

---

2개의 트리를 diffing할 때, 리액트는 2개의 루트 엘리먼트를 비교한다.
이 때, 루트 엘리먼트의 타입에 따라 렌더링 동작이 달라진다.

1. 다른 타입의 엘리먼트

루트 엘리먼트가 다를 때, 기존 트리를 없애고 처음부터 새 트리를 만든다.
<a> -> <img>, <Article> -> <Comment>

_과정을 디테일하게 보자.(라이프사이클로)_

트리를 제거할 때, 기존 DOM node는 파괴된다.

1. 즉, Component instance는 언마운트되고

- componentWillUnmount()

2. new tree가 빌드될 때, new DOM node가 새로 추가된다.
3. component instance를 다시 마운트되고, 기존 트리의 상태는 사라진다.

- componentWillMount, componentDidMount

아래와 같은 컴포넌트는 unmount되고 상태도 제거된다. 예를 들어 아래 diffing 할 때,
`Counter`를 파괴할 것이고 새로운 것을 remount할 것이다.

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

2. 동일 타입의 DOM element

동일 타입의 React DOM element를 비교할 때, attributes를 보고, 동일한 DOM 노드를 유지하며

**변경된 속성만 업데이트 한다.**

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

React는 2개 엘리먼트를 비교하여, 동일 타입 DOM 노드인것을 알고
attributes를 보고, 동일 DOM노드에서 `className`만 수정한다.

```js
<div style={{color: 'red', fontWeight: 'bold'}} />

<div style={{color: 'green', fontWeight: 'bold'}} />
```

위 상황에서 React는 color만 수정하면 된다는 것을 안다.

DOM 노드를 처리한 후에, React는 자식들에 대해 동일하게 순환한다.

_과정을 디테일하게 보자.(라이프사이클로)_

컴포넌트가 동일타입인 경우에 업데이트될 때, 인스턴스는 동일 하므로 상태는 렌더 간에 유지된다.

1. new element와 일치 시키기 위해 prop을 업데이트한다.

- componentWillReceiveProps, componentWillUpdate를 수행한다.

2. 렌더 메서드는 호출되고, diff 알고리즘은 이전결과와 새로운 결과에 대해 재귀호출한다.

## Recursing On Children

기본적으로, DOM node의 자식을 순환할 때, 리액트는 동시에 자식 리스트를 반복 실행하고 차이가 있을 때마다 변경을 생성한다.

예컨대 다음과 같이 자식의 마지막에 엘리먼트를 추가할 때는 2개의 트리간 전환이 잘 된다.

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

React는 1,2번째 트리를 매치시킬 것이고, 3번째 트리만 삽입할 것이다.

근데, 자식들 맨 앞에 추가하는 것은 비효율 문제가 발생한다.

왜냐하면 리액트는 하위 트리를 그대로 유지해도 된다는 사실을 모른다. **즉, 기존 트리가 언마운트 되고 새로운 트리를 생성한다.**

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

## 해결책은 Keys

이 문제를 해결하기 위해 `key` attribute를 지원한다. 리액트는 원래 트리의 자식과 subsequent(후속) 트리의 자식을 매치 시키기 위해 key를 이용한다.

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

키를 이용하여 리액트는 2014가 새로운 엘리먼트인지 판단할 수 있다.
키를 이용하여 기존트리와 비교하기 때문에 unique한 ID를 가져야한다. unique ID가 아니라면 기존 트리와 동일한 엘리먼트인지 판단할 수 없다. 이 떄 키는 글로벌 스코프 내에서 고유한 값이 아닌 형제 사이에서 고유하면 된다.

사실 재정렬 할게 아니라면 unique한 ID가 아닌 index를 전달해도 된다.

index를 키로 가진 컴포넌트들을 재정렬시에 문제가 발생한다. **컴포넌트 인스턴스는 `Key`에 따라 업데이트되고 재사용된다.** **key가 인덱스일 경우 item을 움직이면 해당 아이템이 변경된다. 왜냐하면 item이 움직인 이상 index도 변경되기 때문이다**
결과적으로, uncontrolled inputs과 같은 것의 컴포넌트 상태가 섞이고 예상치 못한 방법으로 업데이트 된다. [index as key](https://codepen.io/pen?&editable=true&editors=0010) 이 예제를 보면 uncontrolled component가 key기반으로 상태가 고정되는 것을 볼 수 있다.

## TradeOff

reconcilation 알고리즘의 디테일한 구현을 기억하는 것은 중요하다. 리액트는 every action 마다 전체 앱을 리렌더할 수 있다; 최종 결과는 동일하다. 명확하게 하기 위해 이번 맥락에서 rerender는 모던 컴포넌트에 대해 `render`를 호출하는 것을 의미한다. 이것은 React가 모든 컴포넌트를 unmount하고 remount 한다는 말은 아니다. 앞에서 말한 규칙에 따라 차이가 있는곳에만 unmount-remount를 거칠 것이다.

리액트는 heuristics에 의존하기 때문에, 만약 몇가지 다음 2가지 가정이 충족되지 않는다면 성능이 저하된다.

1. 알고리즘은 다른 컴포넌트 타입의 subtree를 매치시키려고 시도하지 않을 것이다. 만약 매우 비슷한 output을 가지는 2가지 컴포넌트 타입들을 번갈아 사용하는 경우, 같은 타입으로 만들 수 있다. 실제로, 이것이 문제가 되지 않았다.

2. Key는 안정적이고 예측가능하며 고유해야 한다. `Math.random()`을 이용해 생성된 키와 같은 불안정한 키는 많은 컴포넌트 인스턴스와 DOM노드가 불필요하게 다시 작성되어 하우 컴포넌트의 성능 저하 및 state를 잃어버릴 수 있다.

### 요약의 요약

Diff 알고리즘을 O(N^3)에서 O(N)으로 줄이기 위한 2가지 가정

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성한다
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 리액트에게 알려줄 수 있다.

3. 2개의 다른 타입 엘리먼트

- 루트 엘리먼트가 다를 경우

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

기존 컴포넌트 언마운트되고 새로운 컴포넌트 마운트되서 DOM이 추가된다.(기존 컴포넌트의 상태 사라짐)

- (반대로) 동일한 타입의 DOM 엘리먼트

DOM노드를 유지하며 (리마운트 하지 않고) 변경된 속성만 업데이트 한다.(이로 인해 기존 컴포넌트 상태 유지)

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

2. key를 이용하여 stable한 컴포넌트 알려주기

리액트는 뒤에 추가되는 컴포넌트에 대해서만 효율적으로 동작한다.
즉, 1,2번 컴포넌트 뒤에 3번 컴포넌트가 추가된 경우
"1,2번 컴포넌트 뒤에 3번이 추가됐으니까 1,2번은 그대로 두고 3번 컴포넌트만 추가하면 되구나"라는 걸 안다.

하지만 1번 컴포넌트 앞에 3번 컴포넌트가 추가된 경우 모든 트리를 언마운트 후 리마운트 한다.
이를 해결하기 위해 key를 이용한다.

- key는 가급적 유니크 ID를 이용
  - 재정렬 할 컴포넌트가 아니라면 인덱스로 사용해도됨.
- 만약 재정렬되는 컴포넌트에 index를 사용할 경우, 문제 발생한다.
  - 문제는 컴포넌트 인스턴스는 키에 따라 업데이트되거나 리마운트 되거나 재사용되기 때문이다.

## FAQ

Q. Diffing 알고리즘이란?
A. 2개의 트리의 차이점을 비교하는거다. 리액트는 먼저 2개의 root element를 비교한다. diffing 동작은 루트 엘리먼트의 타입에 따라 다르다.

---

## React의 Diff 알고리즘 요약

디프 알고리즘을 알고나면 컴포넌트 업데이트가 예측 가능하다.

리액트 해본사람은 다 알고 있는 사실은

state나 prop의 업데이트마다, `render()` 함수는 다른 리액트 엘리먼트 트리를 리턴할 것이라는 점이다.

그러고나서 리액트는 가장 최근의 트리와 일치하도록 UI를 효율적으로 업데이트하는 방법을 찾는다.

UI를 효율적으로 업데이트하기 위해 (하나의 트리를 다른 트리로 변환하기 위해) 최소 O(n^3)이 소요된다.
[the state of art algorithm](https://grfia.dlsi.ua.es/ml/algorithms/references/editsurvey_bille.pdf)

리액트에서는 다음 2가지 가정을 기반으로 O(n)으로 개선했다.

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성할 것이다.
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 알려줄 수 있다.

---

2개의 트리를 diffing할 때, 리액트는 2개의 루트 엘리먼트를 비교한다.
이 때, 루트 엘리먼트의 타입에 따라 렌더링 동작이 달라진다.

1. 다른 타입의 엘리먼트

루트 엘리먼트가 다를 때, 기존 트리를 없애고 처음부터 새 트리를 만든다.
<a> -> <img>, <Article> -> <Comment>

_과정을 디테일하게 보자.(라이프사이클로)_

트리를 제거할 때, 기존 DOM node는 파괴된다.

1. 즉, Component instance는 언마운트되고

- componentWillUnmount()

2. new tree가 빌드될 때, new DOM node가 새로 추가된다.
3. component instance를 다시 마운트되고, 기존 트리의 상태는 사라진다.

- componentWillMount, componentDidMount

아래와 같은 컴포넌트는 unmount되고 상태도 제거된다. 예를 들어 아래 diffing 할 때,
`Counter`를 파괴할 것이고 새로운 것을 remount할 것이다.

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

2. 동일 타입의 DOM element

동일 타입의 React DOM element를 비교할 때, attributes를 보고, 동일한 DOM 노드를 유지하며

**변경된 속성만 업데이트 한다.**

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

React는 2개 엘리먼트를 비교하여, 동일 타입 DOM 노드인것을 알고
attributes를 보고, 동일 DOM노드에서 `className`만 수정한다.

```js
<div style={{color: 'red', fontWeight: 'bold'}} />

<div style={{color: 'green', fontWeight: 'bold'}} />
```

위 상황에서 React는 color만 수정하면 된다는 것을 안다.

DOM 노드를 처리한 후에, React는 자식들에 대해 동일하게 순환한다.

_과정을 디테일하게 보자.(라이프사이클로)_

컴포넌트가 동일타입인 경우에 업데이트될 때, 인스턴스는 동일 하므로 상태는 렌더 간에 유지된다.

1. new element와 일치 시키기 위해 prop을 업데이트한다.

- componentWillReceiveProps, componentWillUpdate를 수행한다.

2. 렌더 메서드는 호출되고, diff 알고리즘은 이전결과와 새로운 결과에 대해 재귀호출한다.

## Recursing On Children

기본적으로, DOM node의 자식을 순환할 때, 리액트는 동시에 자식 리스트를 반복 실행하고 차이가 있을 때마다 변경을 생성한다.

예컨대 다음과 같이 자식의 마지막에 엘리먼트를 추가할 때는 2개의 트리간 전환이 잘 된다.

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

React는 1,2번째 트리를 매치시킬 것이고, 3번째 트리만 삽입할 것이다.

근데, 자식들 맨 앞에 추가하는 것은 비효율 문제가 발생한다.

왜냐하면 리액트는 하위 트리를 그대로 유지해도 된다는 사실을 모른다. **즉, 기존 트리가 언마운트 되고 새로운 트리를 생성한다.**

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

## 해결책은 Keys

이 문제를 해결하기 위해 `key` attribute를 지원한다. 리액트는 원래 트리의 자식과 subsequent(후속) 트리의 자식을 매치 시키기 위해 key를 이용한다.

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

키를 이용하여 리액트는 2014가 새로운 엘리먼트인지 판단할 수 있다.
키를 이용하여 기존트리와 비교하기 때문에 unique한 ID를 가져야한다. unique ID가 아니라면 기존 트리와 동일한 엘리먼트인지 판단할 수 없다. 이 떄 키는 글로벌 스코프 내에서 고유한 값이 아닌 형제 사이에서 고유하면 된다.

사실 재정렬 할게 아니라면 unique한 ID가 아닌 index를 전달해도 된다.

index를 키로 가진 컴포넌트들을 재정렬시에 문제가 발생한다. **컴포넌트 인스턴스는 `Key`에 따라 업데이트되고 재사용된다.** **key가 인덱스일 경우 item을 움직이면 해당 아이템이 변경된다. 왜냐하면 item이 움직인 이상 index도 변경되기 때문이다**
결과적으로, uncontrolled inputs과 같은 것의 컴포넌트 상태가 섞이고 예상치 못한 방법으로 업데이트 된다. [index as key](https://codepen.io/pen?&editable=true&editors=0010) 이 예제를 보면 uncontrolled component가 key기반으로 상태가 고정되는 것을 볼 수 있다.

## TradeOff

reconcilation 알고리즘의 디테일한 구현을 기억하는 것은 중요하다. 리액트는 every action 마다 전체 앱을 리렌더할 수 있다; 최종 결과는 동일하다. 명확하게 하기 위해 이번 맥락에서 rerender는 모던 컴포넌트에 대해 `render`를 호출하는 것을 의미한다. 이것은 React가 모든 컴포넌트를 unmount하고 remount 한다는 말은 아니다. 앞에서 말한 규칙에 따라 차이가 있는곳에만 unmount-remount를 거칠 것이다.

리액트는 heuristics에 의존하기 때문에, 만약 몇가지 다음 2가지 가정이 충족되지 않는다면 성능이 저하된다.

1. 알고리즘은 다른 컴포넌트 타입의 subtree를 매치시키려고 시도하지 않을 것이다. 만약 매우 비슷한 output을 가지는 2가지 컴포넌트 타입들을 번갈아 사용하는 경우, 같은 타입으로 만들 수 있다. 실제로, 이것이 문제가 되지 않았다.

2. Key는 안정적이고 예측가능하며 고유해야 한다. `Math.random()`을 이용해 생성된 키와 같은 불안정한 키는 많은 컴포넌트 인스턴스와 DOM노드가 불필요하게 다시 작성되어 하우 컴포넌트의 성능 저하 및 state를 잃어버릴 수 있다.

### 요약의 요약

Diff 알고리즘을 O(N^3)에서 O(N)으로 줄이기 위한 2가지 가정

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성한다
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 리액트에게 알려줄 수 있다.

3. 2개의 다른 타입 엘리먼트

- 루트 엘리먼트가 다를 경우

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

기존 컴포넌트 언마운트되고 새로운 컴포넌트 마운트되서 DOM이 추가된다.(기존 컴포넌트의 상태 사라짐)

- (반대로) 동일한 타입의 DOM 엘리먼트

DOM노드를 유지하며 (리마운트 하지 않고) 변경된 속성만 업데이트 한다.(이로 인해 기존 컴포넌트 상태 유지)

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

2. key를 이용하여 stable한 컴포넌트 알려주기

리액트는 뒤에 추가되는 컴포넌트에 대해서만 효율적으로 동작한다.
즉, 1,2번 컴포넌트 뒤에 3번 컴포넌트가 추가된 경우
"1,2번 컴포넌트 뒤에 3번이 추가됐으니까 1,2번은 그대로 두고 3번 컴포넌트만 추가하면 되구나"라는 걸 안다.

하지만 1번 컴포넌트 앞에 3번 컴포넌트가 추가된 경우 모든 트리를 언마운트 후 리마운트 한다.
이를 해결하기 위해 key를 이용한다.

- key는 가급적 유니크 ID를 이용
  - 재정렬 할 컴포넌트가 아니라면 인덱스로 사용해도됨.
- 만약 재정렬되는 컴포넌트에 index를 사용할 경우, 문제 발생한다.
  - 문제는 컴포넌트 인스턴스는 키에 따라 업데이트되거나 리마운트 되거나 재사용되기 때문이다.

## FAQ

Q. Diffing 알고리즘이란?
A. 2개의 트리의 차이점을 비교하는거다. 리액트는 먼저 2개의 root element를 비교한다. diffing 동작은 루트 엘리먼트의 타입에 따라 다르다.

---

## React의 Diff 알고리즘 요약

디프 알고리즘을 알고나면 컴포넌트 업데이트가 예측 가능하다.

리액트 해본사람은 다 알고 있는 사실은

state나 prop의 업데이트마다, `render()` 함수는 다른 리액트 엘리먼트 트리를 리턴할 것이라는 점이다.

그러고나서 리액트는 가장 최근의 트리와 일치하도록 UI를 효율적으로 업데이트하는 방법을 찾는다.

UI를 효율적으로 업데이트하기 위해 (하나의 트리를 다른 트리로 변환하기 위해) 최소 O(n^3)이 소요된다.
[the state of art algorithm](https://grfia.dlsi.ua.es/ml/algorithms/references/editsurvey_bille.pdf)

리액트에서는 다음 2가지 가정을 기반으로 O(n)으로 개선했다.

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성할 것이다.
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 알려줄 수 있다.

---

2개의 트리를 diffing할 때, 리액트는 2개의 루트 엘리먼트를 비교한다.
이 때, 루트 엘리먼트의 타입에 따라 렌더링 동작이 달라진다.

1. 다른 타입의 엘리먼트

루트 엘리먼트가 다를 때, 기존 트리를 없애고 처음부터 새 트리를 만든다.
<a> -> <img>, <Article> -> <Comment>

_과정을 디테일하게 보자.(라이프사이클로)_

트리를 제거할 때, 기존 DOM node는 파괴된다.

1. 즉, Component instance는 언마운트되고

- componentWillUnmount()

2. new tree가 빌드될 때, new DOM node가 새로 추가된다.
3. component instance를 다시 마운트되고, 기존 트리의 상태는 사라진다.

- componentWillMount, componentDidMount

아래와 같은 컴포넌트는 unmount되고 상태도 제거된다. 예를 들어 아래 diffing 할 때,
`Counter`를 파괴할 것이고 새로운 것을 remount할 것이다.

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

2. 동일 타입의 DOM element

동일 타입의 React DOM element를 비교할 때, attributes를 보고, 동일한 DOM 노드를 유지하며

**변경된 속성만 업데이트 한다.**

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

React는 2개 엘리먼트를 비교하여, 동일 타입 DOM 노드인것을 알고
attributes를 보고, 동일 DOM노드에서 `className`만 수정한다.

```js
<div style={{color: 'red', fontWeight: 'bold'}} />

<div style={{color: 'green', fontWeight: 'bold'}} />
```

위 상황에서 React는 color만 수정하면 된다는 것을 안다.

DOM 노드를 처리한 후에, React는 자식들에 대해 동일하게 순환한다.

_과정을 디테일하게 보자.(라이프사이클로)_

컴포넌트가 동일타입인 경우에 업데이트될 때, 인스턴스는 동일 하므로 상태는 렌더 간에 유지된다.

1. new element와 일치 시키기 위해 prop을 업데이트한다.

- componentWillReceiveProps, componentWillUpdate를 수행한다.

2. 렌더 메서드는 호출되고, diff 알고리즘은 이전결과와 새로운 결과에 대해 재귀호출한다.

## Recursing On Children

기본적으로, DOM node의 자식을 순환할 때, 리액트는 동시에 자식 리스트를 반복 실행하고 차이가 있을 때마다 변경을 생성한다.

예컨대 다음과 같이 자식의 마지막에 엘리먼트를 추가할 때는 2개의 트리간 전환이 잘 된다.

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

React는 1,2번째 트리를 매치시킬 것이고, 3번째 트리만 삽입할 것이다.

근데, 자식들 맨 앞에 추가하는 것은 비효율 문제가 발생한다.

왜냐하면 리액트는 하위 트리를 그대로 유지해도 된다는 사실을 모른다. **즉, 기존 트리가 언마운트 되고 새로운 트리를 생성한다.**

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

## 해결책은 Keys

이 문제를 해결하기 위해 `key` attribute를 지원한다. 리액트는 원래 트리의 자식과 subsequent(후속) 트리의 자식을 매치 시키기 위해 key를 이용한다.

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

키를 이용하여 리액트는 2014가 새로운 엘리먼트인지 판단할 수 있다.
키를 이용하여 기존트리와 비교하기 때문에 unique한 ID를 가져야한다. unique ID가 아니라면 기존 트리와 동일한 엘리먼트인지 판단할 수 없다. 이 떄 키는 글로벌 스코프 내에서 고유한 값이 아닌 형제 사이에서 고유하면 된다.

사실 재정렬 할게 아니라면 unique한 ID가 아닌 index를 전달해도 된다.

index를 키로 가진 컴포넌트들을 재정렬시에 문제가 발생한다. **컴포넌트 인스턴스는 `Key`에 따라 업데이트되고 재사용된다.** **key가 인덱스일 경우 item을 움직이면 해당 아이템이 변경된다. 왜냐하면 item이 움직인 이상 index도 변경되기 때문이다**
결과적으로, uncontrolled inputs과 같은 것의 컴포넌트 상태가 섞이고 예상치 못한 방법으로 업데이트 된다. [index as key](https://codepen.io/pen?&editable=true&editors=0010) 이 예제를 보면 uncontrolled component가 key기반으로 상태가 고정되는 것을 볼 수 있다.

## TradeOff

reconcilation 알고리즘의 디테일한 구현을 기억하는 것은 중요하다. 리액트는 every action 마다 전체 앱을 리렌더할 수 있다; 최종 결과는 동일하다. 명확하게 하기 위해 이번 맥락에서 rerender는 모던 컴포넌트에 대해 `render`를 호출하는 것을 의미한다. 이것은 React가 모든 컴포넌트를 unmount하고 remount 한다는 말은 아니다. 앞에서 말한 규칙에 따라 차이가 있는곳에만 unmount-remount를 거칠 것이다.

리액트는 heuristics에 의존하기 때문에, 만약 몇가지 다음 2가지 가정이 충족되지 않는다면 성능이 저하된다.

1. 알고리즘은 다른 컴포넌트 타입의 subtree를 매치시키려고 시도하지 않을 것이다. 만약 매우 비슷한 output을 가지는 2가지 컴포넌트 타입들을 번갈아 사용하는 경우, 같은 타입으로 만들 수 있다. 실제로, 이것이 문제가 되지 않았다.

2. Key는 안정적이고 예측가능하며 고유해야 한다. `Math.random()`을 이용해 생성된 키와 같은 불안정한 키는 많은 컴포넌트 인스턴스와 DOM노드가 불필요하게 다시 작성되어 하우 컴포넌트의 성능 저하 및 state를 잃어버릴 수 있다.

### 요약의 요약

Diff 알고리즘을 O(N^3)에서 O(N)으로 줄이기 위한 2가지 가정

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성한다
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 리액트에게 알려줄 수 있다.

3. 2개의 다른 타입 엘리먼트

- 루트 엘리먼트가 다를 경우

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

기존 컴포넌트 언마운트되고 새로운 컴포넌트 마운트되서 DOM이 추가된다.(기존 컴포넌트의 상태 사라짐)

- (반대로) 동일한 타입의 DOM 엘리먼트

DOM노드를 유지하며 (리마운트 하지 않고) 변경된 속성만 업데이트 한다.(이로 인해 기존 컴포넌트 상태 유지)

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

2. key를 이용하여 stable한 컴포넌트 알려주기

리액트는 뒤에 추가되는 컴포넌트에 대해서만 효율적으로 동작한다.
즉, 1,2번 컴포넌트 뒤에 3번 컴포넌트가 추가된 경우
"1,2번 컴포넌트 뒤에 3번이 추가됐으니까 1,2번은 그대로 두고 3번 컴포넌트만 추가하면 되구나"라는 걸 안다.

하지만 1번 컴포넌트 앞에 3번 컴포넌트가 추가된 경우 모든 트리를 언마운트 후 리마운트 한다.
이를 해결하기 위해 key를 이용한다.

- key는 가급적 유니크 ID를 이용
  - 재정렬 할 컴포넌트가 아니라면 인덱스로 사용해도됨.
- 만약 재정렬되는 컴포넌트에 index를 사용할 경우, 문제 발생한다.
  - 문제는 컴포넌트 인스턴스는 키에 따라 업데이트되거나 리마운트 되거나 재사용되기 때문이다.

## FAQ

Q. Diffing 알고리즘이란?
A. 2개의 트리의 차이점을 비교하는거다. 리액트는 먼저 2개의 root element를 비교한다. diffing 동작은 루트 엘리먼트의 타입에 따라 다르다.

---

## React의 Diff 알고리즘 요약

디프 알고리즘을 알고나면 컴포넌트 업데이트가 예측 가능하다.

리액트 해본사람은 다 알고 있는 사실은

state나 prop의 업데이트마다, `render()` 함수는 다른 리액트 엘리먼트 트리를 리턴할 것이라는 점이다.

그러고나서 리액트는 가장 최근의 트리와 일치하도록 UI를 효율적으로 업데이트하는 방법을 찾는다.

UI를 효율적으로 업데이트하기 위해 (하나의 트리를 다른 트리로 변환하기 위해) 최소 O(n^3)이 소요된다.
[the state of art algorithm](https://grfia.dlsi.ua.es/ml/algorithms/references/editsurvey_bille.pdf)

리액트에서는 다음 2가지 가정을 기반으로 O(n)으로 개선했다.

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성할 것이다.
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 알려줄 수 있다.

---

2개의 트리를 diffing할 때, 리액트는 2개의 루트 엘리먼트를 비교한다.
이 때, 루트 엘리먼트의 타입에 따라 렌더링 동작이 달라진다.

1. 다른 타입의 엘리먼트

루트 엘리먼트가 다를 때, 기존 트리를 없애고 처음부터 새 트리를 만든다.
<a> -> <img>, <Article> -> <Comment>

_과정을 디테일하게 보자.(라이프사이클로)_

트리를 제거할 때, 기존 DOM node는 파괴된다.

1. 즉, Component instance는 언마운트되고

- componentWillUnmount()

2. new tree가 빌드될 때, new DOM node가 새로 추가된다.
3. component instance를 다시 마운트되고, 기존 트리의 상태는 사라진다.

- componentWillMount, componentDidMount

아래와 같은 컴포넌트는 unmount되고 상태도 제거된다. 예를 들어 아래 diffing 할 때,
`Counter`를 파괴할 것이고 새로운 것을 remount할 것이다.

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

2. 동일 타입의 DOM element

동일 타입의 React DOM element를 비교할 때, attributes를 보고, 동일한 DOM 노드를 유지하며

**변경된 속성만 업데이트 한다.**

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

React는 2개 엘리먼트를 비교하여, 동일 타입 DOM 노드인것을 알고
attributes를 보고, 동일 DOM노드에서 `className`만 수정한다.

```js
<div style={{color: 'red', fontWeight: 'bold'}} />

<div style={{color: 'green', fontWeight: 'bold'}} />
```

위 상황에서 React는 color만 수정하면 된다는 것을 안다.

DOM 노드를 처리한 후에, React는 자식들에 대해 동일하게 순환한다.

_과정을 디테일하게 보자.(라이프사이클로)_

컴포넌트가 동일타입인 경우에 업데이트될 때, 인스턴스는 동일 하므로 상태는 렌더 간에 유지된다.

1. new element와 일치 시키기 위해 prop을 업데이트한다.

- componentWillReceiveProps, componentWillUpdate를 수행한다.

2. 렌더 메서드는 호출되고, diff 알고리즘은 이전결과와 새로운 결과에 대해 재귀호출한다.

## Recursing On Children

기본적으로, DOM node의 자식을 순환할 때, 리액트는 동시에 자식 리스트를 반복 실행하고 차이가 있을 때마다 변경을 생성한다.

예컨대 다음과 같이 자식의 마지막에 엘리먼트를 추가할 때는 2개의 트리간 전환이 잘 된다.

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

React는 1,2번째 트리를 매치시킬 것이고, 3번째 트리만 삽입할 것이다.

근데, 자식들 맨 앞에 추가하는 것은 비효율 문제가 발생한다.

왜냐하면 리액트는 하위 트리를 그대로 유지해도 된다는 사실을 모른다. **즉, 기존 트리가 언마운트 되고 새로운 트리를 생성한다.**

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

## 해결책은 Keys

이 문제를 해결하기 위해 `key` attribute를 지원한다. 리액트는 원래 트리의 자식과 subsequent(후속) 트리의 자식을 매치 시키기 위해 key를 이용한다.

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

키를 이용하여 리액트는 2014가 새로운 엘리먼트인지 판단할 수 있다.
키를 이용하여 기존트리와 비교하기 때문에 unique한 ID를 가져야한다. unique ID가 아니라면 기존 트리와 동일한 엘리먼트인지 판단할 수 없다. 이 떄 키는 글로벌 스코프 내에서 고유한 값이 아닌 형제 사이에서 고유하면 된다.

사실 재정렬 할게 아니라면 unique한 ID가 아닌 index를 전달해도 된다.

index를 키로 가진 컴포넌트들을 재정렬시에 문제가 발생한다. **컴포넌트 인스턴스는 `Key`에 따라 업데이트되고 재사용된다.** **key가 인덱스일 경우 item을 움직이면 해당 아이템이 변경된다. 왜냐하면 item이 움직인 이상 index도 변경되기 때문이다**
결과적으로, uncontrolled inputs과 같은 것의 컴포넌트 상태가 섞이고 예상치 못한 방법으로 업데이트 된다. [index as key](https://codepen.io/pen?&editable=true&editors=0010) 이 예제를 보면 uncontrolled component가 key기반으로 상태가 고정되는 것을 볼 수 있다.

## TradeOff

reconcilation 알고리즘의 디테일한 구현을 기억하는 것은 중요하다. 리액트는 every action 마다 전체 앱을 리렌더할 수 있다; 최종 결과는 동일하다. 명확하게 하기 위해 이번 맥락에서 rerender는 모던 컴포넌트에 대해 `render`를 호출하는 것을 의미한다. 이것은 React가 모든 컴포넌트를 unmount하고 remount 한다는 말은 아니다. 앞에서 말한 규칙에 따라 차이가 있는곳에만 unmount-remount를 거칠 것이다.

리액트는 heuristics에 의존하기 때문에, 만약 몇가지 다음 2가지 가정이 충족되지 않는다면 성능이 저하된다.

1. 알고리즘은 다른 컴포넌트 타입의 subtree를 매치시키려고 시도하지 않을 것이다. 만약 매우 비슷한 output을 가지는 2가지 컴포넌트 타입들을 번갈아 사용하는 경우, 같은 타입으로 만들 수 있다. 실제로, 이것이 문제가 되지 않았다.

2. Key는 안정적이고 예측가능하며 고유해야 한다. `Math.random()`을 이용해 생성된 키와 같은 불안정한 키는 많은 컴포넌트 인스턴스와 DOM노드가 불필요하게 다시 작성되어 하우 컴포넌트의 성능 저하 및 state를 잃어버릴 수 있다.

### 요약의 요약

Diff 알고리즘을 O(N^3)에서 O(N)으로 줄이기 위한 2가지 가정

1. 2개의 다른 타입의 엘리먼트는 다른 트리를 생성한다
2. 개발자는 `key` prop으로 어떤 자식 요소가 stable한지 리액트에게 알려줄 수 있다.

3. 2개의 다른 타입 엘리먼트

- 루트 엘리먼트가 다를 경우

```js
<div>
  <Counter />
</div>

<span>
  <Counter />
</span>
```

기존 컴포넌트 언마운트되고 새로운 컴포넌트 마운트되서 DOM이 추가된다.(기존 컴포넌트의 상태 사라짐)

- (반대로) 동일한 타입의 DOM 엘리먼트

DOM노드를 유지하며 (리마운트 하지 않고) 변경된 속성만 업데이트 한다.(이로 인해 기존 컴포넌트 상태 유지)

```js
<div className="before" title="stuff" />

<div className="after" title="stuff" />
```

2. key를 이용하여 stable한 컴포넌트 알려주기

리액트는 뒤에 추가되는 컴포넌트에 대해서만 효율적으로 동작한다.
즉, 1,2번 컴포넌트 뒤에 3번 컴포넌트가 추가된 경우
"1,2번 컴포넌트 뒤에 3번이 추가됐으니까 1,2번은 그대로 두고 3번 컴포넌트만 추가하면 되구나"라는 걸 안다.

하지만 1번 컴포넌트 앞에 3번 컴포넌트가 추가된 경우 모든 트리를 언마운트 후 리마운트 한다.
이를 해결하기 위해 key를 이용한다.

- key는 가급적 유니크 ID를 이용
  - 재정렬 할 컴포넌트가 아니라면 인덱스로 사용해도됨.
- 만약 재정렬되는 컴포넌트에 index를 사용할 경우, 문제 발생한다.
  - 문제는 컴포넌트 인스턴스는 키에 따라 업데이트되거나 리마운트 되거나 재사용되기 때문이다.

## FAQ

Q. Diffing 알고리즘이란?
A. 2개의 트리의 차이점을 비교하는거다. 리액트는 먼저 2개의 root element를 비교한다. diffing 동작은 루트 엘리먼트의 타입에 따라 다르다.
