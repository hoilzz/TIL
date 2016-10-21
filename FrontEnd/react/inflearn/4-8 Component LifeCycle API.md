# Component LifeCycle API
: Component가 DOM위에 생성되기 전과 후, 데이터가 변경되어 상태를 업데이트 하기 전과 후, 컴포넌트가 돔에서 사라지기 전에 실행되는 메서드들

## 7가지 LifeCycle API
1. componentWillMount
  : 렌더링 되기 전, 컴포넌트가 DOM 위에 만들어지기 전에 실행된다. 그래서 여기서 DOM처리 불가능

2. componentDidMount
  : 렌더링 된 다음, 첫 렌더링 마치고 실행됨
  - 이 안에서 다른 js 프레임워크 연동 및 setTimeout, setInterval 및 AJAX 사용

3. componentWillReceiveProps
  : 새로운 props 받았을 때
  - prop에 따라 state를 업데이트 할 때 사용하면 유용
  - 이 안에서 setState 사용해도 상관 없다.

4. shouldComponentUpdate
  : Component가 업데이트를 해야할지 말아야할지 정함
  - props나 state가 업데이트 됐는데, 뷰랑 관계가 없으면 false를 반환하여 그 다음 메서드들 실행하지 않도록 할 수 있음
  - 실제로 사용할 때는 필요한 비교를 하고 값을 반환하자.
    - Ex. return nextProps.id !== this.props.id
    - JSON.stringify를 사용하여 여러 filed를 편하게 비교

5. componentWillUpdate : Component가 업데이트 되기 전 실행됨
  - 4번 메서드에서 true반환시 이 메서드 실행
  - nextProps, nextState 인자로 다음 받을 props나 state 접근 가능
  - 여기서 setState 절대 사용하지 말것 (무한루프 빠짐)
  - 이거 다음 render 작업

6. componentDidUpdate : Component 업데이트 후 실행
  - 여기서도 setState 사용 금지

7. componentwillMount : Component가 제거될 때 실행

### constructor
: 컴포넌트 처음 만들어질 때 실행된다.

## Summary
나중에 프로젝트에서 LifeCycle 관리할 때 유용하게 사용 가능
[Component LifeCycle API](https://facebook.github.io/react/docs/component-specs.html)
