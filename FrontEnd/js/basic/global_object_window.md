# 전역객체 window

### Window 객체
모든 객체가 소속된 객체이고, 전역객체이면서, 창이나 프레임을 의미

### 전역객체
Window 객체는 식별자 window를 통해서 얻을 수 있다.
또한 생략 가능.
Window 객체의 메소드 인출방법

> window.alert('hello world');

전역변수 a에 접근하는 방법

> var a = 1;
> alert(a);
> alert(window.a);

객체를 만든다는 것은 결국 window객체의 프로퍼티를 만드는 것고 ㅏ같다

> var a = {id:1};
> alert(a.id);
> alert(window.a.id);

예제를 통해서
전역변수와 함수가 사실은 window 객체의 프로퍼티와 메서드라는 것
또한 객체는 사실 window의 자식이라는 것도 알 수 있다
이러한 특성을 ECMAScript에서 Global 객체라고 부른다

웹브라우저 자바스크립트에서
Window 객체는 ECMAScript의 전역객체이고
웹브라우저의 창이나 프레임을 제어한다.
