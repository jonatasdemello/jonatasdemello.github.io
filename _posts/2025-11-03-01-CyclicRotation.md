### Lesson-02 - Arrays

---------------------------------------------------------------------------------------------------

https://app.codility.com/programmers/lessons/2-arrays/

---------------------------------------------------------------------------------------------------

[easy]

# Cyclic Rotation

    Given the problem description:

Rotate an array to the right by a given number of steps.

An array A consisting of N integers is given.
Rotation of the array means that each element is shifted right by one index, and the last element of the array is moved to the first place.

For example, the rotation of array A = [3, 8, 9, 7, 6] is [6, 3, 8, 9, 7] (elements are shifted right by one index and 6 is moved to the first place).

The goal is to rotate array A K times; that is, each element of A will be shifted to the right K times.

Write a function:

    function solution(A, K);

that, given an array A consisting of N integers and an integer K, returns the array A rotated K times.

For example, given:

    A = [3, 8, 9, 7, 6]
    K = 3
    the function should return [9, 7, 6, 3, 8].

Three rotations were made:

    [3, 8, 9, 7, 6] -> [6, 3, 8, 9, 7]
    [6, 3, 8, 9, 7] -> [7, 6, 3, 8, 9]
    [7, 6, 3, 8, 9] -> [9, 7, 6, 3, 8]

For another example, given:

    A = [0, 0, 0]
    K = 1
    the function should return [0, 0, 0]

Given

    A = [1, 2, 3, 4]
    K = 4
    the function should return [1, 2, 3, 4]

Assume that:

    N and K are integers within the range [0..100];
    each element of array A is an integer within the range [−1,000..1,000].

In your solution, focus on correctness.
The performance of your solution will not be the focus of the assessment.

-----

## Problem Analysis

I will start with the boundaries test, from the problem description:

    N and K are integers within the range [0..100];
    each element of array A is an integer within the range [-1,000..1,000].

I will start a new test case and test K (number or rotations) first. K should be between 0 and 100. Next test is N (number of elements in the array) and because an array cannot have a negative number of elements, I can skip this test. So I will test an array with more than 100 elements.

The following test is to check if each element of the array is within the range -1k..1k. In order to do that, I will follow a standard practice in Unit Test: the Arrange, Act and Assert (AAA) Pattern. This means that the unit test contain 3 parts:

- Arrange: setup and prepare things needed by the test. Create objects, assign values or set expectations.

- Act: invoke the method being tested.

- Assert: verify the results and check if the expectations were met.

```js
// cyclic-rotation.js

  // N and K are integers within the range [0..100];
  test('N and K are integers within the range [0..100];', () => {

    // K: rotations = less than 0 or greater than 100
    expect(() => {
      solution(new Array(1), -1)
    }).toThrow("Parameter K is invalid!");

    expect(() => {
      solution(new Array(1), 101)
    }).toThrow("Parameter K is invalid!");

    // N: number of elements in A[] = less than 0 or greater than 100
    // an array cannot have less than 0 elements, so we skip that test
    expect(() => {
      solution(new Array(150), 5)
    }).toThrow();
  });

  // each element of array A is an integer within the range [−1,000..1,000].
  test('each element of array A is an integer within the range [-1,000..1,000].', () => {
    // arrange
    const N = 5;
    const K = 3;
    const A = [];
    // values added are A[0, 500, 1000, 1500, 2000]
    for (let i = 0; i < N; i++) {
      A.push(i * 500);
    }

    // act & assert
    expect(() => {
      solution(A, K)
    }).toThrow();

  });
```

With the validations and boundaries in place, I can add more unit tests using the requirements in the problem description.

The next test will be to test one valid input array and the correct result expected.

I can start with a basic rotation:

    input: A = [1, 2, 3]
    rotation: K = 1
    output: A = [2, 3, 1]

But I like to use the same from the problem description:

*"Given an array A consisting of N integers and an integer K, returns the array A rotated K times."*

    input:  A = [3, 8, 9, 7, 6]
    rotation:  K = 3
    output: A = [9, 7, 6, 3, 8]

In this test, I will need to provide the input Array, the number of rotations K and the expected result Array to compare.

The good thing here is that the Jest framework offers this method from it's [matchers](https://jestjs.io/docs/using-matchers).

- toEqual(): This matcher performs a deep comparison, checking if both arrays have the same elements in the same order. It works for arrays of primitives and objects.

Since my arrays only contain integers, this should work. I could chain the calls to make the code more short, but for now I will keep it separated so I can `console.log` the results to make sure it is working. If I didn't have a method to compare the arrays, I would need to loop/iterate to both and compare the values.

Here is the Unit Test:

```js
  // test case to rotate A[1,2,3,4,5] K=2 return should be A[4,5,1,2,3]
  test('rotate A[1,2,3,4,5] with K=2 should return A[4,5,1,2,3]', () => {
    // arrange
    const A = [1, 2, 3, 4, 5];
    const K = 2;
    const expected = [4, 5, 1, 2, 3];

    // act
    const result = solution(A, K);

    // assert
    expect(result).toEqual(expected);
  });
```

I can add more tests. One nice feature of the Jest test framework is the possibility to send a list (or table, or array) of different test data to the same test function - this is useful when we want to use the same Unit Test to check different sets of data.

In the example bellow I am using [test.each](https://jestjs.io/docs/api#testeachtablename-fn-timeout) to keep duplicating the same unit test with different data sets. I also merged the test and expect in the same statement: `expect(solution(A, K)).toEqual(expected);`.

```js
  test.each([
    [[1, 2, 3, 4, 5], 2, [4, 5, 1, 2, 3]],
    [[1, 2, 3, 4, 5], 1, [5, 1, 2, 3, 4]],
    [[1, 2, 3, 4, 5], 3, [3, 4, 5, 1, 2]],
  ])('array: %s and K: %i => %s', (A, K, expected) => {
    // each parameter goes into the test function: A, K, expected
    expect(solution(A, K)).toEqual(expected);
  });
```

and run the tests

```js
 FAIL  02-Arrays/cyclic-rotation.test.js
  CyclicRotation Tests
    × N and K are integers within the range [0..100]; (6 ms)
    × each element of array A is an integer within the range [-1,000..1,000]. (1 ms)
    × rotate A[1,2,3,4,5] with K=2 should return A[4,5,1,2,3] (3 ms)
    × array: [ 1, 2, 3, 4, 5 ] and K: 2 => [ 4, 5, 1, 2, 3 ]
    × array: [ 1, 2, 3, 4, 5 ] and K: 1 => [ 5, 1, 2, 3, 4 ] (1 ms)
    × array: [ 1, 2, 3, 4, 5 ] and K: 3 => [ 3, 4, 5, 1, 2 ] (1 ms)

Test Suites: 1 failed, 1 total
Tests:       6 failed, 6 total
Snapshots:   0 total
Time:    0.938 s, estimated 1 s
```

So the next step is to implement the validations.

```js
    // k: integer representing number of rotations;
    if (K < 1 || K > 100) {
    throw new Error("Parameter K is invalid!");
    }

    // N: number of elements in A[];
    let N = A.length;
    if (N < 0 || N > 100) {
    throw new Error("Parameter N is invalid!");
    }

    // each element of array A is an integer within the range [-1,000..1,000].
    for (let i = 0; i < N; i++) {
    if (A[i] < -1000 || A[i] > 1000) {
        throw new Error("Element A[" + i + "] is invalid!");
    }
    }
```

and run the tests again

```js
 FAIL  02-Arrays/cyclic-rotation.test.js
  CyclicRotation Tests
    √ N and K are integers within the range [0..100]; (11 ms)
    √ each element of array A is an integer within the range [-1,000..1,000]. (1 ms)
    × rotate A[1,2,3,4,5] with K=2 should return A[4,5,1,2,3] (6 ms)
    × array: [ 1, 2, 3, 4, 5 ] and K: 2 => [ 4, 5, 1, 2, 3 ] (1 ms)
    × array: [ 1, 2, 3, 4, 5 ] and K: 1 => [ 5, 1, 2, 3, 4 ] (1 ms)
    × array: [ 1, 2, 3, 4, 5 ] and K: 3 => [ 3, 4, 5, 1, 2 ]

Test Suites: 1 failed, 1 total
Tests:       4 failed, 2 passed, 6 total
Snapshots:   0 total
Time:    0.901 s, estimated 1 s
```

the failing tests now are for the actual solution array - which I have not implemented anything yet.

### Solution 1

I have to start thinking about the problem and how to find a solution.
The problem description says:

    Rotate an array to the right by a given number of steps.
    Rotation of the array means that each element is shifted right by one index, and the last element of the array is moved to the first place.

So if I rotate the array by 1 step, the last element is removed and added to the beginning of the array.
To do that in JavaScript I looked at the Array methods and saw that I can use pop() and unshift():

- The pop() method of Array instances removes the last element from an array and returns that element. This method changes the length of the array.
- The unshift() method of Array instances adds the specified elements to the beginning of an array and returns the new length of the array.

OK, so if I want to do it K times, here is the code I added to my `cyclic-rotation.js` file:

```js
// cyclic-rotation.js

    for (let i = 0; i < K; i++) {
    let item = A.pop();
    A.unshift(item);
    }
```

and run the tests again:

```js
 PASS  02-Arrays/cyclic-rotation.test.js
  CyclicRotation Tests
    √ N and K are integers within the range [0..100]; (12 ms)
    √ each element of array A is an integer within the range [-1,000..1,000]. (1 ms)
    √ rotate A[1,2,3,4,5] with K=2 should return A[4,5,1,2,3] (1 ms)
    √ array: [ 1, 2, 3, 4, 5 ] and K: 2 => [ 4, 5, 1, 2, 3 ] (1 ms)
    √ array: [ 1, 2, 3, 4, 5 ] and K: 1 => [ 5, 1, 2, 3, 4 ]
    √ array: [ 1, 2, 3, 4, 5 ] and K: 3 => [ 3, 4, 5, 1, 2 ]

Test Suites: 1 passed, 1 total
Tests:       6 passed, 6 total
Snapshots:   0 total
Time:    0.746 s, estimated 1 s
```

Nice! all my tests are passing now.

**Note:** this is a solution that match the criteria in the problem description but it is not an optimized solution yet and this is fine. First I solve the problem, then I iterate over it trying to find ways to optimize it (use less memory, space or computing time). Sometimes this is not necessary - for example when the code is not used very often or something needs to be deployed fast to fix a bug. And sometimes there are spots where memory and processing time are really important.

In order to find a better solution, lets look at what happens in each iteration and draw some conclusions.

### Problem Exploration

For example, given:

    A = [3, 8, 9, 7, 6]
    K = 3
    the function should return [9, 7, 6, 3, 8]

Step by step:

```js
Rotation 1 => [3, 8, 9, 7, 6] -> [6, 3, 8, 9, 7]
Rotation 2 => [6, 3, 8, 9, 7] -> [7, 6, 3, 8, 9]
Rotation 3 => [7, 6, 3, 8, 9] -> [9, 7, 6, 3, 8]

or

K = 3 rotations
Initial Arr=> [3, 8, 9, 7, 6]
Rotation 1 => [6, 3, 8, 9, 7]
Rotation 2 => [7, 6, 3, 8, 9]
Rotation 3 => [9, 7, 6, 3, 8]

idx  0  1  2  3  4
A = [3, 8, 9, 7, 6]
O = [9, 7, 6, 3, 8]
K=3  |________^
```

I can draw some conclusions: given K (rotation), if K <= A.length, then K is the new index of the first element. Item 3 was at position 0, after 3 rotations it was moved to position 3 (remember indexes in JavaScript arrays start with 0)

```js
K = 3
idx  0  1  2  3  4
A = [3, 8, 9, 7, 6]
O = [9, 7, 6, 3, 8]
     |________^
```

This will be true only when K <= A.length. But what happens if K > A.length?

Looks like it goes back to 0 index and start again...

```js
----------------------------------------
K: 1 A: [ 3, 8, 9, 7, 6 ] A.length: 5 (K % A.length): 1
i: 1 A: [ 6, 3, 8, 9, 7 ]
----------------------------------------
K: 6 A: [ 3, 8, 9, 7, 6 ] A.length: 5 (K % A.length): 1
i: 1 A: [ 6, 3, 8, 9, 7 ]
i: 2 A: [ 7, 6, 3, 8, 9 ]
i: 3 A: [ 9, 7, 6, 3, 8 ]
i: 4 A: [ 8, 9, 7, 6, 3 ]
i: 5 A: [ 3, 8, 9, 7, 6 ]
i: 6 A: [ 6, 3, 8, 9, 7 ]
```

If A.length = 5, both K=1 and K=6 produce the same result.
This tells me that I can use the remainder of a division to reduce the number or rotations - why do 6 rotations if I can do just 1 and get the same result?

So if K > A.length, then use (K MOD A.length)

       MOD: is the "modulus" (the remainder of a division)

The first improvement I can do is:

```js
    let N = A.length;
    // if K > N, we can reduce the number of rotations
    if (K > N) {
    K = K % N;
    }
    for (let i = 0; i < K; i++) {
    let item = A.pop();
    A.unshift(item);
    }
```

And run the tests again. Tests pass! This is the beauty of TDD and Unit Tests - I can make changes to my code and see it still returns the correct results.
If I made a breaking change or introduced any bugs, the tests will show me.
If you understand this then my job is done!

I could stop here because my requirement says: "N and K are integers within the range [0..100];" which means the biggest array I may have will contain 100 items.
If the requirements were different and I could have thousands or millions or items, improving this would be a must.

Another thing to consider is memory usage. In some languages array sizes are fixed (immutable) which means that an operation to resize (remove or add elements) will return a new array in memory and the old one must be released of freed by the garbage collector.
For example if I have an array with 100 integers and each integer use 8 bytes of memory, my array takes 800 bytes of memory.
This is not much, but if I do that operation 100x twice (one for pop and another for unshift) that is 800 x 200 = 160,000 bytes or 160k (ish).
Now if my array has 10,000 integers: x8 bytes each = 80,000 bytes x200 = 16,000,000 or 16 Mbytes of space (even if temporary).
Many times this type of optimization is not relevant, but there are times when the application is slow or the site is down and you have no clue why.
Or when working with limited resources such as IoT devices where every byte counts!

### Further Exploration

What if instead of modifying the array every step we could calculate the final state and then split the array in a way that matches the expected result?

Let's take a look in this particular case:

    A = [1, 2, 3, 4, 5]
    K = 3
    the function should return [3, 4, 5, 1, 2]

For K = 3 rotations, the array can be split into: [1, 2] and [3, 4, 5]

And then merged again as: [3, 4, 5] + [1, 2]

```js
K: 3
A: [ 1, 2, 3, 4, 5 ]
A.length: 5
R = K % A.length: 3  => split point
result [3, 4, 5, 1, 2]

     0  1  2  3  4  = index (start at 0)
A: [ 1, 2, 3, 4, 5 ]

split at 2 (R - 1)
   [1, 2] + [3, 4, 5]
flip
   [3, 4, 5] + [1, 2]
```

if K=3 then split the array at position (K-1) = 2 (remember that array index start at 0)

Split point R is A[2] : [1, 2] + [3, 4, 5]

Flip and join: [3, 4, 5] + [1, 2]

R is the "rotation point".

```js
// if K is bigger than the array size, the use the remainder
if (K > A.length) {
    K = K % A.length;
}

// calculate where to split
let R = A.length - K; // from end the until the split point

// split the array:
let arrLeft = A.slice(0, R); // from start to R
let arrRight = A.slice(R, A.length); // from R to end

// merge new array: R .. L
let result = arrRight.concat(arrLeft);
return result;
```

**Document** about Arrays from the [MDN documentation site](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/slice):

- The **`slice()`** method of [`Array`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array) instances returns a [shallow copy](https://developer.mozilla.org/en-US/docs/Glossary/Shallow_copy) of a portion of an array into a new array object selected from `start` to `end` (`end` not included) where `start` and `end` represent the index of items in that array. The original array will not be modified.

```js
const animals = ["ant", "bison", "camel", "duck", "elephant"];
console.log(animals.slice(2, 4));
// Expected output: Array ["camel", "duck"]
```

- The **`concat()`** method of [`Array`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array) instances is used to merge two or more arrays. This method does not change the existing arrays, but instead returns a new array.

```js
const array1 = ["a", "b", "c"];
const array2 = ["d", "e", "f"];
const array3 = array1.concat(array2);
// Expected output: Array ["a", "b", "c", "d", "e", "f"]
```

Time complexity: O(N) Where n is the number of elements in the input array nums. This is because we are iterating through the array twice, once to copy the elements to a new array and once to update the original array with the rotated elements.

Space complexity: O(N) We are creating a copy of the input array nums with the same size, which requires additional space.

### Extras

One thing to keep in mind is that there is always a different way to solve the same problem, so here it is.

Since the array rotation does not change the array size, another approach is to just reorganize the items to their new location in a new array of the same size. This is much more efficient in terms of space and processing.

The idea is to iterate over the array and set each item in the new array and position, calculating the new index of that element.

The new position is the current position (i) + the number of rotations (K), but it is necessary to use the MOD because if it passes the number of elements, it need to start at 0 again.

It is easy to see bellow

```js
K = 3
N = A.length = 5
========================================
i = 0 mod 5 =  0
i = 1 mod 5 =  1
i = 2 mod 5 =  2
i = 3 mod 5 =  3
i = 4 mod 5 =  4
i = 5 mod 5 =  0
i = 6 mod 5 =  1
i = 7 mod 5 =  2
i = 8 mod 5 =  3
i = 9 mod 5 =  4
i = 10 mod 5 =  0
========================================
(i = 0 + K = 3) mod 5 =>  3
(i = 1 + K = 3) mod 5 =>  4
(i = 2 + K = 3) mod 5 =>  0
(i = 3 + K = 3) mod 5 =>  1
(i = 4 + K = 3) mod 5 =>  2
(i = 5 + K = 3) mod 5 =>  3
(i = 6 + K = 3) mod 5 =>  4
(i = 7 + K = 3) mod 5 =>  0
(i = 8 + K = 3) mod 5 =>  1
(i = 9 + K = 3) mod 5 =>  2
(i = 10 + K = 3) mod 5 =>  3
========================================
```

Here is the code:

```js
    // rotate the array
    let N = A.length;
    for (let i = 0; i < N; i++) {
    let newIndex = (i + K) % N;
    result[newIndex] = A[i];
    }
    return result;
```

run the tests again

```js
 PASS  02-Arrays/cyclic-rotation.test.js
  CyclicRotation Tests
    √ N and K are integers within the range [0..100]; (16 ms)
    √ each element of array A is an integer within the range [-1,000..1,000]. (2 ms)
    √ rotate A[1,2,3,4,5] with K=2 should return A[4,5,1,2,3] (2 ms)
    √ array: [ 1, 2, 3, 4, 5 ] and K: 2 => [ 4, 5, 1, 2, 3 ] (1 ms)
    √ array: [ 1, 2, 3, 4, 5 ] and K: 1 => [ 5, 1, 2, 3, 4 ]
    √ array: [ 1, 2, 3, 4, 5 ] and K: 3 => [ 3, 4, 5, 1, 2 ] (1 ms)

Test Suites: 1 passed, 1 total
Tests:       6 passed, 6 total
Snapshots:   0 total
Time:    0.713 s, estimated 1 s
```
