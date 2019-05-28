# scope chain

[https://github.com/hoilzz/hoilzz.github.io/blob/f966ccf6c7162ca6714f89d581a773d6fc61e47b/\_posts/2017-6-12-scope-chain.md](https://github.com/hoilzz/hoilzz.github.io/blob/f966ccf6c7162ca6714f89d581a773d6fc61e47b/_posts/2017-6-12-scope-chain.md)

스코프 체인의 목적은 `실행 컨텍스트가 접근할 수 있는 모든 변수와 함수에 순서를 정의`하는 것.

- 스코프 체인의 앞쪽은 항상 코드가 실행되는 컨텍스트의 변수 객체
- 변수 객체의 다음 순서는 해당 컨텍스트를 포함하는 부모 컨텍스트
- 부모의 부모를 타고 올라간다. until 전역 컨텍스트 도달

```javascript
var color = 'blue';
function changeColor() {
  var anotherColor = 'Red';

  function swapColor() {
    var tempColor = anotherColor;
    anotherColor = color;
    color = tempColor;
  }
  swapColor();
}
changeColor();
```

위 코드에는 3개의 실행 컨텍스트가 존재

1. 전역 컨텍스트
2. changeColor()의 로컬 컨텍스트
3. swapColors()의 로컬 컨텍스트

<img>

swapColors()의 로컬 컨텍스트 스코프 체인의 객체 3개

1. swapColors()의 변수 객체
2. changeColor()의 변수 객체
3. 전역 변수 객체

- 각 사각형은 실행 컨텍스트임
- 내부 컨텍스트는 스코프 체인을 따라 상위(외부) 컨텍스트에서 변수나 함수를 검색할 수 있다
- 상위 컨텍스트는 내부 컨텍스트를 따라 내려 가며 검색 불가능
