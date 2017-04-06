# 6.3 캡슐화

캡슐화는 관련된 여러 정보를 하나의 틀 안에 담는 것이다. (이는 OOP에서 개 중요하다.)

- 멤버변수, 메서드가 서로 관련 정보가 된다.
- 클래스가 이를 담는 하나의 큰 틀이다.
- 여기서 중요한 것은 `정보의 공개여부`다.
	- JAVA나 C++에서는 `public`, `private`을 제공한다. js는 없지만 구현 가능하다.

```javascript
var Person = func(arg){
	var name = arg ? arg : "zzoong",
	return {
		getName : function{
			return name;
		},
		setName : function(value){
			name = value;
		}
	}
}
var me = Person();
```

메서드가 담긴 객체를 반환하는 함수는 여러 유명 js 라이브러리에서 볼 수 있는 구조다.

다만 주의할 점은, 접근하는 `멤버`가 객체나 배열이면 `얕은 복사`로 `참조` 만을 반환한다.

```javascript

var ArrCreate = function(arg){
	var arr = [1,2,3];

	return {
		getArr : function(){
			return arr;
		}
	};
}

var obj = ArrCreate();
var arr = obj.getArr();
arr.push(5);
obj.getArr(); // [1,2,3,5] 5가 추가되었다. obj와 arr은 동일한 변수를 참조한다.

```

해결책
- 보통의 경우, 객체를 반환하지 않고, **객체의 주요 정보를 새로운 객체에 담아서 반환**한다.
- 하지만, 객체가 반환되어야 한다면, 깊은 복사로 `복사본` 만들어서 반환한다.

---

다시 첫번째 예제로 돌아와서..

**사용자가 반환받은 객체는 Person 함수 객체의 프로토타입에는 접근할 수 없는 단점**이 있다.

왜냐하면 Person() 생성자 함수에 대한 반환값이 아니기 때문이다.

이로 인해, Person을 부모로 하는 프로토타입을 이용한 상속을 구현하기 용이하지 않다.

**이를 보완하려면 객체를 반환하는 것이 아닌 함수를 반환하는 것이 좋다.**

```javascript
var Person = function(arg){
	var name = arg ? arg : "zzoon";

	var Func = function() {}
	Func.prototype = {
		getName: function(){
			return name;
		},
		setName: function(value){
			name = value;
		}
	}
	return Func;
}();

var me = new Person();
me.getName(); // zzooon
```

클로저를 활용하여 name에 접근할 수 없게 했다.

즉시 실행 함수에서 반환되는 Func가 클로저가 된다.

이 함수가 참조하는 name 프로퍼티가 자유변수가 된다.

따라서 사용자는 name에 접근 불가하다.
