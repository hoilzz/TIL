# index를 통해 관리하고 있다. 그래서 조건문이나 loop문 등에 포함되면 순서가 보장되지 않기 떄문에이 작동하는 방식 hook 관련 린트에러가 발생한다.

[getting closure on react hooks](https://rinae.dev/posts/getting-closure-on-react-hooks-summary#%ed%81%b4%eb%a1%9c%ec%a0%80-%ed%99%9c%ec%9a%a9)
[deep dive: how do react hook really work](https://www.netlify.com/blog/2019/03/11/deep-dive-how-do-react-hooks-really-work/)

두번째 글을 번역한 게 첫번째 글

## Hook 바닥부터 순차적 작성해보기

클로저를 활용한 add 함수부터 만들어보자.

```js
function getAdd() {
  let _count = 0;
  return function() {
    const addCount = () => (_count += 1);
    // const state = _count;
    const getCount = () => _count;
    const printCount = () => console.log(_count);
    return {
      // count,
      getCount,
      addCount,
      printCount,
    };
  };
}

const addEnv1 = getAdd();

const add1 = addEnv1();

add1.printCount();
add1.addCount();
add1.addCount();
add1.printCount();
console.log(add1.getCount());
```

주석처리된 `const state = _count`는 state를 직접 접근하여 변경하지 못하도록 하기 위해 선언했지만, 변경된 값에 접근을 하지 못하는 문제 발생한다. 참조 값이 아니라서 한번 할당하고 끝나기 때문이다.
함수를 통해 \_count에 접근하는 것으로 변경하여 문제 해결하였다.

## useState 만들기

```js
// 대충 요렇게 사용된다.
const [count, setCount] = useState(1);
console.log(count); // 1
setCount(2);
console.log(count); // 2
```

```js
function useState(initVal) {
  let _val = initVal;
  const setState = newVal => (_val = newVal);
  // const state = _val // 할당되고 끝나기 때문에 아래와 같이 함수 호출해야한다.
  const state = () => _val;
  return {
    state,
    setState,
  };
}
const [count, setCount] = useState(1);
console.log(count()); // 1
setCount(2);
console.log(count()); // 2
```

## 컴포넌트에 붙여보기

useState를 사용하여 미니 리액트 만들자. 사용방법은 다음과 같다.

리액트의 특징인 제어의 역전처럼 우리는 컴포넌트만 만들어주고 렌더링은 리액트가 하게 한다.

```js
function Component() {
  const [count, setCount] = React.useState(1);
  return {
    render: () => console.log(count),
    click: () => setCount(count + 1),
  };
}
var App = React.render(Component);
App.click();
var App = React.render(Component);
```

일단, React라는 네임스페이스에 useState와 render 함수를 작성하자.

```js
const React = (function() {
  function useState(initVal) {
    let _val = initVal;
    const setState = newVal => (_val = newVal);
    // const state = _val // 할당되고 끝나기 때문에 아래와 같이 함수 호출해야한다.
    const state = () => _val;
    return {
      state,
      setState,
    };
  }
  function render(component) {
    //
    const C = Component();
    C.render();
    return C;
  }
})();

function Component() {
  const [count, setCount] = React.useState(1);
  return {
    render: () => console.log(count),
    click: () => setCount(count + 1),
  };
}

var App = React.render(Component); // 1
App.click(); // 2
var App = React.render(Component); // 1
```

증가하지 않는 이유는 함수가 실행되고 종료될 떄마다 useState의 EC가 새로 생성되면서 \_val가 initVal로 초기화된다.
그래서 \_val를 클로저 환경에 둬서 상태를 유지하자.

```js
const React = function() {
  let _val;
  function useState(initVal) {
    // let _val = initVal;
    _val = _val || initVal;
  }
};
```

## 훅 여러개 사용해보기

```js
function Component() {
  const [count, setCount] = React.useState(1);
  const [text, setText] = React.useState('apple');
  return {
    render: () => console.log({ count, text }),
    click: () => setCount(count + 1),
    type: word => setText(word),
  };
}

var App = React.render(Component); // {count: 1, text: 'apple'} // 사실 React 함수 클로저 환경에서 _val는 'apple'로 덮여쓰여짐.
App.click(); // 이 때 2로 덮여 쓰여짐
var App = React.render(Component); // {count: 2, text: 2}
App.type('banana'); // banana로 덮여쓰여짐.
var App = React.render(Component); // {count: 'banana', text: 'banana'}
```

**이 문제를 해결하기 위해 각 값별로 배열에 담아서 관리한다.**
즉, 훅을 담아 둔 배열과 현재 어떤 훅이 어떤 인덱스를 바라보는지 관리가 필요하다.

```js
const React = (function() {
  let hooks = [];
  let index = 0;

  function useState(initVal) {
    const state = hooks[idx] || initVal;
    const _index = index; // 이 훅이 사용해야 하는 인덱스를 가둬둔다.
    const setState = newVal => {
      hooks[_index] = newVal;
    };
    index++; // 다음 훅은 다른 인덱스를 사용하도록 한다.
    return [state, setState];
  }

  function render(Component) {
    idx = 0; // 랜더링 시 훅의 인덱스를 초기화한다.
    const C = Component();
    C.render();
    return C;
  }

  return { useState, render };
})();
```

위와 같이 각 useState의 index를 내부 함수에서 사용하여 클로저 환경에서 저장하여 상태 관리할 수 있다.
그리고, 렌더링마다 index를 초기화하여 N개의 HOOK을 0~N까지 순서대로 호출하여 상태를 보장한다.

그래서 React hook의 규칙이 왜 있는지 알 수 있다.

> hook rule
>
> - top level 에서만 hook 호출하기
> - 이 규칙에 따라 렌더링 될 떄마다 **항상 동일한 순서로** hook이 호출되는 것을 보장한다.
>   - 조건부로 훅을 호출, 루프안에서 훅이 호출된다면 순서 보장 어려움 -> 상태 유지 관리 보장 어려움
> - useState와 useEffect가 여러번 호출되도 hook상태를 올바르게 유지할 수 있다.

## useEffect 구현하기

```js
function Component() {
  const [count, setCount] = React.useState(1);
  const [text, setText] = React.useState('apple');

  // 랜더링 시 최초에 한 번만 실행된다.
  // 배열 안에 관찰하고자 하는 상태를 전달하면 그 상태에 반응하여 콜백이 실행된다.
  React.useEffect(() => {
    console.log('side effect');
  }, []);
  // ...
}
```

useEffect의 특징은 두 번쨰 인자인 dependency array의 값중 하나라도 값이 변했다면 콜백을 실행한다.

```js

const useEffect(cb, deps) {
  // let isFirstCall = true;
  // hooks[index] = deps;
  // if(isFirstCall) {
  //   cb();
  //   return;
  // }

  // const isDifferent = deps.some((dep, i) => Object.is(
  //   dep, hooks[index][i]
  // ));

  // if(isDifferent) {
  //   cb();
  // }

  let oldDeps = hooks[index];
  let hasChanged = true;

  if(oldDeps) {
    hasChanged = oldDeps.some((dep, i) => !Object.is(oldDep, deps[i]))
  }

  if(hasChanged) {
    cb();
  }

  hooks[idex] = deps;

  index += 1;

}
```

## Summary

hook의 상태관리는 클로저로 되고 있다.

순서를 보장해야하는 hook의 규칙에 대해 이해할 수 있다.
클로저 내부의 상태를 index를 통해 관리하고 있다. 그래서 조건문이나 loop문 등에 포함되면 순서가 보장되지 않기 떄문에 hook 관련 린트에러가 발생한다.
