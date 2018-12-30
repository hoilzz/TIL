# throw, try-catch

예외 사용시 throw Expression을 사용한다.

```javascript
throw "Error2"
throw 42;
throw true;
throw {toString: function() {return 'I"m an object!';}}
```

> 예외 사용시 객체를 명시할 수 있다. catch문 안에서 객체의 특성을 참조할 수 있다. 

