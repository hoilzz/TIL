# immutable.js

불변성의 데이터를 효과적으로 다룰 수 있는 라이브러리.

다음과 같은 복잡한 데이터를 효과적으로 다룰 수 있게 도와준다.

```javascript
// use es6 ...
let object1 = {
    a: 1,
    b: 2,
    c: 3,
    d: {
        e: 4,
        f: {
            g: 5,
            h: 6
        }
    }
};

// h값을 10으로 업데이트함
let object2 = {
    ...object,
    d: {
        ...object.d,
        f: {
            ...object.d.f,
            h: 10
        }
    }
}
```

```javascript
let object1 = Map({
    a: 1,
    b: 2,
    c: 3,
    d: Map({
        e: 4,
        f: Map({
            g: 5,
            h: 6
        })
    })
});

let object2 = object1.setIn(['d', 'f', 'h'], 10);
```

## 3.1 Map

```javascript

```
