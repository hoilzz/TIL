# render-prop pattern

> render props는 React의 새로운 context API로 사용할 수 있다.

[HOC pattern](https://facebook.github.io/react/docs/higher-order-components.html)은 인기있는 코드 재사용 방법이다. HOC는 "render prop"을 사용하는 일반적인 컴포넌트로 100% 대체될 수 있다.

## mixin의 문제점

**code reuse**를 해결하기위해 설계된 HOC의 주요 문제점에 대해 알아보자.

`React.createClass`를 쓰던 시대로 돌아가자. mouse 위치를 추적하고 페이지에 그것을 보여주느 간단한 리액트 앱을 예시로 들어보자.

```javascript
import React from 'react'
import ReactDOM from 'react-dom'

const App = React.createClass({
  getInitialState() {
    return { x: 0, y: 0 }
  },

  handleMouseMove(event) {
    this.setState({
      x: event.clientX,
      y: event.clientY
    })
  },

  render() {
    const { x, y } = this.state

    return (
      <div style={{ height: '100%' }} onMouseMove={this.handleMouseMove}>
        <h1>The mouse position is ({x}, {y})</h1>
      </div>
    )
  }
})

ReactDOM.render(<App/>, document.getElementById('app'))
```

이제 다른 컴포넌트에서도 마우스 위치를 추적하고 싶다고 하자. `<App>`으로부터 어떤 코드를 재사용할 수 있는가?

`createClass` 패러다임에서, 코드 재사용의 문제는 `mixin`이라 불리는 기법으로 해결되었다. 마우스 위치를 추적하기 위해 누구나 사용할 수 있는 `MouseMixin`을 만든다고 해보자.

```javascript
import React from 'react'
import ReactDOM from 'react-dom'

// This mixin contains the boilerplate code that
// you'd need in any app that tracks the mouse position.
// We can put it in a mixin so we can easily share
// this code with other components!
/**
    아래 믹스인은 마우스 위치를 추적하는 모든 앱에 필요한 boilerplate 코드다.
    이 믹스인을 추가하고 우리는 쉽게 다른 컴포넌트에서 이 코드를 공유할 수 있다.
*/
const MouseMixin = {
  getInitialState() {
    return { x: 0, y: 0 }
  },

  handleMouseMove(event) {
    this.setState({
      x: event.clientX,
      y: event.clientY
    })
  }
}

const App = React.createClass({
  // Use the mixin!
  mixins: [ MouseMixin ],

  render() {
    const { x, y } = this.state

    return (
      <div style={{ height: '100%' }} onMouseMove={this.handleMouseMove}>
        <h1>The mouse position is ({x}, {y})</h1>
      </div>
    )
  }
})

ReactDOM.render(<App/>, document.getElementById('app'))
```

문제는 해결됐다. 아무나 this.state안에서 x와 y를 얻기 위해 `MouseMixin`을 컴포넌트 클래스에 추가할 수 있다.

## HOC는 New mixin이다.

ES6 클래스가 도입되고 React 팀은 `createClass`를 이용하지 않고 대신 ES6 클래스를 사용하기로 결정했다. 현명한 결정이다. JS의 빌트인된 클래스가 있는데 class model을 누가 유지하고 싶을까?

하지만 문제가 있다. ES6는 mixin을 지원하지 않는다. 또한, ES6 class 스펙의 부분도 아니다. 믹스인은 단점도 많다. (댄의 [블로그](https://facebook.github.io/react/blog/2016/07/13/mixins-considered-harmful.html)를 참고하자)

문제를 요약하면,

- ES6 class. mixin 미지원
- Indirection(우회). mixin은 state가 어디서 오는지 아는 것이 까다롭다. (특히, mixin이 2개 이상이면)
- Naming Collisions. 동일한 state를 업데이트 하려는 2개의 mixin이 서로 값을 덮어쓴다. `createClass` API는 2개의 믹스인이 동일한 key를 가진 `getInitialState` 값을 가진다면 경고한다.

그래서 code reuse를 위해 mixin 사용하는 것 대신에 HOC라는 대체 기법을 마련했다. 이 패러다임에서 [decorator](https://en.wikipedia.org/wiki/Decorator_pattern) 기법을 사용하여 코드는 공유된다. 렌더링될 마크업 덩어리로 정의된 컴포넌트, 너가 공유하기를 원하는 행동을 포함한 컴포넌트에 그것을 wrapping 한다.  너가 필요한 행동을 mixing in 하는 것 대신에, 단순히 component를 *decorate* 할 수 있다.

```javascript
import React from 'react'
import ReactDOM from 'react-dom'

const withMouse = (Component) => {
  return class extends React.Component {
    state = { x: 0, y: 0 }

    handleMouseMove = (event) => {
      this.setState({
        x: event.clientX,
        y: event.clientY
      })
    }

    render() {
      return (
        <div style={{ height: '100%' }} onMouseMove={this.handleMouseMove}>
          <Component {...this.props} mouse={this.state}/>
        </div>
      )
    }
  }
}

const App = React.createClass({
  render() {
    // Instead of maintaining our own state,
    // we get the mouse position as a prop!
    const { x, y } = this.props.mouse

    return (
      <div style={{ height: '100%' }}>
        <h1>The mouse position is ({x}, {y})</h1>
      </div>
    )
  }
})

// Just wrap your component in withMouse and
// it'll get the mouse prop!
const AppWithMouse = withMouse(App)

ReactDOM.render(<AppWithMouse/>, document.getElementById('app'))
```

이것은 ES6 class의 세계에서 우아하게 코드 재사용 문제를 해결할 수 있는 좋은 솔루션이다.

이 시점에서 나는 묻고 싶다. HOC로 바꿔서 우리가 얻은게 뭘까? mixin이 가진 문제를 우리가 해결했는가?

- ES6 class. ES6 class를 이용하여 생성된 컴포넌트로 HOC 사용할 수 있다.
- Indirection. mixin이용할 떄와 같은 여전히 동일한 문제점(indirection)을 가진다. state가 어디서 오는지 궁금해하는 것 대신에 **어떤 HOC가 어떤 prop을 제공하는지 알 수 없다.**
- Naming Collisions. 이 문제 또한 여전히 가지고 있다. 동일한 prop을 사용하려는 2개의 HOC는 충돌하고 서로 오버라이팅한다. 이번에는 React가 prop name collision을 경고하지 않기 때문에 더 insidious하다.

...

mixin, HOC 둘 다 가진 문제

**dynamic composition** 대신에 **static composition**을 사용하는 것이다. *where is the composition happening in the HOC paradigm?* component class가 생성될 때, Static Composition은 한번 일어난다.

(React의 **dynamic composition model**의 key인) `render` method 안에서 HOC나 mixin을 사용하지 않는다. `render`에서 compose할 때, React lifecycle의 이점을 얻을 수 있다.

그래서 요약하면: ES6 class로 HOC를 사용하는 것은 mixin과 동일한 문제를 일으킨다.

HOC는 컴포넌트를 래핑하고, 기존 컴포넌트에 믹스되는 것 대신 새로운 것을 생성한다는 점에서 축하받을만 하다. HOC에서 리턴된 컴포넌트는 (동일한 prop을 사용해야 하는) 그것이 래핑하는 컴포넌트와 가능한 유사하게 동작해야 한다. 좋은 예제는 [withRouter HOC](https://github.com/ReactTraining/react-router/blob/master/packages/react-router/modules/withRouter.js)다. 

## Render Props

mixins과 HOC의 결점을 피할 수 있는 기법 Render-Prop에 대해 알아보자.

> render prop은 컴포넌트가 **어떤 것을 렌더링 할지 알기 위한** function prop이다.

더 일반적으로 말하자면, 아이디어는 이거다. "mixing in" or 행동을 공유하기 위한 decorating component 대신에, 단지 너에게 어떤 state를 공유하기 위해 사용할 수 있는 function prop을 가진 일반적인 컴포넌트를 렌더링하는 것이다.

아래 예제에서, `withMouse` HOC를 함수인 `render` prop을 가진 `<Mouse>`로 단순화 해보자. 그리고나서 `<Mouse>`의 `render`내부에서, 뭘 렌더링할지 알기 위해 prop을 사용할 수 있다.

```javascript

import React from 'react'
import ReactDOM from 'react-dom'
import PropTypes from 'prop-types'

// Instead of using a HOC, we can share code using a
// regular component with a render prop!
class Mouse extends React.Component {
  static propTypes = {
    render: PropTypes.func.isRequired
  }

  state = { x: 0, y: 0 }

  handleMouseMove = (event) => {
    this.setState({
      x: event.clientX,
      y: event.clientY
    })
  }

  render() {
    return (
      <div style={{ height: '100%' }} onMouseMove={this.handleMouseMove}>
        {this.props.render(this.state)}
      </div>
    )
  }
}

const App = React.createClass({
  render() {
    return (
      <div style={{ height: '100%' }}>
        <Mouse render={({ x, y }) => (
          // The render prop gives us the state we need
          // to render whatever we want here.
          <h1>The mouse position is ({x}, {y})</h1>
        )}/>
      </div>
    )
  }
})

ReactDOM.render(<App/>, document.getElementById('app'))
```

`<Mouse>`컴포넌트는 `<App>` 컴포넌트에게 render prop을 호출하여 state를 노출시켰다. 그러므로, <App>은 state만 있다면 어떤 것이든 렌더링할 수 있다.

"children as a function"은 개념이 정확히 동일한 컨셉이라고 분명히 말하고 싶다. 단지 render 대신에 `children` prop을 사용하는것이다. `render`로 이름지어진 prop에 대해 말하는 것이 아니다. **오히려 어떤것을 렌더링 하기 위해 사용하는 prop을 가지는 컨셉에 대해 말하고 싶다.** 

이 기법은 mixin과 HOC가 가진 모든 문제를 피한다. 

- ES6 classes : ES6 class를 사용하여 생성된 컴포넌트에서 render props을 사용할 수 있다.
- Indirection: state나 props이 어디서 왔는지 궁금해할 필요가 없다. render prop의 인자 리스트에서 그것들을 확인할 수 있다. 
- Naming Collisions: 프로퍼티 이름이 자동 병합되지 않는다. 그래서 naming collistion이 없다. 

다른 컴포넌트를 래핑하거나 decorating하지 않기 때문에, render prop을 사용하는 것은 절대 필요하지 않다. 그것은 단지 함수다.

게다가, **composition model은 dynamic하다** render 내부에서 모든것이 일어난다. **그래서 react lifecycle의 모든 이점과 자연스러운 props & state의 흐름을 가질 수 있다.**

이 패턴을 사용하여, HOC를 render prop으로 된 일반적인 컴포넌트로 대체할 수 있다. 

## Render Props > HOCs

render prop이 HOC보다 강력한 패턴이라는 가장 확실한 증거 중 하나는 render prop을 이용하도록 구현된 점이다. (하지만 HOC는 render prop을 이용하지 못한다.) 다음은 일반적인 `<Mouse>`를 이용하여 `withMouse` HOC 구현부다. 

```javascript
const withMouse = (Component) => {
    return class extends React.Component {
        render() {
            return <Mouse render={mouse => (
                <Component {...this.props} mouse={mouse} />
            )}
        }
    }   
}
```

민감한 독자는 이미 react router 코드 내부의 `withRouter` HOC가 실제로 [render prop](https://github.com/ReactTraining/react-router/blob/f77440ec9025d463c6713039ab1a6db1faca99bb/packages/react-router/modules/withRouter.js#L13)으로 구현된 것을 이미 알고 있을 것이다.

HOC를 찾고 render prop으로 된 일반적인 컴포넌트로 바꿔라. 그렇게 하면 dynamic composition의 이점을 가질 수 있다.

> Render props은 React의 새로운 API, context API로 사용되고 있다. 