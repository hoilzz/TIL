# Virtual DOM과 DOM의 차이

[virtual DOM vs DOM](http://webframeworks.kr/tutorials/translate/virtual-dom/)

위에 글을 요약해보자..

## DOM

DOM은 Document Object Model을 나타내고 구조화된 텍스트의 개념이다.
HTML은 단순 텍스트일지라도 **DOM은 메모리에 값을 가진 표현식이다.**

> 하나의 프로그램에 다수의 프로세스가 있듯이, 하나의 HTML 문서 안에 다수의 DOM이 있다.

DOM은 노드 접근(such as `getElementById`), 수정과 같은 API를 제공한다.

### DOM의 문제

DOM은 tree 구조다.
**트리는 탐색하기 쉽지만 빠르지 않다.**

DOM 탐색, 수정은 SPA에서 많이 사용된다. 만약 DOM안에 1000개의 div와 수많은 이벤트 핸들러가 있다고 해보자. 이것은 1.이벤트를 다룰 노드를 찾고 2. 필요하면 업데이트 한다.

이것은 2가지 문제점이 있다.

1. 다루기가 힘들다. 이벤트 핸들러를 다룰 때, 문맥을 제대로 찾지 못한다면 코드가 어케 흘러가는지 깊게 파고들어야 하는데.. 이것은 시간 소모가 크고 버그 발생 가능성이 있다.

2. 불편하다. 탐색을 일일히 해야한다..

어떤 노드가 업데이트 되야 하는지 구분할 수 있다면..?

리액트는 이 부분을 도와준다. DOM 트리를 탐색하는 것과 같은 것은 리액트가 대신해준다. 개발자는 컴포넌트가 무슨 일을 해야 할징에 대해 정의만 해주면된다.

> (요 부분에 대한 자세한 설명은 [ReactElement 포스팅](https://ko.reactjs.org/blog/2015/12/18/react-components-elements-and-instances.html)을 읽어보면 도움된다.. react가 reactelements와 같은 인스턴스들을 알아서 생성,업데이트,제거 한다. 개발자는 UI만 잘 정의해놓으면 리액트가 알아서 traverse하며 인스턴스를 관리)

이것이 퍼포먼스 이슈를 해결하지 않는다. 요건 가상돔의 도움을 받자.

### 가상돔

가상 돔은 HTML DOM의 추상화한 것.

가볍고, 브라우저 스펙의 구현체와는 분리(즉, DOM API를 가지지 않고 단순한 객체. 그래서 가벼움)

### ReactElement vs ReactComponent

**ReactElement**

가상 돔에서는 위 두가지 타입은 결국 UI를 설명하는 객체(내부 프로퍼티에서 다음과 같이 구분 `type: (string | ReactClass`)인데, 둘의 차이점에 대해 알아보자.

ReactElement는

- tag name을 가진 DOM을 설명
- 파싱할 필요 없이 설명만하는 단순 객체기 때문에 DOM보다 가볍다.
- **상태가 없다.**
- 불변이다. 그래서 비교와 업데이트가 빠르다.

```js
var el = React.createElement('div');
// 위 코드를 jsx로
var el = <div />;
```

**ReactComponent**

**ReactElement와의 차이점은 상태를 유지하는 점.**

```js
// createElement가 아닌 createClass
var CommentBox = React.createClass({
  render: function() {
    return <div>Hello, world!</div>;
  }
});
```

ReactComponent는 ReactElement로 쉽게 컨버팅 된다. 갑자기 이게 뭔소리냐면.. 렌더링을 위해 ReactElement를 찾을 때까지 traverse해야된다. 렌더링 하기 위해 React는 ReactElement(DOM tag element)를 알 때까지 파고든다.

```js
var element = React.createElement(MyComponent);
// or equivalently, with JSX
var element = <MyComponent />;
```

## 그래서..

ReactComponent의 상태가 바뀔 때, DOM은 최대한 적게 변하는게 이상적이다. 이 때 ReactElement는 빠르고 쉽게 비교될 수 있다.(불변성과 diff 알고리즘을 이용하여) 이 작업은 일반 DOM보다 훨씬 빠르고 정확하다.

리액트가 수정내역을 알고 나면 low-level(HTML DOM)로 바뀌고 일반 DOM 안으로 삽입된다.
