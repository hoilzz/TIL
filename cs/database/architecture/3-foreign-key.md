# 3. 테이블이 점점 많아지고 커짐

원자적인지 않은 열은 새로운 테이블로 옮겨야 함

## 참조키

참조키는 연결되는 기본키와 다른 이름일 수 있음
- 참조키에서 참조하는 기본키는 부모키라고도 함
  - 부모키가 있는 테이블을 부모 테이블이라고 함
- 참조키는 한 테이블의 열들이 다른 테이블의 열과 연결 되도록 사용할 수 있음 
- 참조키는 null일 수 있음
- 참조키는 유일할 필요가 없음, 실제로 유일하지 않은 경우가 많음

### 제약조건

__참조 무결성__
- 참조키의 값으로는 부모 테이블에 존재하는 키의 값만 넣을 수 있음
  - 규칙 위반시 에러 발생하여 실수로 규칙 위반을 막을 수 있음

### 참조키가 있는 테이블의 생성

참조키가 어느 테이블을 참조하는지 알려면 CONSTRAINT 명명

ex. interests 테이블은 contacts 테이블의 기본키를 참조할거임

```sql
create table interests {
  int_id int not null auto_increment primary key,
  interest varchar(50) not null,
  contact_id int not null, # 참조키
  constraint my_contacts_contact_id_fk foreign key (contact_id) references my_contacts (contact_id)
}
```

- 제약조건(constraint)은 참조키가 어느 테이블을 참조하는지, 그리고 키의 이름 또한 제약 조건이 참조키(fk)라고 명명
  - 얘를 해줘야 부모 테이블에 존재하는 값만 넣을 수 있음
  - 그리고 얘를 해주면 연결을 강제
    - 이 뜻은, 기본키 테이블에서 행을 지우거나 기본키 값 바꾸려고할 때, 기본키의 값이 다른 테이블의 참조키 제약조건이면 에러 발생
      - 그래서 참조키쪽의 행을 먼저 지우고 기본키 행을 지워야함
      - 기본키 행 먼저 지우면 참조키쪽 행은 고아가 되서 정보 검색 쓸데없이 느려지게 함
- `foreign key (${부모 테이블의 기본키})`
- `references ${부모키의 테이블이름} (${다른 테이블의 열 이름})`