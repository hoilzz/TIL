# Hook 규칙

hook의 규칙을 지키기 위해 걍 [linter plugin](https://www.npmjs.com/package/eslint-plugin-react-hooks)을 사용하면 룰을 강제로 지키게 된다.

## Top Level에서만 Hooks을 호출하자.

Hook을 다음 내부에서 호출하지 말자.

- loop
- condition
- nested function

대신에, 리액트 함수의 top level에서만 hook을 사용하자.
이 규칙을 지키면, hook은 각 컴포넌트 렌더에서 **동일한 위치에서** 호출된다.
이거슨 여러개의 `useState`와 `useEffect` 호출 사이에서 리액트가 올바르게 hook의 상태를 보존하게 한다.

## 리액트 함수에서만 hook을 호출하ㅏㅈ.

일반 JS 함수에서 hook을 호출하지 마랒. 대신,

- 리액트 함수형 컴포넌트에서
- 커스텀 훅에서

만 호출하자.

## Explanation

여러개의 상태와 effect hook을 단일 컴포넌트에서 사용할 수 있다.

```js
function Form() {
  // 1. Use the name state variable
  const [name, setName] = useState('Mary');

  // 2. Use an effect for persisting the form
  useEffect(function persistForm() {
    localStorage.setItem('formData', name);
  });

  // 3. Use the surname state variable
  const [surname, setSurname] = useState('Poppins');

  // 4. Use an effect for updating the title
  useEffect(function updateTitle() {
    document.title = name + ' ' + surname;
  });
  // ...
}
```

리액트는 useState call이 어떤 state와 일치하는지 어떻게 알까?

정답은 **리액트는 hook의 호출 순서에 의존한다는 점** 이다.

hook의 호출 순서가 모든 렌더에서 동일하기 때문에 위 코드는 동작한다.

```js
// ------------
// First render
// ------------
useState('Mary'); // 1. Initialize the name state variable with 'Mary'
useEffect(persistForm); // 2. Add an effect for persisting the form
useState('Poppins'); // 3. Initialize the surname state variable with 'Poppins'
useEffect(updateTitle); // 4. Add an effect for updating the title

// -------------
// Second render
// -------------
useState('Mary'); // 1. Read the name state variable (argument is ignored)
useEffect(persistForm); // 2. Replace the effect for persisting the form
useState('Poppins'); // 3. Read the surname state variable (argument is ignored)
useEffect(updateTitle); // 4. Replace the effect for updating the title

// ...
```

hook의 호출 순서가 렌더간에 동일하다면, 리액트는 local state를 긱 hook들과 연관지을 수 있다. 하지만 만약 조건문 내부에 hook 호출을 넣는다면?

```js
// 🔴 We're breaking the first rule by using a Hook in a condition
if (name !== '') {
  useEffect(function persistForm() {
    localStorage.setItem('formData', name);
  });
}
```

name이 ''만 아니면 hook이 동작한다. 그러나, 다음 렌더 때 name이 빈 문자열이면, hook 순서가 달라진다.

```js
useState('Mary'); // 1. Read the name state variable (argument is ignored)
// useEffect(persistForm)  // 🔴 This Hook was skipped!
useState('Poppins'); // 🔴 2 (but was 3). Fail to read the surname state variable
useEffect(updateTitle); // 🔴 3 (but was 4). Fail to replace the effect
```

리액트는 2번째 useState call에서 뭘 리턴해야할지 모른다.
리액트는 두번째 hook이 persisteForm effect와 일치한다고 생각한다. 하지만 아니다.
이 시점부터, 모든 다음 hook 호출은 1개씩 변경되어 버그가 발생한다.

이래서 hook은 컴포넌트의 top level에서 호출되어야 한다.
만약 조건부로 effect를 호출한다면 **hook 내부에** 조건문을 넣자.

여튼 이런 문제는 lint rule 쓰면 걱정할 필요가 없다. 걍 hook이 왜 이런방식으로 동작해야 하는지 알아만 두자.

## Summary

hook도 react의 재조정 작업과 비슷하지만 비슷하지 않게 동작한다.

재조정 작업은 이전 호스트 트리와 새로운 엘리먼트 트리를 일치시킨다. 그래서 이전 호스트 트리를 고치는 작업을 하는데,
이 때 특정 위치에 이전 트리가 동일한 엘리먼트 타입을 가지고 있는지 비교한다. 그래서 새로운 호스트 객체를 만들지, 걍 기존 객체 활용할지 판단한다.

재조정 작업은 정말 단순하게 이 위치에 동일한 엘리먼트 타입을 가지고 있니?를 비교하는데,

hook 또한 해당 위치에서 뭔가를 비교한다.

그 이후에 비교를 하지 않고 hook은 해당 위치에 처음에 호출한 hook이 있을 것을 기대한다.
그래서 hook의 위치는 항상 top-level에서 유지되어야한다.
