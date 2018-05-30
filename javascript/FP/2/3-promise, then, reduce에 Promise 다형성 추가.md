# Promise, then, 동기/비동기 다형성, reduce에 Promise 다형성 추가

데이터 외에 UI 다룰 때에도 많이 쓰인다. 예를 들어 confirm창을 디자인해서 띄워야하는 경우 확인 누르기 전까지 가만히 있어야된다. 이것을 Promise를 통해 코드를 작성하면 중간에 대기할 수 있다.

Promise는 비동기 상황을 다루는 값이다.

```javascript
function reduce(f, coll, acc) {
  const iter = collIter(coll);
  acc = acc === undefined ? iter.next().value : acc;
    for (const v of iter) {
      acc = f(acc, v);
      if (acc instanceof Promise) return acc.then(recur);
    }
    return acc;
}
```

브라우저에서 변화가 생길 경우, 어떤 애 크기를 키웠다가 색을 바꿨다가 크기를 줄였다가 이런것들을 몇번해서 변화를 주면, 브라우저가 이런 변화가 일어날 때마다 렌더링을 할까?

브라우저가 한 번 그리는 타이밍은 js 콜스택이 비워질 때이다. 그럼 이 콜스택은 언제 비워질까? 함수가 다 끝나야 비워진다. 중간에서 비동기가 이뤄지면 바로 비워진다. 크기, 색 변화가 비동기에 들어있다면 혹은 위에서 리듀서 하기 위해 비동기가 생겼고 await 걸고 css 넣고, await 걸고 css 넣으면 틱틱 렌더링 된다.

동기와 비동기를 나눠서 코딩하는 것은 굉장히 중요하다. 