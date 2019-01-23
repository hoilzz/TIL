# example

## async

## cancellable-counter

## cart

- root
  1. fork(getAllPropducts)
  2. fork(watchGetProducts)
    - takeEvery(GET_ALL_PRODUCTS, getAllProducts)
  3. fork(watchCheckout)
    1. checkout watch 중. while(true)
      - take(CHECKOUT_REQ)
      - call(checkout)

3-1. checkout task
  - call(api.buyProducts, cart) : 카트에 담긴거 구매?
  - put(success)

2-1. watchGetProducts()
  - takeEvery(GET_ALL_PRODUCTS, getAllProducts)

> takeEvery(pattern, saga, ..args)
> pattern과 일치하는 dispatch된 각 action에 대해 saga 생성하기
> ex
> 

## faq

- 사가 단위?를 어케 나눌까?