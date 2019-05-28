# 브라우저 렌더링

[https://m.post.naver.com/viewer/postView.nhn?volumeNo=8431285&memberNo=34176766](https://m.post.naver.com/viewer/postView.nhn?volumeNo=8431285&memberNo=34176766)

## 동작 과정

렌더링 엔진의 동작 과정.

1. DOM 트리 구축을 위한 HTML 파싱
2. 렌더 트리 구축
3. 렌더 트리 배치
4. 렌더 트리 그리기

렌더링 엔진은 좀 더 나은 사용자 경험을 위해 가능한 빠르게 내용을 표시하기 위해, HTML 파싱할 떄 까지 기다리지 않고 배치와 그리기 과정 시작한다. 즉, 네트워크로부터 나머지 내용이 전송되기를 기다리는 동시에 받은 내용 일부를 먼저 화면에 표시.

[!img](https://d2.naver.com/content/images/2015/06/helloworld-59361-4.png)

## critical rendering path

1. HTML 데이터 파싱
2. 파싱한 결과로 DOM tree 생성.
3. 파싱하는 중 CSS 파일 링크를 만나면 CSS 파일 요청
4. CSS 파일 읽어서 CSSOM(css object model) 생성
5. DOM tree와 CSSOM이 모두 만들어지면 이 둘을 사용해 render tree 만듬
6. 렌더 트리에 있는 노드들을 Layout(reflow)

- CSS box model이 여기서 쓰인다. 즉, 크기나 배치 관련 부분들이 여기서 계산

7. paint(스타일 속성)

- 실제로 화면에 그리는 과정

FAQ
Q. reflow는 언제 다시 일어날까?
A. width:50% 인 엘리먼트가 있을 때, 브라우저 리사이즈할 경우 보이는 요소들은 변함 없으니 render tree는 그대로이고, layout 단계만 다시 거쳐서 위치계산. (참고로 layout은 웹킷, reflow는 gecko 용어)

Q. repaint는 언제 일어날까?
