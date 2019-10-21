# useEffect 완벽가이드 3

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
