# sinon - test stub

## .stub

한 번에(`once`) 반환된 함수는 original 함수가 리턴하는 값을 반환해야 한다. 이것을 테스트 하기 위해 우리는 stub을 만든다.

```javascript
it('returns the return value from the original function', function() {
    var callback = sinon.stub().returns(42);
    var proxy = once(callback);

    assert.equals(proxy(), 42);
})
```

### stub.callsFake(fakeFunction)

호출될 때, stub이 제공된 `fakeFunction`을 호출하도록 만든다.