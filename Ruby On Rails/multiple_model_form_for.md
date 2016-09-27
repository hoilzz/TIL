## 2가지 이상의 모델을 1개의 form_for에서 수정하기

1 라우팅
2 전송
3 controller에서 save

## Reference

1 Active Record Nested Attribute
2 multiple routing
3 form for send multiple model


1 Active Record Nested Attribute

Nested attribute는 associated된 레코드의 attribute를 부모를 통해 save하도록 해준다.
기본적으로 nested attribute updating은 turned off고
accepts_nested_attributes_for class method를 이용하여 toggle할 수 있다.

nested attribute를 활성화하면
attribute writer가 모델에서 정의된다.

attribute writer는 association 후에 작성해라
2가지 메서드가 너의 모델에 추가된다.

1 author_attributes=(attributes) and
2 pages_attributes=(attributes)

class Book < ActiveRecord
  has_one :author
  has_many  :pages

  accepts_nested_attributes_for :author, :pages

:autosave option은 자동으로 활성화된다.


### One-to-many

post를 가지는 member 모델

class member
  has_many :posts
  accepts_nested_attributes_for :posts
end

associated posts에서 member hash를 통해
attribute 세팅 or update 할 수 있다.
(:posts_attributes key에 post attribute의 해시 배열을 값으로 포함해라.)

만약 hash 또한 true로 설정된 *_destroy* key를 포함하지 않는다면
id key를 가지지 않는 각 hash에 대해
new record가 이니셜라이징 된다.

params = { member: {
  name: 'joe', posts_attributes: [
    {title: "Kari, the awesome Ruby document"},
    {title: "The egalitarian assumption of the modern citizen"},
    {title: '', *_destroy*: '1'}  # this will be ignored
  ]
  }}

  member = Member.create(params[:member])
  member.posts.length
  member.posts.first.title


  :reject_if proc 도 설정할 수 있다
  (criteria 통과하지 못한다면 new record hash 무시함)


-> has_many된 모델명을 accepts_nested_attributes_for의 인자값으로 전달





2 multiple routing
