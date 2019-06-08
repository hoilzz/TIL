# Modules

TS의 모듈 개념에 대해 araboza

## Global Module

기본적으로 TS 파일에서 코드 작성하면 _global_ namespace으로 작성된다.

`foo.ts` 파일이 있다고 하자.

```ts
// foo.ts
var foo = 123;
```

동일프로젝트에 `bar.ts` 파일 생성하면, 타입 시스템이 `foo` 변수를 global하게 사용하도록 허용한다.

```ts
// bar.ts
var bar = foo; // allowed
```

네이밍 충돌 때문에 global namespace는 위험하다.
fil modules을 이용하기를 권장한다.

## file module

_external module_ 이라고 부른다

TS 파일 루트 레벨에서 `import`, `export`를 가지고 있다면, 해당 파일 내에서 _local_ scope가 생성된다.

(첨에 바닐라 스크립트와 .js 확장자로 작성된 파일을 ts 파일로 전부 변경했을 때 별개파일에 생성된 함수가 duplicate implementation 에러를 뱉었고, stackoverflow에서 export 문 쓰라고 해서 썼더니 에러가 사라졌다. 이 이유때문이었구나..)

`foo.ts`에 `export` 문 추가해보자.

```ts
// foo.ts
export var foo = 123;

// bar.ts
var bar = foo; // ERROR: 'cannot find name "foo"'
```

global namespace에서 `foo`가 사라졌다. `foo.ts`꺼 사용하려면 import 하자.

```ts
import { foo } from "./foo";
var bar = foo;
```

---

## globals.d.ts

_global vs file modules_, global namespace를 오염시키는 것이 아닌 file based module을 추천한다.

TS 초심자라면 TS 코드가 쉽게 타입을 갖도록 하기 위해 global namespace에 interface와 type이 작성된 `globals.d.ts` file을 생성하자.

> JS로 생성될 어떤 파일이든 file moudule을 적극 추천한다.

- `global.d.ts`는 `lib.d.ts`를 확장하는데 좋다.
- `declare module "some-library-you-dont-care-to-get-defs"`는 좋다.
