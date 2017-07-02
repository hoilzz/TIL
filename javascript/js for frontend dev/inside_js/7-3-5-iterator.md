# 7.3.5 iterator

## 7.3.5.1 each

배열의 각 요소 혹은 객체의 각 프로퍼티를 하나씩 꺼내어 특정 함수에 인자로 넣어 실행시켜보자.

```javascript
var arr = [1,2,3,4];

function each(obj, fn, args){
  // object인 경우
  if(obj.length == undefined){
    for(var i in obj){
      fn.apply(obj[i], [i, obj[i]]);
    }
  }
  // 배열인 경우
  else{
    for(var i = 0; i < obj.length; i++){
      fn.apply(obj[i], [i,obj[i]]);
    }
  }
  return obj;
}

var user = {
  name:"hoil",
  age:20,
  job:"student"
};

each([10,20,300], function(idx, num){
  console.log(idx + " : " + num);
})

each(user, function(key, num){
  console.log(key + " : " + num);
})
```

- 배열을 length가 있는 경우, 객체는 length가 없는 경우다.

## 7.3.5.2 map

배열에서 많이 사용되는 함수다.

배열의 각 요소를 꺼내서 사용자 정의 함수를 적용시켜 새로운 값을 얻은 후, 새로운 배열에 넣는다.

```javascript


// 배열의 값을 꺼낸다.
// 꺼낸 배열 값을 콜백 함수에 넣는다.
// 콜백 반환 값을 받는다.
// 새로 만든 배열 객체[i] = 콜백 반환 값
// 이터레이터 종료 후, return 새로만든배열객체

Array.prototype.map = function(callback){
    var obj = this;

    var newArr = new Array(obj.length)

    for(var i=0; i<newArr.length; i++){
        var value = obj[i];
        var mappedValue = callback(value);
        newArr[i] = mappedValue;
    }
    return newArr;
}

var arr = [1,2,3];
var new_arr = arr.map(function(value){
    return value*value;
})
console.log(new_arr);
```
