# \*.d.ts

d.ts 파일은 JS로 작성된 API에 대한 타입 정보를 제공하는데 사용한다.

jQuery나 underscore와 같은 것을 TS로 재작성 하는 것 대신에, type annotation만 포함하고 있는 d.ts file을 작성할 수 있다.

pure JS 라이브러리 사용하는 동안, TS 코드에서 static type checking 이점을 얻을 수 있다.

---

[types을 위해 dts 파일 작성하기](https://devblogs.microsoft.com/typescript/writing-dts-files-for-types/)를 번역

선언 파일은 **기존 JS codebase의 모양을 TS로 설명한 단순한 파일** 이다. 선언 파일을 이용하여(`.d.ts`) 라이브러리를 잘못 사용하는 것을 피할 수 있고 에디터에서 자동완성 이점을 얻을 수 있다.

## FAQ

1. d.ts란?
2. declare 키워드란?

[do we need to use "declare" for type aliased in d.ts files?](https://github.com/Microsoft/TypeScript/issues/1940)

d.ts file 선언에서 all top level non-interface element(module, class, var)의 경우 `declare`는 필수다.

하지만 type aliase에도 이게 필요할까?

`tests.d.ts` file은 에러 발생시킨다.

```ts
interface ITest {
  foo: string;
  bar: string;
}

type IMyAlias = ITest;
```

3. d.ts 에서 declare를 하지 않는다면?
