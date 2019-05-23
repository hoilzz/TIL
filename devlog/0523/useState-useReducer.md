# useState vs useReducer

useState에 primitive 값만 관리했다.

그러다가 여러개의 아코디언의 열고닫힘 상태를 관리해야했다. 그래서 부모 컴포넌트에서 다음과 같이 상태 관리하려했다.

```js
const defaultOpenState = {
  acco1: true,
  acco2: true,
  acco3: true,
  acco4: true
}; // 처음엔 다 열려 있는 상태.

function Component() {
  const [openState, setOpenState] = useState(defaultOpenState);

  const handleClickAcco = useCallback(
    name => {
      setOpenState({
        ...openState,
        [name]: !openState[name]
      });
    },
    [openState]
  ); // 나는 1개의 아코디언 상태만 바꿨는데.. 4개의 아코디언의 함수가 다시 실행되는 상황..
  // 왜냐면 openState는 새로운 상태 객체를 갖기 떄문에.. useCallback deps가 콜백함수 다시 만듬

  return (
    <>
      <Acco1 onClick={handleClickAcco} />
      <Acco2 onClick={handleClickAcco} />
      <Acco3 onClick={handleClickAcco} />
      <Acco4 onClick={handleClickAcco} />
    </>
  );
}
```
