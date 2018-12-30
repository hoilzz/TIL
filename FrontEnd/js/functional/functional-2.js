function gen(g) {
  return function(v) {
    const iter = g(v);
    return { next: () => iter.next(), [Symbol.iterator]() { return this; } }
  }
}

const hasIter = coll => !!coll[Symbol.iterator];

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
const collIter = coll =>
  hasIter(coll) ?
    coll[Symbol.iterator]() :
    valuesIter(coll);

const then = (f, a) => a instanceof Promise ? a.then(f) : f(a);
const then2 = (a, f) => a instanceof Promise ? a.then(f) : f(a);

function reduce(f, coll, acc) {
  // return then(function(coll) {
    // console.log(coll);
    const iter = collIter(coll);
    acc = acc === undefined ? iter.next().value : acc;
    // return then(function recur(acc) {
      for (const v of iter) {
        acc = f(acc, v);
        if (acc instanceof Promise) return acc.then(recur);
      }
      return acc;
    // }, acc);
  // }, coll);
}

const posts = [
  { id: 1, body: '내용1', comments: [{}, {}] },
  { id: 2, body: '내용2', comments: [{}] },
  { id: 3, body: '내용3', comments: [{}, {}, {}] },
];

console.log(reduce((count, p) => count + p.comments.length, posts, 0));

const users = [
  {id: 1, name: 'name1', age: 30},
  {id: 2, name: 'name2', age: 31},
  {id: 3, name: 'name3', age: 32},
  {id: 4, name: 'name4', age: 31},
  {id: 5, name: 'name5', age: 32},
];

/*
아래와 같은 결과가 나오도록 reduce를 통해 구현해보기
{
  30: [{ id: 1, name: 'name1', age: 30}],
  31: [{id: 2, name: 'name2', age: 31}, {id: 4, name: 'name4', age: 31},],
  32: [...]
}
*/

//
function incSel(parent, k) {
  parent[k] ? parent[k]++ : parent[k] = 1;
  return parent;
}

// f인자에서 리턴된 값을 count
function countBy(f, coll) {
  return reduce((counts, a) => incSel(counts, f(a)), coll, {})
}

console.log(reduce((results, user) => {
  results[user.age] ? results[user.age].push(user) : results[user.age] = [user]
  // (results[user.age] || (results[user.age] = [])).push(user);
  return results;
}, users, {}))

console.log(reduce((counts, a) => incSel(counts, a.age), users, {}));

countBy(u => u.age, users);

// ag를 기준으로 results 객체에 push
console.log(reduce((results, user) => pushSel(results, user.age, user)
// {
  // results[user.age] ? results[user.age] += 1 : results[user.age] = 1;
  // // (result[user.age] || (results[user.age] = 0)) += 1;
  // return results;

// }
, users, {}))

function pushSel(parent, k, v) {
  (parent[k] || (parent[k] = [])).push(v);
  return parent;
}

const groupBy = (f, coll) => reduce((group, a) => pushSel(group, f(a), a), coll, {})

groupBy(u => u.age, users)

console.log(
  groupBy(a => a, [1,2,3,4,5,5,10,10,10])
)