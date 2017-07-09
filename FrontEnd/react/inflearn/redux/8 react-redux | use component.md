# react-redux | 컴포넌트 사용하기

Provider
- 뷰 레이어 바인딩 도구다
- 리액트 컴포넌트에서 리덕스 사용할 때 복잡한 작업 얘가 다 해준다.
- IT부서와 같다.

## 핵심
1. provider
  - 컴포넌트에서 리덕스를 사용하도록 서비스 제공
  - 하나의 컴포넌트
```html
  <provider store = {store}>
    <App/>
  </provider>
```
  - 프로젝트에서 사용하는 컴포넌트를 리액트 돔으로 페이지에 렌더링하게 될 때 **해당 컴포넌트를 이 프로바이더 컴포넌트 안에 감싸주면 프로바이더가 복잡한 작업을 알아서 한다**
  - 일단 인덱스 파일에서 앱 컴포넌트를 프로바이더 컴포넌트로 감싸보자

```javascript
ReactDOM.render(
  <Provider store = {store}>
      <App />
  </Provider>,

  document.getElementById("root")
);
```
- **위 상태라고 해서 app component와 counter컴포넌트에서 스토어에 접근할 수 있는 것은 아니다**




2. connect([...options])

- 옵션을 인수로 받고 전달받은 옵션을 사용해서 **컴포넌트를 리덕스에 연결하는 또다른 함수를 반환**
- **그래서 그 함수에다가 다음과 같이 Counter를 인수로 전달하면, 그 카운터가 리덕스에 연결되서 함수의 반환값으로 새로운 컴포넌트 클래스가 반환**된다.
- 새로운 컴포넌트 클래스는 리덕스에 연결된다
- 기존의 component가 변하는 것이 아닌 새로운 컴포넌트가 변하게됨
```javascript
connect()(Counter)
// store에 연결된 새로운 컴포넌트가 반환
// 옵션이 없으면 this.props.store로 접근 가능
```
- 렌더링 할 때 그 스토어를 사용해서 getState로 특정 값을 가져오면된다.
- 아니면 변화 일으킬 때 dispatch하면된다. 만약 여기다 옵션 넣으면 더 깔끔해짐

```javascript
connect(
  [mapStateToProps],
  [mapDispatchToProps],
  [mergeProps],
  [options]
)
```
- 첫번째 세개는 함수형태의 파라미터
- mapStateToProps는 스테이트를 파라미터로 가지는 함수
  - state를 해당 컴포넌트의 props로 연결
- 2번째
  - dispatch를 파라미터로 가진다
  - 디스패치한 함수를 props로 연결
- mergeProps
  - 만약 컴포넌트에 연결해야할 프롭스가 스테이트와 디스패치를 동시에 사용해야 한다면 여기서 쓰면 됨
  - 잘 사용아노딤
- options는 객체 형태
  - pure : true로 설정되어있으면 불필요한 업데이트 안함(디폴트 트루)
  - withRef : 기본 false, 만약 트루로 설정되어있으면 리듁스에 연결된 컴포넌트를 ref에 담아서 getWrappedInstance()로 접근가능, 보통 사용안함
- 그럼 counter 컴포넌트를 커넥트를 통하여 리덕스에 연결해보자.


똑똑한 컴포넌트(Counter) 에서 리덕스의 커넥트를 한 다음, 여기서 리덕스 관련 작업 한다. 그리고 밸류 컴포넌트와 컨트롤 컴포넌트는 counter에서 리덕스를 연결해서 받은 값을 전달


## Counter.js
export default Counter 하기전에 이 위에 함수를 작성하자.

### 먼저 mapStateToProps
**리덕스 state 안에 있는 걸 이 component의 props에 매핑**
- 여기서 사용된 state는 그냥 파라미터 이름
  - component의 state와 다르다
- number라는 props(Counter)를 여기다가 연결

```javascript
const mapStateToProps = (state) => {
  return {
    // number라는 props를 여따 연결해줘라고 얘기
    number : state.counter.number,
    color  : state.ui.color
  };
}
```
- 이렇게 return하면 state안에 있던 값들이 이 컴포넌트의 number, color props로 연결됨
- **state안에 있던 값이란 무엇인가?**

### mapDispatchToProps
dispatch를 parameter로 받는다.
- 마찬가지로 return
- action을 dispatch하는 함수를 props로 연결
- 우리에게 필요한 건
  - 값 올리기, 낮추기, 색 변경 3개
  - Counter Component에서도 각 세가지를 담당하는 것들을 연결
- 일단, actionCreator 불러오자
```javascript
import * as actions from '../actions';
```
- increment를 담당할 handleIncrement라는 props를 만들어서 값은 함수로
  - 함수 내용은 `dispatch(action.increment())`
  - handleIncrement 사용시 `dispatch..`가 사용됨

## Counter Comp를 Redux에 연결
mapStateToProps, mapDispatchToProps를 이용하여 Counter Component를 Redux에 연결
```javascript
export default connect()(Counter);
```
- **이 connect가 반환하는 것은 component를 Redux에 연결하는 또다른 함수 반환**
- **그 반환된 함수에 parameter로 Counter를 넣는다.**

```javascript
<Value number = {this.props.store.getState().counter.number}/>
```
원래는 위와 같이 해야하지만, mapStateToProps와 mapDispatchToProps가 있으니까 이걸 connect에 전달해주자
```javascript
export default connect(mapStateToProps, mapDispatchToProps)(Counter);
...
<Value number = {this.props.number}/>
```
이렇게만 해도 전달 됨

### Component
```javascript
render() {
  return (
    <div style = {style}>
      <Value number = {this.props.number}/>
      <Control
        onPlus = {this.props.handleIncrement}
        onSubtract = {this.props.handleDecrement}
        onRandomizeColor = {this.setRandomColor}
        />
    </div>
);}
```
onRandomizeColor를 구현하기 위해 component자체에 함수 구현
- why onRandomizeColor만 컴포넌트에서 구현?

색상은 div의 style로 설정해보자. 일단 smart component에 예외상황으로 style적용해보자.
```javascript
const color = this.props.color;
const style = {
  background : 'rgb(${color[0]},${color[1]},${color[2]})'
};
```
- 기존의 es면 'rgb('+ color[0] + ', ' + 0,0,0);
- es6에서는 템플릿 리터럴이 있다
- 'string text' 이런식으로 작성
- 그 안에 이런식으로 js expression 표현 위해 ${} 넣어주면 변수 상수 넣을 수 있음
