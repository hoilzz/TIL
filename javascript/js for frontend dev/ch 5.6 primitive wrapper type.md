## 5.6 원시 래퍼 타입

Boolean, Number, String은 원시 값을 편리하게 조작하기 위해 디자인된 참조 타입이다.

**원시 값 읽을 때마다 해당 래퍼 타입이 이면에서 생성되므로** 메서드를 사용할 수 있다.

```javascript
var s1 = "some text";
var s2 = s1.substring(2);
```

원시 값은 객체가 아니므로 논리적으로 메서드를 가질 수 없다.

하지만 메서드를 호출했고 동작했다.

이것은 위 2번째 줄에서 **읽기 모드로 s1에 접근하는 순간**,

다시 말해 메모리에서 값을 읽는 순간 다음 세 단계가 일어났다.

1. String 타입의 인스턴스를 만든다.
2. 해당 인스턴스에서 메서드를 호출한다.
3. 인스턴스를 파괴한다.

위 내용을 코드로 적으면

```javascript
var s1 = new String("some text");
var s2 = s1.substring(2);
s1 = null;
```

이와 같은 동작이 발생하므로 원시 문자열 값을 마치 객체처럼 사용가능하다.

`참조 타입`과 `원시 래퍼 타입`의 **주요 차이**는 `생명 주기`다.

---

new 연산자를 사용한 참조 타입의 인스턴스는 스코프를 벗어날 때까지 메모리에 존재한다.

자동으로 생성된 원시 래퍼 타입은 코드의 해당 행을 벗어나는 즉시 파괴된다.

따라서 원시 래퍼 타입에는 런타임에 프로퍼티나 메서드 추가 불가능하다.

```javascript
var s1 = "some text";
s1.color = "red";
alert(s1.color); // undefined
```

2번째 행에서 s1에 color란 프로퍼티를 추가하지만 다음 행에서 바로 파괴된다.

3번째 행 실행시 다른 String 객체가 생성되며 여기에는 color 프로퍼티가 존재하지 않는다.

---

물론 Boolean, Number, String 생성자를 사용해 명시적으로 원시 래퍼 객체를 생성할 수 있지만,

이렇게 하면 지금 다루는 값이 원시 값인지 래퍼 객체인지 혼란 스러울 수 있다. 그러므로 한정되서 사용해야 한다.

원시 래퍼 타입을 typeof에 대입하면 `object`를 반환한다.

```javascript
var str = "String";

var newStr = new String("string");

var str2 = String("String");

typeof str; // string
typeof newStr; // object
typeof str2; // string
```

- new 없이 래퍼 생성자를 사용하면, 래퍼 생성자가 인자를 원시 데이터 타입의 값으로 변환한다.

결론은 원시 데이터 값도 언제든 객체 처럼 사용할 수 있기 때문에, 장황한 래퍼 생성자를 사용할 필요가 없다.

그냥 `var num = 20`이라고 하면 되는데 굳이 `var num = new Number(20)`라고 할 필요가 없다.
