# useEffect 완벽가이드

[useEffect 완벽가이드 번역](https://rinae.dev/posts/a-complete-guide-to-useeffect-ko#tldr-too-long-didnt-read---%ec%9a%94%ec%95%bd)

내맘대로 요약해보기

## TLDR;

Q. useEffect로 componentDidMount 동작 흉내내기 가능?
A. 완전히 같진 않지만 가능 `useEffect(fn, [])`. 얘는 componentDidMount나 다른 라이프사이클 메서드와 다르다는 점을 인지하자. 생산적으로 접근하기 위해 "이펙트 기준으로 생각하기", 이 멘탈 모델은 동기화를 구현하는 것에 가깝다. 라이프사이클 메서드 이벤트에 응답하는 것과는 다르다.

Q. useEffect의 두번쨰 인자인 배열은 뭐지?
A. `[]`는 이펙트에 리액트 데이터 흐름에 관여하는 어떤 값도 사용하지 않겠다느 뜻.(그래서 한번 적용되어도 안전하다는 뜻). 잘못된 방식으로 의존성 체크를 생략하는 것보다 의존성을 필요로 하는 상황을 제거하는 몇가지 전략(`useReducer`, `useCallback`)을 익히자.

Q. 이펙트 의존성 배열에 함수 가능할까?
A. [이 글을 주목하자](https://rinae.dev/posts/a-complete-guide-to-useeffect-ko#tldr-too-long-didnt-read---%ec%9a%94%ec%95%bd). 만약 useEffect 내부에서 prop이나 컴포넌트 내부 state를 이용하여 함수를 호출하는 동작이 있다고 하자. 이 떄 useEffect의 의존성 배열이 [] 라면, 내부 prop이나 state가 변경되더라도 함수 내부에서 사용되는 prop이나 state는 절대 변경되지 않는다. 왜냐하면

요약하면,
React data flow(prop, state)에 있고 hook 내부에서 사용되는 모든 값을 포함해야한다.
그래서 이걸 해결할 방법은 두 가지다.

1. 해당 함수를 useEffect 내부로 가져와서 useEffect에 함수에서 사용하는 prop, state를 dependecy list에 추가
2. useCallback에 함수 선언하여, 함수에서 사용하는 prop, state dependency list에 추가. useEffect에서는 함수만 디펜던시로 추가.

Q. 이펙트 안에서 이전 state나 prop 참조할때
A. 보통 비동기 함수 내에서 state를 사용할 때, 비동기 호출이 일어나거나 처리 되기 전에 state가 변경되더라도, 비동기 함수내에서는 호출 당시의 state를 바라본다. 이렇게 동작하는 이유는 prop이나 state가 변경되지 않는다고 가정하여 코드로 인한 버그를 방지할 수 있기 때문이다. 여튼 우리는 최신값이 필요한데 이걸 해결할 방법은 ref를 통해 값을 직접 참조하는 것이다. 코드샌드박스에 간단히 만들어보았다. [async-fn-use-component-state](https://codesandbox.io/s/async-fn-use-component-state-642qo)

## 모든 렌더링은 고유의 Prop과 State가 있다.

```js
function Counter() {
  const [count, setCount] = useState(0);

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>Click me</button>
    </div>
  );
}
```

count는 그냥 primitive한 숫자다.
데이터 바인딩, 워쳐,프록시와 같은 마법같은 일이 일어나지 않는다.

count는 그저 숫자다.

**그럼 count의 값은 어떻게 변경되는걸까?**
바인딩된것도 아니고, 워쳐 프록시 이런게 아닌데..

**count가 변경될 때마다 함수가 다시 호출(리렌더링)된다.**
**그리고 호출 결과물은 고유의 count 상태값을 "살펴본다"**
이 값은 함수 안에서 상수로 존재한다.

다시 말하면, setCount호출시 리액트는 다른 count 값과 함께 컴포넌트를 재호출한다.

중요한거는 **count** 상수는 시간이 지난다고 변경되는것이 아니다.
**컴포넌트가 다시 호출되고, 각 렌더링마다 격리된 고유의 count값을 "보는 것"이다.**

> _위 문장이 모든걸 요약한다_
> 위 문장을 이해하려면 UI 런타임에서 React을 읽어보자.
> React element를 영화의 프레임으로 비유하는데, 매 순간 어떻게 보여야 되는지만 파악하고 변경되지 않는다 라는 말을 이해하면 된다.

## 모든 렌더링은 고유의 이벤트 핸들러를 가진다.

```js
function Counter() {
  const [count, setCount] = useState(0);

  function handleAlertClick() {
    setTimeout(() => {
      alert('You clicked on: ' + count);
    }, 3000);
  }
  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>Click me</button>
      <button onClick={handleAlertClick}>Show alert</button>
    </div>
  );
}
```

1. show Alert 누른다
2. 3초 되기 전에 버튼 3번 누른다
3. alert의 출력값은?

출력값과 그 이유를 설명할 수 있다면 이번 단원을 잘 이해한거다.

먼저, **count 값이 매번 별개의 함수 호출마다 존재하는 상수다.**
매번 별개의 함수 호출이라는 뜻은, 리렌더링 될 때마다 함수는 호출된다.
각 렌더링에서 함수 안의 count는 상수이자 독립적인 값(특정 렌더링의 상태)로 존재한다.

근데 이 얘기는 리액트에만 한정되는게 아니다.

```js
function sayHi(person) {
  const name = person.name;
  setTimeout(() => {
    alert('Hello, ' + name);
  }, 3000);
}

let someone = { name: 'Dan' };
sayHi(someone);

someone = { name: 'Yuzhi' };
sayHi(someone);

someone = { name: 'Dominic' };
sayHi(someone);
```

컴포넌트의 상태(예컨대 prop)가 함수에 재할당 되는 것처럼 함수도 인자값이 재할당 되며 호출된다.
sayHi 내부에서, 특정 호출마다 person과 엮여있는 name이라는 지역 상수(const)가 존재한다.
name은 지역 상수라, 각각의 함수 호출로부터 분리되어 있다. 결과적으로 setTimeout내부의 name 변수는 고유의 name을 가진다.

이와 같이 클릭 이벤트 핸들러가 렌더링마다 각각의 count값을 바라보는 것을 확인할 수 있다.

```js
// 처음 랜더링 시
function Counter() {
  const count = 0; // useState() 로부터 리턴
  // ...
  function handleAlertClick() {
    setTimeout(() => {
      alert('You clicked on: ' + count);
    }, 3000);
  }
  // ...
}

// 클릭하면 함수가 다시 호출된다
function Counter() {
  const count = 1; // useState() 로부터 리턴
  // ...
  function handleAlertClick() {
    setTimeout(() => {
      alert('You clicked on: ' + count);
    }, 3000);
  }
  // ...
}

// 또 한번 클릭하면, 다시 함수가 호출된다
function Counter() {
  const count = 2; // useState() 로부터 리턴
  // ...
  function handleAlertClick() {
    setTimeout(() => {
      alert('You clicked on: ' + count);
    }, 3000);
  }
  // ...
}
```

위에서 설명한 것처럼.. 렌더링 될 때마다 그 프레임만을 기억한다는 점, 즉 render 될 때의 값들을 유지한다는 점을 떠올리자.

위 Counter를 통해 정리하자면,

이벤트 핸들러는 특정 핸들러에 "속해 있다".
그래서 얼럿 표시 버튼 클릭시 **그 렌더링 시점의 counter state를 유지한채로 사용** 한다.
따라서, 이벤트 핸들러 내부의 비동기 함수라 할지라도 같은 count 값을 보게된다.

> 그렇다면, 참조값인 객체는 어떨까?
> 원시값이 아니라 참조값이기 때문에 이벤트 핸들러의 count가 count: {value:string} 로 구성되어있다고 하자.
> 그래도 동일한 결과를 나타낼 것이다.
> 왜냐하면 함수가 매번 호출될 때마다 불변 값을 사용하기 때문이다.

## 모든 렌더링은 고유의 이펙트를 가진다

```js
function Counter() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    document.title = `You clicked ${count} times`;
  });
  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>Click me</button>
    </div>
  );
}
```

위 이펙트는 어떻게 최신의 count를 유지할까?

위 함수는 각 리렌더링에 속한 count 상태, 이펙트 를 가진다.
즉, 이펙트 내의 함수 자체가 렌더링마다 별도로 존재한다.(dependency가 없다는 점을 참고하자)
이펙트도 마찬가지로 렌더링마다 별도로 존재한다.

그래서, 리액트는

1. 제공한 이펙트 함수를 기억해뒀다가 DOM 변화를 처리하고
2. 브라우저가 스크린에 그리고 난 뒤 실행합니다.

> 개념적으로 이펙트는 렌더링 결과의 일부
> 엄격하게 이야기하자면 아니지만, 이펙트 함수는 특정 렌더링에 속한 함수다.

시나리오로 보면 더 빠르게 이해할 수 있다.

첫 렌더링 시

1. 리액트: state가 0일 때 UI 내놔
2. 컴포넌트

- <p>You clicked 0 time</p> 여깄수다
- 그리고 처리 다하고 나서 이 이펙트 실행해줘. () => {document.title = 'you clicked 0 time'}

3. 리액트 : ㅇㅇ 먼저, UI 업데이트할게. 브라우저야 DOM에 추가할거 생김
4. 브라우저: ㅇㅇ 화면에 그림
5. 리액트: 이제 이펙트 실행하자

- () => {document.title...} 실행

버튼 클릭 후 다음 렌더링도 동일하다.

## 모든 렌더링은 고유의 ... 모든 것을 가지고 있다

class component vs functional component with hook

[class component](https://codesandbox.io/s/kkymzwjqz3)

```js
componentDidUpdate() {
  setTimeout(() => {
     console.log(`You clicked ${this.state.count} times`);
  }, 3000);
}
```

class component에서 동일하게 버튼 클릭시 다른 값이 나온다.

#### 왜때문에?

`this.state.count`는 특정 렌더링 시점의 값이 아닌 언제나 최신의 값이다.
this.state는 불변값이다. 하지만, 최신의 값을 참조하기(point to) 때문이다.

이 문제는 클로저로 해결 가능하다.
this.state.count를 const count로 다시 할당하여 setTimeout 함수 내에서 이 값을 바라보도록 하면 해결된다.

## 여기까지 읽고 정리

Q. useEffect를 componentDidMount처럼 사용 가능한가?
A. ㅇㅇ 가능하다. 하지만 둘이 완전히 같지 않다. useEffect로 스케줄링된 이펙트는 브라우저 스크린 업데이트를 막지 않는다. useEffect의 첫번째 인자는 브라우저의 레이아웃과 페인트 후에 비동기로 실행되기 때문이다. class component의 componentDidMount와 componentDidUpdate는 렌더링 후에 동기적으로 실행된다.

Q. 그럼 class component의 라이프사이클의 동기 실행과 useEffect의 비동기 실행의 차이가 뭘까?
A. 만약에 effect의 콜백이 DOM을 직접 변경한다면(ref를 통해서), DOM 변경 시점은 렌더링 되고 effect 콜백이 수행 될 때 일어난다. 이렇게 될 경우, 유저는 깜박이는 걸 볼 수 있다. 클래스 컴포넌트의 라이프사이클처럼 동기적으로 수행해야하는데, 이 때는 useLayoutEffect를 사용하면 된다. useLayoutEffect는 모든 DOM 변경 후에 동기적으로 **즉시** 수행한다. 코드는 DOM이 업데이트된 직후에 실행되지만, 브라우저가 변경 사항을 페인트 하기 전에 실행된다. (브라우저가 다시 페인트 될 때까지 사용자는 실제로 업데이트를 보지 못하기 때문이다.)

Q. DOM이 업데이트가 됐는데 브라우저가 페인트 되기 전까지 보지 못한다는 말은 무슨말인가?
A. 브라우저는 DOM과 CSSOM 트리를 결합하여 렌더링 트리를 생성한다. 완료되면 레이아웃(혹은 reflow)을 진행한다. 이것은 뷰포트내의 정확한 위치와 크기를 계산한다.(CSSOM에서 DOM트리의 각 노드에 계산된 스타일을 기반으로). 이제 실제 화면에 픽셀로 변환하는 마지막 작업인 페인트를 실시한다. 이 페인트가 일어나야 유저는 변경된 화면을 볼 수 있다.

Q. hook을 통해 만들어진 함수형 컴포넌트를 설명해달라.
A. 컴포넌트 자체 상태의 경우 클래스 컴포넌트와 비교하자면, 함수형 컴포넌트는 렌더링 될 때의 값들을 유지한다. 클래스 컴포넌트의 this.state는 최신 값을 바라본다. 함수형 컴포넌트의 useState의 경우 렌더링 될 당시의 값을 유지한다. 왜냐하면 this.state 처럼 어떤 값을 바라보는게 아닌, 특정 렌더링에 속한 값이다.

Q. useEffect의 라이프사이클은 정확히 어느시점인가?
A. 리액트가 브라우저에게 업데이트할 DOM tree를 전달한 후에(?)
