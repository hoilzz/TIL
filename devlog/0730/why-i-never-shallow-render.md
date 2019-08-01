# shallow rendering 사용하지 않는 이유

enzyme의 shallow 함수는 컴포넌트 내부에 다른 리액트 컴포넌트가 있다면 렌더링하지 않는다.
다음과 같은 컴포넌트를 shallow render 한다면,

```js
import React from 'react';
import { CSSTransition } from 'react-transition-group';
function Fade({ children, ...props }) {
  return (
    <CSSTransition {...props} timeout={1000} className="fade">
      {children}
    </CSSTransition>
  );
}
class HiddenMessage extends React.Component {
  static defaultProps = { initialShow: false };
  state = { show: this.props.initialShow };
  toggle = () => {
    this.setState(({ show }) => ({ show: !show }));
  };
  render() {
    return (
      <div>
        <button onClick={this.toggle}>Toggle</button>
        <Fade in={this.state.show}>
          <div>Hello world</div>
        </Fade>
      </div>
    );
  }
}
export { HiddenMessage };

shallow(<HiddenMessage />);
```

```jsx
// 결과
<div>
  <button onClick={[Function]}>Toggle</button>
  <Fade in={true}>
    <div>Hello world</div>
  </Fade>
</div>
```

왜냐하면 Profile 컴포넌트를 호출하여 렌더링하는 대신에, shallow는 shallowly rendering하는 컴포넌트에 의해 생성되는 React element에 적용되는 props만 본다.

만약 Counter컴포넌트의 `render` method의 결과값을 console.log의 인자로 사용하면 다음과 같은 결과를 얻는다.

```js
{
  "type": "div",
  "props": {
    "children": [
      {
        "type": "button",
        "props": {
          "onClick": [Function],
          "children": "Toggle"
        }
      },
      {
        "type": [Function: Fade],
        "props": {
          "in": true,
          "children": {
            "type": "div",
            "props": {
              "children": "Hello world"
            }
          }
        }
      }
    ]
  }
}
```

비슷하게 보이는가? 그래서 모든 shallow rendering은 주어진 컴포넌트의 render 메소드의 결과(React element)를 가지고 wrapper object에 준다.

이것은 라이프사이클 메서드를 실행하지 않는다는 뜻이다. (왜냐하면 처리하기 위해 React element만을 단지 가지고 있다.), 실제로 DOM element와 인터랙션할 수 없다.(왜냐하면 실제로 렌더링되지 않았기 때문이다.) 그리고 custom component가 리턴한 실제로 react element를 갖지 않는다.(like our Fade component)
