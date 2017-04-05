# sequlize day1

sequlize 도입기 1일차.

Sequelize는 promise 기반 ORM이다.

NOSQL을 사용해보고 싶었지만, Rails의 Active Record ORM에 적응되어있었고, 시간이 많지 않았기 때문에 Sequelize를 선택했다.

---

먼저, Project dir은 다음과 같다.

```
helloSequelize
|- app
   |- bin
   |- models
   		|- index.js
		|- memo.js (블로그에 맞게 다시 바꿀꺼임.)
```

- `index.js`는 sequelize를 설정한다.
- `memo.js` 1개 테이블에 대한 파일이다. `테이블명.js` 네이밍을 따른다.

---

먼저, model은 db 공간의 table의 schema 표현수단이다.

model을 정의하고, 실제 메모리에 올리려면 import를 사용해야한다.

---

## import

import method를 이용하여 **1개의 파일에서 모델 정의**를 저장할 수 있다.

import method는 `index.js`에서 호출하고, 호출될 즉 import될 모델 정의부를 먼저 살펴보자.

리턴된 객체는 import된 파일의 함수 내에 정의된 것과 완전 똑같다.

Sequelize (v1:5.0)에서 import는 캐시된다. 그래서 file import를 2번이상 호출해도 에러 없다.


*memo.js*
```javascript
module.exports = function(sequelize, DataTypes) {
    return sequelize.define('Memo', {
        pub_id: {type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true},
        name: {type: DataTypes.STRING(32), allowNull: false},
    });
};
```

- `sequelize.define`은 모델을 정의한다.
- 모델 정의 함수를 리턴하는 파일을 `index.js`에서 임포트할 것이다.

---

위에서 정의한 모델 정의를 import해보자.

먼저, 호출하기 전에 간단한 db 세팅을 하자.


*index.js*
```javascript

var fs = require('fs');
var path = require('path');
const Sequelize = require('sequelize');
const sequelize = new Sequelize(
    'db이름', // 데이터베이스 이름
    '유저명', // 유저 명
    '비번', // 비밀번호
    {
        'host': 'localhost', // 데이터베이스 호스트
        'dialect': 'mysql' // 사용할 데이터베이스 종류
    }
);

var db = {};

db['Memo'] = sequelize.import(path.join(__dirname, 'memo.js'));
db['Memo'].sync({force: true});
db.sequelize = sequelize;
db.Sequelize = Sequelize;
module.exports = db;
```

db라는 객체를 생성하여, 위와 같이 작업한다.

서버가 생성시, 정의된 모델들은 import를 통해서, 또한 app단에서도 캐시하면 import 메서드를 여러번 호출할 필요가 없다.

여튼, 서버 생성시 단 한 번 import 하면 다음은 require로 가져다 쓰기만 하면 된다.

서버가 구동될때 정의된 모델을 app단에서도 캐쉬하면 import 메소드를 여러번 호출할 필요가 없다.

만약, models에 각 table에 대한 정의가 이뤄진 파일을 모아놓는다면 다음과 같이 import문을 사용하면 더 효율적이다.

```javascript
fs.readdirSync(__dirname)
    .filter(function(file) {
        return (file.indexOf('.') !== 0) && (file !== 'index.js');
    })
    .forEach(function(file) {
        var model = sequelize['import'](path.join(__dirname, file));
        db[model.name] = model;
    });
module.exports = db;
```

다음은 레코드 생성, 조회, 업데이트, 삭제에 대해 알아보자.
