# Uncontrolled Components

[Uncontrolled Components](https://reactjs.org/docs/uncontrolled-components.html)를 번역해보자.

forms을 구현하기 위해 controlled component를 구현하는 것을 추천한다. controlled component 내부에서, form data는 React Component로 처리된다. 대안은 `uncontrolled component`다. (form data는 DOM 그 자체로 처리된다.)

uncontrolled component를 작성하기 위해, 모든 state update를 위해 event handler를 작성하는 대신에, DOM으로 부터 form 값을 가져오기 위해 `ref`를 사용할 수 있다.

예를 들어, 이 코드는 uncontrolled component에서 단일 이름을 허용한다. 

```javascript
class NameForm extends React.Component {
  constructor(props) {
    super(props);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleSubmit(event) {
    alert('A name was submitted: ' + this.input.value);
    event.preventDefault();
  }

  render() {
    return (
      <form onSubmit={this.handleSubmit}>
        <label>
          Name:
          <input type="text" ref={(input) => this.input = input} />
        </label>
        <input type="submit" value="Submit" />
      </form>
    );
  }
}
```

uncontrolled component가 DOM에서 `the source of the truth`를 유지하기 때문에, uncontrolled component를 이용할 때 React와 non-react code를 통합하는 것은 더 쉽다. 만약 너가 quick and dirty를 원한다면 약간 코드가 짧아질 수 있다. 그렇지 않다면, controlled component를 사용해야 한다. 

만약 특정 상황에서 사용해야 하는 컴포넌트 타입이 명확하지 않다면, 다음 아티클을 읽어라.
[controlled vs uncontrolled](https://goshakkk.name/controlled-vs-uncontrolled-inputs-react/)

component component는 form input과 같은 것들을 구현할 수 있는 가장 간단한 방법이다. 리액트 배울 때 가장 간단한 form에서 사용하는 경우가 있다. 하지만..

## Controlled Component

`controlled input`은 현재 값을 `props`으로 받아들인다. 뿐만 아니라, 그 값을 바꾸기 위한 `callback`으로도 받아들인다. 이것을 더 `React way`로 접근한다고 할 수 있다.(그렇다고 항상 이것을 사용하란 말은 아니다.) 

```javascript
<input value={someValue} onChange={handleChange} />
```

이것은 괜찮지만.. input 의 값은 `state` 내에서 유지되어야 한다. input을 렌더링 하는 component가 자신의 `state` 내부에 그 값을 저장해야 한다.

```javascript
class Form extends Component {
  constructor() {
    super();
    this.state = {
      name: '',
    };
  }

  handleNameChange = (event) => {
    this.setState({ name: event.target.value });
  };

  render() {
    return (
      <div>
        <input
          type="text"
          value={this.state.name}
          onChange={this.handleNameChange}
        />
      </div>
    );
  }
}
```

**물론 다른 컴포넌트의 state 내부에서 해도된다. 혹은 분리된 state store(like redux) 에서도 해도된다.**

새로운 문자를 입력할 때 마다, `handleNameChange`는 호출된다. 

![state](https://d33wubrfki0l68.cloudfront.net/d92387dc57d2689c2b02e5f511b2b13c6b22433b/dbafb/assets/images/controlled-vs-uncontrolled/controlled-flow.png)

- 값은 ''로 시작
- a 입력하고 `handleNameChange`는 `a`를 가져오고 `setState`를 호출한다. 인풋은 a값을 가지기 위해 re-rendering된다.

**값을 `pushes`하는 flow 종류는 form component를 변하게 한다. 그래서 `Form` 컴포넌트는 항상 input의 현재 값을 가진다. (명시적으로 현재 값을 가지기 위한 요청을 할 필요 없이)**

또한 이것은 form component가 input 변경을 즉시 응답할 수 있다는 것을 의미한다. 예를 들어,

- validation과 같은 적절한 피드백
- 만약 모든 필드가 유효한 데이터를 가지지 않는다면 버튼을 disable하기
- 특정 input format을 강요하기 (신용 카드 번호 입력)

하지만 위와 같은 것들이 필요 없다면 uncontrolled component를 고려해라. 그러면 심플해진다.

### element를 controlled로 만드는 것

다른 form element들이 있다. checkboxes and radios and select, textareas. **만약 너가 prop을 통해 값을 세팅한다면, form element는 `controlled`가 될 수 있다.** 그것이 다야! form element가 값을 세팅하기 위해 각각 다른 prop을 가진다면, 그것들 요약할 수 있는 테이블이 있다. 

- type text는 onChange로 string
- type checkbox는 onChange로 bool값 

## Conclusion

controlled and uncontrolled form fields 둘다 merit가 있다. 니 상황을 평가하고 올바른 접근방식을 골라라. 만약 너의 form이 간단하다면 refs와 함께 uncontrolled를 사용하자. 

걍 controlled 사용하는게 확장성 측면에서 더 낫다고 생각이 든다.

- input 변경에 즉시 응답할 수 있다. 
  - [submit할 때 validate 하기](https://goshakkk.name/submit-time-validation-react/)
  - [만약 모든 필드가 유효한 데이터를 가지지 않는다면 버튼 disable하기](https://goshakkk.name/form-recipe-disable-submit-button-react/)
  - input format 따르게 하기
  - [Dynamic inputs](https://goshakkk.name/array-form-inputs/)
  - 등등, 아래 참조된 블로그를 참고하자.

마지막으로 특징 및 구현 방법을 정리하자.

- element에서 현재 값은 state 내에서 유지되어야 한다. 
  - 이 때, state는 상위 컴포넌트의 state에서 해도된다.
  - 혹은, separate state store(like redux)에서도 해도된다. 여튼 컴포넌트 내에서 유지만 되면 된다.
- state에 반영할 때마다, `setState`를 호출한다. 이 떄 input과 같은 엘리먼트는 반영된 state를 가지기 위해 re-rendering된다.

## 참고

[https://goshakkk.name/controlled-vs-uncontrolled-inputs-react/](https://goshakkk.name/controlled-vs-uncontrolled-inputs-react/)