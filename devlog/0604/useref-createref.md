#

## useRef

useRef는 `initialValue` 인자에 전달된 걸로 이니셜라이징 된 `.current` 프로퍼티를 가진 mutable한 ref object를 반환한다. 리턴된 오브젝트는 component의 full lifetime동안 유지된다.

common use case는 child에 접근하는거다

```js
```

useRef는 .current property 내부에 mutable value를 가진 box와 같다.

DOM에 접근하기 위한 방법으로 ref를 주로 사용할거다. 만약 ref object를 react에 전달한다면, react는 node가 바뀔때마다 일치하는 DOM에 .current 프로퍼티를 세팅한다.

`useRef`는 `ref` attribute보다 유용하다. 클래스에서 인스턴스 필드를 사용하는 방법과 비슷하게 mutable한 값을 유지하는 것이 편리하다. 이게 되는 이유는 useRef는 plain JS object를 생성하기 때문이다. `useRef()`와 `{current...}`를 생성하는 것의 차이는 `useRef`는 모든 render마다 동일한 ref object를 제공한다.

useRef는 content가 변경 될 때 너에게 알려주지 않는다. .current property가 변경되는 것은 re-render를 일으키지 않는다. 만약 리액트가 DOM node에서 ref를 attach or detach할 때 코드가 실행된다면, callback ref를 대신 사용하는 것
