# babel-lodaer

## 왜 바벨 로더는 node_modules를 기본적으로 exclude할까?

1. babel-loader는 느리다.

가능하면 최소 파일만 transform 하자. 왜냐하면 node_modules foler나 원치 않는 파일들을 transform 할 수 있기 때문이다.

node_modules를 배제하기 위해, exclude 옵션을 사용하자.

cacheDirectory option으로 속도를 높이자. fs에 transformation을 캐싱할거다.
