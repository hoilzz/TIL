# 어드민 개발하면서 flex 써먹은거 정리

flex 부모(container)와 자식(item)으로 나뉜다.

부모는 전체적인 정렬, 흐름을 제어한다.

## flex

flex : 1; (1 1 0)
grow, shrink, basis 순으로 값이 정해진다.

## flex-grow

flex-item의 확장에 관련된 속성 0이상의 양의 정수

값이 0이면 flex container의 크기가 커져도 flex item의 크기가 커지지 않음
값이 1 이상이면 1이상의 값읋 가져야함

## flex-shirink

0이상의 양의 정수

값이 0이면 container의 크기가 item보다 작아져도 item의 크기는 줄어들지 않고 원래 크기 유지
1이상이면 container가 item보다 작아질 때, 그것에 맞춰 item이 줄어든다.

## flex-basis

기본크기 결정(auto가 기본값)

px, %등과 같은 width에서 사용하는 단위.

값을 0으로 하면 flex item의 크기가 고정됨. 이렇게 하면 flex-container를 기준으로 크기가 결정됨.

## flex

- intial: 기본값. flex container의 크기가 작아지면 flex item의 크기가 작아진다. 하지만 flex container의 크기가 커져도 item의 크기는 커지지 않음.

- none: flex itemㅇ의 크기가 커지거나 작아지지 않는다. flex container의 크기에 영향을 받지 않음. 원래 크기 유지

- auto: 크기에 맞춰 크기가 커지거나 작아짐

- 양의 정수 : container를 일정한 비율로 나눠가짐.

## justify-content

자식요소들을 정렬

## align-items

자식들의 수직 중앙 정렬

[간단히 공부한거](https://codepen.io/cooking/pen/zYONagp?editors=1100)

[참고](https://d2.naver.com/helloworld/8540176):w
