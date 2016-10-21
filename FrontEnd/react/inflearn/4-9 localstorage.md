# localStorage
: html5의 로컬 스토리지
- 브라우저에 저장.
- 쿠키와 비슷. 쿠키는 도메인당 4KB가 최대 용량
- 2.5MB ~ 5MB까지 저장할 수 있다.

## syntax
localStorage.*
- *에 아무거나 들어가도됨
```javascript
localStorage.state = object
localStroage.state // "[object, object]"
localStroage.state = JSON.stringify(object);
localStorage.state // "{"text":"codelabe"}"
JSON.parse(localStorage.state)l // Object {text:"codelab"}
```
- string 값만 저장. 즉 객체 저장 불가능
  - 그래서 JSON.stringify 사용해야함

## 저장해보자
`componentWillMount` DOM 생성전에 실행됨
- contactData 값이 localStorage 안에 존재한다면 setState를 통하여 저장된 값을 불러오자

```javascript
componentWillMount() {
  const contactData = localStorage.contactData;

  if (contactData) {
    this.setState({
      // string 형태를 객체형으로 바꿔 업데이트
      contactData: JSON.parse(contactData)
    })
  }
}
```

## 업데이트될 때마다 실행
`componentDidUpdate(prevProps, prevState)`
- contact 데이터가 이전 값과 지금 값이 다르면 지금 값을 저장하자.
```javascript
componentDidUpdate(prevProps, prevState){
  if(JSON.stringify(prevState.contactData) != JSON.stringify(this.state.ContactData)) {
    localStorage.contactData = JSON.strinify(this.state.contactData);
  }
}
```

## localStorage 초기화
`localStorage.clear();`

## ref
[LocalStorage](http://www.w3schools.com/html/html5_webstorage.asp)
