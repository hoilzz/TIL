# closure 알아보기

[what is a closure](https://medium.com/javascript-scene/master-the-javascript-interview-what-is-a-closure-b2f0d2152b36)

클로저는 중요하다. 왜냐하면 클로저는 특정 함수 내의 스코프에 있는 것과 없는것을 제어하고 동일한 스코프 내에 있는 형제 함수 간에 변수를 공유하기 때문이다.
변수와 함수가 서로 연관되는 방식은 중요하니까 이해해야한다. 그래야 코드에서 무슨일이 일어나는지 알 수 있으니까..

## 클로저란

클로저는 함수를 둘러싼 상태(**lexical 환경**)에 대한 참조로 번들된 함수의 결합이다.
다시말해서, 클로저는 내부 함수에서 외부 함수 스코프에 대한 접근을 가능하도록 한다.
JS에서 클로저는 함수가 **생성** 될 떄마다 생성된다.

클로저를 사용하기 위해, 다른 함수 내부에서 함수를 정의하고 노출시켜라.
여기서 노출은 그 함수를 리턴하거나 다른 함수에 전달해야 한다.

내부 함수는 외부함수 스코프의 변수에 대한 접근이 가능하다. (외부함수가 리턴되고 나서도..)

## 클로저 사용하기

클로저는 일반적으로 객체에 private 데이터를 제공하는데 사용된다. private 데이터는 구현이 아닌 interface로 프로그래밍하는데 도움이 되는 필수 속성이다.
이것은 좀 더 robust한 sw를 만들도록 도움을 주는 중요한 컨셉이다. 왜냐하면 interface 보다 구현체가 변경될 가능성이 더 높기 때문이다.

> 구현체가 아닌 인터페이스를 프로그래밍 해라
> [Design Pattern](https://www.amazon.com/gp/product/B000SEIBB8?ie=UTF8&camp=213733&creative=393177&creativeASIN=B000SEIBB8&linkCode=shr&tag=eejs-20&linkId=CSQYBHTUP625XI4T)

JS에서 클로저는 private 데이터를 가능하도록 해주는 주요 메커니즘이다.
private data를 위해 클로저를 사용할 때, enclosed된 변수는 외부 함수 스코프에만 존재한다.
**객체의 권한을 가진 메서드** 를 거치는 방법을 제외하고 외부 스코프에서 데이터를 가져올 수 없다.
JS에서 클로저 스코프에서 노출된 메서드는 특권을 가진다.

예를 들어보자,

```js
// https://jsbin.com/gareno/edit?js,console,output
const getSecret = secret => {
  return {
    get: () => secret
  };
};

test('Closure for object privacy.', assert => {
  const msg = '.get() should have access to the closure.';
  const expected = 1;
  const obj = getSecret(1);

  const actual = obj.get();

  try {
    assert.ok(secret, 'This throws an error.');
  } catch (e) {
    assert.ok(
      true,
      `The secret var is only available
      to privileged methods.`
    );
  }

  assert.equal(actual, expected, msg);
  assert.end();
});
```

`.get` 메서드는 `getSecret()` 스코프 내부에서 정의되었다.
이것은 getSecret()의 변수에 접근할 수 있고 특권을 가진 메서드로 만들어준다.
위 케이스의 경우에, 파라미터 `secret` 변수에 접근할 수 있다.

---

객체로만 private data를 만들 수 있는건 아니다.
클로저는 내부 상태에 영향을 받는 값을 리턴하는 **stateful function** 을 만들 때 사용된다.

```js
// Secret - creates closures with secret messages.
// https://gist.github.com/ericelliott/f6a87bc41de31562d0f9
// https://jsbin.com/hitusu/edit?html,js,output

// secret(msg: String) => getSecret() => msg: String
const secret = msg => () => msg;

test('secret', assert => {
  const msg =
    'secret() should return a function that returns the passed secret.';

  const theSecret = 'Closures are easy.';
  const mySecret = secret(theSecret);

  const actual = mySecret();
  const expected = theSecret;

  assert.equal(actual, expected, msg);
  assert.end();
});
```

함수형 프밍에서, 클로저는 partial application & currying에서 연속으로 사용된다.
이것은 몇몇 정의를 필요로한다.

Application: return value를 만들기 위해 _인자_ 를 함수에 applying 하는 과정

Partial Application: 부분적으로 적용된 함수는 나중에 사용하기 위해 리턴된다. Partial application은 리턴된 함수 내부에서 1개 이상의 인자를 수정한다.
그리고 리턴된 함수는 function application을 완성하기 위해 남아있는 파라미터를 인자로 이용한다.

Partial application은 파라미터를 **fix** 하기 위해 클로저 스코프의 이점을 이용한다. 타겟 함수에 인자를 부분적응로 적용하는 generic 함수를 작성할 수 있다. 다음 시그니처를 갖는다.

```js
partialApply(targetFunction: Function, ...fixedArgs: Any[]) =>
  functionWithFewerParams(...remainingArgs: Any[])
```

여러개의 인자를 이용하는 함수를 가지고, 함수에 부분적으로 다음 인자를 적용할 수 있다. 그리고 남아있는 인자를 가지는 함수를 리턴한다.

```js
const add = (a, b) => a + b;
```

숫자에 10을 더해주는 함수를 만들어보자. 우리는 `add10()`이라고 부를거다. `add10(5)`의 결과는 15다.
`partialApply()` 함수를 이용하자

```js
const add10 = partialApply(add, 10);
add10(5);
```

이 예제에서 `10`은 **fixed parameter** 가 되고, `add10()` 클로저 스코프 내부에서 기억된다.

```js
function partialApply(fn, ...rememberedArgs) {
  return function(...restArgs) {
    return fn.apply(null, rememberedArgs.concat(restArgs));
  };
}

const add = (a, b) => a + b;

const add10 = partialApply(add, 10);

add10(5);
```

partialApply() 함수로 전달되는 인자인 rememberedArgs에 접근할 수 있는 함수를 간단히 리턴할 수 있다.

## QNA

Q. 클로저란?
A. 내부 함수에서 외부함수 스코프에 대해 접근 가능한것과 같이 함수를 둘러싼 상태에 대해 참조가능한 함수. 클로저는 함수가 생성될 때마다 생성된다.

Q. 클로저를 사용하려면?
A. 어떤 함수 내부에서 외부 함수 스코프에 대한 접근 가능하도록 한다. 그래서 그 함수를 리턴하건나 다른 함수의 인자로 전달한다.

Q. 클로저를 어떻게 활용할 수 있나?
A. private 데이터 제공. 이 데이터는 외부 함수 스코프에만 존재하므로 private 하게 접근 가능하다. 그래서 이 스코프에 접근 가능한 메서드를 생성하여 리턴하여 사용가능하다.
또한, stateful 함수를 만들 수 있다. 이것은 currying을 이용하여 생성된다.
