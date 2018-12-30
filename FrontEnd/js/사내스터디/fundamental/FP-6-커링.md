# 커링

커링은 함수와 인자를 다루는 기법이다. 함수에 인자를 하나씩 적용하면서 필요한 인자가 모두 채워지면 함수 본체를 실행하는 기법이다. 일급함수 및 평가시점을 마음대로 다룰 수 있기 때문에 구현 가능하다. add_maker에 인자 하나를 설정 해두고 더하기 함수를 만들었던 것과 비슷한 기법이다. 

```javascript
function _curry(fn) {
    return function(a) {
        // if (arguments.length == 2) return fn(a, b);
        return function(b) {
            return fn(a, b);
        }
    }
}

var add = function(a, b) {
    return a + b;
}

console.log( add(10, 5) );
```

커리함수는 위 add함수를 만들 때 감싸주기만 하면 된다. 

```javascript
var add = _curry(function(a, b) {
    return a + b;
});

var add10 = add(10);
var add5  = add(5);
console.log( add10(5) );
console.log( add(5)(3) );

add5(3);
add(10)(3);

add(1,2) // 함수를 리턴받음 위 주석 풀면 예상한대로 동작 
```

curry는 본체 함수인 `add()` 를 들고 있다가 원하는 시점까지 미루다가 최종 평가하는 기법이다. 함수가 함수를 대신 실행 혹은 함수가 함수를 리턴하여 함수를 조합해 나갈 수 있는 것이 FP다. 

정리하면, curry는 필요한 인자를 모두 채울때까지 인자를 적용해나간다. 모든 인자 개수가 채워지면 함수 본체를 실행하는 기법이다.

커리 함수를 통해 빼기 함수를 만들어보자.

```javascript
function _curry(fn) {
    return function(a) {
        return arguments.length === 2 ? fn(a,b) : function(b) { return fn(a, b) };
    }
}

function _curryr(fn) {
    return function(a) {
        return arguments.length === 2 ? fn(a, b) : function(b) { return fn(b, a) };
    }
}

var sub = _curryr(functino (a, b) {
    return a - b;
});

console.log( sub(10, 5) ); // 10 - 5

var sub10 = sub(10);
console.log(sub10(5)); // 5 - 10
```

## _get 만들어보기

_get()은 오브젝트에 있는 값을 안전하게 참조하는 함수다. 

```javascript
function _get(obj, key) {
    return obj === null ? undefined : obj[key];
}

var users = [
    { id: 1, name: 'hoil', age: 27 },
    { id: 2, name: 'meensuni', age: 25 },
    { id: 3, name: 'aa', age: 23 },
    { id: 4, name: 'bb', age: 21 },
    { id: 5, name: 'cc', age: 29 },
    { id: 6, name: 'dd', age: 39 },
    { id: 7, name: 'ee', age: 32 },
]

var user1 = users[0];
console.log(_get(user1, 'name')); 

console.log(users[10].name); // undefined이므로 에러 발생
console.log(_get(user1, 'name')); // error 발생하지 않고 undefined를 리턴
```

좀 더 안전하게 객체의 속성을 가져올 수 있다. 

```javascript
var _get = _curryr(function(obj, key) {
    return obj === null ? undefined : obj[key];
})
console.log(_get('name')(user1));

var get_name = _get('name');
console.log( get_name(user1) );
console.log( get_name(users[3]) );

// 예전에 만들었던 다음 코드가 간결해질 수 있다. 
_map (
    _filter(users, function(user) { return user.age >= 30}),
    // function(user) {return user.name}
    _get('name')
)
```
