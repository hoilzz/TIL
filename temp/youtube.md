# youtube

API KEY : **AIzaSyBxTx0SlIZShZWXjgU4Ry5tBLNh2fhou4c**

- 비공개 사용자 데이터에 액세스하는 모든 Youtube Data APi 요청의 경우 애플리케이션에서 **OAuth.2.0 토큰을 함께 전송해야 한다.**
- 애플리케이션은 클라 ID를 전송하며 **토큰을 가져오기 위해 클라 비번을 전송할 수 있다**.
- HOW TO
  - 웹 브라우저는 네트워크를 통해 웹 어플리케이션에 액세스 가능
    - JS를 사용하는 애플리케이션은 **인증된 JS 출처 지정**.
    - 출처는 애플리케이션의 API 요청이 시작될 수 있는 도메인을 표시



- API 키: OAuth 2.0 토큰을 제공하지 않는 요청은 API 키를 전송해야 합니다. 키는 프로젝트를 식별하고 API 액세스, 할당량, 보고서를 제공합니다.

- 필요한 키 유형이 없다면 새 키 만들기를 선택한 후 적절한 키 유형을 선택하여 API 키를 만듭니다. 그런 다음 키 유형에 필요한 추가 데이터를 입력합니다.
- 애플리케이션이 클라이언트(예: 웹브라우저)에서 실행되는 경우 브라우저 키를 사용합니다. 키가 인증되지 않은 사이트에서 사용되지 않도록 하려면 관리하는 도메인에서 리퍼러만 허용합니다.



## Data API

데이터 API를 사용하면 유튜브에서 일반적으로 실행하는 기능을 웹사이트 또는 애플리케이션에 통합 가능
- API를 사용하여 검색할 수 있는 다양한 유형의 리소스 확인 가능
- API는 이러한 여러 개의 리소스를 삽입하거나 업데이트 또는 삭제하는 메서드도 지원

## API 호출
1. 모든 요청은 `API키`를 지정하거나 `OAuth 2.0토큰`을 제공해야 한다
  - API키는 APIs console에서 프로젝트의 **API Access**창에 있다. `AIzaSyBxTx0SlIZShZWXjgU4Ry5tBLNh2fhou4c`

2. 모든 삽입, 업데이트 및 삭제 요청시 반드시 `인증 토큰` 전송해야 한다.

3. API는 OAuth 2.0 인증 프로토콜을 지원한다. OAuth 2.0토큰은 다음 방법 중 하나로 제공 가능
  - **`access_token` 쿼리 매개 변수 사용, `?access_token=oauth2-token`**
  - HTTP `Authorization` 헤더 사용 `Authorization: Bearer` `oauth2-token`

### search

검색 결과에는 API 요청에 지정된 검색 매개변수와 일치하는 유튜브 동영상, 채널 또는 재생목록의 정보가 포함되어 있습니다. 검색 결과는 동영상과 같이 고유하게 식별할 수 있는 리소스를 보여준다. 하지만 자체적으로는 영구적인 데이터를 갖지 않는다.

- `https://www.googleapis.com/youtube/v3의 상대 URI`
- 메서드 : list
- HTTP : get
- 설명  : API 요청에 지정된 쿼리 매개변수와 일치하는 검색 결과의 모음을 반환. 기본적으로 검색 결과의 집합은 쿼리 매개 변수와 일치하는 비디오, 채널 플레이리스트 리소스를 식별하지만 특정 유형의 리소스만 검색하도록 쿼리를 구성할 수 있다.

## gapi.client.youtube unknown property

1. 요청인증?
  - auth.js 스크립트는 API 액세스를 제공
  - 사용자 요청 인증하기 위해 JS용 구글 API 클라 라이브러리 사용하는 방법 보여준다.
  - 이 페이지 이후에 나오는 모든 샘플은 이 스크립트를 사용하여 요청 인증
  - 인증이 필요하지 않은 요청에는 `OAuth 2.0` 사용하지 않고 `key` 쿼리 매개변수를 사용하여 API 키를 지정


## standard Query Parameter
다음 쿼리 파라미터는 모든 자원과 메서드에서 이용된다. 모든 유튜브 데이터 API에 적용하는 쿼리 파라미터는 테이블 아래 보여진다

**노트** (on API keys and auth tokens)
1. `key` parameter는 모든 요청마다 필요하다. **만약 너가 OAuth 2.0 token을 요청마다 제공하지 않으면**
2. `authorization` token을 모든 요청마다 보내야한다. `OAuth 2.0`은 선호되는 authorization protocol이다.
3. OAuth 2.0 token을 2가지 방식으로 요청마다 제공할 수 있다.
  1. `access_token`을 쿼리 파라미터에 사용하는것 : ?access_token=oauth2-token
