# Components and Props

컴포넌트는 UI를 독립적이고 재사용가능한 조각으로 쪼개도록 도와주고 독립적으로 각 조각에 대해 생각할 수 있도록 도와준다. 

## Funtional and Class Components

컴포넌트를 정의하는 가장 간단한 방법은 JS `function`으로 작성하는 것이다.

```javascript
function Welcome(props) {
    return <h1>Hello, {props.name}</h1>
}
```

이 함수는 유효한 React component다. 왜냐하면 single props 객체를 받고 React Element를 리턴하기 때문이다. 이것을 함수형 component라고 부른다. 

`ES6 클래스`를 사용하여 컴포넌트를 정의해보자.

클래스는 추가 피처를 가진다.(다음 장에서 알아보자.)

```javascript
const element = <Welcome name="Sara" />
```

**React가 user-defined component를 볼 때, 이 컴포넌트에 single object로써 JSX attribute를 전달한다. 우리는 이것을 `props`라고 부른다.**

예를 들어, 이 코드는 "hello, sara"를 페이지에 렌더링한다.

```javascript
function Welcome(props) {
    return <h1>Hello, {props.name}</h1>;
}

const element = <Welcome name="Sara" />;
ReactDOM.render(
    element,
    document.getElementById('root');
)
```

위 과정을 재생 시켜보자.

1. `ReactDOM.render()`를 `<Welcome name="Sara" /> `와 함꼐 호출했다.
2. React는 `Welcome` 컴포넌트를 `{name: 'Sara'}`를 props로써 함께 호출한다.
3. `Welcome` 컴포넌트는 `<h1>Hello, Sara</h1>`를 엘리먼트를 리턴한다.
4. React DOM은 `<h1>Hello, Sara</h1>`와 일치시키기 위해 효율적으로 DOM을 업데이트 한다.

## Composing Components

컴포넌트는 그들의 아웃풋에서 다른 컴포넌트를 참조할 수 있다. 이것은 우리가 동일 컴포넌트 추상화를 이용하도록 한다. 

## Extracting Components

컴포넌트를 더 작은 컴포넌트로 쪼개는 것을 두려워하지 마라. 예를 들어 `Commnet` Component를 고려해보자.

## Props are Read-Only

**function or class로 뭐든 컴포넌트를 선언하면, 자신의 props를 절대 수정할 수 없다.**

```javascript
function sum(a, b){
  return a + b;
}
```

`pure` function이라 부른다. 대조적으로, 이 펑션은 퓨어하지 않다.

```javascript
functino withdraw(account, amount){

}
```

## Summary

컴포넌트를 정의하는 방법 2가지
1. function
2. class