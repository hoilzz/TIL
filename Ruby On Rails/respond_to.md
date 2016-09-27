## respond_to

웹 서비스 지원 없이, 사람들의 리스트를 dp하기 위한 데이터를 모은 action
like this:

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

What that says is,
"만약 클라이언트가 해당 action에 대한 응답으로 HTML을 원한다면,
 just respond as we would have before,

 하지만 만약 클라이언트가 XML을 원한다면, XML format으로 사람 리스트를 return 해라."
 (Rails는 클라이언트에 의해 제출된 *HTTP Accept header* 로부터 원하는 response format을 결정한다)
 *클라가 XML or HTML을 원하는지 어떻게 알까 : HTTP Accept header*


 new person을 추가하는 action을 가진다고 가정해보자.
 만약 기존에 존재하지 않는다면 optionally creating their company (by name)
 :

 def create
  @company = Company.find_or_create_by_name(params[:company][:name])
  @person = @company.people.create(params[:person])

  redirect_to(person_list_url)
 end

 Here's the same action, with seb-service suppoer baked in:


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


##### 만약 클라이언트가 HTML을 원한다면,
person list로 단순하게 redirect back 하면된다.

##### javascript를 원한다면
(format.js), then it is an RJS request and
we render the RJS template associated with this action

(RJS는 AJAX 요청에 대한 응답으로 브라우저에 의해 실행된 Javascript를 생성하는 template)


##### XML을 원한다면

생성된 person을 XML로 렌더한다.
but with a twist: 렌더링된 XML에서 person's company를 포함한다.
그래서 이와 같이 무언가 얻을 수 있다.






## form_for (remote: true)

- javascript driver가 form for의 행동을 수정하도록 허용
- 예상된 행동은 regular POST arrangement 대신에 background에서 XMLHttpRequest다.
- form element를 serialize하기 위해 Javascript 이용
