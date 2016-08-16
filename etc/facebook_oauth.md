## 액세스 토큰

페북 로그인 사용시 앱에 연결하면

앱에서 액세스 토큰을 얻게됨(Facebook API에 대한 임시 보안 액세스 제공)

- 사용자, 앱 또는 페이지를 식별하는 불명확한 문자열
- 액세스 토큰은 여러 메서드를 통해 얻을 수 있다.



## OmniAuth: Standardized Multi-Provide Authentication

OmniAuth는 멀티 프로바이더 인증을 표준화할 수 있는 라이브러리다.

어떠한 개발자든
종류가 다른 system을 통해 유저를 인증할 수 있는 OmniAuth 전략을 만들 수 있다.
OmniAuth 전략은 Facebook to LDAP까지 모든 것을 위해 만들어졌다

너의 앱에 OmniAuth를 사용하기 위해,
너는 1개 이상의 전략에 leveage할 필요가 있다.
이러한 전략은 RubyGem에 따라 개별적으로 릴된다.

Developer라고 불리는 1가지 전략은 OmniAuth를 포함하고
완전히 불안전한, non-production-usable startegy를 제공한다
(이 전략은 인증 정보를 위해 직접 유저에게 prompts한다
  그리고 그것을 straight through 통과시킨다.)

개발을 시작할 때 placeholder로써 그것을 사용할 수 있다.
그리고 swap할 수 있다.



### Getting Started

각 OmniAuth 전략은 Rack Middleware다.
이것은 동시에 다른 Rack middleware를 사용할 수 있다는 것을 의미한다.
예를 들어, Sinatra 어플리케이션을 사용하기 위해 나는 이것을 한다
:

require 'sinatra'
require 'omniauth'

class MyApplication < Sinatra::Base
  use Rack::Session::Cookie
  use OmniAuth::Strategies::Developer
end

왜냐하면 OmniAuth는 multi-provider 인증이 내장되어있다.

OmniAuth::Builder class는

다음 코드와 middleware에 따라 개별적인 사용은 차이가 없다.

Rails initializer에 넣을 수 있는 거다

Rails.application.config.middleware.use OmniAuth::Builder do
  provider :developer unless Rails.env.production?
  provider :twitter, ENV['TWITTER_KEY'], ENV['TWITTER_SECRET']
end



### Integrating OmniAuth Into Your application

OmniAuth는 극도로 low-touch 라이브러리다.
너으 어플리케이션 유저를 보낼 수 있는 블랙박스로 디자인되어있다
(너가 인증을 필요하고 정보를 다시 얻을 때)

OmniAuth는 의도적으로 User model과 자동 associate되지 않도록 내장 되어있다.
(또한, 너가 사용할 인증 메서드가 약 얼마나 될지 가정하지도 않고 한번 인증된 유저를 가지고 뭘할지도 가정하지 않도록)

이것은 OmniAuth가 엄청 유연하다는 것을 말한다.

#### OmniAuth 사용하기 위해,
- redirect users to /auth/:provider로 리다이렉팅만 시키면 된다.
- :provider는 전략 이름이다.(예컨대, developer or twitter)
- 거기서부터 OmniAuth는 take over할 것이고
- 인증하기 위한 필수 스텝을 거칠 것이다.

유저가 인증되고 나면 다음은?
- /auth/:provider/callback에 대한 요청의 Rack 환경에서 Authentication 해시라 불리는 스페셜 해시를 세팅한다.
- 이러한 hash는 유저에 대한 많은 정보를 포함한다.
