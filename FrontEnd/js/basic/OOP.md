# OOP

[zerocho님의 js에서 OOP](https://www.zerocho.com/category/JavaScript/post/573c2acf91575c17008ad2fc)

정리하면

- constructor는 생성자 함수 그 자체를 가리킴
- **prototype은 생성자 함수에 정의한 모든 객체가 공유할 원형**

- **proto**는 생성자 함수를 new로 호출할 때, 정의해두었던 prototype을 참조한 객체

- prototype은 생성자 함수에 사용자가 직접 넣는 거고,

- **proto**는 new를 호출할 때 prototype을 참조하여 자동으로 만들어짐

- 생성자에는 prototype, 생성자로부터 만들어진 객체에는 **proto**

- 따라서 사용자는 prototype만 신경쓰면 된다. **proto**는 prototype이 제대로 구현되었는지 확인용으로 사용한다.
