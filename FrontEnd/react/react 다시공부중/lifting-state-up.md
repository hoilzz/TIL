# Lifting State Up

여러 컴포넌트가 동일한 변경 데이터 반영하기. 이 때, 가장 가까운 공통 조상에게 state를 lifting up 하기.

`onTemperatureChange` prop은 `Calculator` component에 의해 `temperature` prop이 함께 제공될 것이다. 자신의 local state를 수정하여 그것을 처리할 것이고, 양쪽 input을 `re-rendering`하여 새 값을 반영할 것이다. 

## 1. 단순 온도 입력기

```javascript
class Calculator extends React.Component {
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
    this.state = {temperature: ''};
  }

  handleChange(e) {
    this.setState({temperature: e.target.value});
  }

  render() {
    const temperature = this.state.temperature;
    return (
      <fieldset>
        <legend>Enter temperature in Celsius:</legend>
        <input
          value={temperature}
          onChange={this.handleChange} />

        <BoilingVerdict
          celsius={parseFloat(temperature)} />

      </fieldset>
    );
  }
}
```

state를 통해 controlled component로 생성하여 온도 입력시 state 반영 후, 리렌더링 하여 반영된 값 노출한다.

## 2. Second Input 추가하기

Celsius input외에, Fahrenheit input 추가하기. 2개의 input은 서로 sync 유지해야 한다.

먼저, 다음과 같이 input 컴포넌트를 생성하여 재사용 하기위해 `TemperatureInput` component 생성하자.

```javascript
class Calculator extends React.Component {
  render() {
    return (
      <div>
        <TemperatureInput scale="c" />
        <TemperatureInput scale="f" />
      </div>
    );
  }
}
```

```javascript
const scaleNames = {
  c: 'Celsius',
  f: 'Fahrenheit'
};

class TemperatureInput extends React.Component {
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
    this.state = {temperature: ''};
  }

  handleChange(e) {
    this.setState({temperature: e.target.value});
  }

  render() {
    const temperature = this.state.temperature;
    const scale = this.props.scale;
    return (
      <fieldset>
        <legend>Enter temperature in {scaleNames[scale]}:</legend>
        <input value={temperature}
               onChange={this.handleChange} />
      </fieldset>
    );
  }
}
```

```javascript
class TemperatureInput extends React.Component {
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(e) {
    this.props.onTemperatureChange(e.target.value);
  }

  render() {
    const temperature = this.props.temperature;
    const scale = this.props.scale;
    return (
      <fieldset>
        <legend>Enter temperature in {scaleNames[scale]}:</legend>
        <input value={temperature}
               onChange={this.handleChange} />
      </fieldset>
    );
  }
}
```

input 컴포넌트 2개를 가지지만, 둘 중 하나의 값을 업데이트할 때 다른 거는 업데이트 되지 않는다. sync가 유지되야 하는 조건을 만족시키지 못한다.

## 3. Writing Conversion Functions

2개 함수 작성할거다 (C to F, F to C). 그리고 각 상황에 맞게 호출하도록 함수 하나 더 생성할 거다.

```javascript
function toCelsius(fahrenheit) {
  return (fahrenheit - 32) * 5 / 9;
}

function toFahrenheit(celsius) {
  return (celsius * 9 / 5) + 32;
}

function tryConvert(temperature, convert) {
  const input = parseFloat(temperature);
  if (Number.isNaN(input)) {
    return '';
  }
  const output = convert(input);
  const rounded = Math.round(output * 1000) / 1000;
  return rounded.toString();
}
```

## 4. Lifting State Up

현재, `TemperatureInput` 컴포넌트는 독립적으로 local State를 유지한다. 

```javascript
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
    this.state = {temperature: ''};
  }

  handleChange(e) {
    this.setState({temperature: e.target.value});
  }

  render() {
    const temperature = this.state.temperature;
    // ...  
```

독립적으로 유지하게 되면 서로 sync 맞출 수 없다. 즉, C-input 업데이트 하면 F가 동시에 반영되야한다.(반대도 마찬가지). **React에서 state를 공유하는 것은 가장 가까운 조상에게 그 값을 lifting up 함으로써 구현할 수 있다.** 그래서 local state를 제거하고 상위 컴포넌트(Calculator)로 값을 이동시키는 것을 구현할 거다.

왜 이렇게까지 하냐면, `source of truth` 때문이다. 

현재 input의 `temperature`와 `scale`을 TemperatureInput의 상위 컴포넌트인 Calculator의 local State 안에 저장할 것이다. 그리고 이것은 input 컴포넌트 둘 다에게 `source of truth`로써 제공될 것이다. 

```javascript
class TemperatureInput extends React.Component {
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(e) {
    this.props.onTemperatureChange(e.target.value);
  }

  render() {
    const temperature = this.props.temperature;
    const scale = this.props.scale;
    return (
      <fieldset>
        <legend>Enter temperature in {scaleNames[scale]}:</legend>
        <input value={temperature}
               onChange={this.handleChange} />
      </fieldset>
    );
  }
}
```

```javascript
class Calculator extends React.Component {
  constructor(props) {
    super(props);
    this.handleCelsiusChange = this.handleCelsiusChange.bind(this);
    this.handleFahrenheitChange = this.handleFahrenheitChange.bind(this);
    this.state = {temperature: '', scale: 'c'};
  }

  handleCelsiusChange(temperature) {
    this.setState({scale: 'c', temperature});
  }

  handleFahrenheitChange(temperature) {
    this.setState({scale: 'f', temperature});
  }

  render() {
    const scale = this.state.scale;
    const temperature = this.state.temperature;
    const celsius = scale === 'f' ? tryConvert(temperature, toCelsius) : temperature;
    const fahrenheit = scale === 'c' ? tryConvert(temperature, toFahrenheit) : temperature;

    return (
      <div>
        <TemperatureInput
          scale="c"
          temperature={celsius}
          onTemperatureChange={this.handleCelsiusChange} />

        <TemperatureInput
          scale="f"
          temperature={fahrenheit}
          onTemperatureChange={this.handleFahrenheitChange} />

        <BoilingVerdict
          celsius={parseFloat(celsius)} />

      </div>
    );
  }
}
```

## Lesson Learned

React app에서 변경되는 데이터에 대한 단일 `source of truth`가 있어야 한다. 보통, 렌더링을 위해 state를 필요로 하는 컴포넌트에 state가 추가된다. 그리고나서, 만약 다른 컴포넌트가 그것을 필요로 한다면, 가장 가까운 조상 컴포넌트로 그것을 리프팅 up 할 수 있다. 다른 component 간의 state를 sync 맞추려고 시도하는 것 대신에, `top-down` data flow에 의존해야 한다.

`Lifting State`는 two-way binding보다 코드를 더 많이 작성하지만 이점이 있다. 버그를 찾는데 덜 작업해도 된다. 어떠한 state가 component에 존재하고 그 컴포넌트만 그것을 변경할 수 있기 때문에, 버그 지역이 크게 줄어든다. 또한, user input을 변형하거나 거절하기 위해 custom 로직을 구현할 수 있다. 

만약 props or state에서 상속되는 값이 있다면, 그것은 state 내부에 있지 않아야 한다. 예를 들어, celsius값, fahreheit값 둘 다 저장하는 것 대신에, 가장 최근에 편집된 온도와 그것의 scale만 저장한다. 다른 input 값은 항상 `render()` 내부에서 계산된다. 이를 통해 사용자 입력에서 정밀도를 잃지 않고 다른 필드에 반올림을 적용하거나 지울 수 있다. 

## Summary

요약하자면,  여러 컴포넌트가 동일한 변경 데이터를 반영할 때, 가장 가까운 공통 조상에게 값을 lifting up 하자. 그래서 조상 컴포넌트는 props로 해당 값을 사용하는 컴포넌트에게 내려주자.(`top-down`)

왜 쓸까?
- source of the truth
    - 버그 찾는데 덜 작업해도 된다. 왜냐하면 상위 컴포넌트만 값을 변경 할 수 있기 떄문이다. 그래서 버그 지역도 줄어든다.


