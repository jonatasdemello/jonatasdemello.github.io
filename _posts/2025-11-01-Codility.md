# Codility Lessons Using TDD

The goal of this project is to show how to solve coding problems using [TDD - Test Driven Development](https://martinfowler.com/bliki/TestDrivenDevelopment.html).



In the process of learning or during a coding interview, the process (how) is much more important than the result itself.
If I only needed a solution I could simply Google it or use AI.
Your final solution may not even be complete, but through multiple iterations it can always be improved.
There are many ways to solve a problem as you will see if you look for solutions on the Internet.
In a real world scenario, the solution may not be easily available, and some exploration,  thinking and refactoring may be necessary.

I will take a step-by-step approach showing the steps that any interviewer would like to see, providing explanations along the way.
In order to solve any problem, you need to understand it first. Then take gradual iterations, sometimes by trial and error, until a solution is achieved.
This is how things work in a company or the real world.

For the purpose of this exercise, I will use JavaScript since it is one of the most popular languages and requires less setup and tools.
Maybe later I will expand it to other languages like C# or Python.
I like to do this exercise to learn other languages or understand how it works.

I will use the Test Driven Development (TDD) approach, writing the tests first then the code.
This allows for more experimentation and helps with correctness.
The Codility tool will generate a suite of tests to validate the solution, but I can start with the information provided in the problem description.
Codility also has a timer, which I don't like - so running it locally can be less stressful.

## Lessons

For this I will use the [Codility Developer Training](https://app.codility.com/programmers/) site lessons.
Please go ahead visit the site, create an account there and start exploring the lessons.

Each problem description will be copied here to make it easier to follow.

## Setup

I assume you have a computer and access to the Internet. A Windows, Linux or MacOS machine and some familiarity with the console (command line or terminal).

### Tools

First, install the development tools. If you don't have it, please install:

- Node.JS (any LTS version is good).
- Visual Studio Code (or any other IDE that you like, even Notepad++ will do).

I decided to use Node.JS and JavaScript so it can run on Mac, Windows or Linux.
Also, it can run on "watch mode" re-running tests automatically after any file changed.

### Project

Next, I create a new project and install [Jest](https://jestjs.io/) to run the tests
(you can use Mocha or Jasmine if you like).
Open the console or terminal, create a new folder for the project and then type (inside the project folder):

`npm init --yes`

`npm install --save-dev jest`

Then modify the `package.json` file to run the tests:

```js
"scripts": {
    "test": "jest"
  },
```

Then you can run the tests with:

`npm test`

To run in "watch mode":

`npm run test -- --watch`

Or to show more information:

`npm run test -- --verbose`

Next, create sub-folders, one for each lesson (to make it easy to find and keep it organized):

```bash
mkdir 01-Iterations
mkdir 02-Arrays
mkdir 03-Time-Complexity
mkdir 04-Counting-Elements
mkdir 05-Prefix-Sums
mkdir 06-Sorting
mkdir 07-Stacks-and-Queues
mkdir 08-Leader
mkdir 09-Maximum-Slice-Problem
mkdir 10-Prime-and-Composite-Numbers
mkdir 11-Sieve-of-Eratosthenes
mkdir 12-Euclidean-Algorithm
mkdir 13-Fibonacci-Nnumbers
mkdir 14-Binary-Search-Algorithm
mkdir 15-Caterpillar-Method
mkdir 16-Greedy-Algorithms
mkdir 17-Dynamic-Programming
```

Now I am ready to starting solving some problems using TDD.
Here I will start with the first lesson (warm-up), but the setup process will be the same for all.

### Template

Since I will be working on multiple problems and they all start the same way,
I will create a template so I can duplicate it for each new problem and start from there.

The first file is the solution code and it is called **"solution-template.js"**:

```js
// solution-template.js
'use strict';

module.exports = function solution(N) {
  // your code here
  return 1;
}
```

The other file is the test suite for this problem called **"solution-template.test.js"**:

```js
// solution-template.test.js
'use strict';

const solution = require("./solution-template");

describe('solution-template tests', () => {

  test('given 1 should return 1.', () => {
    expect(solution(X)).toBe(Y);
  });

});
```

And with that I can just run `npm test` and see the results:

```
PS > npm test

> codility-javascript@1.0.0 test
> jest

 PASS  00-template/solution-template.test.js
  Template Tests
    √ given 1 should return 1. (2 ms)

Test Suites: 1 passed, 1 total
Tests:       1 passed, 1 total
Snapshots:   0 total
Time:    0.492 s, estimated 1 s
Ran all test suites.
```

Here I have

- one Test Suite defined with "describe()" and

- one Unit Test defined with "test()".



## The Problems

The problems were copied from the  [Codility](https://app.codility.com/programmers/lessons/1-iterations/binary_gap/) web site. I recommend you go there create an account and try to solve the problems there too.


For detailed step-by-step approach, analysis and solution to each problem, check the links bellow:

-------------------

### Solutions

- Lesson-01 - Iterations
  - [BinaryGap](./01-Iterations/01-BinaryGap.md)
- Lesson-02 - Arrays
  - [CyclicRotation](./02-Arrays/01-CyclicRotation.md)
  - [OddOccurrencesInArray](./02-Arrays/02-OddOccurrencesInArray.md)
- Lesson-03 - Time Complexity
  - [FrogJump](./03-Time-Complexity/01-FrogJmp.md)
  - [PermMissingElem](./03-Time-Complexity/02-PermMissingElem.md)
  - [TapeEquilibrium](./03-Time-Complexity/03-TapeEquilibrium.md)
- Lesson-04 - Counting Elements
  - [FrogRiverOne](./04-Counting-Elements/01-FrogRiverOne.md)
  - [PermCheck](./04-Counting-Elements/02-PermCheck.md)
  - [MaxCounters](./04-Counting-Elements/03-MaxCounters.md)
  - [MissingInteger](./04-Counting-Elements/04-MissingInteger.md)
- Lesson-05 - Prefix Sums
  - [PassingCars](./05-Prefix-Sums/01-PassingCars.md)
  - [CountDiv](./05-Prefix-Sums/02-CountDiv.md)
  - [GenomicRangeQuery](./05-Prefix-Sums/03-GenomicRangeQuery.md)
  - [MinAvgTwoSlice](./05-Prefix-Sums/04-MinAvgTwoSlice.md)
- Lesson-06 - Sorting
  - [Distinct](./06-Sorting/01-Distinct.md)
  - [MaxProductOfThree](./06-Sorting/02-MaxProductOfThree.md)
  - [Triangle](./06-Sorting/03-Triangle.md)
  - [NumberOfDiscIntersections](./06-Sorting/04-NumberOfDiscIntersections.md)
- Lesson-07 - Stacks and Queues
  - [Brackets](./07-Stacks-and-Queues/01-Brackets.md)
  - [Fish](./07-Stacks-and-Queues/02-Fish.md)
  - [Nesting](./07-Stacks-and-Queues/03-Nesting.md)
  - [StoneWall](./07-Stacks-and-Queues/04-StoneWall.md)
- Lesson-08 - Leader
  - [Dominator](./08-Leader/01-Dominator.md)
  - [EquiLeader](./08-Leader/02-EquiLeader.md)
- Lesson-09 - Maximum slice problem
  - [MaxProfit](./09-Maximum-Slice-Problem/01-MaxProfit.md)
  - [MaxSliceSum](./09-Maximum-Slice-Problem/02-MaxSliceSum.md)
  - [MaxDoubleSliceSum](./09-Maximum-Slice-Problem/03-MaxDoubleSliceSum.md)
- Lesson-10 - Prime and composite numbers
  - [CountFactors](./10-Prime-and-Composite-Numbers/01-CountFactors.md)
  - [MinPerimeterRectangle](./10-Prime-and-Composite-Numbers/02-MinPerimeterRectangle.md)
  - [Flags](./10-Prime-and-Composite-Numbers/03-Flags.md)
  - [Peaks](./10-Prime-and-Composite-Numbers/04-Peaks.md)
- Lesson-11 - Sieve of Eratosthenes
  - [CountNonDivisible](./11-Sieve-of-Eratosthenes/02-CountNonDivisible.md)
  - [CountSemiprimes](./11-Sieve-of-Eratosthenes/03-CountSemiprimes.md)
- Lesson-12 - Euclidean algorithm
  - [ChocolatesByNumbers](./12-Euclidean-Algorithm/01-ChocolatesByNumbers.md)
  - [CommonPrimeDivisors](./12-Euclidean-Algorithm/02-CommonPrimeDivisors.md)
- Lesson-13 - Fibonacci numbers
  - [FibFrog](./13-Fibonacci-Nnumbers/01-FibFrog.md)
  - [Ladder](./13-Fibonacci-Nnumbers/02-Ladder.md)
- Lesson-14 - Binary search algorithm
  - [MinMaxDivision](./14-Binary-Search-Algorithm/01-MinMaxDivision.md)
  - [NailingPlanks](./14-Binary-Search-Algorithm/02-NailingPlanks.md)
- Lesson-15 - Caterpillar method
  - [AbsDistinct](./15-Caterpillar-Method/01-AbsDistinct.md)
  - [CountDistinctSlices](./15-Caterpillar-Method/02-CountDistinctSlices.md)
  - [CountTriangles](./15-Caterpillar-Method/03-CountTriangles.md)
  - [MinAbsSumOfTwo](./15-Caterpillar-Method/04-MinAbsSumOfTwo.md)
- Lesson-16 - Greedy algorithms
  - [MaxNonoverlappingSegments](./16-Greedy-Algorithms/01-MaxNonoverlappingSegments.md)
  - [TieRopes](./16-Greedy-Algorithms/02-TieRopes.md)
- Lesson-17 - Dynamic programming
  - [NumberSolitaire](./17-Dynamic-Programming/01-NumberSolitaire.md)
  - [MinAbsSum](./17-Dynamic-Programming/02-MinAbsSum.md)
