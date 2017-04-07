# mysqljs

## Establishing Connection

```javascript
var mysql = require('mysql');
var connection = mysql.createConnection({
	host: 'example.org',
	user: 'bob',
	password:'secret'
})


connection.connect(function(err){
	if(err) {
		console.error('error connecting: ' + err.stack);
		return;
	}
	console.log('connected as id ' + connection.threadId);
});
```

## Performing queries

`.query()` 메서드는 오브젝트(`connection`, `Pool`)로 호출할 수 있는 가장 기본적인 쿼리 수행 방식.

`.query()`의 가장 기본적인 form은 `.query(sqlString, callback)`이다.

```javascript
connection.query('select * from books Where author = "david"',
				 function (err, results, fields){

	// results는 쿼리의 결과들을 담고 있다.
	// fields는 리턴된 results field에 관한 정보를 포함한다.
})
```

`.query()`의 second form은 `query(sqlString, values, callback)`은 placeholder 값을 사용할 때 나타난다.

```javascript
connection.query('select * from books where author = ?', ['david'],function(err, results, fields){});

```



## Escaping query values


SQL injection 공격 피하기 위해, SQL 쿼리 내부에 그것을 이용하기 전에 제공된 데이터를 항상 escape해야한다. `mysql.escape()`, `connection.escape()` or `pool.escape()`메서드를 이용하면 된다.

```javascript
var userId = `some user provided value`;
var sql = `SELECT * from users where id = ` + connection.escape(userId);
connection.query(sql, function (error, results, fields){
	...
})
```

대신, 다음과 같이 escape하기 위해 `?` 문자를 사용할 수 있다.

```javascript
connection.query('SELECT * FROM users where id = ?', [userId], function(error, results, fields) {
	...
})
```

Multiple placeholder는 동일한 순서대로 매핑된다. 예를 들어,

```javascript
connection.query('UPDATE users SET foo = ?, bar = ?, baz = ? WHERE id = ?', ['a', 'b', 'c', userId], function (error, results, fields) {
  if (error) throw error;
  // ...
});
```

escaping은 다음과 같은 neat things도 허용한다.

```javascript
var post = {id: 1, title: 'Hello MySQL'};
var query = connection.query('INSERT INTO posts SET ?', post, function (err, results, fields){
	...
})
console.log(query.sql);
```

## Preparing Queries

multiple insertion points를 만들기 위해 `mysql.format`이용하기

```javascript
var sql = "SELECT * FROM ?? WHERE ?? = ?";
var inserts = ['users', 'id', userId];
sql = mysql.format(sql, inserts);
```
