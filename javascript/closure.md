# closure
js scope chain을 이용하여 이미 생명 주기가 끝난 외부 함수의 변수를 참조하는 방법.
외부 함수가 종료되더라도 내부함수가 실행되는 상태면, 내부함부에서 참조하는 외부함수는 닫히지 못하고 내부 함수에 의해서 닫히게 되어 클로저라 부른다.

내부 변수는 하나의 클로저에만 종속될 필요는 없다. 외부 함수가 실행될 때마다 새로운 scope chain과 새로운 내부 변수를 생성한다. 또, 클로저가 참조하는 내부 변수는 실제 내부 변수의 복사본이 아닌 그 내부 변수를 직접 참조한다.

```javascript
function outerFunc(){
    var a= 0;
    return {
        innerFunc1 : function(){
            a+=1;
            console.log("a :"+a);
        },
        innerFunc2 : function(){
            a+=2;
            console.log("a :"+a);
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


## 클로저의 사용 이유
클로저를 사용하면 전역변수의 오,남용 없는 깔끔한 스크립트를 작성할 수 있다. 그의 대표적인 예로 `모듈 패턴`

## NOTE
**for문 클로저는 상위 함수의 변수를 참조할 때 자신의 생성될 떄가 아닌 내부 변수의 최종 값을 참조한다**
```javascript
window.onload = function(){
    var list = document.getElementsByTagName("button");

    for(var i =0, length = list.length; i<length; i++){
        list[i].onclick=function(){
        console.log(this.innerHTML+"은"+(i+1)+"번째 버튼입니다");
        }
    }
}
<button>1번째 버튼</button>
<button>2번째 버튼</button>
<button>3번째 버튼</button>
//실행결과
/*
1번째 버튼은 4번째 버튼입니다
2번째 버튼은 4번째 버튼입니다
3번째 버튼은 4번째 버튼입니다
*/
```
- 클릭 에빈트가 참조하는 변수 i의 값이 for문 다 돌고 난 후의 i값을 참조
- 1가지 i값을 참조하므로 전부 4라는 결과 나옴

#### 해결책 : 중첩 클로저
```javascript
window.onload = function(){
    var list = document.getElementsByTagName("button");

    var gate = function(i){
        list[i].onclick=function(){
        console.log(this.innerHTML+"은"+(i+1)+"번째 버튼입니다");
        }
    }
    for(var i =0, length = list.length; i<length; i++){
         gate(i);
    }
}
<button>1번째 버튼</button>
<button>2번째 버튼</button>
<button>3번째 버튼</button>
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
#### 클로저가 필요하지 않는 부분에서 클로저를 사용하는 것은 좋지 않은 방법

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
var obj= new MyObject("서");
console.log(obj.getName());
//실행결과
/*
서
*/
```
- 함수 객체가 생성될 때마다 클로저가 생성된다.(쓸데 없는 메모리 차지)

#### 함수 객체가 생성될 때마다 클로저 생성 -> prototype 객체를 이용한 클로저 생성
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
var obj= new MyObject("서");
console.log(obj.getName());
//실행결과
/*
서
*/
```
- 객체가 아무리 생성되어도 클로저를 한 번만 생성
- 여러 객체에서 쓸 수 있는 메모리 낭비 줄임
