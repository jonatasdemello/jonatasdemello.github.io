### Lesson-01 - Iterations

---------------------------------------------------------------------------------------------------

https://app.codility.com/programmers/lessons/1-iterations/

---------------------------------------------------------------------------------------------------

[easy]

# Binary Gap

    Find longest sequence of zeros in binary representation of an integer.

A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

For example,

- number 9 has binary representation 1001 and contains a binary gap of length 2.
- The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3.
- The number 20 has binary representation 10100 and contains one binary gap of length 1.
- The number 15 has binary representation 1111 and has no binary gaps.
- The number 32 has binary representation 100000 and has no binary gaps.

Write a function:

    function solution(N);

that, given a positive integer N, returns the length of its longest binary gap.

The function should return 0 if N doesn't contain a binary gap.

For example,

- given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5.
- Given N = 32 the function should return 0, because N has binary representation '100000' and thus no binary gaps.

Write an efficient algorithm for the following assumptions:

    N is an integer within the range [1..2,147,483,647].

---------------------------------------------------------------------------------------------------

## Solution


**BinaryGap**

Find longest sequence of zeros in binary representation of an integer.

A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

For example,

- number 9 has binary representation 1001 and contains a binary gap of length 2.
- The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3.
- The number 20 has binary representation 10100 and contains one binary gap of length 1.
- The number 15 has binary representation 1111 and has no binary gaps.
- The number 32 has binary representation 100000 and has no binary gaps.

Write a function:

    function solution(N);

that, given a positive integer N, returns the length of its longest binary gap.

The function should return 0 if N doesn't contain a binary gap.

For example,

- given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5.
- Given N = 32 the function should return 0, because N has binary representation '100000' and thus no binary gaps.

Write an efficient algorithm for the following assumptions:

    N is an integer within the range [1..2,147,483,647].

-------------------

## Logical Thinking in Programming

Before starting to write a solution for any problem it is necessary to better understand it first.
Many junior developers or people new to code fail in this step.
The urge to start writing code is strong.
I found the quotes below (don't ask me about the historical accuracy, focus on the idea instead):

> "If I had an hour to solve a problem I’d spend 55 minutes thinking about the problem and 5 minutes thinking about solutions" - Albert Einstein
>
> "Give me six hours to chop down a tree and I will spend the first four sharpening the axe" - Abraham Lincoln
>
> "A problem well defined is a problem half solved" - Dan Martell

Logical thinking involves using systematic reasoning to solve problems efficiently.
In programming, this means applying clear, structured thought processes to debugging, algorithm optimization, and feature design tasks.
The primary methods include deductive reasoning, inductive reasoning, and problem decomposition.

- Deductive Reasoning: Deductive reasoning involves drawing specific conclusions from general premises.
- Inductive Reasoning: Inductive reasoning is the process of forming general conclusions from specific instances or observations.
- Problem Decomposition: Problem decomposition breaks down complex problems into smaller, more manageable parts, making it easier to solve them.

With that in mind, let's take a look at our first problem.

## The Problem/Solution Thinking

Based on the problem description: I will assume the input is "positive integer N",
and that the parameter **N** passed to the **solution(N)** is decimal.
Then in order to find a binary gap in a given number, I need to convert it from decimal to binary.

To understand it and make things more clear, I created the table below.
I like to visualize and look for patterns before writing the code.

Each decimal number has its binary representation and now I can see the '0' gaps.
Some numbers have more than one gap and some have none.

```
+--------+-----------------------+------------+--------+
| Number | Binary Representation | Binary Gap | Result |
+--------+-----------------------+------------+--------+
|      9 |                  1001 | 2          |      2 |
|    529 |            1000010001 | 4 & 3      |      4 |
|     20 |                 10100 | 1          |      1 |
|     15 |                  1111 | 0          |      0 |
|     32 |                100000 | 0          |      0 |
|   1041 |           10000010001 | 5 & 3      |      5 |
+--------+-----------------------+------------+--------+
```

## Write Some Code

Before jumping into the solution, I need to create my code and test files.
So I copied the template files `solution-template.js` and `solution-template.test.js` in the "01-Iterations" folder.

The first file is the code (solution) itself and it was renamed from `solution-template.js` to  `binary-gap.js`:

```js
// binary-gap.js
'use strict';

module.exports = function solution(N) {
  var maxGap = -1;

  return maxGap;
}
```

I will return -1 as an invalid value for now.

The other file is the unit test suite for this problem, which was renamed from `solution-template.test.js` to `binary-gap.test.js`:

```js
// binary-gap.test.js
'use strict';

const solution = require("./binary-gap");

describe('BinaryGap Tests', () => {

  test('given 1 should return 1.', () => {
    expect(solution(1)).toBe(1);
  });

});
```

Now I can start writing unit tests and solution code.

## Adding Unit Tests First

TDD is called Test Driven Development, which means the development is driven by tests.

The process follows a cycle called "Red-Green-Refactor": write a failing test (Red), write just enough code for the test to pass (Green), and then clean up the code while ensuring tests remain green (Refactor). This iterative approach helps create higher-quality, more maintainable code by ensuring every new piece of functionality is built upon a passing test.

Based on the instructions provided in the problem description, I can start adding the test cases.

Feel free to add more, start simple and add more as you go and look for edge cases or potential issues. It is good to also add test cases to check conditions outside the scope or boundaries too.



Start with the requirements from the problem description:

- The number 9 has binary representation 1001 and contains a binary gap of length 2.
- The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3.
- The number 20 has binary representation 10100 and contains one binary gap of length 1.
- The number 15 has binary representation 1111 and has no binary gaps.
- The number 32 has binary representation 100000 and has no binary gaps.
- Given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5.
- Given N = 32 the function should return 0, because N has binary representation '100000' and thus no binary gaps.



The test syntax is pretty straightforward, but in doubt check the [Jest documentation](https://jestjs.io/docs/getting-started).

The problem description does not say anything about errors, so I will assume that an invalid parameter will throw an error.

The first tests will cover boundaries and invalid numbers from this statement in the problem description:



>  N is an integer within the range [1 .. 2,147,483,647].



```js
// binary-gap.test.js
'use strict';

const solution = require("./binary-gap");

describe('BinaryGap Tests', () => {

  // valid input: negative number
  test('Given -1 should throw an error.', () => {
    expect(() => {
      solution(-1);
    }).toThrow();
  });

  // valid input: zero
  test('Given 0 should throw an error.', () => {
    expect(() => {
      solution(0);
    }).toThrow();
  });

  // valid input: big number
  test('Given 2,147,483,648 should throw an error.', () => {
    expect(() => {
      solution(2147483648);
    }).toThrow();
  });

  // valid input boundary: 1
  test('Given 1 [0001] should return 0.', () => {
    expect(solution(1)).toBe(0);
  });

  // valid input boundary: 2,147,483,647
  test('Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.', () => {
    expect(solution(2147483647)).toBe(0);
  });
```



After adding the test cases to `binary-gap.test.js`, run the tests with:

`npm test`

or using the "watch mode" so the tests will run automatically and also using "verbose" to display more information about the test cases being executed:

`npm run test -- --watch --verbose`

And the test result is:

```js
 PASS  00-template/solution-template.test.js
  Template Tests
    √ given -1 should throw an error (9 ms)
    √ given 1 should return 1. (1 ms)

 FAIL  01-Iterations/binary-gap.test.js
  BinaryGap Tests
    × Given -1 should throw an error. (4 ms)
    × Given 0 should throw an error.
    × Given 2,147,483,648 should throw an error.
    × Given 1 [0001] should return 0. (1 ms)
    × Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.

Test Suites: 1 failed, 1 passed, 2 total
Tests:       5 failed, 2 passed, 7 total
Snapshots:   0 total
Time:    0.732 s, estimated 1 s
```

The `solution-template.tests.js` has 1 test suite and 2 unit tests - all passing.

The `binary-gap.tests.js` has 1 test suite and 5 unit tests - all failing.

A total of 2 test suites and 7 unit tests.

With the validations and boundaries in place, I can add more tests using the requirements in the problem description.
Lets check some other numbers. These will be valid input numbers that should return valid output results. For example: 9, 529, 20, 15, 32, 1041.

In the test name, I added the converted binary number inside the backets to make it easier to understand: 9 decimal = [1001] binary.

Like this: 'Given 9 [1001] should return 2.'

Here are the unit tests:

```js
  // valid input boundary: 1
  test('Given 1 [0001] should return 0.', () => {
    expect(solution(1)).toBe(0);
  });

  // valid input boundary: 2,147,483,647
  test('Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.', () => {
    expect(solution(2147483647)).toBe(0);
  });

  // test numbers from the problem description:
  test('Given 9 [1001] should return 2.', () => {
    expect(solution(9)).toBe(2);
  });
  test('Given 529 [0010.0001.0001] should return 4.', () => {
    expect(solution(529)).toBe(4);
  });
  test('Given 20 [0001.0100] should return 1.', () => {
    expect(solution(20)).toBe(1);
  });
  test('Given 15 [1111] should return 0.', () => {
    expect(solution(15)).toBe(0);
  });
  test('Given 32 [0010.0000] should return 0.', () => {
    expect(solution(32)).toBe(0);
  });
  test('Given 1041 [0100.0001.0001] should return 5.', () => {
    expect(solution(1041)).toBe(5);
  });
```

Run the tests again, and some of the tests will fail. This is expected.

I removed part of the results because they are very similar and I will focus on fixing one error at a time.
Here is the test output:

```js
 PASS  00-template/solution-template.test.js
  Template Tests
    √ given -1 should throw an error (10 ms)
    √ given 1 should return 1.

 FAIL  01-Iterations/binary-gap.test.js
  BinaryGap Tests
    × Given -1 should throw an error. (5 ms)
    × Given 0 should throw an error. (1 ms)
    × Given 2,147,483,648 should throw an error. (1 ms)
    × Given 1 [0001] should return 0. (2 ms)
    × Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0. (1 ms)
    × Given 9 [1001] should return 2.
    × Given 529 [0010.0001.0001] should return 4. (1 ms)
    × Given 20 [0001.0100] should return 1.
    × Given 15 [1111] should return 0.
    × Given 32 [0010.0000] should return 0.
    × Given 1041 [0100.0001.0001] should return 5. (1 ms)

... more errors ...

Test Suites: 1 failed, 1 passed, 2 total
Tests:       11 failed, 2 passed, 13 total
Snapshots:   0 total
Time:    0.725 s, estimated 1 s
```

## Write Some Code

Now it is time to start writing some functional code.

Note that I don't have a "main" or "index" as an application entry point calling the **solution(N)** function.
This is intended and if I run `npm start` I will get an error.
I want to test my function in isolation, provide multiple inputs and evaluate the results.
This would be more difficult and time consuming to do without a test framework.

With the tests in place, I can now start writing the code to solve the problem.
I may even go back and add more tests for other uses cases, but this is enough for now. TDD is an incremental approach.

The first thing I usually do is to add some validations to test the input parameters in the **solution(N)** function inside the `binary-gap.js` file.

First, for this statement in the problem description:



>  N is an integer within the range [1 .. 2,147,483,647].



I already have the unit tests, now it is time to write the functional code to address that.

```js
// `binary-gap.js`
'use strict';

module.exports = function solution(N) {
  var maxGap = -1;

  // validations
  if (N < 1 || N > 2147483647) {
    throw new Error("Parameter is invalid!");
  }

  return maxGap;
}
```

Then run the tests again with:

`npm test`

And he result is:

```js
 FAIL  01-Iterations/binary-gap.test.js
  BinaryGap Tests
    √ Given -1 should throw an error. (11 ms)
    √ Given 0 should throw an error. (1 ms)
    √ Given 2,147,483,648 should throw an error. (1 ms)
    × Given 1 [0001] should return 0. (2 ms)
    × Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.
    × Given 9 [1001] should return 2.
    × Given 529 [0010.0001.0001] should return 4. (1 ms)
    × Given 20 [0001.0100] should return 1. (1 ms)
    × Given 15 [1111] should return 0. (1 ms)
    × Given 32 [0010.0000] should return 0. (1 ms)
    × Given 1041 [0100.0001.0001] should return 5. (1 ms)
```

Now I have some progress and the first 3 tests as passing! They check for numbers outside the scope (invalid inputs).

Next, I will start the problem/solution logic.

----

The first thing to consider is that my input number is a decimal number.
I need to convert it to its binary representation.

In JavaScript, the simplest and most common method to convert a decimal number to its binary representation is by using the built-in toString() method with a radix of 2.

See Javascript Number.prototype.toString() reference at [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Number/toString).

```js
// `binary-gap.js`
'use strict';

module.exports = function solution(N) {
  var maxGap = -1;

  // validations
  if (N < 1 || N > 2147483647) {
    throw new Error("Parameter is invalid!");
  }

  // first, convert the number to binary
  bin = N.toString(2);
  console.log(bin);

  return maxGap;
}
```

And run the tests again.

Looking at the test results again, I can plan the next steps.

```js
 FAIL  01-Iterations/binary-gap.test.js
  BinaryGap Tests
    √ Given -1 should throw an error. (11 ms)
    √ Given 0 should throw an error. (1 ms)
    √ Given 2,147,483,648 should throw an error. (1 ms)
    × Given 1 [0001] should return 0. (2 ms)
    × Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.
    × Given 9 [1001] should return 2.
    × Given 529 [0010.0001.0001] should return 4. (1 ms)
    × Given 20 [0001.0100] should return 1. (1 ms)
    × Given 15 [1111] should return 0. (1 ms)
    × Given 32 [0010.0000] should return 0. (1 ms)
    × Given 1041 [0100.0001.0001] should return 5. (1 ms)

  ● BinaryGap Tests › Given 1 [0001] should return 0.

    expect(received).toBe(expected) // Object.is equality

    Expected: 0
    Received: -1

      28 |   // valid input boundary: 1
      29 |   test('Given 1 [0001] should return 0.', () => {
    > 30 |     expect(solution(1)).toBe(0);
     |             ^
      31 |   });
      32 |
      33 |   // valid input boundary: 2,147,483,647

      at Object.toBe (01-Iterations/binary-gap.test.js:30:25)
```

The test results show which tests failed and some other important information:

> BinaryGap Tests › Given 1 [0001] should return 0.

This tells me that:

- **Test Suite:** 'BinaryGap Tests'
- **Unit Test:** 'Given 1 [0001] should return 0.'
- **Expected:** 0
- **Received:** -1
- **test code:** expect(solution(1)).toBe(0);

In summary: the test received the input parameter "1" and expected the result to be "0" but received "-1" instead.

The output will show where the **unit test** failed, not the functional code (there is no code yet!).
So the first thing to do is look at this condition and write the functional code to fix this test.

### Problem Logic

Note that I added the `console.log(bin);` after the conversion.
The reason for that is to see what the result of the decimal to binary conversion is.
This is important because depending on the language or the result returned from the binary conversion function, I may need to remove the trailing zeros (they can be discarded).

| dec | bin    | bytes     |
| --- | ------ | --------- |
| 1   | 1      | 0001      |
| 5   | 101    | 0101      |
| 7   | 111    | 0111      |
| 9   | 1001   | 1001      |
| 32  | 100000 | 0010.0000 |

**Note:**

> Here is one situation where it is OK to do a Google search.
> I usually work with multiple languages and environments (C#, C, C++, Python, JavaScript, PowerShell, T-SQL, TypeScript just to name a few) and there is no way to know all the syntaxes and parameters for all languages and functions.
>
> But there is a difference between asking "how to convert decimal to binary in JavaScript" to "give me the solution to this problem so I can copy it".
> Sometimes in a real work situation it is necessary to just get one solution and apply it, instead of reinventing the wheel and creating your own solution. Viewer discretion is advised.

I will remove the `console.log(bin);` now, because it affects performance.
It is OK to have it while developing/debugging, but it is ideal to remove before shipping the code (when the work is done).

Assuming there are no trailing 0's so that all binary numbers will start with 1 (see table above, column 'bin') and the converted binary number can be accessed as an array, I can use the index/array syntax:

```
  N = 5 (decimal)
  bin = 101 (binary)
then
  bin[0] = 1
  bin[1] = 0
  bin[2] = 1
```

Algorithm:

- convert the decimal number to binary
- iterate over the binary digits counting the 0's

Next, I will iterate over the binary digits and count the 0's.
I added a new variable `zeros = 0` to hold the count of 0's.
After the loop, I need to assign `maxGap = zeros;` because I return `maxGap`.

```js
    let maxGap = -1;
    let zeros = 0;
    // now iterate over the 0's and 1's and count
    for (var x = 0; x < bin.length; x++) {
    if (bin[x] == 0) {
        zeros++;
    }
    }
    maxGap = zeros;
    return maxGap;
```

Run the tests again:

```js
 FAIL  01-Iterations/binary-gap.test.js
  BinaryGap Tests
    √ Given -1 should throw an error. (10 ms)
    √ Given 0 should throw an error.
    √ Given 2,147,483,648 should throw an error.
    √ Given 1 [0001] should return 0. (1 ms)
    √ Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.
    √ Given 9 [1001] should return 2.
    × Given 529 [0010.0001.0001] should return 4. (4 ms)
    × Given 20 [0001.0100] should return 1. (1 ms)
    √ Given 15 [1111] should return 0. (1 ms)
    × Given 32 [0010.0000] should return 0. (2 ms)
    × Given 1041 [0100.0001.0001] should return 5. (1 ms)

  ● BinaryGap Tests › Given 529 [0010.0001.0001] should return 4.
```

This is interesting, the failed tests tell me that the returned value is wrong when
I have more than one gap: 529 [0010.0001.0001] and 20 [0001.0100]
or when there is no 1 closing the last gap [100000].

To fix that I will need to modify my main loop and add some more checks.
I need to check for 1's too (closing gap).

```js
    // now iterate over the 0's and 1's and count
    for (var x = 0; x < bin.length; x++) {
    if (bin[x] == 0) { // means that there is gap
        zeros++;
    }
    if (bin[x] == 1) { // means that the gap ended
        // if the gap ended, check if this is biggest found
        if (zeros > maxGap) {
        maxGap = zeros;
        }
        // reset the zero counter
        zeros = 0;
    }
    }
    return maxGap;
```

Run the tests again:

```js
 PASS  00-template/solution-template.test.js
  Template Tests
    √ given -1 should throw an error (10 ms)
    √ given 1 should return 1.

 PASS  01-Iterations/binary-gap.test.js
  BinaryGap Tests
    √ Given -1 should throw an error. (11 ms)
    √ Given 0 should throw an error. (1 ms)
    √ Given 2,147,483,648 should throw an error.
    √ Given 1 [0001] should return 0. (1 ms)
    √ Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.
    √ Given 9 [1001] should return 2. (1 ms)
    √ Given 529 [0010.0001.0001] should return 4.
    √ Given 20 [0001.0100] should return 1. (1 ms)
    √ Given 15 [1111] should return 0.
    √ Given 32 [0010.0000] should return 0. (1 ms)
    √ Given 1041 [0100.0001.0001] should return 5.

Test Suites: 2 passed, 2 total
Tests:       13 passed, 13 total
Snapshots:   0 total
Time:    0.854 s, estimated 1 s
```

And we have a solution!

Now I can start improving the solution, cleaning up the code, adding more tests.

Just to be sure, I went back to the Codility site and tested my solution there.
The site also show some other unit tests, so I added them to my test suite too.

And ran the tests again.

```js
 PASS  00-template/solution-template.test.js
  Template Tests
    √ given -1 should throw an error (10 ms)
    √ given 1 should return 1. (1 ms)

 PASS  01-Iterations/binary-gap.test.js
  BinaryGap Tests
    √ Given -1 should throw an error. (13 ms)
    √ Given 0 should throw an error. (1 ms)
    √ Given 2,147,483,648 should throw an error. (1 ms)
    √ Given 1 [0001] should return 0.
    √ Given 2147483647 [0111.1111.1111.1111.1111.1111.1111.1111] should return 0.
    √ Given 9 [1001] should return 2.
    √ Given 529 [0010.0001.0001] should return 4. (1 ms)
    √ Given 20 [0001.0100] should return 1.
    √ Given 15 [1111] should return 0.
    √ Given 32 [0010.0000] should return 0.
    √ Given 1041 [0100.0001.0001] should return 5.
    √ Given 64 [0100.0000] should return 0. (1 ms)
    √ Given 132 [1000.0100] should return 4.
    √ Given 133 [1000.0101] should return 4.
    √ Given 5 [0101] should return 1.
    √ Given 6 [0110] should return 0.
    √ Given 9 [1001] should return 2.
    √ Given 11 [1011] should return 1. (1 ms)
    √ Given 16 [0001.0000] should return 0.
    √ Given 19 [0001.0011] should return 2. (1 ms)
    √ Given 42 [0010.1010] should return 1.
    √ Given 328 [0001.0100.1000] should return 2. (1 ms)
    √ Given 1024 [0100.0000.0000] should return 0.
    √ Given 1162 [0100.1000.1010] should return 3.
    √ Given 51712 [0110.0101.0000.0000] should return 2. (1 ms)
    √ Given 561892 [1000.1001.0010.1110.0100] should return 3.
    √ Given 66561 [0001.0000.0100.0000.0001] should return 9.
    √ Given 6291457 [0110.0000.0000.0000.0000.0001] should return 20. (1 ms)
    √ Given 74901729 [0100.0111.0110.1110.1000.1110.0001] should return 4.
    √ Given 805306373 [0011.0000.0000.0000.0000.0000.0000.0101] should return 25.
    √ Given 1376796946 [0101.0010.0001.0000.0100.0001.0001.0010] should return 5.
    √ Given 1073741825 [0100.0000.0000.0000.0000.0000.0000.0001] should return 29. (1 ms)
    √ Given 1610612737 [0110.0000.0000.0000.0000.0000.0000.0001] should return 28.

Test Suites: 2 passed, 2 total
Tests:       35 passed, 35 total
Snapshots:   0 total
Time:    0.882 s, estimated 1 s
Ran all test suites related to changed files
```

### Suggestions

Sometimes, when working on a problem it is better to use **Pseudocode** to think about the algorithm logic, this way I don't have to worry about the syntax or language construction rules.

Something like this:

<pre>
  let maxGap = 0; // max gap found
  let zeros = 0; // zero counter

  // convert input N to bin
  let n = ConvertToBinary(N);

  // example:
  // N = 5 (decimal) => n = 101 (binary)
  // so
  // n[0] = 1
  // n[1] = 0
  // n[2] = 1

  // loop through all binary digits
  for x = 0 to n.length:
    if x == 0 then
      // n[0] = 1 first digit
      skip // do nothing
    end if
    if x > 0 then
      // second digit and on
      // check if is 0
      if n[x] == 0 then // it is a 0 gap
    // increase out counter
    zeros++
      end if
      // save the maxGap number
      maxGap = zeros
    end if
  next x
  return maxGap
</pre>

Then it is easier later to find the correct syntax for the language I am using.
