# png, gif, jpg, svg

[png vs gif vs jpeg vs svg](https://stackoverflow.com/questions/2336522/what-are-the-different-usecases-of-png-vs-gif-vs-jpeg-vs-svg)

이미지 타입을 알기 전에 알아야할 요소

무손실 압축, 손실압축

- Loseless: 이미지를 압축해도 이미지의 퀄리티가 손상 안됨
- Lossy: 이미지를 압축하여 크기를 줄이지만 이미지의 퀄리티는 손상됨.

indexed Color, Direct Color

- indexed Color는 제작자에 의해 Color Map이라는 곳에 제한된 수의 색상(256개)을 가진 팔레트로만 저장 가능.
- direct color제작자가 직접 선택하지 않은 수천가지의 컬러를 저장할 수 있는 속성

**BMP: loseless / indexed and direct**

- 압축 안해서 사이즈 크다.
- 사이즈가 불필요하게 커서 웹에서 거의 사용 안함.
- 장점
  - 대신 디코딩할 게 없어서 속도가 빠르다점

**GIF: loseless / indexed only**

- 무손실 압축을 사용
- indexed color라 256가지의 컬러만 저장가능.
- 장점
  - 애니메이션 가능
  - 투명 표현 가능

## **JPEG: lossy / direct**

Vector VS Raster

Raster(png, gif, jpeg ..)

- 픽셀로 표현

Vector(svg)

- 라인과 곡선으로 표현
  - 그래서 retina screen이나 사이즈가 변경되어도 모양 유지하고싶을 때 즉 로고나 아이콘에 알맞음.
  - 곡선과 선을 그릴 때 수학 계산이 필요하여 래스터 이미지보다 더 많은 계산 능력 필요.
  - 로고가 복잡하다면 컴퓨터 속도가 느려지고 파일크기가 커질 수 있다.
  - 그래서, 벡터 모양을 단순화하는 것이 중요.
