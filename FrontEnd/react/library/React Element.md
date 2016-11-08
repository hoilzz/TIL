# React (Virtual) DOM Terminology
1. ReactElement / ReactElementFactory
2. ReactNode
3. ReactComponent / ReactComponent Class

## React Elements
React에서 기본 타입은 `ReactElement`이고 4가지 프로퍼티를 가진다.
1. type
2. props
3. key
4. ref
- method 없고 prototype도 없다.

```
var root = React.createElement('div');
```

new tree를 DOM으로 렌더링하기 위해, `ReactElement`를 생성하고 `ReactDOM.render`로 regular DOM `Element`(`HTMLElement` or `SVGElement`)와 함께 new tree를 통과시킨다.
- `ReactElement`는 Virtual DOM이다.

```
ReactDOM.render(root, document.getElementById('example'));
```

DOM element로 *프로퍼티를 추가하기 위해*
- 2번째 인자 : object
- 3번째 인자 : children

```
var child = React.createElement('li', null, 'TextContent');
var root  = React.createElement('ul', { className: 'my-list'}, child);
ReactDOM.render(root, document.getElementById('example'));
```

If you use React JSX
```
var root = <ul className="my-list">
             <li>Text Content</li>
           </ul>;
ReactDOM.render(root, document.getElementById('example'));
```


## Summary
- React에서 기본 타입은 `ReactElement`이고 4가지 프로퍼티를 가진다.
- new tree를 DOM으로 렌더링하기 위해 `ReactElement` 만들고 `ReactDOM.render()`의 인자값에 추가
- `ReactElement`는 VirtualDOM이다. (DOM Elements와 혼동하지마. 이건 light, stateless, immutable, virtual DOM element야)


> var root  = React.createElement('ul', { className: 'my-list'}, child);
> ReacTDOM.render(root, document.getElementById('example'));
