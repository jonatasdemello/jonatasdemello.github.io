### Lesson-03 - Time Complexity

---------------------------------------------------------------------------------------------------

https://app.codility.com/programmers/lessons/3-time_complexity/

---------------------------------------------------------------------------------------------------

[easy]

# PermMissingElem

    Find the missing element in a given permutation.

An array A consisting of N different integers is given.
The array contains integers in the range [1..(N + 1)], which means that exactly one element is missing.

Your goal is to find that missing element.

Write a function:

    function solution(A);

that, given an array A, returns the value of the missing element.

For example, given array A such that:

    A[0] = 2
    A[1] = 3
    A[2] = 1
    A[3] = 5

the function should return 4, as it is the missing element.

Write an efficient algorithm for the following assumptions:

    N is an integer within the range [0..100,000];
    the elements of A are all distinct;
    each element of array A is an integer within the range [1..(N + 1)].

---------------------------------------------------------------------------------------------------

## Problem Analysis

The first thing that comes to mind for this problem is to sort the array then check each number and its successor to check for missing ones.

Another idea that comes to my mind is something that I read in the book [Programming Pearls](https://books.google.ca/books/about/Programming_Pearls.html?id=kse_7qbWbjsC) (2nd Edition by Jon Louis Bentley) where the problem statement is similar to this:

Column 1: Cracking the Oyster

Input:

> A file containing at most n positive integers, each less than n, where n = 10^7. It is a fatal error if any integer occurs twice in the input. No other data is associated with the integer.

Output:

> A sorted list in increasing order of the input integers.

Constraints:

> At most (roughly) a megabyte of storage is available in main memory; ample disk storage is available. The
run time can be at most several minutes; a run time of ten seconds need not be decreased.

It is better to read the full chapter to understand the process, but the main idea is to use a **bitmap** or **bit vector** representation to solve this problem.

For example A = [1, 2, 3, 5, 8, 13] can be represented in a bitmap:

```
                            1 1 1 1 1 1 1 1 1 1
index:  0-1-2-3-4-5-6-7-8-9-0-1-2-3-4-5-6-7-8-9
number: 0 1 1 1 0 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0
          ^ ^ ^   ^     ^         ^
A = [1, 2, 3, 5, 8, 13]
```

Every number's position (index) is set to "1" if the number is in the array "A", or set to "0" if not.
If memory/space was a constraint it could be done with bits, but for now I will use another array to make things easier.

```
A = [1, 2, 3, 5, 8, 13]
B = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
```

From the problem description:

    A[2, 3, 1, 5]
    A.length = N = 4

so

    A[0] = 2
    A[1] = 3
    A[2] = 1
    A[3] = 5

The new array is: (index 0 is ignored)

```
idx= 0  1  2  3  4  5
B = [0, 1, 1, 1, 0, 1]
```

so the first missing integer is idx = 4.


Solution:

- create a new array B[N+1] and initialize it with 0's;
- loop through A, (for i=0; i < A.length; i++)
- set B[A[i]-1] = 1 (true);
- after that, loop through B again and return the first i where B[i] == 0;


## Alternate Approach

Solution approach:

Uses the mathematical sum method for O(N) time complexity and O(1) space complexity
Expected sum of 1 to (N+1) = (N+1) × (N+2) / 2
Missing element = Expected sum - Actual sum
