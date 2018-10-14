# delete operator

## delete와 host objects

`delete`의 알고리즘은 대략 다음과 같다.

1. operand가 참조값이 아니라면 true
2. object가 direct property를 가지지 않는다면, `true`를 리턴한다.
  - 여기서 object는 Activation object or Global object다.
3. 만약 프로퍼티가 존재하지만 DontDelete면, false를 리턴한다.
  - 반면에 가능하면, remove property and return false


```javascript
let i = 0;
const obj = {}
while(i<1000) {
    obj[i] = i;
    i+=1
}

const collection = new Map();
i = 0;

while(i < 1000) {
    collection.set(i, i);
    i+=1
}

console.time('object delete');
delete obj[500];
console.timeEnd('object delete');

console.time('map delete');
collection.delete('500');
console.timeEnd('map delete');
```