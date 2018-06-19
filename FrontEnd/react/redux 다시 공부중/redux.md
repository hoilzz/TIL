# redux

## react state가 불변이여야 하는 이유

react는 immutability를 강조한다. 프밍을 하다보면 수정 불가능한 변수를 가끔 볼 수 있다.

수정 불가능한 변수는 다양한 장점을 가지는데 그 중 2가지가 대표적이다.

1. 변수가 수정 불가능하면 함수에서 side effect 발생 확률이 낮아진다. side effect가 없는 것으로 프로그램의 복잡도를 줄일 수 있다. 또한, 병렬 처리를 효율적으로 할 수 있는데 빅데이터 분석 프로그램의 spark에서 함수형 언어인 scala를 주 언어로 채택한 이유가 여기 있다.

```
var getPlusOneDay = function(date) {
  date.setDate(date.getDate() + 1);
  return new Date(date);
}

var date1 = new Date(2016, 1, 1);
var date2 = getPlusOneDay(date1);
// 의도치 않게 date1과 date2는 동일한 값을 가진다. 
```

- 수정 불가능한 변수는 thread-safe 하므로 동기화 문제에서 자유롭다. 두 개의 스레드가 동시에 같은 변수를 수정하려고 하는 경우를 생각해보면 이해하기 쉽다.

하지만 성능이 중요한 경우 수정 가능한 변수를 사용해야 한다. 60 fps를 목표로 하는 게임에서 캐릭터 위치 값을 업데이트하는 경우 매 번 새로운 객체 생성하는 것보다 기존 객체의 값을 변경하는 것이 효율적이다.

수정 불가능한 변수의 일반 장점 외에도 react state에서의 불변성을 강조하는 이유는 따로 있다.

## React가 화면을 업데이트 하는 과정

1. setState를 호출 (혹은 부모로부터 props를 받음)
2. SCU를 실행하여 false 리턴시 해당 컴포넌트 및 하위에서 호출하는 render()를 포함한 렌더링 프로세스 생략
3. *가상 DOM과 실제 DOM일 비교하여 변경사항이 있으면 화면을 다시 그린다.*

