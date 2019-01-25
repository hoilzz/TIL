# example

## async

사가 리스트

1. startup

- 초기 레딧 데이터 받아오기

2. nextRedditChange

- 셀렉트 박스에 바뀐 거 기준으로 데이터 재요청하기

3. invalidateReddit

- startup
  - fork(fetchPosts, reddit)
    - fetchPosts
      - put(action.requestPosts)
      - posts = call(fetchPostApi)
      - put(action.requestPost(reddit, posts))
- nextRedditChange
  - fork(fetchPosts, reddit)
- invalidateReddit

### 배운거

- 초기 root에서 3가지 task를 all로 돌린게 아닌(병렬 처리가 아닌) yield fork, yield fork 로 진행

  - 그 이유는 1번 startup이 무조건 첫번째 실행되어야 하기 때문인듯.
  - 초기 데이터 받아오는 사가이기 때문에..

- 

- 그리고 최대한 task를 잘개 쪼개야 재사용하기 쉬워짐.
  - 일단은 막 짜고 그 다음에 task들을 잘개 쪼개자..

## cancellable-counter

## cart

- root
  1. fork(getAllPropducts)
  - products = call(api.getProducts)
  - put(receiveProducts(products))
  2. fork(watchGetProducts)
  - takeEvery(GET_ALL_PRODUCTS, getAllProducts)
  3. fork(watchCheckout)
  1. checkout watch 중. while(true)
     1. take(CHECKOUT_REQ)
     2. call(checkout)

3-1. checkout task

- call(api.buyProducts, cart) : 카트에 담긴거 구매?
- put(success)

2-1. watchGetProducts()

- takeEvery(GET_ALL_PRODUCTS, getAllProducts)

> takeEvery(pattern, saga, ..args)
> pattern과 일치하는 dispatch된 각 action에 대해 saga 생성하기

## faq

- 사가 단위?를 어케 나눌까?
