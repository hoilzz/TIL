# Thinking in React

리액트는 javascript로 big, fast Web apps을 만들기 위한 최고의 방식이다. 페이스북과 인스타그램에서 잘 스케일링 되어있다. 리액트의 훌륭한 부분 중 하나는 앱을 구축할 때, 앱에 대해 어떻게 생각하느냐는 것이다. 이 문서에서 React를 사용하여 검색 가능한 제품 데이터 테이블을 구축하는 과정을 안내할 것이다.


## Start With A Mock

JSON API를 이미 가지고 있고 디자이너로부터 mock도 받았다고 하자.

## Step 1: UI를 컴포넌트 계층으로 나누기

`자체 컴포넌트`(its own component)가 되어야만 하는 것은 어떻게 알 수 있을까? **새로운 함수 혹은 객체를 생성해야만 하는지를 결정하기 위한 동일한 기법을 사용하자** 그러한 테크닉 중 하나는 `single responsibility principle` 이다. 컴포넌트는 이상적으로 한 가지 일만 해야한다. 만약 역할이 더 커지게 된다면, 더 작은 서브 컴포넌트로 쪼개야 한다.



## Summary

`single responsibility principle`