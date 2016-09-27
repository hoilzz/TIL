## transform

### 요약
CSS의 transform 속성을 사용함으로써, CSS의 시각적 서식 모델(visual formatting model)의 *좌표 공간을 변형* 시킬 수 있다. 해당 속성에 지정된 값에 따라 엘리먼트의
1 이동 (translate)
2 회전 (rotate)
3 크기변경 (scale)
4 기울임 (skew) 등의 효과를 줄 수 있다.

### syntax
> 기본문법 : <transform-fuction> [<transform-function>] * | none

#### matrix
  transform: matrix(a, c, b, d, tx, ty)
  a, b, c, d 로 transformation matrix 가 구성되며,
  ┌     ┐
  │ a b │
  │ c d │
  └     ┘
  tx, ty 는 이동되는 값이다.  

#### translate
  transform:  translate(tx[, ty]) 하나 혹은 두개의 <length> 값
  벡터(vector) [tx, ty]에 의한 2D 이동 (translation) 연산이다. 만약 ty 값을 지정하지 않는다면, 0값으로 가정하여 계산한다
