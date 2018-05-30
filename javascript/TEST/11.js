const { sum, subtract } = require('./math');

test('sum adds numbers', () => {
  const result = sum(3, 7);
  const expected = 11;
  expect(result).toBe(expected);
})

function test(title, callback) {
  try {
    callback()
    console.log(`- [x] ${title}`);
  } catch (error) {
    console.error(`X ${title}`);
    console.error(error);
  }
}

function expect(actual) {
  return {
    toBe(expected) {
      if (actual !== expected) {
        throw new Error(`${actual} is not equal to ${expected}`);
      }
    },
  }
}