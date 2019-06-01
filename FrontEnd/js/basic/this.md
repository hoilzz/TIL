# this

## 생성자 내부의 this

```js
function Person(name, age) {
  this.name = name;
  this.age = age;
}

Person.prototype.printAge = function() {
  console.log(this.age);
};

var user = new Person('hoil', 29);
```

##
