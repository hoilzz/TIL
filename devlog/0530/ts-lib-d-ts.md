# lib.d.ts

TS 설치할 때 마다 `lib.d.ts` 선언 파일이 딸려온다. 이 파일은 JS 런타임 및 DOM에 있는 다양한 common JS 구문에 대한 ambient declarations이 포함되어 있다.

- 이 파일은 TS 프로젝트의 컴파일 context에 자동으로 포함된다.
- 이 파일의 목적은 _type checked JS code_ 를 작성하기 쉽도록 해준다.

--noLib 옵션으로 이 파일을 컴파일 단계에서 제거할 수 있다.

## Example Usage

noLib 옵션으로 컴파일시 타입 체크 에러 발생한다.
noLib 옵션이 없다면 `toString` 함수는 `lib.d.ts`에 정의되어있기 때문에 타입체킹 가능하다.

```ts
var foo = 123;
var bar = foo.toString(); // ERROR: Property 'toString' does not exist on type 'number'.
```

## `lib.d.ts` 내부를 보자.

```ts
declare var window: Window;
```

단순 변수 선언이다.

`declare var` 뒤에 변수이름이 있고 type annotation(`Window`)을 위해 인터페이스도 작성되어있다.

이 변수는 일반적으로 global interface를 가리킨다.

_interface_ 를 global로 이용하는 좋은 이유가 있다. `lib.d.ts` 바꿀 필요 없이 전역에 추가 속성을 작성할 수 있다.

## Native Type 수정하기

TS의 인터페이스가 열린 상태이기 때문에, `lib.d.ts`에 선언된 인터페이스에 멤버를 추가할 수 있다.

`lib.d.ts`와 연관된 인터페이스를 [global modules](https://basarat.gitbooks.io/typescript/docs/project/modules.html)에서 이 변경건을 작업해야한다. 해당 작업을 위해 [`global.d.ts`](https://basarat.gitbooks.io/typescript/docs/project/globals.html)라는 file 만드는 것을 권장한다.

`window` 예제
