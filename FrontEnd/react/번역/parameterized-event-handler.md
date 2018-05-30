# ReactJS - 파라미터로 바꾼 이벤트 핸들러

React Component의 이벤트 핸들러를 파라미터로 전달하는 것은 필수다. 이벤트에 대한 참조값이 필수인지에 따라 ES6로 이벤트 핸들러를 파라미터로 전달 할 수 있는 방법은 다양하다.

## Using the bind function

이벤트 핸들러를 this로 바인딩하는 것을 정의할 수 있다.

```javascript
handleClick(e) {
  console.log('Clicked', e);
}
render() {
  <button onClick={this.handleClick.bind(this)}></button>
}
```

만약 custom parameter를 전달할 필요가 있다면, bind 호출시 파라미터에 전달하면 된다. SyntheticEvent는 핸들러에 두번쨰 파라미터로 전달될 것이다.

```javascript
handleClick(param, e) {
  console.log('Parameter', param);
  console.log('Event', e);
}

render() {
  <button onClick={this.handleClick.bind(this, 'Parameter')}></button>
}
```

위에서 JSX prop 값인 `bind` 호출 함수는 렌더링할 때마다 새로운 함수를 생성할 것이다. 이것은 성능에 좋지 않고, 그 결과 가비지 컬렉터가 필요 이상으로 호출될 것이다. 또한, 업데이트 여부를 결정하기 위해 prop의 참조값 equality 여부를 체크하는 component에 새로운 함수가 prop으로 전달되면, 불필요한 리렌더를 발생시킨다.

렌더링 할 때마다 새로운 함수를 생성하는 것을 피하기 위해 constructor에서 함수를 바인딩할 수 있다.

```javascript
class MyComponent extends React.Component {

  constructor() {
    super();
    this.handleClick = this.handleClick.bind(this, 'Parameter');
  }

  handleClick(param, e) {
    console.log('Parameter', param);
    console.log('Event', e);
  }

  render() {
    <button onClick={this.handleClick}></button>
  }
}
```

button의 onClick prop에서 이벤트 핸들러를 지정하는 동안, 함수를 바인딩 할 필요가 없다. 그러나 이 방식의 단점은 파라미터에 동적으로 값을 전달할 수 없는 것이다.

## Using ES6 arrow function

`bind`를 매번 호출하는 것은 귀찮다. `bind` 호출을 피하기 위해 `this`를 자동으로 함수에 바인딩 해주는 ES6의 arrow function을 사용할 수 있다.

```javascript
handleClick(e) {
  console.log('Event', e);
}

render() {
  <button onClick={(e) => this.handleClick(e)}></button>
}
```

또한, arrow function을 이용할 경우 이벤트 핸들러에 추가 파라미터도 전달할 수 있다.

```javascript
handleClick(param, e) {
  console.log('Parameter', param);
  console.log('Event', e);
}

render() {
  <button onClick={(e) => this.handleClick(param, e)}></button>
}
```

위 예제 둘 다의 문제는 컴포넌트가 렌더링 될 때마다 다른 콜백 인스턴스가 생성되는 것이다. `bind` function과 동일한 문제다.

모든 렌더링 마다 새로운 콜백 인스턴스 생성을 피하기 위해, callback을 bind하기 위해 property initializer 문법을 사용할 수 있다.

```javascript
handleClick = (e) => {
  console.log('Event', e);
}

render() {
  <button onClick={this.handleClick}></button>
}
```

property initializer을 통해 이벤트 핸들러에 파라미터를 전달하기 위해, 우리는 currying을 이용해야 한다

```javascript
handleClick = (param) => (e) => {
  console.log('Event', e);
  console.log('Parameter', param);
}

render() {
  <button onClick={this.handleClick('Parameter')}></button>
}
```

커링은 호출 될 때마다 새로운 인스턴스가 생성되는 점을 주목하자.

## Conclusion

currying으로 arrow function을 사용하는 것은 유저가 정의한 파라미터를 받는 이벤트 핸들러를 정의하기 위한, 깔끔하고 가장 간결(가장 효율적이지는 않지만)한 방법이다.

> 마지막에 알려준 커링과 arrow function으로 작성한 이벤트 핸들러도 컴포넌트가 re-rendering될 경우 새로운 함수를 생성하는건 마찬가지일거라는 생각이 들었다. 댓글을 보자.

## 댓글

1. 반박댓글

curried arrow function 또한 렌더링 될 때마다 새로운 메서드를 생성할 것이다. 알려준 방식은 나쁘다고 말하는 것은 아니지만, 그 방법은 다른 옵션들보다 반드시 "더 낫다고" 할 수 없다. 개인적으로 나는 extra parameter가 필요할 때 inline callback을 선호한다.

2. 필자

currying은 렌더링 될 때마다 새로운 함수를 생성하지 않을 것으로 생각한다. 하지만, 새로운 함수는 버튼이 클릭 될 때마다 생성된다. onClick handler가 호출 될 때만 새로운 함수가 생성될 것이다.

3. 반박댓글

*??Whenever you add parenthesizes after a function you are calling it??*. 그래서 curry 예제는 렌더링 될 때 호출된다. 생성된 함수는 이벤트 핸들러로 할당될 것이다.

만약 렌더링 될 때마다 새로운 함수가 생성되는 것을 원하지 않는다면(하지만 이전 코멘트에서 말했듯이, 새로운 함수가 만들어지는 것에 대해 걱정할 필요가 없다. 적어도 application을 프로파일링 하고 성능 이슈가 있다는것을 알기 전까지는 걱정할 필요 없다.), 사용될 함수 인스턴스를 가진  new class component를 생성해야 한다. 인스턴스 함수는 커링 없이 prop, state, etc를 통해 custom parameter에 접근할 수 있다.
[ http://jsbin.com/rozayedibe/edit?js,console,output]( http://jsbin.com/rozayedibe/edit?js,console,output) 요기서 예제 볼 수 있다.

## Summary

해당 포스트에서 리렌더링 될 때마다 새로운 함수가 생성됨으로써 생기는 성능 이슈를 최종적으로 제안한 커링 + arrow function 으로 해결하려 했다. 하지만, 해당 방식도 렌더링 될 때마다 새로운 함수가 생성된다. 그래서 해당 방식으로는 렌더링 될때마다 새로운 함수 인스턴스가 생기는 이슈를 해결할 수 없다. 또한, 댓글에서는 application의 프로파일링, 성능이슈가 있다는 것을 인지하기 전까지 걱정할 필요가 없다고 제안한다. ([이 글과 관련된 포스팅](https://cdb.reacttraining.com/react-inline-functions-and-performance-bdff784f5578) : 요약하면, 이론적으로는 맞다. 하지만 제대로 증명된 것은 없고 섣부른 최적화) 그리고 extra parameter가 필요할 경우 inline callback을 사용하고 굳이 새로운 함수가 생성되는 것을 원하지 않는다면 함수 인스턴스를 가진 클래스 컴포넌트를 생성하는 방식을 보여줬다.

아래 링크는 댓글의 예제 코드에 함수 참조값을 비교하여 새로운 객체가 생성됐는지 비교하는 버튼을 추가한 예제다.

[![Edit k5xzxn6ppr](https://codesandbox.io/static/img/play-codesandbox.svg)](https://codesandbox.io/s/k5xzxn6ppr)