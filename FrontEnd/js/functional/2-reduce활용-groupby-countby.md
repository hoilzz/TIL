# reduce 활용 (posts, users), countBy, groupBy

```javascript
const valuesIter = gen(function *(obj) {
  for (const k in obj) yield obj[k];
});

const entriesIter = gen(function *(obj) {
  for (const k in obj) yield [k, obj[k]];
});

const reverseIter = gen(function *(arr) {
  var l = arr.length;
  while (l--) yield arr[l];
});

const hasIter = coll => !!coll[Symbol.iterator];

const collIter = coll =>
  hasIter(coll) ?
    coll[Symbol.iterator]() :
    valuesIter(coll);

const then = (f, a) => a instanceof Promise ? a.then(f) : f(a);
const then2 = (a, f) => a instanceof Promise ? a.then(f) : f(a);

function reduce(f, coll, acc) {
  return then(function(coll) {
    const iter = collIter(coll);
    acc = acc === undefined ? iter.next().value : acc;
    return then(function recur(acc) {
      for (const v of iter) {
        acc = f(acc, v);
        if (acc instanceof Promise) return acc.then(recur);
      }
      return acc;
    }, acc);
  }, coll);
}
```

FP할 때 가장 큰 뼈대가 reduce, map, filter, find다. reduce는 전체를 다 돌려고 할 때, find는 중간에 멈추기 위해서.. 명령형 프밍 때 break를 짤 때가 있는데 그 때 find 사용한다. 최적화 해서 중간에 멈추고자 한다면 find를 사용한다.

---

reduce를 통해 comments의 총합을 구해보자. 일단 return 하고자 하는 타입이 입력 값 타입과 다르다.

Q. posts의 총 comments를 reduce를 이용하여 출력하자.

```javascript
const posts = [
  { id: 1, body: '내용1', comments: [{}, {}] },
  { id: 2, body: '내용2', comments: [{}] },
  { id: 3, body: '내용3', comments: [{}, {}, {}] },
];

console.log(reduce((count, p) => count + p.comments.length, posts, 0));
```

입력값인 posts를 개발자가 알고 있고, 보조 함수에서 맞춰줘야할 규격 혹은 프로토콜은 내가 posts를 넣고 있기 때문에 모든 형을 접을 수 있다. 리듀스의 다형성은 바깥 데이터의 다형성 뿐만 아니라 안에 있는 값의 다형성도 보조함수를 통해 높일 수 있다. 그래서 FP는 다형성을 높게 가질 수 있는 패러다임이다.

```javascript
reduce((count, p) => count + p.comments.length, posts, 0);
reduce((count, p) => count + p.getComments().length, posts, 0);
```

```javascript
// 할 일 하고 자기 자신을 받는 함수
function incSel(obj, sel) {
  obj[k] ? obj[k]++ : obj[k] = 1;
  return obj;
}

const users = [
  {id: 1, name: 'name1', age: 30},
  {id: 2, name: 'name2', age: 31},
  {id: 3, name: 'name3', age: 32},
  {id: 4, name: 'name4', age: 31},
  {id: 5, name: 'name5', age: 32},
];

/*
{
  30: [{ id: 1, name: 'name1', age: 30}],
  31: [{id: 2, name: 'name2', age: 31}, {id: 4, name: 'name4', age: 31},],
  32: [...]
}

{
  30: 1,
  31: 2,
  32: 2
}

*/

// reduce를 통해 위와 같은 결과값 만들기

console.log(reduce((results, user) => {
  results[user.age] ? results[user.age].push(user) : results[user.age] = [user]
  // (results[user.age] || (results[user.age] = [])).push(user);
  return results;
}, users, {}))

console.log(reduce((results, user) => incSel(results, user.age), users, {}))

// incSel({}, 'a'); // {a: 1}
// incSel(incSel({}, 'a'));
function incSel(parent, k) {
  parent[k] ? parent[k]++ : parent[k] = 1;
  return parent;
}

function countBy(f, coll) {
  return reduce((counts, a) => incSel(counts, f(a)), coll, {})
}

console.log(reduce((counts, a) => incSel(counts, a.age), users, {}));

countBy(u => u.age, users);

// ag를 기준으로 results 객체에 push
console.log(reduce((results, user) => pushSel(results, user.age, user), users, {}))

function pushSel(parent, k, v) {
  (parent[k] || (parent[k] = [])).push(v);
  return parent;
}

const groupBy = (f, coll) => reduce((group, a) => pushSel(group, f(a), a), coll, {})

groupBy(u => u.age, users);
```

위와 같은 일은 앞으로도 많이 할 거 같다. 개선시켜보자. (`incSel` 참고)

**reduce 부터 groupBy까지 수업 때 만든 메서드들 다시 만들어보세여. 그럼 왕도움됨**

