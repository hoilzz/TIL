# 생성자와 new

  var person = {} // 객체 생성 방법 중 1개 {}

## 생성자
생성자는 **객체를 만드는 역할을 하는 함수**

  function Person() {}  // 평범한 함수
  var p0 = Person();    // p0 는 undefined 함수는 어떠한 값도 리턴하고 있지 않기 때문에
  var p1 = new Person() // new를 추가하면? Person {} 빈 객체가된다.
                        // new가 붙어있는 함수는 생성자. 즉 객체의 생성자.

  함수에 new를 붙이면 리턴값으로 객체를 생성.
````
  function Person(){}
  var p1 = new Person();
  p1.name = 'egoing';
  p1.introduce = function(){
      return 'My name is '+this.name;
  }
  document.write(p1.introduce()+"<br />");

  var p2 = new Person();
  p2.name = 'leezche';
  p2.introduce = function(){
      return 'My name is '+this.name;
  }
  document.write(p2.introduce());

````  
  따로 이름 정하지 말고 생성자 호출하자마자 초기화로 개선
````
  function Person(name){
    this.name = name;
    this.introduce = function(){
        return 'My name is '+this.name;
      }   
  }
  var p1 = new Person('egoing');
  document.write(p1.introduce()+"<br />");

  var p2 = new Person('leezche');
  document.write(p2.introduce());
````
