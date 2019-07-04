# as const와 generic으로 타입 추론 하기

## as const부터 알아보자.

TS 3.4는 `const` assertion이라고 부르는 literal value를 위한 새로운 생성자를 소개한다
이 syntax는 `123 as const`와 같은 type 이름에 `const`로 type assertion을 한다.
const assertion으로 새로운 literal 표현식을 생성할 때, TS 시스템에게 다음 것들을 알려준다.

- 해당 표현식에 literal type이 확장되지 않아야한다. (hello에서 string으로 확장 ㄴㄴ)
- object literal은 readonly property를 갖는다.
- array literal은 readonly tuple이 된다.

> readonly 키워드는 프로퍼티들을 읽기 전용으로 만든다. 또한 해당 프로퍼티들은 선언 또는 생성자에서 초기화 해야한다.

이 기능은 컴파일러에게 불변성을 암시하는 용도로 사용되는 형식을 생략할 수 있다는 것을 의미한다.

```ts
// Works with no types referenced or declared.
// We only needed a single const assertion.
function getShapes() {
  let result = [
    { kind: "circle", radius: 100 },
    { kind: "square", sideLength: 50 }
  ] as const;

  return result;
}

for (const shape of getShapes()) {
  // Narrows perfectly!
  if (shape.kind === "circle") {
    // as const로 readonly로 선언될 경우, shape. 했을 때 radius만 나온다.
    // 만약 as const를 제거하면 shape. 했을 경우 radius, sideLength가 나온다.
    console.log("Circle radius", shape.radius);
  } else {
    console.log("Square side length", shape.sideLength);
  }
}
```

## Generics

제네릭의 주요 동기는 멤버들 사이에 의미 있는 유형의 제약조건을 제공하는 것이다.
멤버는 다음과 같다.

- class instance members
- class methods
- function arguments
- function return value

## motivation and sample

reverse function이다. **내가 궁금했던 예제다.**

```ts
function reverse<T>(items: T[]): T[] {
  var toreturn = [];
  for (let i = items.length - 1; i >= 0; i--) {
    toreturn.push(items[i]);
  }
  return toreturn;
}

var sample = [1, 2, 3];
var reversed = reverse(sample);
console.log(reversed); // 3,2,1

// Safety!
reversed[0] = "1"; // Error!
reversed = ["1", "2"]; // Error!

reversed[0] = 1; // Okay
reversed = [1, 2]; // Okay
```

`reversed[0] = '1'` 의 에러는 이미 컴파일러가 추론 가능한 타입에 대해 타입을 정의했기 때문이다.

이번 섹션에서 _class level_ 과 _function level_ 에서 정의되는 제네릭 예제를 볼 수 있다.

> TIP: 너가 원할 때마다 generic parameter를 호출 할 수 있다. 간단한 제네릭일 때 T, U, V로 사용하는게 컨벤션이다. 만약 1개 이상의 제네릭 인자를 가진다면 의미있는 이름을 지어라.

## ts와 redux 예제 만들다가 궁금했던 점

[TS 예제와 주석을 확인하자.](http://www.typescriptlang.org/play/#code/C4TwDgpgBAkgogO2AS1AHgEoBooGUcBiAfFALxQDeAUFFBnAIoCqcuAKgFx0DcNeTAYQGtcXXL1oEAgjAAyTelwK8AvryqhIsRClAAmMpT71mrTlADOwAE7IEAcwn8hIrldsOn0uQrhubdo5UalRUAPRhUPYQCBC2AMaAIuNQgK2LgC6rUDG6IFLxKAD2CBaAGuN0WPgEUIBINcmAL3OAMMuAPuOAN+2AADVQgATjgCmzAHThkYAu41CAIa2EcGwCABIA+gBCUgByC3AYuFCAAz2AGEOAC6NQAIYWUPGFVu2AY6OAJ02ALl04Wag5ecgnu4AnLYAto4A0Y9WAAuOWAQ6AHnHADodUEAAwuAUPGhoBUCeKgBwWi59CJQQCRk7ckPdcgUij0TCx2IAUpr+HnswLBkKgMPhPSggBV5wA7LVAAMwAFkAET2AD8moIAfdsAHuNQUmtQAJ431jkVgEdrBA9sAIDoMY8ToZMDh8FBiAAKO6gTFPIpceDo9DYPCEIgASjIJHV1FokoAjgBXCBWLjqi2kK022hQTQQLhah5Yiw4xh4th8FRmrDBM3qUVWCVSmVy7UKooGciaw2B3UWfUpkB6d2evj2p0uqBuy2Vig+8B+zLZnUnEOmdhQSPRyNxk7igjjKZzRbLVaGL24sxcADk-YmM3mSxWuGmE-YU+jtFwgmEuFEUBnA-nw6X0y3Ll36743nkin3s8HC5Hy+vvkvKigVHjfcPQ8Xq2mUjLgIADyCztuQ46hpOd4-o+J6rmwl6bturgwXOv5PqeKEXhuaoyDefhoQ+x7-i+9BvvshxfqE-RqrBJFrIAuDWAC0zuwHEcvaAD6dUCAC19gAHNWM6FwasuyABOdgANY4AJUPcR8gAkHYALz3CkSgSkhCUBdIABh1Up+vZQAAZhAwDxAAFrMewILE1iHOQ8SStKspNmmFjqveR5-rgsa0exX7cekUAADaoHEez+VAgA6K4AIGuALtDpKABarmzcYAHGuADmzgA6qwiUD1FygAf3YADItiVJMmADWdVwBUF1gheF0XJIAPz1QJsUCABHjGWACKjgAZ7VA8VQClUCAAG9gAhvYAI81QKJgA0M60gADkwiOlivphkmWZFlxBYUgWAIuk2XZyaOUGLn0e5AFAaB7CeV+c1GaZ5mWRYGaJvZBbNume1CQxnlUAZF2LddPRls6wBurwH0LVdy16D9ECOn9APvfNl1LVZq3rWK4OQ1YANAA)

## summary, FAQ

as const는 불변성을 암시한다.

- literal type 확장 불가.
- object literal은 readonly property. 즉 수정 불가.
- array literal은 readonly tuple

as const를 통해 객체를 정의한다면, narrow도 완벽하게 된다.

## 참조

https://basarat.gitbooks.io/typescript/docs/types/type-inference.htm
https://stackoverflow.com/questions/38687965/typescript-generics-argument-type-inference
