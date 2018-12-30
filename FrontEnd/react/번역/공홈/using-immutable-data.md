# Optimizing Performance

내부적으로, React는 UI를 업데이트하기 위해 필요한 DOM 동작을 최소화 하기 위해 현명한 방법을 사용한다. 많은 application에서, React를 사용하면 성능 최적화를 위해 많은 작업을 수행하지 않고도 빠른 사용자 인터페이스를 이끌어 낼 수 있다. 그럼에도 불구하고, React application을 빠르게 할 수 있는 방법이 있다.

## shouldComponentUpdate In Action

components의 서브트리를 보자.

![shouldComponentUpdate](https://facebook.github.io/react/img/docs/should-component-update.png)

- `SCU` : `shouldComponentUpdate`가 리턴하는 것을 가리킨다.
- `vDOMEq` : 렌더링된 React element가 동일한지 여부를 나타낸다.
- circle's color는 컴포넌트가 변경 이전과 이후의 값이 일치하는지 여부를 나타낸다.

subtree의 루트인 C2에서 `shouldComponentUpdate`가 `false`를 리턴하기 때문에,
React는 C2를 렌더링하지 않는다. 따라서 C4와 C5에서 `shouldComponentUpdate` 호출하지 않는다.

C1과 C3에서, `shouldComponentUpdate`를 `true`를 리턴한다. 그래서 React는 자식 컴포넌트를 따라 내려가고 그것들을 확인한다. 렌더링된 엘리먼트는 React가 update해야하는 DOM과 일치하지 않기 때문에 C6의 경우 `true`를 리턴한다.

마지막 흥미로운 C8이다. React는 이 컴포넌트를 렌더링 해야한다. 하지만 React element는 이전의 렌더링 한것과 동일하기 때문에 DOM을 업데이트 하지 않는다.

React는 C6의 DOM 변경만을 해야만 한다. C8의 경우 제외되고, C2의 서브트리와 C7도 제외된다.




> shouldComponentUpdate란
```javascript
shouldComponentUpdate(nextProps, nextState){
    console.log("shouldComponentUpdate: " + JSON.stringify(nextProps) + " " + JSON.stringify(nextState));
    return true;
}
```
prop 혹은 state 가 변경 되었을 때, 리렌더링을 할지 말지 정하는 메소드입니다.
위 예제에선 무조건 true 를 반환 하도록 하였지만, 실제로 사용 할 떄는 필요한 비교를 하고 값을 반환하도록 하시길 바랍니다. (
```javascript
return nextProps.id !== this.props.id;
```
를 쓰면 여러 field 를 편하게 비교 할 수 있답니다.



## Examples

Component의 변경 방식이 `props.color` or `state.count` 변수가 바뀔 때라면,
`shouldComponentUpdate`를 확인해야한다.

```javascript
class CounterButton extends React.Component {
  constructor(props) {
    super(props);
    this.state = {count: 1};
  }

  shouldComponentUpdate(nextProps, nextState) {
    if (this.props.color !== nextProps.color) {
      return true;
    }
    if (this.state.count !== nextState.count) {
      return true;
    }
    return false;
  }

  render() {
    return (
      <button
        color={this.props.color}
        onClick={() => this.setState(state => ({count: state.count + 1}))}>
        Count: {this.state.count}
      </button>
    );
  }
}
```

위 코드에서, `shouldComponentUpdate`는 단순히 `props.color`나 `state.count`에 변화 여부만 체크한다. 만약 값이 안바꼈다면 컴포넌트는 없데이트 되지 않는다. 만약 컴포넌트가 복잡해지면, 컴포넌트가 업데이트 되야하는지 결정하기 위해 `props`와 `state` 필드간 shallow comparison`을 하는 것과 같은 비슷한 패턴을 이용해야 한다.

```javascript
class CounterButton extends React.PureComponent {
  constructor(props) {
    super(props);
    this.state = {count: 1};
  }

  render() {
    return (
      <button
        color={this.props.color}
        onClick={() => this.setState(state => ({count: state.count + 1}))}>
        Count: {this.state.count}
      </button>
    );
  }
}
```

`shouldComponentUpdate`를 작성하는 것 대신에 `React.PureComponent`를 사용한다.
이거는 `shallow comparison`만 할 수 있다. **만약에 `shallow comparison`이 놓칠 수 있는 방식으로 props나 state가 변경된다면, 우린 이것을 사용할 수 없다.**

더 복잡한 데이터 구조에 경우 문제가 될 수 있다. 예를 들어 `ListOfWords` Component가 comma로 구분된 단어 리스트로 렌더링 되기를 원한다고 해보자. (버튼을 클릭하면 list에 단어를 추가하는 `WordAdder`라는 부모 component와 함께). 다음 코드는 올바르게 동작하지 않을 것이다.


```javascript
class ListOfWords extends React.PureComponent {
  render() {
    return <div>{this.props.words.join(',')}</div>;
  }
}

class WordAdder extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      words: ['marklar']
    };
    this.handleClick = this.handleClick.bind(this);
  }

  handleClick() {
    // This section is bad style and causes a bug
    const words = this.state.words;
    words.push('marklar');
    this.setState({words: words});
  }

  render() {
    return (
      <div>
        <button onClick={this.handleClick} />
        <ListOfWords words={this.state.words} />
      </div>
    );
  }
}
```

위 코드의 문제점은 `pureComponent`는 `this.props.words`의 변경 전 값과 변경 후 값 사이에 **단순한 비교**를 할것이다. 위 코드는 `WordAdder`의 `handleClick`에서 `words` 배열을 변경하기 때문에, `this.props.words`의 변경 전과 변경 후 값이 동일하다고 비교될 것이다. (배열 안의 단어가 바꼈더라도..). 따라서, 렌더링 되야 하는 새 단어를 가지고 있더라도 `ListOfWords`는 업데이트 되지 않을 것이다.

---

# The Power Of Not Mutating Data

이 문제를 피하기 위한 가장 간단한 방식은 값을 변경하지 않는 것이다.

# Using immutable Data Structure

Immutable.js는 이 방법을 풀 수 있는 다른 방법이다.
이것은 **구조적 공유를 통해 작동하는** immutable, persistent collections을 제공한다.

- *Immutable* : 한 번 생성된 collection은 다른 시점에서 변경될 수 없다.
- *persistent* : 이전 collection으로 new collection을 생성한다. 원래 컬렉션은 새로운 컬렉션이 생성되고 나서도 여전히 유효하다.
- *Structural Sharing* : new collections은 가능한 original collection과 동일하게 생성된다. (이것은 복사를 최소화하여 성능을 향상시킨다.)

Immutability는 tracking의 변경을 cheap하게 만든다. 변경은 항상 새로운 object의 결과를 낳아서 우리는 오브젝트에 대한 참조가 변경되었는지 확인만 하면된다. 예를 들어 다음 코드를 보자.

```javascript
const x = { foo: 'bar' };
const y = x;
y.foo = 'baz';
x === y; // true
```

`y`가 수정되었더라도, 동일한 오브젝트(`x`)에 대해 참조를 하기 때문이다.
`immutable.js`로 동일한 코드를 작성할 수 있다.

```javascript
const SomeRecord = Immutable.Record({foo: null});
const x = new SomeRecord({foo: 'bar'});
const y = x.set('foo', 'baz');
x === y; // false
```

이번의 경우에 `x`를 변경할 때 새 참조를 반환받는다.

immutable data를 사용하도록 돕는 2개의 라이브러리는 `seamless-immutable`과 `immutability-helper`다.

Immutable data 구조는 너에게 object에 대한 변화를 추적하기 위해 cheap way를 제공한다.
이것은 `shouldComponentUpdate`를 구현하기 위해 필요한 모든것이다.
이것은 너에게 nice performance boost를 제공한다.



---

다른글

# React.js와 불변객체

`shouldComponentUpdate` 메서드는 컴포넌트가 다시 그려지기 전에 호출된다.
만약 `false` 반환시 컴포넌트의 VirtualDOM을 비교하지 않는다.

다량의 엘리먼트를 필요하는 리스트나 피드와 같은 컴포넌트는 매번 VirtualDOM을 비교하게 될 경우,
성능 이슈가 발생한다. 떄문에 필수로 사용해야 하는 메서드다. (되도록 모든 컴포넌트에 작성하자)

## 가변 객체일 때

위와 비슷하다.

객체의 참조는 여튼 동일한 객체를 가리키거나 동일한 객체에 대해 비교를 하기 때문에 렌더링은 계속 안될 것이다. 그것에 대한 해결책으로 이 블로그에서는 먼저, 오브젝트를 클론한다.

즉, 객체 상태를 전부 복사하여 새로운 객체를 만들어 컴포넌트에 전달한다. 이러한 방법은 defensive copy라고 한다.

코드는 의도한대로 작동하겠지만, 비교문은 여전히 복잡하고 매번 객체를 전체적으로 복사하기 때문에 성능면에서 좋지 않다.

그래서 불변객체를 이용한다.

- 매번 객체를 새로 생성하여 메모리 관리에 부담을 줄 수 있지만 시스템에서 병목을 일으킬일은 없다.
- 오히려 객체의 값을 전체적으로 복사하는 방어적 복사가 더 부담될 수 있다. 왜?
