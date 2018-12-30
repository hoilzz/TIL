# mvc와 클래스

자바스크립트는 프로토타입 상속, 모듈, 명칭공간(namespace) 같은 고급 기능을 지원한다.

대표적인 웹 애플리케이션은 지메일, 구글맵스 같은 도구들이 있다.

몇몇 JS 개발자는 MVC 패턴과 같은 구조 모델을 무시하며 HTML과 JS가 서로 엉망인 애플리케이션을 만든다.


## 1.2 구조 추가하기

대규모 JS 애플리케이션을 만드는 비결은 JS 애플리케이션을 대규모로 만들지 않는 것이다.

오히려 애플리케이션을 여러 개의 독립 컴포넌트로 분리해야 한다.

대표적인 패턴으로 MVC가 있다.


## 1.3.1 모델

데이터 오브젝트를 저장하는 창고다.

- 예를 들어 user 목록, 각 사용자의 속성값, 모델과 관련된 로직등을 포함하는 User라는 사용자 모델을 만들 수 있다.

모델은 뷰나 컨트롤러에 대해 신경쓸 필요가 없다.

모델 내부에 뷰나 컨트롤러 관련 코드(이벤트 처리 코드, 뷰 템플릿 등)이 있다면 MVC 패턴이 깨진 것이다.

- 컨트롤러는 서버에서 가져온 데이터나 새로 만든 레코드를 모델 인스턴스로 만든다.

- 즉 모델에서 정의하는 함수와 로직을 이용해 데이터와 관련한 작업을 직접 처리할 수 있도록 `객체지향 데이터`를 만든다.

따라서,

```javascript
var user = users["hoil"]
destroyUser(user);
```

위 코드 보다는

```javascript
var user = User.find("hoil");
user.destroy()
```

가 낫다.

먼저 첫번째 예제는

	- namespace나 객체지향을 활용하지 않았다.
	- 어플리케이션에 이미 `destroyUser()` 함수 정의가 있다면 충돌 발생한다.
	- 전역 변수와 전역 함수는 최소한으로 해야한다.

두번째 예제는

	- User라는 인스턴스 이름을 namespace로 활용하였다. 그리고 `destroy()` 함수를 정의했고 모든 데이터를 저장한다.
	- 전역 변수를 사용하지 않아도 된다.
	- `destroy()` 같은 함수는 상속 기능을 이용시, 모든 모델에서 각자 정의하지 않아도 된다.


## 1.3.2 뷰

사용자는 뷰 계층을 통해 애플리케이션을 보고 사용자와 상호작용 한다.

템플릿에서 사용하는 간단한 조건문 이외에는 어떤 로직도 뷰에 포함하지 말아야한다.

모델과 마찬가지로 뷰도 애플리케이션의 다른 부분과 분리되어야 한다.

- 뷰는 컨트롤러나 모델에대해서 알 필요가 없다. 즉, 서로 독립적이어야 한다.

- 사실 MVC는 뷰 내부에 구현하지 않는다는 조건하에 `표현 로직`을 뷰에 포함하도록 허용한다.

- `표현로직`은 뷰에 관련된 작은 유틸리티 함수 스크립트인 Helper에 포함된다.


아래 코드는 로직을 뷰 안에 포함하는 예제다. 이케 하지말자.

```html
//template.html
<div>
	<script>
		function formatDate(date){
			...
		};
	</script>
	${formatDate(this.date)}
</div>
```

위 코드는 `formatDate()` 함수를 뷰에 추가했다.

이는 MVC를 위반하고 유지보수에 어려운 지저분한 태그를 양산한다.

아래 예제처럼 표현 로직을 헬퍼 내부로 분리함으로써 불필요한 문제를 피할 수 있다.

```javascript
// helper.js
var helper = {};
helper.formateDate = function(){...}
```

```html
<div>${helper.formatDate(this.date)}</div>
```

helper 변수의 namespace를 이용해 모든 표현 로직을 추가했다.




## 1.3.3 컨트롤러

컨트롤러는 모델과 뷰 사이에 있다.

- 컨트롤러는 뷰에서 이벤트와 입력을 수신(이 과정에서 모델 사용)해 처리한다.

- 컨트롤러는 페이지 로드시 폼 제출 및 버튼 클릭 등을 검출하는 `이벤트 리스너`를 추가한다.


```javascript
var Controller = {};

// 익명 함수로 범위를 캡슐화한다.
(Controller.users = function($){
	var nameClick = function(){}

	// 페이지 로드시 이벤트 리스너를 추가
	$(function(){
		$('#view .name').click(nameClick);
	})

})(jQuery);
```

users 컨트롤러를 만들어서 controller 변수의 namespace에 추가했다.

그리고 익명 함수로 범위를 캡슐화해서 불필요한 전역 변수 생성을 막았다.

페이지 로드시, 뷰 엘리먼트에 클릭 이벤트 리스너를 추가한다.



## 1.4 모듈화와 클래스 생성

MVC 핵심을 살펴보기 전에, JS 클래스와 이벤트 같은 기본 개념을 보자.

정적 클래스에서 `JS 오브젝트 리터럴`이 적합하지만

때로는 `상속과 인스턴스를 활용한 전통적인 클래스 생성 방식`도 유용하다.

JS는 네이티브 클래스 구현을 포함하지 않은 prototype 기반 언어다.

클래스 정의 대신 `생성자 함수`와 `new` 키워드를 제공한다.

**생성자 함수를 이용해 오브젝트를 인스턴스화 할 때 오브젝트의 초기 속성 종류와 속성값을 지정**할 수 있다.

모든 자바스크립트 함수는 생성자로 활용할 수 있다.

new 키워드는 return문의 동작과 함수의 컨텍스트를 변경한다.

실제로 new의 사용과 생성자는 네이티브 클래스 구현 언어와 비슷하다.

---

생성자 함수에서는 **return 문이 없으면 현재 컨텍스트를 가리키는 this를 반환**한다.

또는 기본형을 제외한 모든 타입을 반환할 수 있다.

예를 들어, **새 클래스를 설정하는 함수를 반환할 수 있다.**

이 작업은 직접 클래스 에뮬레이션 라이브러리를 만드는 첫 걸음이다.

```javascript
var Class = function(){
	var klass = function(){
		this.init.apply(this, arguments);
	}
	klass.prototype.init = function(){
		console.log("klass.prototype.init");
	}
	return klass;
}

var Person = new Class();

Person.prototype.init = function(){
	console.log("Person.prototype.init");
	// Person을 인스턴스화할 때 호출된다.
}

var person = new Person())
```

class는 예약어이기 때문에, 일반적으로 `_class`나 `klass`를 변수명으로 사용



## 1.5 클래스에 함수 추가하기

JS의 오브젝트에 프로퍼티를 추가하는 방법으로 **클래스에 함수 추가**할 수 있다.

```javascript
Person.find = function(id){..}

var person = Person.find(1);
```

인스턴스 함수를 생성자 함수에 추가하려면 생성자의 prototype 필요하다.

```javascript
Person.prototype.breath = function(){..}
var person = new Person;
person.breath();
```

일반적으로 클래스 prototype을 fn이라는 별칭으로 간결히 사용한다

jQuery 플러그인에서도 위에서 사용한 패턴을 자주 접할 수 있다.

jQuery는 프로토타입의 별칭으로 `jQuery.fn`을 사용한다.


## 1.6 클래스 라이브러리에 메서드 추가하기

문법이 복잡하고, 실용도도 떨어진다.

때문에 정적, 동적 프로퍼티 목록을 한눈에 파악하기 힘들다.

`extend()`, `include()`라는 두 함수를 이용해 다른 방법으로 클래스에 프로퍼티 추가해보자.

```javascript
var Class = function(){
	var klass = function(){
		this.init.apply(this, arguments);
	};

	klass.prototype.init = function(){};

	klass.fn = klass.prototype;

	klass.fn.parent = klass.

	// 클래스 프로퍼티 추가

	klass.extend = function(obj){
		var extended = obj.extended;
		for(var i in obj){
			klass[i] = obj[i];
		}
	}

	klass.extend = function(obj){
		var included = obj.included;
		for(var i in obj){
			klass.fn[i] = obj[i];
		}
	}

	// 인스턴스 메서드 추가

	return klass;
}
```

extended와 included의 콜백 지원도 구현한다.

넘겨진 오브젝트에 일치하는 속성이 있으면 해당 함수 호출한다.

```javascript
Person.extend({
	extended: function(klass){
		console.log(klass,"가 확장됐다");
	}
});
```

위 기법을 이용하면 모듈을 만들 수 있는 장점이 있다.

모듈은 재사용할 수 있는 코드의 일부분으로, 클래스 간 공통 프로퍼티 공유할 때 `상속` 대신 `모듈`을 이용할 수 있다.

```javascript
var ORMModule = {
	save: function(){
		// 공유 함수
	}
}
var Person = new Class();
var Asset = new Class();

Person.icnlude(ORMModule);
Person.include(oRMModule);
```


## 1.7 클래스 상속과 프로토타입 사용

JS는 클래스와 인스턴스를 구별하는 언어가 아니라, 프로토타입 기반 언어다.

JS에서는 새 오브젝트의 초기 프로퍼티를 얻을 때 템플릿으로 사용할 수 있는 오브젝트인

프로토타입 오브젝트 개념을 제공한다.

모든 오브젝트는 다른 오브젝트의 프로토타입이 되어 자신의 프로퍼티를 공유할 수 있다.

이 기능을 상속처럼 생각하자.

---

클래스와 클래스의 프로퍼티를 상속 받으려면 `생성자 함수`를 먼저 정의해야 한다.

그 다음 `부모의 새 인스턴스`를 `생성자 함수의 프로토타입`으로 설정한다.

```javascript
var Animal = function(){};

Animal.prototype.breath = function(){
	console.log('breathe');
}

var Dog = function(){};

Dog.prototype = new Animal();

Dog.prototype.bark = function(){
	console.log('bark');
}

var dog = new Dog();

dog.breath();
dog.bark();
```

## 1.8 클래스 라이브러리에 상속 기능 추가하기

클래스 라이브러리에 상속 기능을 추가하자.

새 클래스 생성시, 선택사항으로 부모를 넘겨줄 수 있도록 함수를 구현하자.

```javascript
var Class = function(parent){
	// 부모가 있으면 부모와 자식간 상속관계 형성
	// 없으면 걍 없는대로 진행
	var klass = function(){
		this.prototype._init.apply(this, arguments);
	}

	if(parent){
		var subClass = function(){};
		subClass.prototype = parent;
		klass.prototype = new subClass();
	}

	klass.prototype._init = function(){};

	klass.fn = klass.prototype;
	klass.fn.parent = klass;
	klass._super = klass.__proto__;

	// include, extend 코드

	return klass;
}
```

class 생성자에 parent를 넘겨주면 모든 하위클래스는 같은 프로토타입을 공유한다.


## 1.9 함수 호출

함수도 오브젝트다.

함수를 언제 어디에서 호출했느냐에 따라 함수의 컨텍스트 (예를 들어 this)가 달라진다.

`apply()`, `call()`로도 함수 호출 가능하다.


### apply와 call


apply는 `컨텍스트`, `인자 배열`이라는 파라미터 2개를 갖는다.

```javascript
func.apply(this, [1,2,3]);
```

---

call은 함수 사용방법만 다르고 같은 동작 수행한다.

첫번째 인자는 컨텍스트,

나머지 인자는 호출자가 알아서 결정한다.

즉, apply 처럼 배열이 아닌 원하는 만큼 인수를 함수에 전달한다.

```javascript
func.call(this,1,2,3);
```

---

>그런데 왜 컨텍스트를 인자로 넘겨줘서 함수의 컨텍스트를 바꾸는 것일까?
JS는 **컨텍스트 변경을 이용해 상태를 공유(특히 이벤트 콜백)**한다.
컨텍스트 변경 때문에 초보자는 혼란을 겪거나, 버그를 유발할 수도 있다.
일단 컨텍스트 변경이 어떻게 동작하는지 알아보자.

---

jQuery는 apply()와 call()을 이용해 자신의 API에서 컨텍스트를 변경한다.

예를 들어 이벤트 핸들러가 each()를 이용한 반복작업.

```javascript
$('.clicky').click(function(){
	// this는 엘리먼트
	$(this).hide();
});

$('p').each(function(){
	// 'this'는 반복하는 항목 가운데 현재 항목
	$(this).remove();
})
```

일반적으로 **지역 변수에 this 값을 저장해서 원래 컨텍스트에 접근하는 방법을 흔히 사용**한다.

예를 들면,

```javascript
var clicky = {
	wasClicked: function(){

	},

	addListeners:function(){
		var self = this;
		$('.clicky').click(function(){
			self.wasClicked();
		});
	}
};

clicky.addListeners();
```

위 코드를 apply로 **원래 컨텍스트를 포함하는 다른 익명 함수 내의 콜백을 감싸면 **더 깔끔한 코드를 만들 수 있다.

```javascript
var proxy = function(func, thisObject){
	return(function(){
		return func.apply(thisObject, arguments);
	})
}

var clicky = {
	wasClicked: function(){
          console.log("wasClicked()");
	},

	addListeners:function(){
// 		var self = this;
// 		$('.clicky').click(function(){
// 			self.wasClicked();
// 		});
	  // 원래 컨텍스트를 포함하는 다른 익명 함수 내의 콜백을 감싸면 더 깔끔한 코드 만들 수 있다.
      $('.clicky').click(proxy(this.wasClicked, this));
	  // 원래 컨텍스트의 wasClicked 함수를 이용하기 위해 this.wasClicked를 인자로 보낸다. 또한, 원래 컨텍스트인 this를 보내서 apply를 통해 컨텍스트를 변경한다.
	}
};

clicky.addListeners();
```

위 예제는 **클릭 콜백 내에서 컨텍스트를 사용하도록 지정**했다.

`jQuery.proxy()`를 이용할 수도 있다.

```javascript
$('.clicky').click($.proxy(function(){...}), this);
```


---

### 위임

JS 위임 기능은 apply()와 call()을 활용할 수 있는 또 다른 예다.

JS에서는 **한 함수의 호출을 다른 함수로 위임할 수 있다**.

**심지어 전달된 인자도 바꿀 수 있다.**



```javascript
var App = {
	log: function(){
		if (typeof console == "undefined") return;

		// 인자를 적절한 배열로 바꾼다.
		var args = jQuery.makeArray(arguments);

		// 새 인자를 가장 앞에 추가한다.
		args.unshift("(App)");

		// console에 위임
		console.log.apply(console, args);
	}
}
```

- 인자를 배열로 만들고, **새 인자도 직접 추가**했다.
- 호출을 `console.log()`로 위임했다.
- `arguments`는 `호출이 일어난 현재 범위`와 `인자 배열을 포함하는 변수`로 인터프리터가 **arguments 값을 설정**한다.
- arguments의 값은 바꿀 수 없으므로 일반적인 배열이 아닙니다.
- 따라서, jQuery.makeArray()로 arguments의 값을 변환한 다음 다시 사용해야 한다.


## 1.10 클래스 라이브러리에서 범위 조절하기

프록시 함수는 우리의 클래스 라이브러리에도 적용할 수 있는 유용한 패턴이다.

>Proxy 객체는 개별적인 행동을 정의하는데 사용되는데, 기초적인 동작(예: property lookup, assignment, enumeration, function invocation 등)을 위함이다.

이벤트 핸들러에서 함수를 처리할 때 클래스 범위h를 유지할 수 있도록

클래스와 인스턴스 모두 프록시 함수를 추가할 것이다.

```javascript
var Class

```

>
>!!!!!!여기 부분 1도 모르겠다!!!!!
>

## 1.11 비공개 함수 추가하기

앞 예제들은 모두 프로퍼티가 공개되어있다. 그러므로 언제든 변경 가능하다.

많은 개0발자들이 비공개 프로퍼티를 `_`를 추가하는 것으로 만족한다.

JS는 수정할 수 없는 프로퍼티 기능을 지원한다.

주요 브라우저에서 이 기능을 구현하지 않았으므로,

대신 JS의 **익명 함수를 이용해 내부에만 접근할 수 있는 비공개 범위** 만들 수 있다.

```javascript
var Person = function(){};

(function(){
	var findById = function(){...}

	Person.find = function(id){
		if (typeof id == "integer") return findById(id);
	}
})();
```

위 예제에서 모든 프로퍼티를 익명함수로 감쌌다.

따라서 지역변수 `findById`는 현재 범위에서만 접근할 수 있다.

Person 변수는 전역으로 정의했으므로 어디에서나 접근할 수 있다.

키워드 var를 사용하면 전역 변수가 되므로 변수 정의시 var는 사용하지 않는다.

전역 변수를 정의하고 싶다면 전역 영역에서 변수를 선언하거나 윈도우에서 프로퍼티로 선언한다.


## 1.12 클래스 라이브러리

클래스는 확실히 이해해야한다. (사실 클래스보다는 라이브러리를 더 자주 사용할 것이다)

jQuery 자체는 클래스를 지원하지 않지만 HJS 같은 플러그인을 제공한다.

HJS는 프로퍼티 집합을 `$.Class.create`에 넘겨주는 방법으로 클래스를 정의한다.


## summary

#### 모듈화와 클래스 생성

- 정적 클래스에서는 오브젝트 리터럴이 적합
- 상속과 인스턴스를 활용한 전통적인 클래스 생성 방식도 유용
- 생성자 함수와 new키워드로 생성자 함수를 이용해 오브젝트를 인스턴스화 할 때 오브젝트의 초기 속성 종류와 속성 값을 지정할 수 있음

#### 클래스에 함수 추가하기

- `클래스명.func_name = function(){..}` 클래스에 함수 추가하기
- `클래스명.prototype.func_name` 인스턴스 함수를 생성자 함수에 추가하기.


#### 클래스 라이브러리에 메서드 추가하기

`extend`와 `include` 두 함수 이용하여 클래스에 property 추가하기

이 기법을 이용하면 모듈을 만들 수 있는 장점이 있다.

모듈은 재사용 가능한 코드의 일부분으로, 클래스 간 공통 프로퍼티 공유할 때 `상속` 대신 `모듈`을 이용할 수 있다.


#### 클래스 상속과 프로토타입 사용

모든 오브젝트는 다른 오브젝트의 프로토타입이 되어 자신의 프로퍼티를 공유할 수 있다.

이 기능을 `상속` 처럼 생각하자.

	- 클래스와 클래스의 프로퍼티 상속 받으려면 `생성자 함수`를 먼저 정의해야한다.
	- 그 다음 `부모의 새 인스턴스`를 `생성자 함수의 프로토타입`으로 설정한다.


#### 클래스 라이브러리에 상속 기능 추가하기

새 클래스 생성시, **선택사항으로 부모를 넘겨줄 수 있도록** 함수 구현하자.

부모가 있으면 클래스 함수의 super로 초기화한다. (중간엔 빈 생성자 함수의 인스턴스를 추가한다.)

#### 함수 호출

`apply`와 `call` 함수를 통해 함수 컨텍스트를 변경할 수 있다.

보통 컨텍스트를 인자로 넘겨줘서 함수의 컨텍스트를 변경하는데,

이것을 통해 상태를 공유(특히 이벤트 콜백)한다.

> 예를 들어, 지역 변수에 this 값을 저장하여 원래 컨텍스트에 접근하는 방법을 흔히 사용한다. 이 때 지역변수에 할당하는 것보다 apply를 활용하면 깔끔해진다.
원래 컨텍스트를 포함하는 다른 익명 함수 내의 콜백에 메서드와 this를 활용하여 apply를 apply를 호출하면 된다.


#### 비공개 함수 추가하기

익명 함수와 즉시실행 함수를 이용해 내부에만 접근할 수 있는 비공개 범위 만들 수 있다.


## summary

대규모 JS 어플리케이션은 대규모로 만들지 않고, 여러 개의 독립 컴포넌트로 분리해야 한다. 대표적인 패턴은 MVC다.

1. 모델

- user 목록, user의 각 속성값, 모델과 관련된 로직을 포함하는 User라는 사용자 모델을 만들 수 있다.
	- 컨트롤러는 서버에서 가져온 데이터나 새로 만든 레코드를 모델 인스턴스로 만든다.
	- 즉 모델에서 정의하는 함수와 로직을 이용해 **데이터와 관련한 작업을 직접 처리할 수 있도록 `객체지향 데이터`를 만든다**.

2. 뷰

- 뷰는 컨트롤러나 모델에 대해서 알 필요가 없다. 즉 독립적이어야한다.
- 뷰 내부에 표현로직을 `구현`하지 않고 뷰에 `포함`하도록 허용한다.
	- 표현 로직은 뷰에 관련된 작은 유틸리티 함수 스크립트인 Helper에 포함된다.

3. 컨트롤러
	- 모델과 뷰 사이에 있다.
	- 뷰에서 이벤트와 입력을 수신(이 과정에서 모델 사용)해 처리한다.

	- `페이지 로드시 이벤트 리스너를 추가` 하는 것을 익명함수를 통해 범위 캡슐화

	```javascript
	var Controller = {};

	// 익명 함수로 범위를 캡슐화한다.
	(Controller.users = function($){
		var nameClick = function(){}

		// 페이지 로드시 이벤트 리스너를 추가
		$(function(){
			$('#view .name').click(nameClick);
		})

	})(jQuery);
	```

1.4 모듈화와 클래스 생성

- 생성자 함수를 이용해 오브젝트를 인스턴스화 할 때 초기 속성 종류와 속성값 지정 가능


1.5 클래스에 함수 추가하기

- 클래스에 함수 추가
- 인스턴스 함수를 생성자 함수에 추가하려면 prototype 필요

1.6 클래스 라이브러리에 메서드 추가하기

- 모듈을 만들 수 있는 장점이 있는데 다음 코드를 참고하자.

```javascript
var ORMModule = {
	save: function(){
		// 공유함수
	}
};
var Person = new Class();
var Asset = new Class();

Person.include(ORMModule);
Asset.include(ORMModule);
```

1.7 클래스 상속과 프로토타입 사용

상속처럼, 모든 오브젝트는 다른 오브젝트의 프로토타입이 되어 자신의 프로퍼티를 공유할 수 있다.

	- 생성자 함수를 정의하고
	- 부모의 새 인스턴스를 자식 생성자 함수의 프로토타입으로 설정

1.8 클래스 라이브러리에 상속 기능 추가하기

```javascript
var Class = function(parent){
	var klass = function(){
		this.prototype._init.apply(this, arguments);
	}

	if(parent){
		var F = function(){};
		F.prototype = parent;
		klass.prototype = new F();
		klass.super = parent;
	}


	klass.fn  = klass.prototype;
	klass.prototype._init = function(){};
	klass.fn.parent = klass;

	return klass;
}
```


1.9 함수 호출

call과 apply 사용이유는 전달한 인자로 함수 컨텍스트를 변경하려는 것이다.
**그 변경을 이용해 `상태를 공유`(특히 이벤트 콜백)한다.**

예를 들어,

```javascript
var clicky = {
	wasClicked: function(){

	},
	addListeners:function(){
		var self = this;
		$('.clicky').click(function(){
			self.wasClicked();
		})
	}
}
clicky.addListeners();
```

지역 변수에 this 값을 저장하여 원래 컨텍스트에 접근하고 있다.

```javascript
var proxy = function(func, thisObject){
	return (function(){
		return func.apply(thisObject, arguments);
	})
}

var clicky = {
	wasClicked: function(){

	},
	addListeners:function(){
		var self = this;
		$('.clicky').click(proxy(this.wasClicked, this));
	}
}
```

1.9.1 위임

apply, call을 활용하여 한 함수의 호출을 다른 함수로 위임할 수 있다.

또한, 인자도 변경할 수 있다.

```javascript
var App = {
	log:function(){
		if (typeof console == "undefined") return;

		// 인자를 적절한 배열로 바꾼다.
		var args = jQuery.makeArray(arguments);

		// 새 인자를 가장 앞에 추가한다.
		args.unshift("(App)");

		// console에 위임
		console.log.apply(console, args);
	}
}
```

새 변수 args에 배열로 변경된 값들을 저장.


1.11 비공개 함수 추가하기

익명함수를 이용해 내부에만 접근할 수 있는 비공개 범위 만들 수 있다.

var Person = function(){};

```javascript
(function(){
	var findById = function(){};

	Person.find = function(id){
		if(typeof id == "integer") return findById(id);
	}
})();
```

지역변수 `findById`는 현재 범위에서만 접근 가능.

Person 변수는 전역에서 정의했으므로 어디서든 접근 가능.
