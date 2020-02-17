# 리렌더링 퍼포먼스 이슈

회사 작업 중에 리렌더링 퍼포먼스 이슈 때문에 A방안을 사용하여 퍼포먼스 최적화를 하자는 식의 얘기가 나왔다.

상황은 아래와 같다.

저 버튼들 중 삭제 버튼을 보자.

이 버튼은 아래 리스트에서 선택된 아이템을 제거한다. 

```tsx

function ToolBar({
  children
}) {
  return (
    <div>
      <Breadcrumbs />
      {children}
    </div>
  )
}

function App() {
  const [selected, setSelected] = useState<number[]>([]);
  return (
    <>
      <ToolBar>
        <button onClick={() => removeItemApi(ids)}>삭제</button>
      </ToolBar>
      <Table>
        {
          item.map( (item) => <Checkbox onClick={() => setSelected(item.id)}/>)
        }
      </Table>
    </>
  )
}
```

위 컴포넌트 구조에서 체크할 때마다 selected 상태는 업데이트된다.
상태가 업데이트 됐으므로, App은 리렌더된다. 
이 때, ToolBar 컴포넌트가 불필요하게 리렌더된다.




