# state와 props 사용하기

## 2 Props
- 컴포넌트에서 사용할 데이터 중 변동되지 않은 데이터 다룰 때 사용
- parent component에서 child 컴포넌트로 데이터 전할 때

### 2.1 props 추가하기
컴포넌트에서 immutable 데이터 필요시
- `render()` 메서드 내부에 `{this.props.propsName}` 형식으로 넣고
- 컴포넌트 사용시, `< >`괄호 안에 `propsName="value"`를 넣어 값 설정

```javascript
render(){
  return(
    <h1>{this.props.title}</h1>
  )
}
```
위와 같이 props 값이 렌더링 될 위치에 {this.props.propsName}을 넣는다

### 2.2 props 사용하기
- App 컴포넌트에 props 넣어주고
- App 컴포넌트에서 사용되는 props 값을 child 컴포넌트를 전달하자

```javascript
class App extends.. {
  render() {
    return(
      <div>
        <Header title={this.props.headerTitle} />
        <Content title={this.props.contentTitle}
                  body={this.props.contentBody}/>

      </div>
    )
  }
}

ReactDOM.render(<App headerTitle="Welcome"
                      contentTitle="Stranger,"
                      contentBody="Welcome to example App"/>, document.getElementById('app'));
```

### 2.3 기본값 설정하기
`className.defaultProps = {propsName: value}` 삽입

### 2.4 Validate Type
원하는 props의 Type과 전달된 props의 Type이 일치하지 않을 때 콘솔에서 오류 메시지 나타는 것
- 컴포넌트 클래스의 `propTypes` 객체를 설정하기
- 또한 필수 props를 지정할 수 도 있다.

```javascript
class Content...{

}

Content.propTypes = {
  title: React.PropTypes.string,
  body: React.PropTypes.string.isRequired
}
```

## 3 State
컴포넌트에서 유동적인 데이터를 다룰 때, `state`를 사용한다. React.js 어플 만들 때 **state 사용하는 컴포넌트 갯수 최소화 하도록 노력하자**
예를 들어
- 10개의 컴포넌트에서 유동적인 데이터 사용하게 될 땐, 각 데이터에 `state` 사용 할 게 아니라, `props`를 사용하고 10개의 컴포넌트를 포함시키는 `container` 컴포넌트 사용하는 것이 효율적

### 3.1 기본 사용 방법

```javascript
class StateExample..{
  constructor(props) {
    super(props);

    this.state = {
      header: "Header initial state",
      content: "Content Initial State"
    };
  }

  _updateHeader(text){
    this.setState({
      header: "Header has changed"
    });
  }
  render() {
    return (
      <div>
           <h1>{this.state.header}</h1>
           <h2>{this.state.content}</h2>
           <button onClick={this._updateHeader.bind(this)}>Update</button>
      </div>
    )
  }
}
```
- state 초기 값 설정 : constructor 메서드에서 `this.state={}`를 통하여 설정
- state 렌더링시 `{this.state.stateName}`
- state 업데이트시 `this.setState({})`
  - ES6 class에선 auto binding 되지 않으므로 setState 메서드를 사용하게 될 메서드를 bind 해주어야 한다.(bind 안하면 React Component가 가진 멤버 함수 및 객체에 접근 불가능)

## 4 적용 : State 와 props

```javascript
class RandomNumber extends React.Component {
    _update(){
        let value = Math.round(Math.random()*100);
        this.props.onUpdate(value);
    }

    constructor(props){
        super(props);
        this._update = this._update.bind(this);
    }
ne3
    render(){
        return (
            <div>
                <h1>RANDOM NUMBER: { this.props.number }</h1>
                <button onClick={this._update}>Randomize</button>
            </div>
        );
    }
}
```
2가지 props를 사용
1. number   : 랜덤 값
2. onUpdate : function 형태의 prop으로써, parent 컴포넌트에 정의된 메소드를 실행하도록 한다.


## Summary

2. props
  - 컴포넌트에서 변동되지 않은 데이터 다룰 때 사용
  - parent component에서 child 컴포넌트로 데이터 전달
  2.1 props 추가하기
  - render 메서드 내부에 `{this.props.propsName}`
  - 컴포넌트 사용시 `< >` 괄호 안에 `propsName="value"`를 넣어 값 설정

  2.3 기본값 설정
  `className.defaultProps = {propsName:value}`
  2.4 Validate Type

3. State
  - 컴포넌트에서 유동적인 데이터를 다룰 때
  - **state 사용하는 컴포넌트 갯수 최소화 하도록 노력하자**
  3.1 기본 사용방법
  - state 초기값 설정 `this.state={}`
  - state 렌더링시 `{this.state.stateName}`
  - state 업데이트시 `this.setState({key:value})`
