# prop drilling

[prop drilling](https://kentcdodds.com/blog/prop-drilling)

## prop drilling?

```js
class Toggle extends React.Component {
  state = { on: false };
  toggle = () => this.setState(({ on }) => ({ on: !on }));
  render() {
    return (
      <div>
        <div>The button is {on ? 'on' : 'off'}</div>
        <button onClick={this.toggle}>Toggle</button>
      </div>
    );
  }
}
```

위 코드를 리팩토링 과정을 거쳐 아래와 같이 작성되었다.

```js
class Toggle extends React.Component {
  state = { on: false };
  toggle = () => this.setState(({ on }) => ({ on: !on }));
  render() {
    return <Switch on={this.state.on} onToggle={this.toggle} />;
  }
}

function Switch({ on, onToggle }) {
  return (
    <div>
      <SwitchMessage on={on} />
      <SwitchButton onToggle={onToggle} />
    </div>
  );
}

function SwitchMessage({ on }) {
  return <div>The button is {on ? 'on' : 'off'}</div>;
}

function SwitchButton({ onToggle }) {
  return <button onClick={onToggle}>Toggle</button>;
}
```

on상태와 onToggle핸들러를 필요한 위치로 주기 위해 prop drilling 하고 있다.

## prop drilling의 장점

뷰에 어떤 값을 명시적으로 전달하는가. on 상태를 열거형으로 리팩토링 한다고하면, 코드를 실행하지 않고도 정적으로 따라가는 것으로 어디서 사용하는지 쉽게 파악 가능. 여기서 중요한 점은 암시적인 것보다 명시적 작성에 있음.

## prop drilling의 문제점

앱이 커지면서 여러 계층의 컴포넌트가 생성되면서 문제가 발생한다.

- 데이터 구조를 변경하는 경우
- 컴포넌트 분리하는 과정에서 필요 없는 프로퍼티가 남는 경우
- 필요보다 적은 프로퍼티를 전달하는데, defaultProps를 과용한 결과 필요 프로퍼티가 전달되지 않은 상황에서 문제를 인지하기 어려운 경우
- 프로퍼티 이름잉 중간에서 변경되어 값을 추적하기 쉽지 않아지는 경우

## 위 문제 해결하기

render메소드를 불필요하게 여러 컴포넌트로 나누면 상황은 더 악화된다.
가능한 한 메소드에 두자. [메소드를 성급하게 나누지 말자.](https://blog.kentcdodds.com/when-to-break-up-a-component-into-multiple-components-4ee75ab53bbc)

defaultProps를 필수 프로퍼티에 사용하지 말자. 컴포넌트가 제대로 동작하기 위해 실제 필요한 프로퍼티를 전달받지 못했는데, 오류 없이 숨겨지고 소리없이 실패하게 된다.

**관련 있는 상태는 될 수 있으면 가까이 보관하자**
app 특정부분에만 필요한 상태라면 가장 높은 계층에 저장하지 말자. **최소 공통 부모 컴포넌트에서 관리하자.**

상태가 리액트 계층에서 정말 깊숙이 위치한 경우라면 Context API를 사용하자. 이 컨텍스트는 전역 변수로 문제를 해결하는 것과 유사하지만, API가 디자인된 방식이 다르기 때문에, 데이터의 원천도 정적으로 쉽게 찾을 수 있다.
