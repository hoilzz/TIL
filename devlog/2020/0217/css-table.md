# table

Q. table의 각 td들의 cell width는 어떻게 결정되는가?

[automatic layout](https://www.w3.org/TR/CSS21/tables.html#auto-table-layout).
브라우저에 구현된 자동 table layout algorithm의 동작 결과다.

테이블은 명시된 width가 없다면(default auto), 셀(with %)의 너비는 콘텐츠만큼 넓어진다.
계산된 너비는 전체 테이블의 최대 width를 찾는 백분율(%)로 사용된다.
그리고 이에 따라 나머지 열의 크기가 조정됩니다.

Q. 특정 column(td들)의 width를 제한하고 싶은데 max-width는 안먹힘. 왜?

[max-width에 관하여](https://www.w3.org/TR/CSS21/visudet.html#propdef-max-width)

inline element, table row, and row groups에 안먹힘.
