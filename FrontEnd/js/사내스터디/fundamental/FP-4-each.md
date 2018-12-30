# Each

FP-3-map-filter에서 함수형 프밍을 통해 중복되는 곳을 제거했다. 이 때 중복되는 for문을 해결하지 못했다. `each()`문을 통해 해결해보자. 

```javascript
function _filter(users, predi) {
    var new_list = [];
    _each(list, function(val){
        if (perdi(val)) {
            new_list.push(val);
        }
    });
    // for (var i = 0; i < users.length; i++) { // 중복
    //     if (predi(users[i])) { // 중복
    //         new_list.push(users[i]);
    //     }
    // }
    return new_list;
}

function _map(list, mapper) {
    var new_list = [];
    _each(list, function(val) {
        new_list.push(mapper(val));
    })
    // for (var i = 0; i < list.length; i++) {
    //     new_list.push(mapper(list[i]));
    // }
    return new_list;
}

/*
    이 함수는 단순히 iter를 돌기.
    안에서 하는 일을 완전히 위임
*/

function _each(list, iter) {
    for (var i = 0; i < list.length; i++) {
        iter(list[i]);
    }
    return list;
}
```

