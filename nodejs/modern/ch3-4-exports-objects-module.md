# exports 객체와 모듈

노드는 모듈을 사용해 기능을 확장한다.

모듈은 기능을 쉽게 사용하고자 메서드와 속성을 미리 정의해 모아놓은 것이다.

모듈을 생성하려면 별도의 js 파일을 생성해야 한다.

	- module.js 파일은 생성할 모듈 파일이다.
	- main.js 는 생성한 모듈을 불러올 파일이다.

모듈을 생성할 때는 exports 객체를 사용한다.

exports 객체에 속성이나 메서드를 지정한다.

다음의 코드는 module 모듈에 abc() 메서드와 circleArea() 메서드가 생성된다.

```javascript
exports.abs = function(number){
	if (0<number){
		return number;
	} else{
		return -number;
	}
}

exports.circleArea = function (radius){
	return radius * radius * Math.PI;
}
```

모듈을 생성해봤다.

이제 다른 js 파일에서 추출해보자.

```javascript
var module = require('./module.js');

console.log('abs(-273) = %d', module.abs(-273));
console.log('circleArea(3) = %d', module.circleArea(3));
```

모듈 생성할 때는 `exports` 객체를 사용
모듈 추출할 때는 `require()` 함수를 사용


> index.js 파일
Node는 require 인자에 확장자를 입력하지 않고 모듈 이름 입력시 2가지 상황을 생각합니다.
1. 실행 파일과 같은 폴더 내부에서 module.js 파일을 찾습니다. 그 파일이 있다면 해당 파일의 exports 객체를 추출합니다.

```javascript
var module = require('./module');
```

2. 이름이 같은 파일이 없을 경우, 현재 경로에서 module 폴더를 찾습니다. module 폴더가 있을 경우에 module 폴더 안 index.js 파일을 찾아 추출합니다.
