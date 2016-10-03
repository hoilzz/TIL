# Array.prototype.map()

## Summary
map() 메서드는 배열 내의 모든 요소 각각에 대하여 제공된 함수(callback)를 호출하고, 그 결과를 모아서, 새로운 배열을 반환.


callback
  새로운 배열 요소를 생성하는 함수로 세가지 인수를 가진다

  currentValue
    배열의 요소 중, 현재 처리되고 있는 요소
  index
    현재 처리되는 요소의 배열 내 인덱스
  array
    map 메소드가 적용되는 본래 배열

  thisArg
    선택항목. callback을 실행할 때 this로 사용되는 값. 기본값은 Window 객체

## 예제
### 배열에 들어있는 숫자들의 제곱근을 구하여 새로운 배열 만들기
다음 코드는 숫자의 배열을 받아 각 숫자들의 제곱근이 들어있는 새로운 배열 만듭니다.

  var numbers = [1,4,9];
  var roots = numbers.map(Math.sqrt);
  // roots의 값은 [1,2,3]이 되지만, numbers는 그대로 [1,4,9]다.

### map을 활용해 오브젝트 다시 구성하기
var kvArray = [{key:1, value:10}, {key:2, value:20}, {key:3, value: 30}];
var refrommattedArray = kvAray.map(function(obj){
      var rObj = {};
      robj[obj.key] = obj.value;
      return rObj;
});

### 숫자가 들어있는 배열을 인수가 있는 함수를 사용하여 재구성하기
다음 코드는 map이 작동하는 방식을 보여준다
