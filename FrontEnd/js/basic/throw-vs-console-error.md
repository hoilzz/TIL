# throw Error VS console.error

## 예외처리문

- throw
- try...catch 문

### throw

예외 사용시 throw문 사용. 사용되는 값을 포함하는 표현을 명시해야함

> throw expression

```
throw "Error2";
throw 42;
throw true;
throw {toString: function() { return I'm an object}}
```

예외 사용시 객체 명시 가능. catch문 안에서 객체의 특성들도 참조 가능.(stackTrace 등).

### try...catch

시도할 블록 표기, 예외 발생시 하나 이상의 반응을 명시한다. 만약 예외 발생시, try...catch는 예외를 잡아낸다.

- try
	- 오류 발생시키는 코드 감싸기
- catch
	- try 블록에서 발생하는 모든 예외 처리

	```
		catch (catchID) {
			statements
		}
	```
	- catchID를 통해 발생된 예외에 대한 정보를 얻을 수 있음.
- finally
	- try, catch 블록의 시행이 끝나고 수행

```javascript
function runWithoutThrowing(func) {
	try {
		func();
	} catch (e) {
		console.log('There was an error, but I will not throw it');
		console.log('The error message was : ' + e.message);
	} finally {
		console.log('finally');
	}
}

function funcThatThrowsError() {
	throw new TypeError('I am TypeError');
}

runWithoutThrowing(funcThatThrowsError);
console.log("asdasd");
```

```javascript
function getMonthName (mo) {
  mo = mo-1; // Adjust month number for array index (1=Jan, 12=Dec)
  var months = ["Jan","Feb","Mar","Apr","May","Jun","Jul",
                "Aug","Sep","Oct","Nov","Dec"];
  if (months[mo] != null) {
    return months[mo];
  } else {
    throw "InvalidMonthNo"; //throw keyword is used here
  }
}

try { // statements to try
  monthName = getMonthName(myMonth); // function could throw exception
}
catch (e) {
  monthName = "unknown";
  logMyErrors(e); // pass exception object to error handler
}
```

## 이거 조사하는 이유

throw Error("msg") vs console.error("msg")

### throw Error('msg')
- js 실행 멈춤 (try 블록 내에서)
- 주로 코드를 처리하기위한 목적
- 실행의 주요 흐름을 변경할 수 있다.

### console.error('msg')
- 브라우저 콘솔에 단순히 Red Color로 아웃풋 보여준다.
- 주로 디버깅을 위해 값을 출력하는 목적
- 디버깅 목적이다.
- 실행 제어 불가(실행 중지 못함)

