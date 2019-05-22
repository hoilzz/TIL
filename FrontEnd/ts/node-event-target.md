# Node vs Element

Typescript 환경에서 event.target을 함수의 인자로 전달받아 사용하는 경우가 있었다.
이 때, event.target은 DOM을 가리키는 것으로 타입 선언을 해주려했다.

이 때 DOM을 Node로 할지 Element로 할지.. 고민하다 차이를 찾아보았다.

---

node는 DOM 계층에서 모든 객체에 대한 generic name이다. node는 document 혹은 document.body와 같은 내장된 DOM element 중 하나다. <input> 이나 <p>와 같은 HTML에서 명시된 HTML 태그도 해당된다. 또는, 다른 element 내부의 텍스트를 블록을 잡기 위한 텍스트 노드가 될 수 있다. 그래서 node는 any DOM object다.

엘리먼트는 노드의 특정 타입 중 하나다. 많은 타입의 노드가 있는 것처럼..(text nodes, comment nodes, document nodes, etc...)

DOM은 각 노드가 부모, 여러개의 자식, 형제 노드를 갖는, 노드 계층으로 구성되어있다. 구조는 트리 계층을 형성한다. document node는 자식 노드 리스트를 갖고, body노드는 자식 노드 리스트를 갖고...

엘리먼트는 HTML 태그로 명시되고 id나 class와 같은 프로퍼티를 갖는 노드의 특정 타입이다. comment node, text node 등 다른 노드를 자식으로 갖는다.

[nodeTypes](https://developer.mozilla.org/en-US/docs/Web/API/Node/nodeType#Node_type_constants)

So document.getElementById("test") can only return one node and it's guaranteed to be an element (a specific type of node). Because of that it just returns the element rather than a list.

그래서 `documnet.getElementById('test')`는 1개 노드를 리턴하고 그것은 엘리먼트다.(node의 특정 타입). 리스트가 아닌 엘리먼트를 리턴한다.

## summary

node가 더 큰 개념이고, element는 노드의 특정 타입 중 하나.
