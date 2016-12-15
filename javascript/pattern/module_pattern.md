# module pattern
기본 싱글톤을 확장하여 `고유 변수`와 `특권 메서드`를 쓸 수 있다

```javascript
var singleton = function() {
  // 고유 변수와 함수
  var privateVar = 10;
  function privateFunction(){
    return false;
  }

  // 특권/공용 메서드와 프로퍼티
  return {
    publicProperty:true,
    publicMethod : function(){
      privateVar++;
      return privateFunction();
    }
  }
}();
```
- 위와 같이 `객체를 반환하는 익명 함수`를 사용
- 모듈 패턴 생성 방법은
  - 먼저, 익명 함수 내부에서 고유 변수와 함수를 정의
  - 객체 리터럴을 함수 값으로 반환
  - 반환된 객체 리터럴에는 공용이 될 프로퍼티(publicProperty)와 메서드(publicMethod)만 들어있다.
- 요약하면, 객체 리터럴이 싱글톤에 대한 공용 인터페이스를 정의 하는 것














































ㅍ
