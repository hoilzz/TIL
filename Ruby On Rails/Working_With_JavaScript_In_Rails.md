## Rails에 내장된 Ajax/JavaScript 를 다룬다



## 1 An Introduction to Ajax
Ajax를 이해하기 위해서는, web browser가 하는 것을 알아야해.

http://localhost:3000 를 브라우저 주소창에 입력하고 hit “Go” 했을 때,
브라우저(client)는 server로 요청을 보낸다.
서버는 response를 parse하고,
연관된 asset(javascript, stylesheet and images와 같은)을 모두 fetch한다
그리고나서 page를 모은다.
만약 링크를 클릭하고 나면
그것은 동일한 프로세스를 거친다.
(프로세스 : fetch the page, fetch the assets, put it all together, show you the results)
이것은 request response cycle이라 불린다.

Javascript 또한 서버에 요청을 만들 수 있다.
그리고 response를 parse할 수 있다.
그것은 또한 page에서 정보를 업데이트할 능력도 가지고 있다.
이러한 2가지 power를 합쳐서
javascript writer는 그 자체의 부분을 업데이트할 수 있는 web page를 만들 수 있다.
(server로부터 full page data를 get할 필요 없이)
이것은 Ajax의 파워풀 테크닉이다

Rails는 default로 CoffeeScript를 ship한다
vanilla JavaScript를 적용할거야

> $.ajax(url: "/test").done (html) ->
> $("#results").append html

이 코드는 "/test"로부터 data를 fetch하고
results라는 id를 가진 div에 결과값을 append한다.

Rails는 이러한 기법으로 web page를 building하는 것을 support한다

너는 이 코드를 혼자서 작성하지 않을거야.
이 가이드의 나머지는
Rails가 이러한 방식으로 website 작성하기위해 도와주는 방식을 보여줄거야


## 2 unobstrusive JavaScript

Rails는
DOM에 JavaScript를 attaching하는 것을 처리하기 위해
"unobstrusive Javascript"라고 불리는 기법을 사용한다

JavaScript를 작성하기 위한 가장 간단한 방식이다.
"inline javascript"



## 4 Server-side concerns

Ajax는 단순한 클라이언트 사이드가 아니다.
그것을 지원하기 위해 server-side에서 몇가지 작업 해야한다.
종종, 사람들은 HTML보다 JSON을 리턴받기 위해 Ajax 요청을 좋아한다.


## 4.1 Simple Example

new user create하기 위해 form을 제공하고
dp할 여러 유저를 가지고 있다고 해보자

controller의 index action은 다음과 같다.

>class UsersController
>  def index
>    @users = User.all
>    @user = User.new
>  end


index view (app/views/users/index.html.erb)

<b>Users</b>
<ul id = "users">
<%= render @users %>
</ul>
<br>
<%= form_for (@user, remote: true) do |f| %>
  <%= f.label :name %> <br>
  <%= f.text_field :name %>
  <%= f.submit %>
<% end %>

app/views/users/user.html.erb partial은 다음을 포함한다

> <li><%= user.name %> </li>

index page의 가장 윗부분은  users를 display한다
가장 아래부분은 new user를 생성하기 위한 form을 제공한다.

bottom form은 UsersController의 create action을 호출한다
왜냐하면 form's remote option은 true이고,
요청은 Ajax 요청으로 UsersController로 post될것이다.
(JavaScript를 찾으면서)

그 요청을 제공하기 위해,
create action은 다음과 같다.

> def create
>  @user = User.new(params[:user])

>  respond_to do |format|

>    if @user.save
>      format.html { redirect_to @user, notice: 'User was successfully created.' }
>      format.js   {}
>      format.json { render json: @user, status: :created, location: @user }

>    else
>      format.html { render action: "new" }
>      format.json { render json: @user.errors, status: :unprocessable_entity }
>    end
>  end
>end

respond_to block안의 format.js을 주목해라
그것은 controller가 Ajax request에 respond하도록 허용한다
그리고나서
이에 상응하는 app/views/users/create.js.erb view file을 가진다
(이 파일은 전송되고 클라이언트 사이드에서 실행될 실제 JavaScript code를 생성한다)


> $("<%= escape_javascript(render @user)%>").appendTo("#users");
















5 Turbolinks

Rails ships with the Turbolinks library, which uses Ajax to speed up page rendering in most applications.

5.1 How Turbolinks Works

Turbolinks attaches a click handler to all <a> on the page. If your browser supports PushState, Turbolinks will make an Ajax request for the page, parse the response, and replace the entire <body> of the page with the <body> of the response. It will then use PushState to change the URL to the correct one, preserving refresh semantics and giving you pretty URLs.

The only thing you have to do to enable Turbolinks is have it in your Gemfile, and put //= require turbolinks in your JavaScript manifest, which is usually app/assets/javascripts/application.js.

If you want to disable Turbolinks for certain links, add a data-turbolinks="false" attribute to the tag:

<a href="..." data-turbolinks="false">No turbolinks here</a>.
