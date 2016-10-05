# 5.7 내장된 싱글톤 객체
Object나 Array, String 같은내장 객체 이외에 Global, Math 두 가지 싱글톤 객체를 더 정의

## 5.7.1 Global 객체
- 명시적으로 접근할 수 없다.
- 전역 변수나 전역 함수라는 것은 존재 하지 않는다. 전역에서 정의한 변수와 함수는 모두 Global 객체의 프로퍼티가 된다.
  + `isNaN()`, `isFinnite()`, `parseInt()` 등 Global 객체의 메서드

### URI 인코딩 메서드
- 브라우저에 전달할 URI를 인코드하는 메서드
- encodeURI(), encodeURIComponent()
- 쿼리 스트링을 인코드하는 경우가 많으므로 encodeURIComponent() 많이 사용

### eval() 메서드
- Global 객체에서 다룰 마지막 메서드는 강력한 eval()
- ECMAScript 인터프리터 자체인 듯 동작

  ```
  eval("alert('hi')");
  alert('hi');
  ```

- 위 두 문장은 동일
- **인터프리터가 eval()을 만나면 매개변수를 실제 ECMAScript 문장으로 해석하여 eval()이 있던 위치에 삽입**
  + 인자값은 eval을 호출한 실행 컨텍스트의 일부분으로 간주되며 해당 컨텍스트와 같은 스코프 체인을 갖음

  ```
  var msg = "hello world";
  eval("alert(msg)");
  ```
