Problem
======
아뭐듣지 google analytics 통계를 보면 모바일 접속이 압도적으로 높았다.
하지만 모바일 대응을 전혀 하지 않았고,
그 결과 시간표 작성시 클릭 이벤트 등이 발생하지 않았다.


SOLUTION
=======
[**TouchEvent**](https://developer.mozilla.org/en-US/docs/Web/API/TouchEvent)
터치 상태가 변할 때 일어나는 이벤트
- 1개 이상의 point의 움직임 감지, 추가 제거 등
- touchstart 이벤트 사용

[**touchstart**](https://developer.mozilla.org/en-US/docs/Web/Events/touchstart)
유저가 터치 point를 가리킬 때 이벤트 전송
이벤트 타겟은 터치가 일어난 엘리먼트가 된다.



>     $('body').on('touchstart click', '.collection-item', function(event){
>       // 시간표에 강의 등록하기
>       event.preventDefault();
>       timetable.putLectureOnTimetable($(this));
>     });
