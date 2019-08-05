# prop과 state는 왜 immutable일까?

[immutability in react](https://blog.logrocket.com/immutability-in-react-ebe55253a1cc/)를 번역해보았읍니다,,

## immutability?

불변성은 한 번 생성되면 값이나 상태를 변경하지 못하는 것을 의미한다.

간단한 컨셉이지만

String value type이 좋은 예제다.

string 문자를 직접 변경할 수 없다.

JS에서, string은 배열이 아니다. 그래서 index로 접근하여 값을 변경할 수 있다.

```js
var str = 'hoilzz';
str[2] = 'd';

// 다른 스트링을 할당할 수 있다.
str = 'meen';
```

## Value Type

스트링은 immutable이다.(생성되면 수정되지 않는다.) 하지만 string object는 아니다.

만약 object가 불변이라면, 상태(프로퍼티의 값)를 변경할 수 없다.
이것은 객체에 새로운 프로퍼티를 추가할 수 없다는 말이기도 하다.

```js
const str = 'hoilzz';
str.newProperty = 'gaga';

// undefined
console.log(str.newProperty);
```

만약 위 코드를 실행한다면, `undefined`를 볼 수 있다.

새 프로퍼티는 추가되지 않는다.

```js
const str = new String('hoilzz');
str.newProperty = 'gaga';

// gaga
console.log(str.newProperty);
```

String은 immutable인데,,

마지막 예제는 `String()` 생성자로 객체를 만들었다.
객체는 frozen 되어있지 않기 때문에 프로퍼티를 추가할 수 있다.

참조(reference)와 값(value)의 동등성의 차이를 이해하는 것은 중요하다.

## 참조 동등성 vs 값 동등성

참조 동등성으로, ===과 !==으로 object 참조값을 비교할 수 있다.
만약 참조값이 동일 객체를 가리킨다면, 동일다고 간주한다

```js
var str1 = 'abc';
var str2 = str1;
```

값이 불변이라면 str1과 str2는 동일한 값을 가리키기 때문에 값이 동일하다.

```js
var str1 = 'abc';
var str2 = 'abc';
str1 === str2; // true
```

하지만 객체라면.. 동일하지 않다.

```js
var str1 = new String('hzz');
var str2 = new String('hzz');

str1 === str2; // false
```

위 상황은 2개의 다른 객체가 생성되었고, 참조값은 동일하지 않다.

---

그래서..

React와 불변성은 어떻게 연관이 될까?

만약 2개의 객체가 immutable 하다면 동일한지 여부를 테스트하는 것이 쉬워진다.
그리고 리액트는 퍼포먼스 최적화를 만드는 데 이득을 얻는다.

## Performance Optimization in React

리액트는 virtual DOM이라 부르는 내부 UI를 유지한다.

컴포넌트의 프로퍼티나 상태가 변경 될 때, virtual DOM은 해당 변경을 반영하기 위해 업데이트 된다. virtual DOM을 조작하는 것은 쉽고 빠르다. **왜냐하면 UI에서 변하는 것은 아무것도 없기 때문이다.**

> virtual DOM은 단순히 객체로 이뤄진 elements들의 트리다. 어떤 클래스의 인스턴스도 아니다. 그래서 메서드도 가지고 있지 않다. 단순히 UI를 설명하는 object다.

그러고나서, 리액트는 변경된 것을 알기 위해 업데이트 전 버전과 virtual DOM을 비교한다. 이것은 [reconciliation](https://reactjs.org/docs/reconciliation.html) 이다.

이러한 방법으로, 변경된 엘리먼트만 real DOM에서 업데이트된다.

하지만 가끔, 변경한 것이 없을 때 다른 부분의 사이드 이펙트 때문에, 몇가지 DOM이 리렌더 된다.

이 경우에는 SCU(shouldComponentUpdate)를 사용하여 프로퍼티와 상태가 진짜 바뀐 경우에만 true를 리턴하여 리렌더를 하면 된다.

**만약 컴포넌트의 프로퍼티와 상태가 immutable한 객체거나 값이면, simple equality operator로 변경 여부를 체크할 수 있다.**

이러한 관점에서 불변은 복잡성을 제거한다.

왜냐하면 뭐가 변경됐는지 찾는 것은 어렵다.

```js
mypackage.sender.address.country.id = 1;
```

위와 같은 깊은 필드가 있다고 하자. (조금 오바한거지만..) 중첩 객체의 변경점을 효율적으로 찾는 방법이 있을까?

배열의 경우도 생각해보자.

**동일한 사이즈의 2개의 배열의 경우, 동일 여부를 따지는 유일한 방법은 각 엘리먼트를 모두 비교하는 것이다.**

가장 간단한 해결책은 불변 객체를 이용하는 것이다.

**만약 객체가 업데이트 되야한다면, 새로운 값을 가진 새로운 객체가 생성된다. 왜냐하면 원래꺼는 immutable하기 때문에 변경되지 못하기 때문이다.**

이제 참조값 비교만 하면 된다.

하지만 일부에게는 비일관성과 performance와 단순함에 대한 아이디어에 약간 모순되거나 반대되는 것으로
보일 수 있다.

## immutability 구현해보기

리얼 앱에서, 상태와 프로퍼티는 객체와 배열이다.

```js
const modifyShirt = (shirt, newColor, new Size) => ({
  id: shirt.id,
  desc: shirt.desc,
  color: newColor,
  size: newSize
})

const modifyShirt = (shirt, newColor, newSize) => {
  return Object.assign( {}, shirt, {
    color: newColor,
    size: newSize
  });
}

const modifyShirt = (shirt, newColor, newSize) => {
  return {
    ...shirt,
    color: newColor,
    size: newSize
  };
}
```

이러한 native 접근은 2가지 결점이 있다.

- 하나의 객체/배열 에서 프로퍼티와 요소를 다른 객체에 카피하여 동작한다. 즉, 큰 객체/배열 에서는 느릴 수 있다.
- 객체와 배열에서 mutable은 기본적으로 가능하다. 불변성을 강제할 수 없다.

라이브러리의 도움을 받자.
-> immutable.js를 사용해라.

## Persistent 데이터 구조

persistent 데이터 구조는 뭔가 수정될 떄마다 모든 버전에 접근을 제공하면서 새로운 버전을 생성한다.

만약 데이터 구조가 부분적으로 persistent하다면, 모든 버전은 접근 가능하지만 새로운 버전만 수정된다. 만약 데이터 구조가 전부 persistent하다면, 모든 버전은 접근 및 수정 가능하다.

> persistent는 값을 변경하는 API를 제공하지만,
> 매번 새 객체를 리턴하고 이전 객체는 계속 유지된다.
> https://ohgyun.com/585 참고

데이터 구조는 list나 map이지만 더 깊게 들어가면 trie라 불리는 트리다. 자세한건 위 포스팅을 참고하자.

[1,2,3,4,5] 배열의 인덱스를 4-bits 바이너리 숫자로 전환할 수 있다.

그림은 해당 [포스팅](https://blog.logrocket.com/immutability-in-react-ebe55253a1cc/)을 참고하자.

요약하자면, persistent를 나타낸다.

새 객체를 수정하고, 기존 버전은 유지된다.

이것은 **structural sharing** 이다.

## 단점

위에 나열한 단점을 극복하기 위해 immutable.js와 같은 라이브러리를 사용한다해도,

다음과 같은 점을 조심해야 한다.

- 커플링이 단계가 높아지는 점
- toJS와 같은 메서드는 좋지 않은 퍼포먼스를 가진다.

만약 새로운 데이터 구조를 구현하지 않는다면, 구조적 공유의 이점은 없다.
대부분의 경우와 같이, 업데이트 될 때 객체는 카피되고 몇몇 경우에(중첩이 심하고 큰 객체/배열..) 퍼포먼스는 고통받는다...

## 결론

불변 값 or 객체는 변경될 수 없다.

그래서 모든 업데이트는 새로운 값을 생성한다. 기존 값은 냅둔채로..

예를 들어, app 상태가 immutable하다면, 모든 상태 오브젝트를 단일 스토어에 저장하여 쉽게 undo/redo 기능을 구현할 수 있다.

친숙하게 들린다면.. 맞다.

git같은 버전관리 시스템도 동일한 방법으로 동작한다.

리덕스도 동일 원칙 기반이다.

그러나, 리덕스는 [pure function](https://medium.com/@jamesjefferyuk/javascript-what-are-pure-functions-4d4d5392d49c)의 측면과 앱 상태의 _snapshot_ 에 더 집중했다. 다음 [stackoverflow](https://stackoverflow.com/questions/34958775/why-should-objects-in-redux-be-immutable/34962065#34962065)의 답변도 리덕스와 불변성의 관계를 잘 설명했다.

불변성은 예상치 못한 사이드 이펙트를 피하기 or [커플링 줄이기](https://stackoverflow.com/questions/34385243/why-is-immutability-so-important-or-needed-in-javascript/43918514#43918514)와 같은 이점이 있다. 하지만 이것은 단점도 될 수 있다. 기억하자.. 프밍은 수많은 트레이드 오프를 거친다..

> 커플링 줄이기
> bar()가 올바르게 작동하기 위해 baz()를 호출해서 유효한 상태 객체를 가져와야한다.
> 근데 누가 이걸 알까?
> 이것을 이해하기 위해 클래스 내부를 면밀히 관찰해야한다.
> 이 문제는 수많은 변경가능한 상태를 가진 큰 코드베이스에서 폭발한다.
> 만약 Foo가 불변이라면 문제가 되지 않는다.
> baz나 bar를 어떤 순서로 호출하든 안전하다. 왜냐하면 내부 상태는 변경되지 않기 때문이다.

```
class Foo {
  baz() {
      // ....
  }
  bar() {
      // ....
  }
}
const f = new Foo();

f.baz();
f.bar();

f.bar();
f.baz();
```

## 참고

[리덕스와 immutability의 관계](https://stackoverflow.com/questions/34958775/why-should-objects-in-redux-be-immutable/34962065#34962065)

[불변성으로 커플링 줄이기](https://stackoverflow.com/questions/34385243/why-is-immutability-so-important-or-needed-in-javascript/43918514#43918514)

## 요약

immutable이란?

- 한 번 생성되면 값이나 상태를 변경하지 못한다.
  - 그럼 값을 어케 변경해..?
- 값이 변경된다면 새로운 값/객체를 생성한다.
  - 객체의 프로퍼티 1개만 바꼈는데 객체를 새로 만들면 손해 아니야? 1개 프로퍼티때문에?
- 새로 객체를 생성해서 얻는 이득은.. **동일여부 테스트** 용이
  - 객체의 참조값만 비교하면되니까..
- 만약 1개 프로퍼티만 수정하면.. 매번 모든 필드를 비교해야해서, 중첩된 객체일 경우 비교 테스트 어려움.

리액트와 immutable의 관계

- SCU나 PureComponent에서 얕은 비교하는데..
- prop이나 state를 immutable하게 유지한다면, 모든 필드를 비교하지 않고 참조값 변경만으로 변경 여부를 알릴 수 있다.
- 이러한 관점에서 불변은 복잡성을 제거한다.
- 여기서부터 내생각..
  - 하지만... SCU나 PureComponent에 객체를 전달하는건.. 적절하지 못한 선택이라고 생각한다.
  - SCU나 PureComponent는 얕은 비교를 하기 때문에
    - 참조값은 그대로지만, 중첩된 내부의 값이 변경되있거나
    - 객체를 전달 했을 경우에는 얕은 비교가 제대로 동작하지 않는다. (그래서 immutable한 값을 전달하라고!, 그럼 참조값만 비교하면 되니까 비교 속도도 빠르다!)
    - 가급적 간단한 구조 혹은 primitive한 값을 전달하여 불필요한 렌더링을 줄이자.

## 모르는거

커플링 줄이기에서 어떤 이득이 있는지 정확히 이해하지 못함..
