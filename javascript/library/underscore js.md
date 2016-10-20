# underscore.js
  Underscore는 내장된 오브젝트를 확장하는 거 없이 유용한 functional 함수 헬퍼의 whole mess를 제공하는 js 라이브러리다. "만약 내가 blank HTML page 앞에 앉고, 즉시 생산적인 것이 되기를 원한다면, 난 뭐가 필요할까?"... and the tie to go along with jQuery's tux and Backbone's suspenders.

  UnderScore는 너가 가장 좋아하는 함수 헬퍼: **map, filter, invoke** 100가지 함수 이상을 제공한다. (저 함수들 뿐만아니라 더 전문화된 goodies : biding, js templating, creating quick indexed, deep equality testing, and so on)

## Collection Functions (Arrays or Objects)

#### each
> .each(list, iteratee, [context]) Alias : forEach
- 엘리먼트 리스트를 iterate
- iteratee function에서 각각 회전
- iteratee는 context object를 바운딩
- iteratee의 각 invaction은 3개의 인자와 함께 호출됨(element, index, list)
- 만약 **list**가 js object면
  - iteratee's의 인자는 (value, key, list)가 될것이다
  - 체이닝 list가 리턴된다.

> _.each([1,2,3], alert);
> => alerts each number in turn..
> _.each({one:1, two:2, three: 3}, alert);
> => alerts each number value in turn...

> var list = [1,2,3,4,5,6];
> _.each({one:10, two:2, three: 3}, (key)=>{alert(key);});
