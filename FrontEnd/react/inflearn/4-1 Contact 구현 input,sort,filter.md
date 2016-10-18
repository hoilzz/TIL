#  Contact 구현 | input, sort, filter

## 검색기능
```javascript
<input
        name        = "keyword"
        placeholder = "Search"
        value       = {this.state.keyword}
        onChange={this.handleChange}>
```
- keyword 값을 state 이용
  - 그러면 생성자 this.state에 keyword를 state로 추가
- keyword 값이 공백으로 지정되있기 때문에 에러뜬다
- input 값안에 뭘 적어도 공백으로 됨
- 즉, 뭘할지 안정했으니까 그걸 구현해야함(핸들링 필요)
s
## 핸들링
```javascript
handleChange(e) {
  this.setState({
    keyword: e.target.value
  });
}
```
- event 객체의 target의 value로 설정
- 저 상태로는 handleChange가 this가 뭔지 모르니까 바인딩 해줘야 함

## 바인딩
```javascript
this.handleChange = this.handleChange.bind(this);
```
- 임의의 메서드 만들시 this와 바인딩 필수임
- 그리고 input에서 onChange=this.handleChange로 설정

## 검색 기능 구현
1. sort
2. filter

```javascript
render() {
  const mapToComponents = (data) => {
    // 오름차순으로 정렬할꺼니까 파라미터 생략
    // 유저한텧서 또 값 받을꺼니까 또 소트 하는거임(미리 소트 되있는데 왜함?)
    data.sort();

    // 함수를 안에 arrow 함수 통해 만들어보자.
    // contact를 파라미터로 갖는 함수 만들자.
    // 그 내부에는 search의 내용이 이름에 포함된 경우 true 반환.
    // 방법은 string의 indexOf 메서드 사용하면됨
    data = data.filter(
      (contact) => {
        return contact.name.toLowerCase()
        .indexOf(this.state.keyword.toLowerCase()) > -1;
      }
    );
    return data.map((contact, i) => {
      return (<ContactInfo contact={contact} key={i}/>);
    });
  };}
```
## Arry.prototype.indexOf
만약 존재하지 않으면 -1 리턴, 주어진 엘리먼트가 배열에서 찾아지면 first index를 리턴

> arr.indexOf(searchElement[,fromIndex=0])

### Parameters
searchElement
  element to locate in the arr
fromIndex
  찾기 시작할 index

### Description
indexOf()는 searchElement와 배열 내의 엘리먼트를 strict equality를 이용하여 비교한다. (===에 의해 사용되는 동일한 메서드 or triple-equals operator)
- 배열에서 엘리먼트의 첫번쨰 index
- 안찾아지면 -1
































































ㅍ
