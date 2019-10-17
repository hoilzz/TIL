# iterator-generator-iterable

[JS의 Iterator와 Generator](https://ui.toast.com/weekly-pick/ko_20151021/)

콜백지옥을 해결하기 위해, Promise를 통해 조금 완화할 수 있었다.

## 제너레이터란?

**함수의 실행을 중간에 멈췄다가 필요 시점에 다시 재개할 수 있다.**

- 함수 실행 도중에 멈추고, **제어권을 다른 곳으로 넘겨줄 수 있고 값도 전달할 수 있다.**

iterator는 연속적이고 종료시에 값을 반환하도록 정의된 객체

- `iterator protocol`을 정의

> [iterator protocol](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Iteration_protocols#The_iterator_protocol)
> iterator 객체는 `next()` 메서드를 구현한 객체
> `next` 프로퍼티는 적어도 2가지 프로퍼티를 가진 객체를 반환하고 파라미터를 갖지 않는 함수
>
> - done(boolean) : iterator가 끝을 지났다면 true 반환, 끝이 안지났다면 false
> - value : iterator가 반환한 값. done이 true면 생략될 수 있음

iterator obj는 next를 반복적으로 호출하여 **명시적으로** iterate된다.
iterator를 반복 호출 하는 것은 iterator를 **사용** 하는 것이다. 이렇게 말하는 이유는 **단 한 번만** 수행할 수 있기 때문

- 이터레이터 가장 마지막 값이 나오고 나서 `next()` 호출하면 `{done: true}`를 리턴

## generator 함수

실행이 연속적이지 않은 1개의 함수를 작성하여 개발자가 iterative algorithm을 직접 정의할 수 있음

- generator 함수는 `function*`문법을 사용하여 작성됨.
- 생성자 함수가 최초 호출시 함수 내부의 어떤 코드도 실행 안됨
  - 대신 생성자라고 불리는 `iterator type` 반환
- 생성자의 next 메서드 호출하여 어떤 값이 소비되면
- 생성자 함수는 yield 키워드 만날 때까지 실행됨.

- 생성자 함수는 원하는 맘큼 호출되고
- 매번 새로운 생성자 반환
- 각 생성자는 단 한번만 순회됨

```js
function* quips(name) {
  yield 'hello ' + name + '!';
  yield 'i hope you are enjoying the blog posts';
  if (name.startsWith('X')) {
    yield "it's cool how your name starts with X, " + name;
  }
  yield 'see you later!';
}
```

## Iterables

Object는 없고 Array or Map과 같은 일부 내장 타입은 iterable 가능
(string, map, set, array 모두 iterable)

iterable하기 위해 **@@iterator** 메서드를 구현해야함. 즉 객체가 Symbol.iterator 속성을 가져야함.

```js
var myIterable = {
  *[Symbol.iterator]() {
    yield 1;
    yield 2;
    yield 3;
  },
};

for (let value of myIterable) {
  console.log(value);
}
```

## faq

Q. Generator 함수란?
A. 함수의 실행을 중간에 멈췄다가 필요 시점에 다시 재개 가능. 생성자 함수 최초 호출시 iterator type을 반환하는데, 이 때 next 메서드를 호출하여 어떤 값이 소비되면 다음 yield 키워드까지 실행됨.
