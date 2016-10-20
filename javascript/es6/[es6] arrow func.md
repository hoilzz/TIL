# arrow function
  화살표 함수 식은 function에 비해 구문이 짧고 (자신의 this, arguments, super 또는 new target을 바인딩 하지 않는) this 값을 렉시컬 바인딩 합니다. 화살표 함수는 항상 익명이다.

## Syntax
> (param1, param2, ... paramN)

블럭 바디를 갖는 화살표 함수의 경우 어떤 값을 자동으로 리턴하지 않는다는 사실에 주의하자. 어떤 값을 리턴하려면 return 구문 사용. 화살표 함수를 이용해서 단순 객체 리턴시, 해당 객체를 항상 괄호로 묶어줘야 한다.

```javascript
var chewToys = puppies.map(puppy => {});    // BUG!!
var chewToys = puppies.map(puppy => ({}));  // OK
```

비어있는 객체 `{}`와 비어이는 블록 `{}`은 보기에 똑같다. ES6 규칙에 따르면 화살표 다음에 오는 `{` 기호는 언제나 블록의 시작으로 취급합니다.
객체리터럴을 괄호로 묶는다는 주의사항만 기억하자.

# this

통상적인 function함수와 화살표 함수 사이에는 약간의 차이가 있다.
- 화살표 함수는 자기 고유의 `this` 값을 갖지 않음
- 화살표 함수 안의 `this` 값은 언제나 화살표 함수를 감싸는 외부 스코프에서 계승 받음

딴 얘기 해보자.
- js에서 `this`는 어떻게 결정되나요?
- `this`는 어디에서 유래하나요?

이 문제가 그토록 자주 제기되는 이유는 `function` 함수의 `this`값이 자동으로 주어지기 때문.

다음과 같은 꼼수 써본 경험이 있을테다.

```javascript
{
  ...
  addAll: function addAll(pieces) {
    var self = this;
    _.each(pieces, function (piece) {
      self.add(piece);
    });
  }
}
```
내부 함수에서 우리가 정말 쓰고 싶은 코드는 `this.add(piece)`
- 내부 함수는 외부 함수의 `this`값을 계승하지 않음
- 내부 함수 `this`값은 `window` or `undefined`가 됨
- 임시 변수 `self`는 외부 함수의 `this` 값을 내부 함수에서 참조하기 위해 사용함

ES6의 경우, 다음과 같은 규칙을 따른다면 `this`와 관련된 꼼수를 쓰지 않아도 됩니다.
- `object.method()` 문법을 통해 호출하는 메서드는 화살표 함수가 아닌 일반함수를 사용하자.
  - 그런 함수들은 호출자로부터 의미 있는 `this`값을 전달 받는다.
- 그 밖의 모든 경우는 화살표 함수 사용하자.

```javascript
{
  addAll: function addAll(pieces) {
    _.each(pieces, piece => this.add(piece));
  },
}
```

ES6에서, addAll 메서드는 호출자로부터 `this`를 전달 받음
- 내부 함수는 화살표 함수이기 때문에, **`this`값을 자신을 감싸는 외부 스코프로부터 계승 받음**

ES6는 객체 리터럴 안에 메서드를 간략하게 정의하는 표기법도 제공, 그래서 위의 코드를 좀 더 간결하게 만들 수 있음

```javascript
{
  addAll(pieces) {
    _.each(pieces, piece => this.add(piece));
  }
}
```
- 메서드와 화살표 중간에 더이상 `function`이라고 쓰지 않아도 됨
- 화살표 함수와 일반 함수 사이에 차이점이 하나 더 있다.
  - 화살표 함수는 `arguments` 객체가 전달되지 않음
  - ES6을 쓴다면 `arguments` 객체보다 레스트(rest) 파라미터나 디폴트 파라미터가 더 좋을거다.
