# Class

ES6은 클래스 메서드를 짧은 구문으로 선언할 수 있다. 먼저, ES5 기준으로 클래스를 작성해보자.

## Class by ES5

```javascript
'use strict';

function User(name){
  this.name = name;
}

User.prototype = {
	constructor: User,

  	say: function() {
		return 'My name is ' + this.name;
	}
}

function Admin(name) {
  User.apply(this, arguments);
}

Admin.prototype = Object.create(User.prototype);

Admin.prototype.constructor = Admin;
Admin.prototype.say = function(){
	var superClassPrototype = Object.getPrototypeOf(this.constructor.prototype);
	return '[Admin] ' + superClassPrototype.say.call(this);
}

var user = new User('Hoil');
console.log(user.say()); // My name is Hoil

var admin = new Admin('Tmon');
console.log(admin.say()); // [Administrator] My name is Hoil
```

> Object.getPrototypeOf(obj)
> 매개변수의 프로토타입 객체가 반환됨


## Class by ES6

```javascript
'use strict';

class User {
  constructor(name) {
	this.name = name;
  }

  say() {
	return 'My name is ' + this.name;
  }
}

class Admin extends User {
  say() {
	return '[Administrator] ' + super.say();
  }
}

var user = new User('Hoil');
console.log(user.say()); // My name is Hoil

var admin = new Admin('Tmon');
console.log(admin.say()); // [Administrator] My name is Hoil
```