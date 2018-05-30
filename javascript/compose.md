# compose

```javascript
export function compose(...funcs) {
  return arg => funcs.reduceRight((composed, f) => f(composed), arg);
}
```

## reduceRight

누적된 함수를 적용하고, 배열의 각 값(R->L)은 single value로 줄인다.

```javascript
var flattened = [[0, 1], [2, 3], [4, 5]].reduceRight(function(a, b) {
    return a.concat(b);
}, []);

// flattened is [4, 5, 2, 3, 0, 1]
```

### syntax

> arr.reduceRight(callback[, initialValue])

- callback
    - prevValue: 콜백의 마지막 호출에서 이전에 리턴된 값
    - currentValue