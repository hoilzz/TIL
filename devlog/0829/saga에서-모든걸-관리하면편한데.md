# saga에서 모든걸 관리하면 편한데

validation이 컨테이너 컴포넌트에 있으니까 코드가 길어져서.. 걍 사가에 모아둘까? 라는 생각이 들었다.

근데 사가에 모아두자니.. 불필요한 action을 dispatch 하는 것같다.

왜냐면 애초에 컨테이너 컴포넌트에서 validation체크하고 (굳이 saga에서만 할 수 있는 validation 이 아니기 때문..)

https://github.com/reduxjs/redux/issues/1165
https://medium.com/@jeffbski/where-do-i-put-my-business-logic-in-a-react-redux-application-9253ef91ce1#.z49ah1act

--- 