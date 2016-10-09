# React Components
only `ReactElement`s 만 사용하여 React 사용할 수 있다. 하지만 React 이점을 완전히 얻기 위해, embedded state인 캡슐화를 생성하는 `ReactComponent`를 사용해야해

`ReactComponent` Class는 단순히 JS class다. (or `constructor function`)

```javascript
var MyComponent = React.createClass({
  render: function() {
    ...
  }
});
```

constructor가 호출될 때, at least `render` 메서드의 object를 리턴한다. 이 오브젝트는 `ReactComponent`를 가리킨다.
```javascript
var component = new MyComponent(props); // Never do this
```
생성자 자체를 *절대절대 never ever* 부르지마.
- 대신에, `ReactComponent` class를 `createElement` 메서드에 통과시켜라.

```javascript
var element = React.createElement(MyComponent);
```

or using JSX:
```javascript
var element = <MyComponent />;
```

이 엘리먼트가 `ReactDOM.render`를 통과 했을 때, React는 생성자를 호출하고 create a `ReactComponent`한다.
```javascript
var component = ReactDOM.render(element, document.getElementById('example'));
```
만약 `ReactElement` 그리고 동일한 container DOM `Element`를 `ReactDOM.render`로 호출하면, 그것은 항상 동일한 인스턴스다. 인스턴스는 stateful하다.

```javascript
var componentA = ReactDOM.render(<MyComponent />, document.getElementById('example'));
var componentB = ReactDOM.render(<MyComponent />, document.getElementById('example'));
componentA === componentB // True
```

이래서 너 자신의 instance를 생성하지 않아야 한다. 대신에, 생성되기 전에 `ReactElement`는 virtual `ReactComponent`다. 만약 new ReactComponent 인스턴스가 생성되야만 하거나 기존의 거를 재사용 해야한다면 old and new `ReactElement`는 비교된다.

`ReactComponent`의 `render` 메서드는 다른 `ReactElement`를 리턴한다. 이것은 컴포넌트가 구성되도록 허용한다. Ultimately render는 `ReactElement`를 DOM `Element` 인스턴스로 이니셜라이징 하고 document로 삽입되는 string tag로 분해한다

React 0.14는 component 정의하는 대안 방식으로 stateless functional component를 소개한다.


## Summary
- ReactElement만으로 React할 수 있지만-- `ReactComponent`를 사용해야해
  + React의 완전한 이점을 얻기 위해 (embedded state인 캡슐화)
- `ReactComponent`는 JS class (or `constructor function`)
- ReactComponent 생성
  + `React.createElement(ReactComponent Class)`
  + `<ReactComponent className/>`
- 위 엘리먼트가 `ReactDOM.render` 통과시 React는 생성자 호출하고 create a `ReactComponent`
- `ReactComponent`의 `render`는 `ReactElement` 리턴


> var MyComponent = React.createClass({
>  render: function() {
>    ...
>  }
> });
> var element = React.createElement(MyComponent);
> var element = <MyComponent />;
> var componentA = ReactDOM.render(<MyComponent />, document.getElementById('example'));
