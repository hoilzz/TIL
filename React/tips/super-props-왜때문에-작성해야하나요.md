# Why do We Write super(props) 요약해보자.

[why do we write super props](https://overreacted.io/why-do-we-write-super-props/)

```js
class Checkbox extends React.Component {
  constructor(props) {
    // 🔴 Can’t use `this` yet
    super(props);
    // ✅ Now it’s okay though
    this.state = { isOn: true };
  }
  // ...
}
```

부모 생성자 호출 하기 전에는, `this`는 생성자에서 사용 못한다.

## 이걸 왜 강제했을까?

```js
class Person {
  constructor(name) {
    this.name = name;
  }
}

class PolitePerson extends Person {
  constructor(name) {
    this.greetColleagues(); // 🔴 This is disallowed, read below why
    super(name);
  }
  greetColleagues() {
    alert('Good morning folks!');
  }
}
```

관련해서 ES6 class 문법을 간략하게 정리해보자.

**constructor**

부모 클래스의 생성자를 호출하기 위해 `super` 키워드를 사용한다.

extends를 통한 클래스 상속

```js
class Animal {
  constructor(name) {
    this.name = name;
  }

  speak() {
    console.log(this.name + ' makes a noise');
  }
}

class Dog extends Animal {
  speak() {
    console.log(this.name + ' barks.');
  }
}
```

subclass에 생성자가 있다면, "this"를 사용하기 전에 가장 먼저 super()를 호출해야 한다.
**자식 클래스의 constructor에서 super()를 호출하지 않으면 this에 대해 참조 에러 발생한다.**

> 클래스는 생성자가 없는 객체(non-constructible)를 확장할 수 없다.

super를 통해 상위 클래스 호출을 할 수 있는데, 이는 객체의 부모가 가지고 있는 함수들을 호출하기 위해 사용.
