# img

## attr

1. `align`
  - surrounding context에 맞춘 이미지 정렬
  - HTML5에서는 `float` 사용하거나 `vertical-align`을 대신 사용

2. `alt`
  - 이미지 설명하는 대체 text.
  - 만약 이미지가 로드 안되면 이 텍스트를 dp

3. sizes
  - source size의 set을 카리킨다. comma로 구분한 1개 이상의 스트링 리스트다.

4. srcset
  - user agent가 이용할 possible image src의 집합
  - Each string is composed of:
    1. a URL to an img
    2. optionally, whitespace followed by one of:
      + width descriptor or a positive integer (directly followed by `'w'`).
      + width descriptor는 sizes attr에서 주어진 src size로 나눠진다.
