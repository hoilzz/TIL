# state 내부 배열 처리하기 | Immutability Helper / ES6 spread

무조건 setState로 처리해야 하는데

state 내부 배열에 변화를 주려면 어떻게 해야 할까
예를 들어 데이터 추가시 js array, 배열의 내장함수 push 쓰면 안됨
왜냐면 이건 배열 자체 변경하니까..

그 대신에 concat으로 추가하고 배열의 새 값을 추가하면된다.

concat은 기존배열 그대로 두고 새 배열 추가

다른 방법은 immutability helper

객체나 배열을 조금 더 쉽게 수정할 수 있는 페북 라이브러리

이 라이브러리 사용하여 배열 간단히 변경 해보자.

update 함수의 첫번째 인수는 처리해야할 배열
2번째 인수는 처리명령 지니고 있는 객체

push 명령을 통하여 리스트 배열에 newObj 2개 추가해

참고로 한 객체 추가해도 배열 형태로 감싸줘야함

혹시 몽고 디비 사용해봤다면...

immutable js는 몽고 디비 쿼리에서 영감 받음

## 원소 제거

splice도 있다. (원소제거))

리스트 배열의 index 아이템부터 시작해서 1개의 데이터를 제거한다는 의미

splice에 전달된 건


## 원소 수정

index 번째 아이템의 field와 field2 값을 변경하는 코드다.

여기서는 set이 사용된다. (간단한 사용법)

이 list가 주어진 값이 배열이 아니라 객체여도 상관없다.

만약 객체 였으면 this.state.list에 객체 들어감

[index] 대신에 객체의 키가 들어가고

field, field2에 또 키가 들어가고

let object = {
  a: '1',
  ...
  c: {
    f: {
      change_this_value : '0',
      this_stays_same : '6'
    }
  }

}

객체 접근할 때도 직접 접근하면 안돼

그래서 immutable helper 사용

let changed = update (object, {
  c: {
    f: {
      change_this_value: '0',
      this_stays_same: '6'
    }
  }
})

----

imuutable helper는
이정도 까지만 다뤄보자

es6에서는 spread 문법 도입되었는데 그걸 사용해도 된다.

## spread
위에꺼 let object가 원소스

```javascript
let changed = {
  ...object
};
```
위값을 출력하면 let object 내용나옴
b값 바꾸고 싶으면
```javascript
let changed = {
  ...object,
  b: "hi",
  c: {
    ...object.c,
    f: {
      ...object.c.f,
      change_this_value: '5'
    }
  }
}
```javascript
let array = [0,1,2,3,4,5,6];
let changed = [...array, 7];
```

```javascript
let array = [1,2,3,4,5,6,7];
let changed = [...array.slice(0,2), '수정', ...array.slice(3, array.slice())];
```

slice 함수는 특정 index에서 특정 index 전까지 값을 불러온다.
지금 상황에선 index0부터2까지 불러오기

spread operator가 immutable보다 쉬울때, 번거로울 때 둘 다 있다.

spread operator 사용하려면 따로 추가해줄게 있다. 프로젝트에

> npm install --save babel-preset-stage-0

webpackconfig.js
여기서 preset에 stage-0 추가하기
우리는 이거 안쓰고 immutable helper 자주써볼께
