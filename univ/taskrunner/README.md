# gulp

- `**/*.css` : 모든 디렉터리의 .css

- `gulp.task(name[,deps],fn)`
	- 태스크를 만든다.
	- name : 태스크 이름을 지정
	- deps : 해당 태스크가 실행되기 이전에 실행되어야 할 태스크를 지정(한개여도 배열로 표현)
	- fn : 태스크의 상세 내용을 정한다.

- `gulp.watch(glob [,opts], tasks)`
	- opts: 거의 사용 ㄴㄴ해
