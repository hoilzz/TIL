# \*.d.ts

d.ts 파일은 JS로 작성된 API에 대한 타입 정보를 제공하는데 사용한다.

jQuery나 underscore와 같은 것을 TS로 재작성 하는 것 대신에, type annotation만 포함하고 있는 d.ts file을 작성할 수 있다.

pure JS 라이브러리 사용하는 동안, TS 코드에서 static type checking 이점을 얻을 수 있다.

---

[types을 위해 dts 파일 작성하기](https://devblogs.microsoft.com/typescript/writing-dts-files-for-types/)를 번역

선언 파일은 **기존 JS codebase의 모양을 TS로 설명한 단순한 파일** 이다. 선언 파일을 이용하여(`.d.ts`) 라이브러리를 잘못 사용하는 것을 피할 수 있고 에디터에서 자동완성 이점을 얻을 수 있다.

1. @types 패키지는 어디서 오는걸까?
2. d.ts file을 업데이트 하는 방법은?

## DefinitelyTyped

@types packages는 [DefinitelyType](https://github.com/DefinitelyTyped/DefinitelyTyped)에서 온다. TS 선언 파일을 호스팅하는 깃허브 저장소다.

## authoring new declarations

우리가 좋아하는 라이브러리에 대해 선언 파일을 만든다고 하자. 첫번째, DefinitelyTyped를 fork 해야한다.
