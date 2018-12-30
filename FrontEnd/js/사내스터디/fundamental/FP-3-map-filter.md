# 유저 목록을 map, filter로 보여주기

```javascript
var users = [
    { id: 1, name: 'hoil', age: 27 },
    { id: 2, name: 'meensuni', age: 25 },
    { id: 3, name: 'aa', age: 23 },
    { id: 4, name: 'bb', age: 21 },
    { id: 5, name: 'cc', age: 29 },
    { id: 6, name: 'dd', age: 39 },
    { id: 7, name: 'ee', age: 32 },
]

/*
    명령형코드
    1. 30세 이상인 users를 필터링
*/
var temp_users = [];
for (var i = 0; i < users.length; i++) {
    if (users[i].age >= 30) {
        tempusers.push(users[i]);
    }
}
console.log(temp_users);

/*
    2. 30세 이상 유저 names 를 필터링
*/
var names = [];
for (var i = 0; i < temp_users.length; i++) {
    names.push(temp_users[i].name);
}
console.log(names);

/*
    3. 30세 미만의 users를 필터링
*/
var temp_users = [];
for (var i = 0; i < users.length; i++) {
    if (users[i].age < 30) {
        tempusers.push(users[i]);
    }
}

/*
    4. 30세 미만인 users의 page를 수집
*/
var ages = [];
for (var i = 0; i < temp_users.length; i++) {
    age.push(temp_users[i].age);
}
console.log(ages);
```

1,3번 코드가 중복이다. 조건부 제외 나머지 코드 동일하다. 조건문 중복 줄이기가 난해하다. 하지만 FP를 통해 중복을 줄일 수 있다. `_filter`라는 함수를 만들어보자. 일단 기존 코드를 복붙하자.

```javascript
function _filter(users) {
    var new_list = [];
    for (var i = 0; i < users.length; i++) {
        if (users[i].age >= 30) {
            new_list.push(users[i]);
        }
    }
    return new_list;
}
```

`var new_list= []`
함수형 프밍은 **인자 값을 직접 변경하지 않는다**. 변형된 새로운 값을 리턴한다. 그리고 코드를 다시 보자. 애매한 부분은 조건문이다. **FP에서 중복을 줄이거나 추상화할 필요가 있을 때, 함수를 이용하면 된다.** 추상화의 단위가 객체, 메서드가 아닌 함수다. 그래서 저 조건문을 함수를 통해 위임하는 방법을 알아보자.

```javascript
function _filter(users, predi) {
    var new_list = [];
    for (var i = 0; i < users.length; i++) {
        if (predi(users[i])) {
            new_list.push(users[i]);
        }
    }
    return new_list;
}

console.log(
    _filter(users, function(user) { return user.age >= 30; });
);
console.log(
    _filter(users, function(user) { return user.age < 30; });
)
```

filter는 응용형 함수다. 함수가 함수를 받아서 원하는 시점에 해당하는 함수가 알고 있는 인자를 적용하는 식으로 프로그래밍 하는 것이 응용형 함수다. 

`고차함수`라고도 부른다. **함수를 인자로 받거나 함수를 리턴하거나 인자로 받은 함수를 실행하는 것을 말한다.**

_filter는 다양한 일을 할 수 있다. 나이 제한 필터링만 할 수 있는게 아니다.

```javascript
_filter([1,2,3,4], function(num) { return num % 2; })
_filter([1,2,3,4], function(num) { return !(num % 2); })
```

전혀 다른 함수도 필터링할 수 있다. filter는 users뿐만아니라 전혀 다른 값([1,2,3,4])도 필터링 할 수 있다. 그 이유는 _filter 함수가 `순수함수`이기 때문이다. 어떤 값이 배열에 들어있더라도 필터링 할 수 있다. _filter는 높은 다형성과 재활용성이 높은 함수다.

---

이번엔 나이, 이름을 수집하는 코드의 중복을 제거한 map함수를 만들어보자. 이번에도 기존 코드를 그대로 복사하자. 

```javascript
var names = [];
for (var i = 0; i < temp_users.length; i++) {
    names.push(temp_users[i].name);
}
```

응용형 함수로 변경해보자. 어떤 프로퍼티를 추출해서 배열에 추가해보는 방식으로 작성하자. 아래 코드 중 **`mapper()`로 변경 후 다형성이 높아지고 데이터가 어떻게 생겼는지 보이지 않는다.** 그래서 재사용성이 극대화되었다.

```javascript
function _map(list, mapper) {
    var new_list = [];
    for (var i = 0; i < list.length; i++) {
        new_list.push(mapper(list[i]));
    }
    return new_list;
}
```

`_map`을 사용해보자

```javascript
var over_30 = _filter(users, function(user) { return user.age >= 30});
console.log(over_30);

var names = _map(over_30, function(user){ return user.name })
console.log(names);

var under_30 = _filter(users, function(user) { return user.age < 30; });

var names = _map(under_30, function (user) {
    return user.name;
})
```

함수형 프밍에서는 대입문을 많이 사용하지 않는다. 그래서 위 코드에서도 대입문을 줄이면 좀 더 간결해진다. 함수형 프밍은 값을 만들어놓고 문장을 내려가면서 값이 변형되는 식이 아니다. 함수를 통과하면서 값을 새롭게 만들어나가는 방식이다. 그래서 함수를 중첩하는 식으로 코드를 간결하게 표현할 수 있다.

```javascript

// var over_30 = _filter(users, function(user) { return user.age >= 30});
// var names = _map(over_30, function(user){ return user.name })
// 위와 같은 코드다. 대입문을 제거하여 코드를 보다 간결하게 표현할 수 있다.
_map (
    _filter(users, function(user) { return user.age >= 30}),
    function(user) {return user.name}
)
// 30세 이상인 유저들을 걸러서 이름만 추출하기
```

## 요약

인자 값을 직접 변경하지 않고 새로운 값을 리턴한다. 중복되는 부분을 함수를 이용하여 추상화를 통해 해결한다. 추상화의 단위는 객체, 메서드가 아닌 함수다. 이 때 함수는 순수함수여야 한다. 이를 통해 다형성과 재활용성을 높일 수 있다. 

응용형 함수는 함수가 함수를 인자로 받아서 원하는 시점에 해당 함수가 알고 있는 인자극 적용하는 식으로 프밍하는 것이다. 이는 `고차 함수`라고 한다. 