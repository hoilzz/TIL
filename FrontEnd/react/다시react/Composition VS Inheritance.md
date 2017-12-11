# Composition vs Inheritance

React는 강력한 composition model이다. 그리고 우리는 컴포넌트 간에 **코드를 재사용 하기 위해** `inheritance`대신에 `composition`을 이용하기를 추천한다.

React 뉴비 개발자들이 inheritance를 위해 도달하는 몇 가지 문제를 알고 있고, 그것을 Composition을 통해 해결하는 방법을 보여줄 거다.

## Containment

몇몇 컴포넌트는 자신의 children을 미리 알지 못한다. 이것은 일반적인 박스를 나타내는 `Sidebar` or `Dialog`와 같은 컴포넌트에 특히 일반적이다. 

```javascript
function FancyBorder(props) {
    return (
        <div className={'FancyBorder FancyBorder-' +
         props.color}>
            {props.children}
        </div>
    )
}
```

이렇게 하면 JSX를 중첩하여 다른 컴포넌트가 임시 children을 전달할 수 있다. 

```javascript
function WelcomeDialog() {
  return (
    <FancyBorder color="blue">
      <h1 className="Dialog-title">
        Welcome
      </h1>
      <p className="Dialog-message">
        Thank you for visiting our spacecraft!
      </p>
    </FancyBorder>
  );
}
```

`<FancyBorder>` 내 어떠한 것도 `chilren` prop을 통해 `FancyBorder`로 전달될 수 있다. 

이건 진짜 드문 경우지만, component에 여러개의 `holes`를 필요 할 수 있다. 그러한 경우 `children`을 이용하는 대신에 `너 자신의 컨벤션`을 사용해라.

```javascript
function SplitPane(props) {
  return (
    <div className="SplitPane">
      <div className="SplitPane-left">
        {props.left}
      </div>
      <div className="SplitPane-right">
        {props.right}
      </div>
    </div>
  );
}

function App() {
  return (
    <SplitPane
      left={
        <Contacts />
      }
      right={
        <Chat />
      } />
  );
}
```

> 출석체크 얼럿 작업시 버튼 1개, 2개짜리 UI가 있다. React를 사용했더라면 이와 같이 깔끔하게 작업할 수 있었을지도..


### 언제 쓰면 좋을까?

말 그대로 일반적인 박스를 나타내는 `Sidebar`, `Dialog`에 사용하면 좋을거 같다. 특히 이번 어드민 작업시 `Dialog` 가 다양한 종류가 있었다. `confirm`을 통해 ok,cancel 버튼이 있거나, 혹은 단순히 확인 버튼만 있는 경우가 있었다. 이러한 것을 props.children 혹은 custom 


## Specialization

