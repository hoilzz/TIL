# AutoBinding

ES6으로 선언된 React 컴포넌트에서, 메서드는 regular ES6 class처럼 동일한 semantic을 따른다. 이것은 메서드들이 자동적으로 instance에 `this`를 바인드하지 못한다는 것을 의미한다. 명시적으로 생성자안에 `.bind(this)` 사용해야 한다.

```javascript
class SayHello extends React.Component {
  constructor(props) {
    super(props);
    // This line is important!
    this.handleClick = this.handleClick.bind(this);
  }
  handleClick() {
    alert('Hello!');
  }
  render( {
    // 'this.handleClick'이 바운드되있기 때문에,
    // event handler로써 handleClick 사용 가능
    return (
      <button onClick={this.handleClick}>
        Say Hello
      </button>
    )
  })
}
```

`React.createClass()`는 모든 메서드에 bind를 했기때문에 위와 같은 코드는 불필요
```javascript
var SayHello = React.createClass({
  handleClick: function() {
    alert('Hello!');
  },

  render: function() {
    return (
      <button onClick={this.handleClick}>
        Say hello
      </button>
    );
  }
});
```

## Summary
- 생성자 안에 메서드 바인딩 해라
  + ES6 class 처럼 메서드들은 자동적으로 instance에 `this`바인딩 못함
