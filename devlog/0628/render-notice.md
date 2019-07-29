# Composition on PureComponent

render 함수 내부에서 어떤 Template 컴포넌트에 props로 ReactNode를 인라인으로 넘겨줄 때, 불필요한 리렌더가 발생한다. 이를 막기 위해 React.memo를 했지만 리렌더가 계속 발생한다. 

https://codesandbox.io/s/gifted-hofstadter-hweu8?fontsize=14

그 이유는  