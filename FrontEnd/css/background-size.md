## background-size

### 특별한 값 : "contain" 과 "cover"

### 1 contain
- 배경 이미지의 가로,세로 길이 모두 *엘리먼트 보다 작다* 라는 전제로 배경 이미지 크기를 크게 조정
- 가로/세로 비율 유지
- 배경 이미지의 크기는 엘리먼트의 크기보다 항상 작거나 같음

<img style = "backbackground-size : contain" />


### 2 cover
- 배경 이미지의 가로,세로 길이 모두 *엘리먼트보다 크다* 라는 조건하에 가능한 배경 이미지 작게 조정
- 가로/세로 비율 유지
- 배경 이미지의 크기는 엘리먼트의 크기보다 항상 크거나 같다


### Summary

1 contain 적용 결과 둘러싸고 있는 element 보다 작게 나온다
2 cover 적용 결과 둘러싸고 있는 element와 fit 하다.
