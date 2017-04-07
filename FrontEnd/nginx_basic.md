# NGINX의 역할


- `nginx.conf` : 메인 설정 파일.

- `fcgi.conf` : FastCGI 환경설정 파일

- `sites-enabled` : 활성화된 사이트들의 설정 파일들이 위치. 아파치에서는 Virtual host의 설정에 해당한다. 기본적으로 존재하지 않을수도 있다. 이 디렉토리를 직접 만들어서 사용하는 방법은 가상 호스팅편에서 알아본다.

- `sites-available` : 비활성화된 사이트들의 설정 파일들이 위치

### core 모듈 설정
worker_processes와 같은 지시자 설정 파일 최상단에 위치하면서
nginx의 기본적인 동작 방식을 정의한다

nginx는 1개의 master process와 worker processes를 가진다
`master process`의 주 목적
  - read and evaluate configuration
  - worker processes 유지하기

`worker processes` : 실제 요청 처리

### NGINX는

 - 이벤트 기반 모델(아파치는 프로세스나 쓰레드 방식, 비동기 이벤트 + 단일 쓰레드 방식 작동->블록킹(프로세스or쓰레드에서 발생)에 의한 지연 및 자원 소모 적어 가볍고 빠른 속도)
 - worker processes에게 효율적으로 요청을 분배하기 위해 OS-기반 메커니즘
 - worker process는 configuration file에서 정의되고
 - 주어진 configuration에서 수정되거나
 - 가용 가능한 CPU core의 양에 따라 자동으로 조정됨

`var/run/` 이 안에는 실행 중인 앱이다.
 시스템운용중에 생성되었다가 삭제되는 데이터를 일시적으로 저장하기 위한 디렉토리.
 거의 모든 시스템로그파일은 /var/log 에 저장되고, DNS 의 zone 설정파일은 /var/named 에 저장되고, 메일파일은 `/var/spool/mail` 에 저장되며, 크론설정파일은 /var/spool/cron 디렉토리에 각각 저장됨.

```
upstream my_app {
  server unix:///var/run/my_app.sock;
  this is socket for puma server and this address will be used

  also in puma configuration
}

server {
  listen 80;
  server_name 127.0.0.1; # change to match your URL/domain
  root /home/workspace/my_app/public; # path to your app

  location / {
    proxy_pass http://my_app; # match the name of upstream directive which is defined above
    proxy_set_header Host $host;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
  }

  location ~* ^/assets/ {
    # Per RFC2616 - 1 year maximum expiry
    expires 1y;
    add_header Cache-Control public;

    # Some browsers still send conditional-GET requests if there's a
    # Last-Modified header or an ETag header even if they haven't
    # reached the expiry date sent in the Expires header.
    add_header Last-Modified "";
    add_header ETag "";
    break;
  }
}
```

## configuration File's Structure
(위에서 worker process 정의한다고 말함)
nginx는 directives에 의해 제어되는 모듈로 구성된다.
Directives는 simple directive와 block directive로 나뉜다

1 simple directive
- 세미콜론으로 끝나고 space에 의해 분리된 파라미터와 이름으로 구성

2 block directive
- simple과 동일 구조
- 하지만 semicolon 대신에 {} 사용
- {} 안에 다른 directive를 가진다면 context라고 불림(events, http, server, and location)

context 밖의 configuration file에 위치한 directive는
main context다.
*events* and *http* directives는 *main* context안에
*server* 는 in *http*, and *location* 은 in *server*

## Serving Static Content

웹 서버의 중요한 task는 file을 serving하는 것
(such as images or static HTML pages)

files은 다양한 local directories에서 제공될 것이다.
local directories: /data/www (HTML files을 포함하는 곳)

이것은 configuration file을 편집하기를 요구하고
*http* block 내부의 2개의 *server* block을 세팅해야 된다.

First,
/data/www directory를 생성하고 index.html 파일을 put해라
그리고 /data/images directory 생성하고 이미지 파일 put 해라

Next,
configuration file열고
default configuration file은 이미 몇몇 server block 예제를
포함한다.

```
http {
  server {
  }
}
```

일반적으로, configuration file은 몇몇 port로 구분된 server block을 포함한다. (on which they listen to and by server name)
한번 nginx가 어떤 server가 요청 처리할지 정하면,
server block 내부에서 정의된 location directives의 파라미터로
요청의 헤더에 명시된 URI를 테스트한다

```
location / {
  root /data/www
}
```

location block은 요청의 URI와 비교되는 `/` prefix를 명시한다

local file system에서 요청된 file에 the path를 형성하기 위해,
URI는 root directive에 명시된 path에 추가된다.

location block은 가장 짧은 prefix를 제공하고
만약 모든 location block이 match되는 것 제공하는데 실패한다면,
이 block이 사용될거다

Next, add the second location block:

```
location /images/ {
  root /data
}
```

2번쨰 location block 추가하자

위의 것은 `/images/`로 시작하는 요청과 일치한다.
(location / 또한 /images/요청과 일치한다 하지만 걔는 더 짧은 prefix를 가지고 있다.)

server block의 configuration은 다음과 같다

```
server {
  location / {
    root /data/www;
  }
  location /images/ {
    root /data;
  }
}
```

이것은 80번 포트를 listen하는 server의 configuration이다.
그리고 `http://localhost/`. 에서 local machine으로 접근 가능하다

`/images/`로 시작하는 URI의 요청에 대한 응답에서,
server는 `data/images` directory로부터 파일을 보낼 것이다.

예를 들어,
`http://localhost/images/example.png` 요청에 대한 응다븡로
nginx는 `/data/images/example.png` file을 전송할 것이다.

만약 그러한 파일이 없다면 404 error를 응답으로 전송할 것이다

`/images/`로 시작하지 않는 URI의 요청은
`/data/www` 디렉토리로 매핑 될 것이다

`http://localhost/some/example.html` 요청에 대한 응답으로
nginx는 `/data/www/some/example.html` file을 전송할 것이다


## Setting Up a Simple Proxy Server

nginx의 빈번한 사용중 하나는 proxy server 세팅이다.
이것은 요청을 받고, 그것들을 proxied server로 통과시키고,
그것들로부터 응답을 받고 클라로 그것들을 전송해주는 서버를 의미한다

basic proxy server 구성해보자.
이것은 로컬 디렉토리로 images file 요청을 서빙할 거야
그리고 proxied server에 모든 다른 요청을 전송할거야.

첫번째, server block을 nginx 환경설정 파일에
추가해서 proxied server를 정의해

```
server {
	listen 8080;
	root /data/up1;
	location / {

	}
}
```

8080 포트에 listen한 simpler server다.
(이전에도, the listen directive는 명시되지 않았다.
  왜냐하면 80번 포트는 스탠다드하게 사용되니까)
그리고 모든 요청을 로컬의 /data/up1 디렉토리에 매핑한다.
이 디렉토리를 생성하고 index.html file을 그곳에 둬라.
`root directive`는 `server context`에 놓인다.

Next, 이전 섹션의 server configuration을 사용하고
그것을 proxy server configuration으로 만들기 위해 수정해라.

첫번쨰 location block에서,

put the proxy pass directive with the protocol,
name and port of the proxied server

(http://localhost:8080)

```
server {
  location / {
   proxy_pass http://localhost:8080;
  }
  location /images/ {
    root /data;
  }
}
```

second location block을 수정할 것이다.
typical file extension 이미지 요청과 매칭되도록 만들기 위해,
이것은 현재 /images/ prefix 요청을
/data/images/ directory와 매핑한다.

`modified location block`은 다음과 같다

```
location ~ /.(gif|jpg|png)$ {
  root /data/images;
}
```

파라미터는 .gif, .jpg or .png로 끝나는 모든 URI와
일치하는 정규식 파라미터다.
정규식 표현은 `~` 를 먼저 기재해야한다.
상응하는 요청은 /data/images direcotry로 매칭될 것이다

요청을 제공하기 위해 nginx가 `location block`을 선택할 때
그것은 첫번째로 prefix를 명시한 `location directives` 을 확인한다

(가장 긴 prefix location을 기억하고 정규식을 확인한다)
만약 `location` 을 고르거나
그렇지 않으면 가장 빠른거 하나를 고른다

```
 server {
 location / {
   proxy_pass http://localhost:8080/;
  }
  location ~ \.(gif|jpg|png)$ {
    root /data/images;
  }
}
```

## nginx에서 gzip으로 압축 전송하기

gzip 전송을 하기 위해 웹 브라우저에서도 gzip을 지원해야 한다. gzip은 GNU zip의 준말로 원래는 파일 압축에 쓰이는 응용소프트웨어이다. gzip 전송의 장점은 html, css, js, json, xml, rss 등 TEXT 기반의 data들을 압축해서 전송하게 되므로 CPU점유율이나 부하를 낮춰주어 성능향상 기대할 수 있다.

### nginX Gzip 설정하기

가상 호스트별로 따로 적용하고 싶다면 sites-available에서 설정된 호스트별로 설정해주면 되지만, 전체 공통으로 적용하고 싶다면 nginx.conf 파일을 편집해주면 된다.

최근 js를 이용한 jQuery등의 프레임워크들, bootstrap 같은 CSS 프레임워크들이 많이 이용되고 있기 때문에 gzip을 이용하면 사용자가 많은 사이트일 수록 좋은 효과가 있다.


- 브라우저가 Gzip압축을 지원하면 브라우저는 서버에게 Accept-Encoding 이라는 헤더를 통해 `Gzip 지원`을 덧붙여서 `Gzip`으로 응답을 받는다

- 웹서버는 위 요청을 받고 응답헤더에 `content-Encoding`에 `gzip`을 명시하여 보낸다.


## Gzip이 무조건 좋을까

그렇지 않다.

- Gzip을 압축하고 푸는데도 서버와 웹 브라우저의 CPU가 약간 쓰인다.
- 그래서 통상 1~2kb는 압축하지 않는게 좋다
- 압축해서 얻는 효과보다 압축을 푸는 리소스가 더 크다.
- 또한 바이너리 or img 파일은 지집 압축을 해도 효과를 볼 수 없다.
- 웹 성능에서 돔과 더불어 가장 큰 성능 저하의 원인이지만 개선을 위해서는 해상도 변경이나 캐싱을 적용하느게 좋다.

# summary

서버 환경과 네트워크 프로토콜을 막론하고 패킷의 사이즈가 작으면 페이지 로딩시간이 빨라지는건 기본. 또 데이터 사용이 직접 비용으로 연결되는 모바일에서는 패킷 사이즈를 최적화 하는 것이 무어솝다 중요하다.

minify, gzip.. 오래된 얘기지만

`minify`
- 파일 용량 줄이기
- white space 제거하기
- 불필요한 바이트 사이즈 줄이고 필요한 정보만 한줄에 보내기 때문에 사이즈 상당 부분 줄어듬


`gzip`
- 파일의 압축과 압축풀기에 사용되는 소프트웨어
- 대부분 모던 브라우저에서 지원, 서버쪽에서 추가했을 경우 쉽게 압축된 파일을 보내고 풀 수 할 수 있다.
- 브라우저에서  accept-encoding 이라는 요청 헤더 필드를 통해 서버쪽에 알려지면
- 서버쪽에서는 이 accept-encoding 값을 보고 브라우저에서 디코딩 가능한 압축파일을 보낸다.
