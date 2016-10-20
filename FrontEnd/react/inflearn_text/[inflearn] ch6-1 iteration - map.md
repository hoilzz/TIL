# Ch 6-1 컴포넌트 iteration - map

## Javascript - Array.prototype.map
`map()` 메서드는 파라미터로 전달된 함수를 통해 배열 내의 각 요소를 프로세싱하여 그 결과로 새로운 배열을 생성

### Syntax
> arr.map(callback, [thisArg])

### parameter
callback 새로운 배열의 요소를 생성하는 함수로써, 다음 3가지 인수를 가진다.
: currentValue 현재 처리되는 요소
: index 현재 처리되고 있는 요소의 index 값
: array 메소드가 불려진 배열
thisArg callback 함수 내부에서 사용할 this 값을 설정

### 예제
```javascript
var numbers = [1,2,3,4,5];
numbers.map((num)=>{
  return num*num;
})
```


## 2 컴포넌트 mapping
데이터 배열을 mapping 하여 컴포넌트 배열로 변환하는 과정을 보자

```javascript
<ul>
    <li>Abet 010-0000-0001</li>
    <li>Betty 010-0000-0002</li>
    <li>Chalie 010-0000-0003</li>
    <li>David 010-0000-0003</li>
</ul>
```



비슷한 코드가 반복되는데.. 저기 나올 데이터가 유동적이라면..? 그때 그때 하드코딩하기는 곤란-

### 2.2 ContactInfo 컴포넌트 만들기
1. ContactInfo 클래스 생성
```javascript
class ContactInfo
<li> {this.props.name} {this.props.phone} </li>
```

> 이름과 전화번호 담길 부분에 props 사용

2. Contacts 컴포넌트 렌더링 부분 수정
```javascript
<ContactInfo name = "Abet" phone = "010-0303-3939">
```

> html 코드를 컴포넌트 형태로 변환. 여전히 같은 코드 반복해서 사용

### 2.3 mapping
: 데이터 매핑해보자

#### 기본 state 추가 (in Contact)
```javascript
constructor(props){
  super(props);
  this.state = {
    contactData: [
      {name: "Abet", phone: "030-0409-3933"},
      {name...}
    ]
  }
}
```

#### 렌더링 부분 배열 mapping으로 교체
```javascript
<ul>
  {this.state.contactData.map((contact, i) => {
    return (<ContactInfo name={contact.name}
                         phone={contact.phone}
                          key={i}
                        />);
  })}
</ul>
```

## 틀린 것들
### 1 JSX의 값은 expression or quoted JSX text여야 한다.
#### Attribute Expression
JS expression을 attribute value로써 사용하기 위해, quotes(`""`) 대신에 **curly braces(`{}`)으로 wrapping 하여 사용해라**

```javascript
// Input (JSX)
var person = <Person name={window.isLoggedIn ? window.name : ''} />;
// Output (JS)
var person = React.createElement(
  Person,
  {name: window.isLoogedIn ? window.name : ''}
)
```

#### Boolean Attributes
attribute 값을 생략하는 것은 JSX가 `true`로 다뤄진다. `false`를 보내기위해 attribute expression은 사용되어야 한다. HTML form element를 사용할 때 이것은 종종 따라온다. (with attributes like `disabled`, `required`, `checked` and `readonly`)
```javascript
<input type = "button" disable />
<input type = "button" disable={true} /> // 둘 다 똑같다.
```

### 2 배열 혹은 iterator에서 각 (child) component는 unique key 가져야한다

### 3 컴포넌트 쪼개기
반복해서 만들어야할 `<li>...</li>`가 있는 상황이 있다. 이 때 저 엘리먼트들은 한가지 컴포넌트 frame으로 생성하여 `<li>`를 담는 컴포넌트에서 반복 생성해야한다.
