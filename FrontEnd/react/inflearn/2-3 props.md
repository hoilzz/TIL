# props $ state
## props

- 컴포넌트 내부의 Immutable data
- JSX 내부에 {this.props.propsName}
- 컴포넌트를 사용 할 때, < > 괄호 안에 propsName="value"
- *this.props.children* 은 기본적으로 갖고있는 props로서, <Cpnt>여기에 있는 값</cpnt>

Ex App Component의 props를 하위 component로 전달하기

### 기본 값 설정

````
  Component.defaultProps = {...}
````
```
  class App extends React.Component {
    render() {
      return (
          <div> {this.props.value} </div>
      );
    }
  };

  App.defaultProps = {
    value:0
  };
```

### Type 검증
Component.propTypes = {...}
이 기능을 통하여 특정 props 값이 특정 type이 아니거나 필수 props인데 입력하지 않았을 때, 개발자 콘솔에서 경고를 띄우게 할 수 있다
- type를 검증시 component순환이 끝난 후 propType를 선언하면 된다.
- 위 예제는 string, number, 어떤 값이든 필수로 입력되어야 한다 로 선언

```
Class App extends React.Component {
  render() {
    return (
      <div>
        {this.props.value}
        {this.props.secondValue}
        {this.props.thirdValue}
      </div>
    );
  }
};

App.propTypes = {
  value:React.PropTypes.string,
  secondValue:React.PropType.number,
  thirdValue:React.PropTypes.any.isRequired
}
```

### Summary
props는 필수가 아니다. 우리가 만든 컴포넌트의 유지보수를 위해 설정한다. 여러개의 컴포넌트를 만드는 프로젝트가 있을 때 동료가 내가 만든 컴포넌트를 사용시 해당 컴포넌트가 어떤 값을 필요로 하는지 알고 있을 때 propTypes를 설정 해놓았다면 쉽게 파악할 수 있다.
- props는 `ReactDOM.render()`에서 다른 컴포넌트 사용시 인자값을 전달하여 재사용성 높이는 것
- 컴포넌트의 유지보수를 위해 설정
- Type 검증 가능
- 기본값 설정 가능
