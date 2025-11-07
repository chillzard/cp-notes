# Note for the Chapter 2 - Competitive Programmer's Handbook

## Time complexity
Time complexity *doesn't tell the exact steps*, but rather order of magnitude

Denote by big O notation

For k loop the time complexity would be $O(n^k)$

With phases, the largest would be the total time complexity (since it's the bottleneck)

With several variables, it depends. For instance, an algo like this 
```cpp
for (int i = 1; i <= n; i++) {
  for (int j = 1; j <= m; j++) {
      // code 
    }
}

```
would take $O(n\cdot{m})$ as the time complexity 

Recursion depends on the number of times the function is called
and the time complexity of a single call. The total time complexity
is the product of these values

```cpp

// single call: O(1)
// times call: n
// => total time complexity: O(n)
void f(int n) {
    if (n == 1) return;
    f(n - 1);
}

// each call: O(1)
// times call:
// for time 1st, it's only 1 call
// for time > 1st, each time call 2 times, so 
// the total time is:
// 1 + 2 + 2*2 + 2*3 + ... + 2^(n-1) = 2^n - 1 
// => time complexity:  O(2^n)
void g(int n) {
  if (n == 1) return;
  g(n - 1);
  g(n - 1);
}

```
## Complexity Classes

O(1) (Constant) – Fixed time, regardless of input.

O(log n) (Logarithmic) – Input size halves each step (e.g., binary search).

O(√n) (Square Root) – Slower than O(log n), faster than O(n).

O(n) (Linear) – Iterates through all elements.

O(n log n) (Linearithmic) – Efficient sorting complexity.

O(n²) (Quadratic) – Nested loops (e.g., checking all pairs).

O(n³) (Cubic) – Three nested loops (e.g., checking triplets).

O(2ⁿ) (Exponential) – Grows exponentially (e.g., generating subsets).

O(n!) (Factorial) – Considers all permutations (e.g., TSP).

> [!IMPORTANT]
> An algorithm is polynomial if its time complexity is at most 
> $O(n^k)$ where k is a constant.
> The constant k is usually small, and therefore a polynomial time 
> complexity roughly means that the algorithm is efficient!

## Estimate efficiency

- Why Time Complexity Matters: Helps determine if an algorithm is efficient before implementation.  
- Rule of Thumb: A modern computer can perform hundreds of millions of operations per second.  
- Example: If n = 10^5 and time complexity is O(n²), the algorithm performs 10^10 operations, which is too slow for a 1-second limit.  

Guideline Table:  
  - n ≤ 10 → O(n!)  
  - n ≤ 20 → O(2ⁿ)  
  - n ≤ 500 → O(n³)  
  - n ≤ 5000 → O(n²)  
  - n ≤ 10⁶ → O(n log n) or O(n)  
  - Large n → O(1) or O(log n)  

Key Takeaway:  
- If n = 10^5, algorithms should aim for O(n) or O(n log n).  
- Constant factors matter but Big-O gives a high-level efficiency estimate.  

NOTE: When the input size is small => all efficient, but 
when it became larger => remarkable differences

## Example 
Here we have this problem: Maximum subarray sum. 

### Attempt 1 

A straightforward way to solve the problem is to go through
all possible subarrays, calculate the sum of values in each
subarray and maintain the maximum sum.


```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n = 8;
  int array[8] = {-1, 2, 4, -3, 5, 2, -5, 2};

  // PS: maybe I will switch to K&R CS50 forced me 
  // to do Allman and it's so ugly
  int best = 0;
  for (int a = 0; a < n; a++) {
    for (int b = a; b < n; b++) {
      int sum = 0;
      for (int k = a; k <= b; k++) {
        sum += array[k];
      }
      best = max(best, sum);
    }
  }

  cout << best << "\n";
  
  return 0;
}

```

**Analogy**: a, b fix the first and last index of the subarray. Sum of values is calculated through `sum`. `best` contains the max sum.

This approach costs $O(n^3)$

### Attempt 2
Removing one loop from it by calculating the sum at the same time when the right end of the subarray moves.


```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

  int n = 8;
  int array[8] = {-1, 2, 4, -3, 5, 2, -5, 2};

  int best = 0;
  for (int a = 0; a < n; a++) {
    int sum = 0;
    for (int b = a; b < n; b++) {
      sum += array[b];
      best = max(best,sum);
    }
  }

  cout << best << "\n";
  return 0;

}
```

$O(n^2)$ time complexity

### Attempt 3
Idea: to calculate, for each array position, the maximum sum of a subarray that ends at that position. After this, the answer for the problem is the max of those sums.

Consider the subproblem of finding the maximum-sum subarray that ends at position k. There are two possibilities:

1. The subarray only contains the element at position k
2. The subarray consists of a subarray that ends at position k - 1, followed by the element at position k


In the latter case, since we want to find a subarray with maximum sum, the subarray that ends at position k - 1 should also have the max sum. Thus, we can solve the problem efficiently by calculating the max subarray sum for each ending position from left to right.

Sometimes known as Kadane's algorithm


```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 8;
  int array[8] = {-1, 2, 4, -3, 5, 2, -5, 2};

  int best = 0, sum = 0;
  for (int k = 0; k < n; k++) {
    sum = max(array[k], sum+array[k]);
    best = max(best,sum);
  }
  cout << best << "\n";

  return 0;
}

```

Time complexity: $O(n)$

