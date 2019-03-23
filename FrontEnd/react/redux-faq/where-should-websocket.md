# Where should websockets and other persistent connection live?

미들웨어는 websocket과 같은 영구적인 연결을 위한 적합한 장소다.

- 미들웨어는 어플리케이션의 라이프타임을 위해 존재한다.
- store와 마찬가지로, 전체 app이 사용할 수 있는 특정 연결의 **single instance만** 필요하다.
- 미들웨어는 dispatch된 모든 action을 볼 수 있고 스스로 action을 dispatch 할 수 있다. 이것은 미들웨어가 dispatch된 action을 가지고 메세지로 변경해서 websocket으로 보낼 수 있다. 그리고 웹소켓에서 받은 메세지를 new action으로 dispatch 할 수 있다.
- 웹소켓 연결 인스턴스는 serializable 될 수 없다. 그러므로 store state에 저장되지 못한다.

참고 : [socket middleware example](https://gist.github.com/markerikson/3df1cf5abbac57820a20059287b4be58)
