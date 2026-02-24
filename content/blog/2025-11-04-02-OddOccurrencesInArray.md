### Lesson-02 - Arrays

---------------------------------------------------------------------------------------------------

https://app.codility.com/programmers/lessons/2-arrays/

---------------------------------------------------------------------------------------------------

[easy]

# Odd Occurrences In Array

    Find value that occurs in odd number of elements.

A non-empty array A consisting of N integers is given.
The array contains an odd number of elements, and each element of the array can be paired with another element that has the same value, except for one element that is left unpaired.

For example, in array A such that:

    A[0] = 9
    A[1] = 3
    A[2] = 9
    A[3] = 3
    A[4] = 9
    A[5] = 7
    A[6] = 9

    the elements at indexes 0 and 2 have value 9,
    the elements at indexes 1 and 3 have value 3,
    the elements at indexes 4 and 6 have value 9,
    the element at index 5 has value 7 and is unpaired.

Write a function:

    function solution(A);

that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the unpaired element.

For example, given array A such that:

    A[0] = 9
    A[1] = 3
    A[2] = 9
    A[3] = 3
    A[4] = 9
    A[5] = 7
    A[6] = 9

the function should return 7, as explained in the example above.

Write an efficient algorithm for the following assumptions:

    N is an odd integer within the range [1..1,000,000];
    each element of array A is an integer within the range [1..1,000,000,000];
    all but one of the values in A occur an even number of times.

---------------------------------------------------------------------------------------------------

## Problem Analysis



I will start with the validations:

```js
// 02-Arrays/odd-occurrences-in-array.test.js

  // each element of array A is an integer within the range [1..1,000,000,000].
  test('each element of array A is an integer within the range [1..1,000,000,000].', () => {
    // arrange
    const A = [0, -1, 10, 5000000000, 1000000001]; // invalid values
    // act & assert
    expect(() => {
      solution(A)
    }).toThrow();
  });
```

This time I will add the input array and the expected output result since the problem description only shows one example. I also used the AAA structure:

```js
// 02-Arrays/odd-occurrences-in-array.test.js

// test case to rotate A[1,2,3,4,5] K=2 return should be A[4,5,1,2,3]
  test('given A[9, 3, 9, 3, 9, 7, 9] should return 7.', () => {
    // arrange
    const A = [9, 3, 9, 3, 9, 7, 9];
    const expected = 7;
    // act
    const result = solution(A);
    // assert
    expect(result).toEqual(expected);
  });
```

Run the tests:

```js
 FAIL  02-Arrays/odd-occurrences-in-array.test.js
  OddOccurrencesInArray Tests
    × each element of array A is an integer within the range [1..1,000,000,000]. (3 ms)
    × given A[9, 3, 9, 3, 9, 7, 9] should return 7. (3 ms)
```

It is time to start working on the solution. Validations first.

```js
// 02-Arrays/odd-occurrences-in-array.js
'use strict';

// Find value that occurs in odd number of elements.

module.exports = function solution(A) { // A array

	// each element of array A is an integer within the range [1..1,000,000,000];
	for (let i = 0; i < A.length; i++) {
		if (A[i] < 1 || A[i] > 1000000000) {
			throw new Error("Element A[" + i + "] is invalid!");
		}
	}
}
```

The problem says that there are pair of elements, except for one element that is left unpaired.
One way to find the odd element would be loop through the array and count the elements, adding them to a table and then look at the rows that have odd numbers.

For example: array A = [9, 3, 9, 3, 9, 7, 9]

| element | count |
|------|-------|
|    9 |     4 |
|    3 |     2 |
|    7 |     1 |

And "7" is the odd element since there is only 1 element in the array.

I learned to program in BASIC (8 bit) then used C later in college and one of the things I always have in mind is how to solve problem using common/simple structures: for/while loops, arrays and so on. Modern languages offer different constructs and data structures and it makes the job a lot easier for sure. Most languages today share the same features: hashes, maps sets and so on.

One way that I can think of solving this problem without using fancy structures is to have 2 arrays (or maybe a bidimensional 2 cols x N rows). This would look like this:

```js
// 2 arrays, one hold the element and another the count
element[0] = 9 , count[0] = 4
element[1] = 3 , count[1] = 2
element[2] = 7 , count[2] = 1

// or using a multidimensional array:
let matrix = [
  [9, 4],
  [3, 2],
  [7, 1]
];

matrix[0][0] = 9; // the first  value of the first inner array
matrix[0][1] = 4; // the second value of the first inner array
```

Both will work and I can simply iterate over it using a for or while loop.

There are may other way to store our data, but since I am working with JavaScript I can think of 2 other options: Map and Set.

**Map**

> A Map is a collection of key-value pairs where keys can be of any data type (including objects or functions), unlike plain JavaScript objects where keys must be strings or Symbols.

**Set**

> A Set is a collection of unique values. It does not store key-value pairs; instead, it simply stores a list of distinct elements.

Since a "Set" can only store unique values I think "Map" is a better option because it can store key-value pairs and I need "element-count" pair.

Looking at the documentation I can see that Map methods and properties are:

    new Map() – creates the map.
    map.set(key, value) – stores the value by the key.
    map.get(key) – returns the value by the key, undefined if key doesn’t exist in map.
    map.has(key) – returns true if the key exists, false otherwise.
    map.delete(key) – removes the element (the key/value pair) by the key.
    map.clear() – removes everything from the map.
    map.size – returns the current element count.

I can use this to:

- loop through the A array;
- check if that element exists in the Map;
- if not exists, then add it to the set with count = 1;
- if exists, then update count = count + 1;

```js
	// using map to count occurrences
	let map = new Map();
	for (let i = 0; i < A.length; i++) {
        let element = A[i];
		let exists = map.get(element);
		if (exists) {
			map.set(element, exists + 1);
		} else {
			map.set(element, 1);
		}
	}
	//debug:
	console.log(map);
```

At this point, I have this table stored in a Map data structure:

| key  | value |
|------|-------|
|    9 |     4 |
|    3 |     2 |
|    7 |     1 |


The last step is to find the odd count (value) and to do that it will be necessary to iterate over the Map.

For looping over a map, there are 3 methods:

    map.keys() – returns an iterable for keys,
    map.values() – returns an iterable for values,
    map.entries() – returns an iterable for entries [key, value], it's used by default in for..of.


```js
    // find the element with odd occurrences
	for (let [key, value] of map) {
		if (value % 2 !== 0) {
			return key;
		}
	}
```

The problem description says that only one element is left unpaired (all but one of the values in A occur an even number of times) so if that element is found, it can be returned as the solution.
Having more than one odd element in the array means that the input is invalid.


