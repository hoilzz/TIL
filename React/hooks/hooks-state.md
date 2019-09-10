# hooks state

```js
import React, { useState } from 'react';

function Example() {
  // 새로운 state 변수를 선언하고, count라 부르겠습니다.
  const [count, setCount] = useState(0);

  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>Click me</button>
    </div>
  );
}
```

## useState vs setState

useState는 여러개의 state 변수를 사용할 수 있다.
또한, 개별 갱신이 가능하다.

this.setState와 달리 state를 갱신하는 것은 merge가 아닌 replace다.

## FAQ

Q. 이름은 왜 createState가 아닌 useState일까?
A. 컴포넌트가 렌더링할 때 딱 한 번 생성되기 때문에, 또한 use로 시작하는 이유는 [hook의 규칙](https://ko.reactjs.org/docs/hooks-rules.html)

Q. 1개 이상의 state변수를 사용해야 할까?
A. class에서 state 업데이트 방식에 익숙하다면, `useState()`를 딱 한 번 호출 하려고 할 것이다. 그리고 단일 객체로 모든 상태를 넣을 것이다. 자 이제 마우스 움직일 때마다 left, top을 업데이트 하는 예시를 보자.

```js
function Box() {
  const [state, setState] = useState({
    left: 0,
    top: 0,
    width: 100,
    height: 100
  });
  useEffect(() => {
    function handleWindowMouseMove(e) {
      // Spreading "...state" ensures we don't "lose" width and height
      setState(state => ({ ...state, left: e.pageX, top: e.pageY }));
    }
    // Note: this implementation is a bit simplified
    window.addEventListener('mousemove', handleWindowMouseMove);
    return () => window.removeEventListener('mousemove', handleWindowMouseMove);
  }, []);
}
```

**useState의 상태 업데이트 함수는 merge가 아닌 replace이기 때문에 이전 상태와 같이 리턴해줘야한다.**
이렇게 해도 되지만..

**어떤 값이 함께 변경되려는 경향이 있는지 파악하여, 여러 개의 상태 변수로 분리하는 것을 권장한다.**

이렇게 하면 좋은 점은 custom hook으로 분리하기 좋다.

```js
function Box() {
  const position = useWindowPosition();
  const [size, setSize] = useState({ width: 100, height: 100 });
  // ...
}

function useWindowPosition() {
  const [position, setPosition] = useState({ left: 0, top: 0 });
  useEffect(() => {
    // ...
  }, []);
  return position;
}
```

독립적인 상태 변수로 상태를 그룹지었는데, 이것의 로직이 복잡해진다면 useReducer를 사용해라.
