# form

웹 서버에 정보를 제출하기 위한 대화형 컨트롤을 포함한 문서의 구획

## property

### 1. accept-charset

### 2. action

### 3. method

- 폼을 제출하기 위한 HTTP method

```html
<!-- Simple form which will send a GET request -->
<form action="">
  <label for="GET-name">Name:</label>
  <input id="GET-name" type="text" name="name">
  <input type="submit" value="Save">
</form>

<!-- Simple form which will send a POST request -->
<form action="" method="post">
  <label for="POST-name">Name:</label>
  <input id="POST-name" type="text" name="name">
  <input type="submit" value="Save">
</form>

<!-- Form with fieldset, legend, and label -->
<form action="" method="post">
  <fieldset>
    <legend>Title</legend>
    <input type="radio" name="radio" id="radio"> <label for="radio">Click me</label>
  </fieldset>
</form>

```

# input

## Summary
user 에서 data를 accept하기 위해 web 기반 form을 위해 interactive control을 생성하는데 이용된다.

## property
- `type`
  - `button` : default 행위가 없는 btn
  - `checkbox` : `value` attribute를 꼭 사용해야 한다. 이 item이 선택 되었는지 가리키기 위해 `checked` attr을 사용해라.
  - `hidden` : 서버에 보내지는 값인데 안보임
  - `search` : single-line text field for entering search string.
  - `submit` : a button that submits the form
  - `text` : a single-line text field

- `name` : form data와 함꼐 submit 될 control 이름

## 예제 코드
from 아뭐듣지

```html
<form class="new_user" id="new_user" action="/users" accept-charset="UTF-8" method="post"><input name="utf8" type="hidden" value="✓"><input type="hidden" name="authenticity_token" value="jbTSq8j0WvgG9RvvvCk6KyN7In7dywqS6ypCIdGRemRI8SWcQpRE4kEIOrVnLH3BI0JU9GYVmNrTY0WqBk1cdg==">




      <div class="input-field col m12">
        <label for="nickname">별명 (학번 및 실명은 권하지 않습니다-)</label>
        <input class="validate" id="nickname" type="text" name="user[nickname]">
      </div>

      <div class="input-field col m12">
        <label for="email" class="">Email</label>
        <input class="validate" id="email" type="text" name="user[email]">
      </div>

      <div class="input-field col m12">
        <label for="password" class="">암호 (6자 이상)</label>
        <input class="validate" id="password" type="password" name="user[password]">
      </div>

      <div class="input-field col m12">
        <label for="password_confirm">암호 한번 더 (똑같이)</label>
        <input class="validate" id="password_confirm" type="password" name="user[password_confirmation]">
      </div>

      <div class="row">
        <input type="submit" name="commit" value="계정 만들기" class="btn col m12">
      </div>
</form>
```
