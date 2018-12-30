## proxy

proxy object는 기본 동작을 위한 커스텀 행동을 정의하기 위해 사용된다.

## 상황을 가정해보자.

```javascript
function PhoneBook(){
	this.dictionary = {
		'이승민': '03049848',
		'이이우': '39829203',
		'구우바': '13839221'
	};
}
PhoneBook.prototype.get = function(name, callback){
	var self = this;
	setTimeout(function(){
		setTimeout(function(){
			callback(self.dictionary[name]);
		})
	})
}
```

```javascript
function phoneBoookProxy(){
	var phoneBook = new Phonebook();
	var viewCount = 0;
	return {
		get: function(name, callback){
			viewcount++;
			phoneBook.get(name, callback);
		},
		getViewCount: function(){
			return viewCount;
		}
	}
}
```

---

### $.proxy()

jQuery의 `$.proxy()` 메소드는 함수 내부의 `this` 컨텍스트를 바꾸는 ES5의 `bind()`와 비슷한 동작을 한다.

실제 코드를 보면 컨텍스트를 바꿔주는 `apply()`와 `call()`을 사용하고 있는 걸 볼 수 있다. 하지만 **컨텍스트를 바꾸어 주는 것** 이외에는 원래 함수에 별다른 커스터마이징 할 수 없다. (원래 그런 용도가 아니다.)

오히려 **특정 함수의 대상이 되는 객체가 프록시 된다**.

따라서 앞서 소개한 프록시 패턴과는 다른 종류라고 볼 수 있다.

*프록시 된다?*
