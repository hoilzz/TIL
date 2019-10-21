## 5-2

### 흐름을 거슬러 올라가기

컴포넌트 렌더링안의 있는 모든 함수(이벤트 핸들러, 이펙트 등)은 **렌더가 호출될 때 정의된 props와 state를 잡아둔다.**

아래 두 예제는 같다.
props.counter를 하여 props의 참조값을 바라보는 것 같지만 단순히 렌더가 호출될 당시의 prop이다.

```js
function Example(props) {
  useEffect(() => {
    setTimeout(() => {
      console.log(props.counter);
    }, 1000);
  });
  // ...
}

function Example(props) {
  const counter = props.counter;
  useEffect(() => {
    setTimeout(() => {
      console.log(counter);
    }, 1000);
  });
  // ...
}
```

만약 위의 클래스 컴포넌트 동작처럼 최신 값을 이용하고 싶다면 useRef를 통해 상태의 참조값을 바라보면 된댜.

```js
function Example() {
  const [count, setCount] = useState(0);
  const latestCount = useRef(count);
  useEffect(() => {
    // 변경 가능한 값을 최신으로 설정한다
    latestCount.current = count;
    setTimeout(() => {
      // 변경 가능한 최신의 값을 읽어 들인다
      console.log(`You clicked ${latestCount.current} times`);
    }, 3000);
  });
  // ...
```

## cleanup은 뭐야?

클린업의 목적은 구독과 같은 이펙트를 되돌리는 것이다.

```js
useEffect(() => {
  ChatAPI.subscribeToFriendStatus(props.id, handleStatusChange);
  return () => {
    ChatAPI.unsubscribeFromFriendStatus(props.id, handleStatusChange);
  };
});
```

첫번째 렌더링에서 prop이 {id: 10} 이고, 두 번쟤 렌더링에서 {id: 20}이라고 하면,

1. id:20 을 가지고 UI 렌더링
2. 브라우저가 리액트가 던져준 DOM 트리로 그리기 시작. 화면에서 id:20 을 볼 수 있음
3. id:10에 대한 이펙트 클린업.
4. id:20을 가지고 이펙트 실행.

## 라이프사이클이 아닌 동기화

리액트는 prop과 state에 따라 DOM과 동기화한다. 동일하게 이펙트도 리액트 트리 바깥에 있는 것들을 props과 state에 따라 동기화할 수 있다.

## 리액트에게 이펙트 비교하는 법 가르치기

매 리렌더링마다 DOM 전체를 새로 그리는게 아닌, 리액트가 실제로 바뀐 부분만 DOM을 업데이트한다.

```js
<h1 className="Greeting">
  Hello, Dan
</h1>

<h1 className="Greeting">
  Hello, Yuzhi
</h1>

const oldProps = {className: 'Greeting', children: 'Hello, Dan'};
const newProps = {className: 'Greeting', children: 'Hello, Yuzhi'};
```

위 객체를 비교하여 prop의 chilren만 바뀐걸 파악했다. 그래서 아래 코드만 호출된다.

```js
domNode.innerText = 'Hello, Yuzhi';
```

## 리액트에게 의존성 거짓말 하지 말기

```js
function SearchResults() {
  async function fetchData() {
    // ...
  }

  useEffect(() => {
    fetchData();
  }, []); // 이게 맞을까요? 항상 그렇진 않지요. 그리고 더 나은 방식으로 코드를 작성하는 방법이 있습니다.

  // ...
}
```

마운트 될 때만 data를 가져온다고 말할 수 있지만,
컴포넌트에 있는 모든값 중 그 이펙트에 사용될 값(props, state, 함수)은 반드시 deps에 있어야한다.

위 코드는 가끔 문제를 일으킨다. 데이터 불러오는 로직이 무한루프에 빠질 수도 있고, 소켓이 너무 자주 반응할 수도 있다.
**이 문제를 해결하는 건 의존성을 제거하는게 아니다**

## 의존성 거짓말하면 생기는 일.

```js
function Counter() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    const id = setInterval(() => {
      setCount(count + 1);
    }, 1000);
    return () => clearInterval(id);
  }, []);
  return <h1>{count}</h1>;
}
```

effect가 한번만 실행되야 하므로, deps에 []를 넣는다.
**하지만 예제는 숫자가 딱 한 번만 증가한다.**

deps는 이펙트를 언제 다시 실행해야하는지 알려줘야할 떄 쓰인다. 그래서 setInterval 한번 실행해놓고 알아서 동작하도록 deps를 []로 작성했다. 근데 왜 문제가 발생할까?

deps의 또다른 정의는 **어떤 렌더링 스코프에서 나온 값 중 이펙트에 쓰이는 전부를 알려주는 힌트** 라고 인식하면 숫자가 한번 증가하는게 맞다. 하지만 deps는 []라고 정의했기 때문에 이펙트를 절대 다시 실행하지 않고 매 초마다 setCount(0 + 1)만 실행한다.

해결책을 찾아보자.

## 의존성 솔직하게 적기

두가지 전략이 있다.

1. 이펙트안에서 사용되는 모든 값이 의존성 배열안에 포함되도록 고치기

```js
useEffect(() => {
  const id = setInterval(() => {
    setCount(count + 1);
  }, 1000);
  return () => clearInterval(id);
}, [count]);
```

count가 변경될 떄마다 인터벌은 해제-재설정을 반복한다. 불필요한 동작이 많다.

2. 이펙트의 코드를 바꿔서 의존성을 적게 넘겨주기

의존성 제거하는 몇가지 기술을 알아보자.

## 이펙트가 자급자족 하기

일단 count를 뭐땜에 쓰고있는지 알아보자. 오로지 setCount때문에 쓴다.
이 경우 스코프 안에서 count를 사용할 필요가 없다. 이전 상태를 기준으로 업데이트할 수 있는 함수형 업데이터를 전달하면 된다.

```js
useEffect(() => {
  const id = setInterval(() => {
    setCount(c => c + 1);
  }, 1000);
  return () => clearInterval(id);
}, []);
```

리액트에게 어떻게 상태가 바껴야 하는지 알려줄 수 있는 함수를 보낸다.
위 방법은 의존성을 제거하지 않고도 실제로 문제를 해결할 수 있따는 점을 나타낸다.

## qna

Q. 리렌더링 될 떄, 클린업은 언제 일어나는가?
A. 브라우저가 리액트가 던져준 DOM 트리를 그리고 나서

Q. 리액트는 이펙트 내의 함수를 매번 재실행하는가?
A. deps를 정해주지 않으면 매번 재실행, deps를 정해주면 재실행을 막을 수 있다.
