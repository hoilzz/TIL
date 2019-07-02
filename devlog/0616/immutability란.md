# immutablility

불변성은 객체가 생성된 이후 그 상태를 변경할 수 없는 디자인 패턴

- 객체는 참조 형태로 전달하고 전달받음
- 이는, 객체가 참조를 통해 공유되어 있다면 상태는 **언제든지 변경 가능**

  - 의도치 않은 변경이 일어난다면, 참조값을 가진 다른 장소에 변경 사실을 통지해야함

- 의도치 않은 변경이 일어나는 이유
  - 주로 참조값을 참조하는 값에서 객체를 변경하기 때문이다.
- 해결책은?

  - 객체를 불변객체로 만들어서 프로퍼티의 변경을 방지하고
  - 변경이 필요한 경우 참조가 아닌 **객체의 방어적 복사를 통해 새로운 객체를 생성하여 변경**

- 불변 객체의 이점
  - 복제나 비교를 위한 조작 단순화

## immutable value vs mutable value

원시타입은 immutable하다.

원시타입 이외의 모든 값은 객체 타입이고 mutable 하다.

### 원시타입은 immutable

JS에서 문자열은 immutable value인데 이러한 값은 primitive value다.
(변경 불가능한 값이다 = 메모리 영역에서의 변경 불가능하다. 재할당은 가능하다.)

```js
var str = 'Hello'; // 'Hello'의 메모리 주소
str = 'world'; // 'Hello 메모리 주소 값을 수정하는게 아닌, 새로운 문자열 'world'를 가리키도록 변경.
```

## mutable value(object)

```js
var arr = [];
arr.push(2);
```

배열(객체)의 메소드 push는 `직접 대상 배열을 변경`
그 이유는 배열은 객체고 객체는 mutable하기 때문이다.

```js
var user1 = {
  name: 'Lee',
  address: {
    city: 'seoul'
  }
};

var user2 = user1;

user2.name = 'Kim';
console.log(user1.name); // Kim
```

user2는 user1과 동일한 메모리 주소를 참조하고 있기 때문에 user1.name이 변경되었다.
이것이 의도한 동작이 아니라면 다른 장소에 변경 사실을 통지해야 한다.

## immutable data pattern

여튼 이와 같은 문제를 해결하기 위해,

- 비용이 들지만 객체를 불변객체로 만들어 프로퍼티 변경을 방지한다
- 변경이 필요한 경우 방어적 복사를 통해 새로운 객체 생성 후 변경
  - Object.assign() 을 이용할거지만 이 메서드도 shallow copy라서 deep copy를 위한 처리가 필요.
