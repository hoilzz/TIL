# state
컴포넌트에서 유동적인 데이터를 보여줄때 사용
- 초기값 설정 필수
  - constructor(생성자)안에서 this.state={}
  - 이 때 초기화 안하고 나중에 렌더링 부분에서 this.state 하려하면 에러 발생
- props와 달리 setState({...})를 통해 변경 가능
- 값이 변경된 다음에 리액트가 알아서 리렌더링한다.

- 렌더링 되기 전엔 setState 사용 안됨
- 렌더링 된 다음에 this.state = 절대 사용 금지
- 강제로 리렌더링은 리액트의 장점인 바뀐 부분만 업데이트 이걸 무시하는꼴
- 성능에도 안좋음

## Ex
```
  class Counter.. {
    constructor (props) {
      super(props);
      this.state = {
        value:0
      };
      this.handleClick = this.handleClick.bind(this);
    }

    // 버튼이 클릭 될 때 실행될 메서드
    handleClick() {
      this.setState({
        value:this.state.value+1
      })
    }

    render() {
      return (
        <div>
          <h2> {this.state.value} </h2>
          <button onClick={this.handleClick.bind(this)}>Press Me
          </button>
        </div>
      )
    }
  }

```


constructor 메서드의 파라미터는 props다.
- 이 props는 나중에 이 class counter가 만들어질 때 전달받을 props다.
- super를 통해 상속받은 클래스인 React.component
- 즉 패런트의 생성자 메서드를 먼저 실행하고 우리가 할 작업들을 한다.
- super(props)를 해야 이 메서드 안에서 this.state, props 접근 가능.

onClick, onChanged와 같은 js 이벤트 이용 가능. 근데 버튼 눌러도 안됨. 정상이다. js 컴포넌트에서 메서드 실행시 해당 메서드에서 this가 뭔지 모른다.

그래서 this뭔지 알려주려면 bind해야함

<button onClick={this.handleClick.bind(this)

위 코드는 handleClick에서 사용될 this는 렌더에서 사용되는 this와 같다라는 으미
근데 컨벤션상 button에 바인딩하는것보다 constructor에서 하는게 보기에 좋다.

### Note

onClick={this.handleClick()} 괄호가 없는데 넣어보자.

handleClick() 실행되면, handleClick에서 state바꾸고
setState하면 렌더링하고.. 이걸 계속 반복..
