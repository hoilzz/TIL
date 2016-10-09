# render

```
ReactElement render()
```
*what*
-

*when*
- when creating a component class by invoking `React.createClass()`
  + `render` 메서드를 포함하는 specification object 제공해야만 함

- should be *pure*
  + component state를 수정하지 않음 을 의미

*`render()`가 호출될 때*
- `this.props` 와 `this.state`를 조사
- 그리고 return a single child element
  + child element는 virtual representation of a native DOM component다.
  + such as `<div/>` or `React.DOM.div()`
