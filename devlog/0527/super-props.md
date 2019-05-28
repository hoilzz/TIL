# super(props) 왜 작성해야 할까?

[https://velog.io/@honeysuckle/%EB%B2%88%EC%97%AD-Dan-Abramov-%EC%99%9C-superprops-%EB%A5%BC-%EC%9E%91%EC%84%B1%ED%95%B4%EC%95%BC-%ED%95%98%EB%8A%94%EA%B0%80](https://velog.io/@honeysuckle/%EB%B2%88%EC%97%AD-Dan-Abramov-%EC%99%9C-superprops-%EB%A5%BC-%EC%9E%91%EC%84%B1%ED%95%B4%EC%95%BC-%ED%95%98%EB%8A%94%EA%B0%80)

얘를 읽고 다시 요약.

---

`super`는 부모 클래스 생성자다. 리액트에서는 `React.Component`다.

중요한 것은 super(props) 선언 전까지 `this`키워드 사용할 수 없다.

```js
class Person {
    constructor(name) {
        this.name = name;
    };
};

const PolitePerson extends Person {
    constructor(name) {
        this.greetColleagues(); // 이것은 허용되지 않는다. 이유를 읽어보자
        super(name);
    };

    greetColleagues() {
        alert('Good morning folks!');
    };
};
```

super 선언전에 `this`를 사용했다고 하자.

시간이 지난 뒤 `greetColleagues`메서드에 메세지를 추가해야한다고 하자.

```js
greetColleagues() {
    alert('Good morning folks!');
    alert('My name is' + this.name + ', nice to meet you');
}
```

`this.greetColleagues()`가 `super()`가 불려오기 전에 실행되었는데, `this.name`은 아직 변경되지 않았다. 이러한 코드는 논리를 복잡하게 만든다.

이런 단점을 보완하기 위해 `super` 키워드 실행 이후 `this`를 사용할 수 있게 한다.

```js
constructor(props) {
    super(props);
    // this 사용 가능!
    this.state = { isOn: true };
};
```

또, `this.props`의 초기 설정을 위해 `props`를 `super`에 넣어준다고 생각할 수 있다.

사실이다. 실제로 하는일이다. (근데 생성자 함수에서 하지 않더라도 컴포넌트 인스턴스 생성 후에 props를 할당한다.)
