### Lesson-03 - Time Complexity

---------------------------------------------------------------------------------------------------

https://app.codility.com/programmers/lessons/3-time_complexity/

---------------------------------------------------------------------------------------------------

[easy]

# FrogJmp

    Count minimal number of jumps from position X to Y.

A small frog wants to get to the other side of the road.
The frog is currently located at position X and wants to get to a position greater than or equal to Y.
The small frog always jumps a fixed distance, D.

Count the minimal number of jumps that the small frog must perform to reach its target.

Write a function:

    function solution(X, Y, D);

that, given three integers X, Y and D, returns the minimal number of jumps from position X to a position equal to or greater than Y.

For example, given:

    X = 10
    Y = 85
    D = 30

the function should return 3, because the frog will be positioned as follows:

    after the first jump, at position 10 + 30 = 40
    after the second jump, at position 10 + 30 + 30 = 70
    after the third jump, at position 10 + 30 + 30 + 30 = 100

Write an efficient algorithm for the following assumptions:

    X, Y and D are integers within the range [1..1,000,000,000];
    X ≤ Y.

---------------------------------------------------------------------------------------------------

## Problem Analysis

A frog starts at position X and needs to reach position Y (or beyond) by jumping a fixed distance D each time.
Find the minimum number of jumps needed.

    X = start position
    Y = final position
    D = jump distance

Distance to cover: Y - X

If X = 10 and Y = 85, the frog needs to cover 75 units.

Jumps needed: Divide distance by jump size and round up

With D = 30: 75 / 30 = 2.5
Round up to 3 jumps (since we can't make partial jumps)

Time Complexity: O(1) - constant time, just one calculation

Example Walkthrough
Given X = 10, Y = 85, D = 30:

    Distance = 85 - 10 = 75
    Jumps = 75 / 30 = 2.5 = 3
    After 3 jumps: 10 + (3 × 30) = 100 >= 85


```js
function solution(X, Y, D) {
    // Calculate the distance to cover
    const distance = Y - X;
    // Calculate number of jumps needed (round up)
    return Math.ceil(distance / D);
}
// or
function solutionInt(X, Y, D) {
    const distance = Y - X;
    return Math.floor((distance + D - 1) / D);
    // or: return Math.floor(distance / D) + (distance % D > 0 ? 1 : 0);
}
```
