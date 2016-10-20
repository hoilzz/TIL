# 선택 기능

## 임의의 메서드 만들기
항상 바인딩 해줘야함
```this.handleClick  = this.handleClick.bind(this);```

## 이벤트
이벤트는 컴포넌트에 적용 안된다. native DOM(div, h1, input, button 등)에만 적용된다.
```javascript
return (<ContactInfo
            contact={contact}
            key={i}
            // 왜 때문 arrow function을 써야하는가
            onClick={()=>this.handleClick(i)}/>);
});
```
- onclick이 props로 전달됨
- 그래서 컴포넌트 클래스 가서 onClick 이벤트 설정해주면 됨.
```javascript
<div onClick={this.props.onClick}>{this.props.contact.name}</div>
```
- onClick을 props로 받았으니까

## 선택 되었을 때와 선택되지 않았을 때 구분 (via mouse)




## Summary
- Component에 이벤트 적용 안됨.
  - 객체를 arrow func를 통해 익명함수로 전달해야한다
  + nativeDOM에는 이벤트 적용 된다.
