# iterator

JS에서는 컬렉션에 대해 몇가지 반복문 함수를 제공(`map`, `filter`, `reduce` 등)

iterator와 generator는 반복 개념을 핵심 언어 내로 가져와 `for...of`` 루프의 동작을 커스터마이징 하는 메커니즘을 제공. 무슨말일까?

가장 일반적인 iterator는 Array iterator다. 이것은 단순히 연속으로 값을 리턴한다.

배열은 전체 값이 미리 할당되어야한다. 하지만 iterator는 필요할 때만 소비된다. 따라서 무한정 크기로 시퀀스를 표현할 수 있다.