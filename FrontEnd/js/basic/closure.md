# closure

[zerocho님의 클로저](https://www.zerocho.com/category/JavaScript/post/5741d96d094da4986bc950a0)

> 클로저는 독립적인 (자유) 변수 (지역적으로 사용되지만, 둘러싼 범위 안에서 정의된 변수)를 참조하는 함수들이다. 다른 말로 하면, 이 함수들은 그들이 생성된 환경을 '기억'한다.

간단히 말하자면 클로저는 `함수를 선언할 때 만들어지는 유효 범위`다. 함수는 클로저를 통해서 자신이 선언될 때 속해 있던 유효 범위 내의 변수와 함수를 사용할 수 있고, 변수의 경우 그 값을 변경 할 수도 있다. 또한, 함수를 선언한 후에 언제든지(**심지어 함수가 속해 있던 유효 범위가 사라진 후에도**) 그 함수를 호출할 수 있다.

클로저를 또다른 방식으로 설명해보자.(왜냐하면 내가 자꾸 까먹으니까)
Scope Chain을 이용하여 이미 생명 주기가 끝난 외부 함수의 변수를 참조하는 방법이다. 외부 함수가 종료되더라도 내부함수가 참조되고 있는 상태면, 내부함부에서 참조하는 외부함수는 닫히지 못하고 내부 함수에 의해서 닫히게 되어 클로저라 부른다.

여튼 클로저는 생성될 당시의 환경을 기억하는 함수다. 이 때 환경은 스코프 체인인데, 스코프체인을 통해 접근할 수 있는 변수나 함수가 스코프가 해제되어야할 시점에도 사라지지 않는다.

이러한 스코프를 통해

- 객체가 갖는 성질인 캡슐화와 은닉화를 구현할 수 있다.
- 클로저가 생성되면서 상태를 포함한 행위를 묶어서 객체를 생성할 수 있다.

내부 변수는 하나의 클로저에만 종속될 필요는 없다. 외부 함수가 실행될 때마다 새로운 scope chain과 새로운 내부 변수를 생성한다.(실행될 때마다 새로운 유효 범위를 생성하는데 이는 메모리 누수를 발생시킬 수 있다) 또, 클로저가 참조하는 내부 변수는 실제 내부 변수의 복사본이 아닌 그 내부 변수를 직접 참조한다.

```javascript
function outerFunc() {
  var a = 0;
  return {
    innerFunc1: function() {
      a += 1;
      console.log("a :" + a);
    },
    innerFunc2: function() {
      a += 2;
      console.log("a :" + a);
    }
  };
}

var out = outerFunc();
out.innerFunc1();
out.innerFunc2();
out.innerFunc2();
out.innerFunc1();

//실행결과
/*
a = 1
a = 3
a = 5
a = 6
*/
```

C언어의 블록 스코프에 익숙하면 위의 코드는 이해하기 힘들다. 왜냐하면 종료된 함수의 지역 변수(`var a`)가 존재하기 때문이다. 그 이유는 Javascript 함수가 클로저를 형성하기 때문이다. 클로저는 함수와 함수가 선언된 문법적 환경의 조합이다. 위의 예시를 다시 보자. 변수 `out`은 `outerFunc()`가 실행될 때 생성된 innerFunc1과 innerFunc2 `함수의 인스턴스에 대한 참조값`을 가진다. `innerFunc1`(innerFunc2도 마찬가지다.)의 인스턴스는 변수 `a`가 있는 `문법적 환경에 대한 참조`를 유지한다.

## 예시를 통해 클로저 동작 알아보자.

```javascript
var outerValue = "hoil";

var later;

function outerFunction() {
  var innerValue = "pyapya";

  function innerFunction() {
    console.log(outerValue, "I can access hoil");
    console.log(innerValue, "I can access pyapya");
  }

  later = innerFunction;
}

outerFunction();

later();
```

- `innerValue`의 유효 범위는 `outerFunction()` 내부로 제한된다. 함수 외부에서는 접근 불가능하다. (**Scope Chain을 떠올리자**)
- `outerFunction`내에 선언된 `innerFunction`은 `innerValue`가 선언된 유효 범위에 존재한다.
- `outerFunction()`실행 시 전역 변수인 `later` 변수에 참조된다.
- `later()`, later 변수를 이용하여 `innerFunction()`을 호출한다. `innerFunction()`의 유효 범위는 `outerFunction`내부까지 제한되어있다.(**마찬가지로 Scope Chain**) 그래서 외부에서 직접 호출하는 것은 불가능하다.

## 클로저의 사용 이유 1

클로저를 사용하면 전역변수의 오,남용 없는 깔끔한 스크립트를 작성할 수 있다. 그의 대표적인 예로 `모듈 패턴`

## 클로저의 사용 이유 2

자바의 private을 흉내낼 수 있다.

## NOTE

**for문 클로저는 상위 함수의 변수를 참조할 때 자신의 생성될 떄가 아닌 내부 변수의 최종 값을 참조한다**

```html
<script>
  window.onload = function() {
    var list = document.getElementsByTagName("button");

    for (var i = 0, length = list.length; i < length; i++) {
      list[i].onclick = function() {
        console.log(this.innerHTML + "은" + (i + 1) + "번째 버튼입니다");
      };
    }
  };
</script>

<button>1번째 버튼</button>
<button>2번째 버튼</button>
<button>3번째 버튼</button>
```

```
//실행결과
/*
1번째 버튼은 4번째 버튼입니다
2번째 버튼은 4번째 버튼입니다
3번째 버튼은 4번째 버튼입니다
*/
```

- 클릭 이벤트가 참조하는 변수 i의 값이 for문 다 돌고 난 후의 i값을 참조
- 1가지 i값을 참조하므로 전부 4라는 결과 나옴

### 해결책 : 중첩 클로저

```html
<script>
  window.onload = function() {
    var list = document.getElementsByTagName("button");

    var gate = function(i) {
      list[i].onclick = function() {
        console.log(this.innerHTML + "은" + (i + 1) + "번째 버튼입니다");
      };
    };
    for (var i = 0, length = list.length; i < length; i++) {
      gate(i);
    }
  };
</script>

<button>1번째 버튼</button>
<button>2번째 버튼</button>
<button>3번째 버튼</button>
```

```
//실행결과
/*
1번째 버튼은 1번째 버튼입니다
2번째 버튼은 2번째 버튼입니다
3번째 버튼은 3번째 버튼입니다
*/
```

- gate라는 함수가 실행될 때마다 새로운 scope chain과 내부 변수를 생성하기 때문이지 않을까
- 즉 각각의 클로저이지 않을까..?

## 클로저의 오남용 - 성능 문제

### 클로저가 필요하지 않는 부분에서 클로저를 사용하는 것은 좋지 않은 방법

```javascript
function MyObject(inputname) {
  this.name = inputname;

  this.getName = function() {
    return this.name;
  };

  this.setName = function(rename) {
    this.name = rename;
  };
}

var obj = new MyObject("서");
console.log(obj.getName());

//실행결과
/*
서
*/
```

- 함수 객체가 생성될 때마다 클로저가 생성된다.(쓸데 없는 메모리 차지)

### 함수 객체가 생성될 때마다 클로저 생성 -> prototype 객체를 이용한 클로저 생성

```javascript
function MyObject(inputname) {
  this.name = inputname;
}

MyObject.prototype.getName = function() {
  return this.name;
};

MyObject.prototype.setName = function(rename) {
  this.name = rename;
};

var obj = new MyObject("서");
console.log(obj.getName());

//실행결과
/*
서
*/
```

- 객체가 아무리 생성되어도 클로저를 한 번만 생성
- 여러 객체에서 쓸 수 있는 메모리 낭비 줄임
