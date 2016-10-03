# map
Map object는 key/value map이다. 객체와 primitive value 어떤 값이든 key 혹은 value로 사용될 수 있다.

## syntax
> new Map([iterable])

### Parameters
iterable
: Iterable은 배열 or 엘리먼트가 key-value pair인 iterable object다. 각 key-value pair는 new Map에 추가된다. null은 undefined로 다뤄진다.

## Description
A Map object는 추가된 순서대로 element를 순회한다. for...of loop는 각 iteration마다 [key, value] 배열을 리턴한다.

object의 map인 Map (특히 dictionary of dictionaries)는 object 추가 순서대로 map할 것이다.
It should be noted that a Map that is a map of an object, especially a dictionary of dictionaries, will only map to the object's insertion order -- which is random and not ordered.  

### Key equality
Key 동등성은 "same-value" 알고리즘 기반이다: Nan은 Nan과 같다 (Nan !== Nan 이다 원래) 그리고 모든 다른 값은 === operator의 문법에 따라 동등한 것으로 간주된다.

## Objects and maps compared

너가 key와 값을 모두 세팅하고, 값을 불러내고, key를 삭제하고, key에 무언가 저장되어있는지 아닌지 detect 한다는 면에서 Objects는 Maps와 동등하다. 이거 때문에 Objects는 Maps로 사용되곤 한다 : 그러나 중요한 차이점이 있고 Map을 이용했을 때 더 나은 점이 있다.
- Object는 prototype을 가진다. 그래서 map안에 default key가 있다. ES5 이래로 `map = object.create(null)`을 이용하여 우회하는 방식을 이용한다. 하지만 이 방법은 거의 이용안한다
- Object의 Key는 String이고 Symbols이다. (Map에선 어떠한 값도 key가 될 수 있다)
- Map의 사이즈를 쉽게 알 수 있다. 반면에 object의 경우 사이즈 기록을 유지해야한다.

<hr><hr>

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
