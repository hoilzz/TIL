# respond_to

웹 서비스 지원 없이, 사람들의 리스트를 보여주기 위해 데이터를 모은 action

```ruby
def index
  @people = Person.find(:all)
end

def index
  @people = Person.find(:all)

  respond_to do |format|
    format.html
    format.xml { render :xml => @people.to_xml}
  end
end
```

클라이언트가 원하는 포맷이 XML, HTML 등 뭐든 간에
Rails는 클라이언트에 의해 제출된 `HTTP Accept header`로부터 원하는 `response format`을 결정한다.

> NOTE
> http accpet header는 rfc 문서를 참고하자.

new person을 추가하는 action을 가진다고 가정해보자.

만약 기존에 존재하지 않는다면 optionally creating their company (by name)

```ruby
def create
	@company = Company.find_or_create_by_name(params[:company][:name])
	@person = @company.people.create(params[:person])

	redirect_to(person_list_url)
end
```

 Here's the same action, with seb-service suppoer baked in:

```ruby
def create
	company = params[:person].delete(:company)
	@company = Company.find_or_create_by_name(params[:company][:name])
	@person = @company.people.create(params[:person])

	respond_to do |format|
		format.html { redirect_to(person_list_url) }
		format.js
		format.xml {render :xml => @person.to_xml(:include => @company)}
	end

end
```

## form_for (remote: true)

- javascript driver가 form for의 행동을 수정하도록 허용
- 예상된 행동은 regular POST arrangement 대신에 background에서 XMLHttpRequest다.
- form element를 serialize하기 위해 Javascript 이용
