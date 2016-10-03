# 상속
javascript는 prototype base 언어다.

  function Person(name){
      this.name = name;
  }
  Person.prototype.name=null;
  Person.prototype.introduce = function(){
      return 'My name is '+this.name;
  }

  function Programmer(name){
      this.name = name;
  }
  Programmer.prototype = new Person();      // Person을 상속
  Programmer.prototype.coding = function(){
      return "hello world";
  }

  var p1 = new Programmer('egoing');
  document.write(p1.introduce()+"<br />");
  document.write(p1.coding()+"<br />");

>  My name is egoing
>  hello world

# prototype

생성자는 함수다. 이 때 함수 호출시 new를 붙이면 생성자. 이 결과 새로운 객체를 리턴한다. 비어있는 객체를 생성하는게 생성자의 역할
하지만 아래 상황은 그냥 빈 객체가 아니다.

  function Ultra(){}
  Ultra.prototype.ultraProp = true;

  function Super(){}
  Super.prototype = new Ultra();

  function Sub(){}
  Sub.prototype = new Super(); // Sub라고 하는 함수는 객체이기 때문에

  var o = new Sub();
  console.log(o.ultraProp);


var o = new Sub();와 var o = {}는 같다. 왜냐면 빈객체를 반환하니까. 하지만 왜 new Sub를 쓰냐?


## Summary
- 프로토타입안에 있는 프로퍼티는 공통으로 쓸 메서드와 변수만 사용하기 (클래스 변수와 비슷)
- 상속은 프로토타입만 됨?
