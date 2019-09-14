# Curry or Partial Application

JS에서 curry의 실제 사용을 보는것은 드문일이기 때문에, 많은 유틸 함수은 curry 함수가 아닌데 스스로 curry()라고 부른다. 실제로 그것은 partial application 함수다.

## 정의

- **Application** : return value를 만들기 위해 인자를 함수에서 적용하는 과정
- **Partial Application** : 인자를 함수에 적용하는 과정. 부분적으로 적용된 함수는 나중에 사용하기 위해 리턴된다. 즉, 여러개의 파라미터를 가진 함수를 사용하고 더 적은 매개변수가 있는 함수를 반환하는 함수다. Partial application은 리턴된 함수 내부의 1개 이상의 인자를 **fix(고정)한다** 그리고 리턴된 함수는 함수를 완료하기 위해 남아있는 파라미터를 인자로 이용한다.

- **Curry** : 여러개의 파라미터를 가진 함수를 input으로 이용하고 정확히 1개의 매개변수가 있는 함수를 리턴하는 함수다.

## 왜 이것이 중요할까?

기능은 함수 타입의 균일함에 따라 다르다.
함수는 타입을 가진다. 예를 들어, 함수와 배열을 이용하여 배열을 리턴하는 함수가 있다.
(e.g. Function.prototype.map())

```js
(fn, array) -> array
```

- partial application은 **예측가능한 리턴 타입을 가질수도 가지지 않을 수도 있다**
- curried function은 모든 인자가 적용될 때까지 항상 arity가 1인(인자는 1개) 다른 함수를 리턴한다.

**function type uniformity** 에 의존하는 것.
예를 들어, promise가 시간에 따른 logic의 의존성을 추상화하는데 도움을 주는 방식에 대해 얘기했다.

promises는 너가 호출하는 함수가 뭐든간에 promise가 **lift** 하기 때문에, return type은 항상 일관성있다. promise를 리턴하는 모든 함수는 동일한 타입을 리턴한다. 이것은 너가 표준화된 방식으로 promise를 사용할 수 있다는 것을 의미한다.

promise는 **functors** 와 같은 _container_ 다. 이것은 데이터 타입에 관계없이 컨테이너 내부에서 데이터를 처리하기 위한 표준화된 방식을 제공할 수 있다.

**container 내부의 값** 대신에 **containers** 를 처리하여, 컨테이너의 interface를 사용하는 어느것이든 보편적으로 동작하는 많은 generic 함수를 만들 수 있다.

promise와 같이, **curried function은 container** 를 리턴한다. 이 컨테이너는 동일한 인터페이스를 공유한다. 이 경우에 **리턴된 함수는 컨테이너다**. 모든 인자를 다 사용하고 최종 값이 반환될 때까지 리턴된 함수를 계속 호출하면 된다.

즉, **curried function은 모든 인자를 lift할 수 있는 함수다.** 그래서 표준화된 방식으로 인자를 처리할 수 있다.

가장 일반적인 유즈케이스는 [합성함수](https://medium.com/javascript-scene/master-the-javascript-interview-what-is-function-composition-20dfb109a1a0)다. (e.g. `c(x) = f(g(x))`) 합성 함수는 1개 함수의 리턴 값을 이용하여 다른 함수의 인자로 전달한다. 함수는 1개의 값만 리턴하기 때문에, 리턴 값을 적용한 삼수는 단항(unary)이어야 한다.

추가적으로, **curried function은 내장 iterator 메커니즘을 가진다** : curried function은 부분적으로 1개 인자를 적용한다. 1개 인자로 할 수 있는 것 이상의 동작을 하지 않는다. 리턴된 함수를 호출하는 것은 다음 스텝을 적용하기 위해 함수에게 말하는 것이다.

예를 들어, curreid function a(b)(c); 는 c application을 당장 호출하지 않는다. 다음과 나눌 수 있다.

```js
const next = a(b);
doSomeStuff().then((0 => next(c)));
```

partial application과 curry의 차이점에 대해 명확히 이해해야한다. 그리고 왜 함수를 커링하고 싶은지에 대해 이유를 알아야한다.

FP에서 커링의 일반적인 유즈케이스는 함수를 compose하기 더 쉽게 만든다.

## 만들어보자.

```js
var plus = function(a, b, c) {
	return a + b + c;
}

var partialApply = function(fn, ...fixedArgs) {
  return function(...remainArgs) {
    return fn(...fixedArgs.concat(...remainArgs))
  }
}

// plus10이라는 partial application 생성
// var plus10 = partialApply(plus, 10)
var plus10 == plus.bind(null, 10);
```

```js
var curryFn = fn => {
  var targetLength = fn.length;
  var memoArgs = [];

  // 커링은 인자를 1개만
  function next(arg) {
    memoArgs = memoArgs.concat(arg);
    // fn bind 호출
    if (memoArgs.length === targetLength) {
      return fn.apply(null, memoArgs);
    } else {
      return function(nextArg) {
        return next(nextArg);
      };
    }
  }
  return next;
};

var plus = (a, b, c) => a + b + c;
var plusCurried = curryFn(plus);

plusCurried(10)(20)(30);
```

## QNA

Q. 둘의 차이점은?
A. partial Application은

- 기존 함수의 매개변수들 중 일부를 미리 넣어둔 새로운 함수를 반환. 만들어진 partial Application은 다음 호출시 무조건 결과 반환.
- 예측가능한 리턴 타입을 가지거나 가지지 않을 수 있다.

curry는

- 기존 함수의 매개변수를 1개씩 받는다. 매개변수를 모두 받을 때까지 새로운 함수를 반환. 1개씩 받은 매개변수는 클로저 환경에서 저장.
- 모든 인자를 받을 때까지 새로운 함수를 반환하니까, 표준화된 방식으로 인자 처리 가능.
- 일반적으로 합성 함수.. c(x) = f(g(x));
