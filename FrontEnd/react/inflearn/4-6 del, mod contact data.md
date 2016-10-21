# Contact 데이터 삭제/수정 기능 구현

## 삭제

src/ContactDetails.js
```javascript
<button onClick={this.pros.onRemove}>Remove</button>

ContactCreate.defaultProps = {
  onCreate: () => {console.error("onCreate not defined");}
}
```
src/Contact.js
```javascript
handleRemove() {
  // 선택되지 않았을 때도 삭제되는 경우를 대비해 예외처리
  if(this.state.selectedKey < 0) {
    return;
  }
  //파라미터는 필요없고 selectedKey를 삭제할 때 사용할거다.
  this.setState({
    contactData: update(this.state.contactData,
      { $splice: [[this.state.selectedKey, 1]]}
    ),
    // 무효화 한다는 의미로 -1 로 설정
    selectedKey: -1
  });
}

<ContactDetails
      isSelected={this.state.selectedKey != -1}
      contact={this.state.contactData[this.state.selectedKey]}
      onRemove={this.handleRemove}
      onEdit={this.handleEdit}
      />
```

## edit
- edit 버튼 만들기
- edit을 toggle할 수 있는 기능 만들기
    - 먼저 state 만들자

```javascript
constructor(props){
  super(props);
  this.state = {
    isEdit:false,
    name: '',
    phone:''
  };
}
```
   - handle toggle이라는 메서드 만들자 (클릭 됐을 때 실행)
```javascript
handletoggle()
{
  this.setState({
    isEdit: !this.state.isEdit
  });
  console.log(this.state.isEdit);
}
```
- console.log가 반대로찍히는걸로 보인다.
    - setState가 비동기로 동작하기 때문이다.

### input 값에 기존 값 넣어주기
```javascript
handleToggle() {

  if(!this.state.isEdit) {
    this.setState({
      // 어떻게 가능한걸까>? contact접근..
      // import와 export 관계는 부모자식 관계인가
      name: this.props.contact.name,
      phone: this.props.contact.phone
    });
  }

  this.setState({
    isEdit: !this.sate.isEdit
  });
  console.log(this.state.isEdit);
}
```
