# typescript debugging 익숙해지기

```ts
React.forwardRef((props, ref) => <p ref={ref} id="sentinel" />);
```

ref property에 에러..

```
'Ref<{}>' 형식은 'string | ((instance: HTMLParagraphElement | null) => void) | RefObject<HTMLParagraphElement> | null | undefined' 형식에 할당할 수 없습니다.
  'RefObject<{}>' 형식은 'string | ((instance: HTMLParagraphElement | null) => void) | RefObject<HTMLParagraphElement> | null | undefined' 형식에 할당할 수 없습니다.
    'RefObject<{}>' 형식은 'RefObject<HTMLParagraphElement>' 형식에 할당할 수 없습니다.
      Type '{}' is missing the following properties from type 'HTMLParagraphElement': align, addEventListener, removeEventListener, accessKey, and 238 more
```

TS가 추론한 ref 파라미터는 다음과 같다.

```ts
(parameter) ref: React.Ref<{}>
```

ref 인자에 타입 정의를 해주지 않아서 forwardRef 함수에서 위와 같이 추론했다.

```ts
function forwardRef<T, P = {}>(
  Component: RefForwardingComponent<T, P>
): ForwardRefExoticComponent<PropsWithoutRef<P> & RefAttributes<T>>;
```
