

# props and state

## props

컴포넌트에서 사용할 데이터 중 변동되지 않는 데이터를 다룰 때 사용된다. parent 컴포넌트에서 child 컴포넌트로 데이터 전달시 `props`가 사용된다.

## state

컴포넌트에서 유동적인 데이터를 다룰 때, state를 사용한다. React 어플리케이션을 만들 때, **state를 사용하는 컴포넌트의 갯수를 최소화 하는 것을 노력해야 한다.** 예를 들어 10개의 컴포넌트에서 유동적인 데이터 사용시, 각 데이터에 state를 사용할 게 아니라, props를 사용하고 10개의 컴포넌트를 포함시키는 container컴포넌트를 사용하는 것이 효율적이다.

|특성|props|state|
|:--|:--|:--|
|parent 컴포넌트에 의해 값이 변경 가능?| Y | N|
|컴포넌트 내부에서 변경 가능?|N|Y|

## A Simple Component

## A Stateful Component

`this.props`로 접근되는 input data를 가져오는 것 이외에, 컴포넌트는 내부 state data(`this.state`를 통해 접근되는)를 유지할 수 있다. **component의 state data가 변경될 때, `render()`를 다시 호출하여 렌더링된 마크업은 업데이트 될 것이다.**

## Summary

props는 parent에서 child로 데이터 전달시 사용한다.

state는 
- 유동적인 데이터 다룰 때 사용한다. 
- state를 사용하는 컴포넌트의 갯수를 최소화 하도록 노력해야 한다.
- 10개의 컴포넌트에서 유동적인 데이터 사용시, 각 데이터에 state를 사용할 게 아니다. props를 사용하는 10개의 컴포넌트를 포함하는 container 컴포넌트를 사용하는 것이 효율적이다.

`stateful Component`
컴포넌트는 state data가 변경될 때, render()를 다시 호출하여 렌더링된 마크업은 업데이트 될 것이다.

**이 때, render 내부에 선언되지 않은 state가 변경되도 리렌더링 될까?**



