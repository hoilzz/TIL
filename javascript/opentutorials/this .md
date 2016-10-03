# this

- this는 함수 안에서 사용할 수 있는 변수
- 함수 내에서 함수 호출 context(맥락)를 의미
- 즉, 그 함수를 어떻게 호출했느냐에 따라 달라진다.



**NOTE**
**window는 웹브라우저 전역변수를 뜻함**

## 2 메서드의 호출

함수가 어느 객체에 속하지 않으면 this는 window라고 하는 전역객체
**o.func()라는 메서드 호출시 this는 o다.**

사실 어느 객체에 속하지 않은 func는
window의 메서드다. 즉 func() 호출 = window.func() 와 같다.


*즉 this는 메서드(or 함수)가 소속된 객체를 가리킨다.*


## 3 생성자의 호출

*생성자 안에서 this는 어떤 의미일까*

Ex

  var funcThis = null;

  function Func() {
    // if (o2 == this) 추가시, 존재하지 않는 o2(undefined와) this를 비교
    // new Func()라는 생성자를 호출시 그 호출 모두 끝나야 o2라는 변수에 우리가 생성한 객체가 할당된다. 즉 undefined다.
    funcThis = this;
  }

  var o1 = Func(); // Func()의 return이 없으므로 o1은 undefined  
                   // Func() 호출시 funcThis = this 여기서 this는 메서드 혹은 함수가 소속된 객체를 가리킨다.
                   // function Func()는 window에 속한다.

  if (funcThis === window) {
    document.write('wi ndow </br>')
  }

  var o2 = new Func();
  if (funcThis === o2) {
    document.write('o2 </br>')
  }

생성자의 맥락(context)에서는 this의 값이 생성될 객체를 가리킨다.

함수로 호출하게 되면 이 함수 안에서의 this값은 window다.

**어떤 식별자에 담기기 전에 그 객체를 참고할 수 있는 레퍼런스(식별자)이기 때문에 this는 굉장히 중요**


## 4 apply, call

// Function이라고 하는 생성자 함수 호출
// 이것의 인자들은 매개변수지정, 마지막 인자가 함수의 본문 해당
// 근데 이렇게 함수 작성하면 되게 불편
var sum2 = new Function('x', 'y', 'return x+y;');

// 함수를 쉽게 작성할 수 있도록 함수리터럴로 선언 가능
//
function sum(x,y){return x_y;}

// 객체 리터럴
var o = {      }

// 배열 리터럴
var a = [ 1,2,3 ] or = new Array(1,2,3)
ls


**함수가 어떤 맥락(context)에서 호출하느냐에 따라 소속된 객체가 달라진다.
this는 변화무쌍하댜..**

**함수가 누구에게 소속되어있느냐에 따라 this가 달라진다.**

  var o = {}
  var p = {}
  function func(){
    switch(this){
        case o:
            document.write('o<br />');
            break;
        case p:
            document.write('p<br />');
            break;
        case window:
            document.write('window<br />');
            break;          
    }
  }
  func();
  func.apply(o);
  func.apply(p);


  window
  o
  p
