# Declaration file

`declare` 키워드를 이용하여 어딘가에 존재하는 코드를 TS에게 말해줄 수 있다.

```ts
foo = 123;
```

```ts
declare var foo: any;

foo = 123; // allowed
```

`.ts` 나 `d.ts` 파일에서 declare를 선언할 수 있다. `.d.ts`에 사용을 권장한다. (`global.d.ts` or `vendor.d.ts`)

만약 file이 `.d.ts`확장자라면, 각 루트 레벨 정의는 `declare` 키워드를 prefix로 가져야한다.

**이것은 작성자가 TS로 코드를 emit할 필요가 없다는 것을 명확하게 만들어준다.**

작성자는 런타임에서 item이 존재하는지 확인해야 한다.

> - Ambient 선언은 너가 컴파일러에게 한 약속이다. 만약 런타임에 존재하지 않고 그것들을 사용하려 한다면, 경고 없이 코드는 고장날거다.
> - Ambient 선언은 문서와 같다. 만약 source가 변경된다면, docs도 업데이트 되어야 한다. 런타임에서 동작하는 새로운 것이 있다면, ambient declaration은 아무도 업데이트 하지 않고 컴파일러는 에러를 발생시킨다.

## Summary

declare 키워드로 어딘가에 존재하는 코드를 TS에게 말해줄 수 있다.

declare는 d.ts에서 작성하여 문서처럼 사용하자.
