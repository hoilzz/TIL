# 인덱스타입

동적 프로퍼티 이름을 사용하는 코드를 컴파일러가 검사하도록 하기.

객체에서 프로퍼티의 하위 집합 선택시 JS 코드.

```js
function pluck(o, names) {
  return names.map(n => o[n]);
}
```

다음은 **인덱스 타입 쿼리** , **인덱스 접근** 연산자를 이용하여 TS에서 이 함수를 작성하고 사용하는 방법

```ts
function pluck<T, K extends keyof T>(o: T, names: K[]): T[K][] {
  return names.map(n => o[n]);
}

interface Person {
  name: string;
  age: number;
}
let person: Person = {
  name: "Jarid",
  age: 35
};
let strings: string[] = pluck(person, ["name"]); // 좋아요, string[]
```

**컴파일러는 name이 실제로 Person의 프로퍼티인지 확인**

### keyof

- `keyof T`: 인덱스 타입 쿼리연산자
  - 어떤 타입의 T에 대해서 keyof T는 T의 알려진 public 프로퍼티 이름들의 유니온;

```ts
let personProps: keyof Person;
```

Person에 address: string을 추가하면 `keyof Person`은 자동으로 `name|age|address`로 업데이트됨.

pluck 과 같은 일반적인 컨텍스트에서 keyof 사용가능. 이때는 프로퍼티 이름을 미리 알 수 없다.
**즉 컴파일러가 올바른 프로퍼티 이름을 pluck으로 전달했는지 확인**

```ts
pluck(person, ["age", "unknown"]); // 오류, 'unknown'은 'name' | 'age'에 없습니다
```

### 인덱스 접근 연산자

`T[K]`, 타입의 구문은 표현식을 반영.

즉, `person[name]`은 `Person[name]` 타입을 가진다.

인덱스 타입 쿼리와 마찬가지로 T[K]를 사용하면 일반적인 컨텍스트에서 사용 가능.
타입 변수 `K extends keyof T`를 확실히 만들어야 한다.

```ts
function getProperty<T, K extends keyof T>(o: T, name: K): T[K] {
  return o[name]; // o[name]은 T[K] 타입입니다
}
```

getProperty에서 `o: T`와 `name: K`는 `o[name]: T[K]`를 의미

`T[K]` 결과를 반환하면 컴파일러는 실제 키의 타입을 인스턴스화하므로,
getProperty의 반환 타입은 사용자가 요청하는 프로퍼티에 따라 달라진다.

```ts
let name: string = getProperty(person, "name");
let age: number = getProperty(person, "age");
let unknown = getProperty(person, "unknown"); // 오류, 'unknown'은 'name' | 'age'에 없습니다
```

## 인덱스 타입과 문자열 인덱스 시그니처

`keyof`와 `T[K]`는 문자열 인덱스 시그니처와 상호작용한다.

문자열 인덱스 시그니처를 가진 타입을 가지고 있다면 `keyof T`는 단지 string이 된다.

```ts
interface Map<T> {
  [key: string]: T;
}
let keys: keyof Map<number>; // string
let value: Map<number>["foo"]; // number
```
