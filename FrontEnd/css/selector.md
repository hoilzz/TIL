# selector
: 특정 요소들을 선택하여 스타일 적용 가능.

## 선택자 & 상속

### 1. type 선택자

```css
    p {
    }
```

### 2. chain 선택자

```css
.class1.class2.class3{}

```

### 3. child 선택자
부모 요소의 직계 자식(손자 제외)를 모두 선택

```css
body > p {

}
```

### 4. 속성(attr) 선택자

- `attr`만 선택자로 이용한 경우
- `속성의 값`까지 이용한 경우

```css
p[title] {
  padding:5px;
}
```

```css
p[title="love"] {

}
```

### 5. 가상 클래스 & 가상 콘텐츠
`:hover` 뒤에 따라오는 자손 선택자 (공백)
- `:hover`가 작동하는 경우에 한해서 하위 자손에게 속성을 줄 수 있다.

```css
a:hover span {

}
```

### 체인 가상 클래스
가상 클래스를 연속적으로 이어서 사용할 수 있다.
- 아래 예시는 첫째 a가 hover 되었을 때만 적용

```css
a:first-child:hover {

}
```
