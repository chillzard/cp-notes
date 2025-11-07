# Note for the Chapter 3 - Competitive Programmer's Handbook

## Sorting theory

```
Given an array that contains n elements, your task is to sort the elements in increasing order
```

There are a lot of algorithms designed to sort an array. Here are some.

### $O(n^2)$ algorithms

Simple way to sort an array, using two nested loops.

For example, let's consider bubble sort. 

Here's the explanation for bubble sort:

```
Bubble sort consists of n rounds.
On each round the algorithm iterates through the elements of the array.
Whenever two consecutive elements are found that are not in correct order, the algorithm swaps them.
```

Here's the implementation
```cpp

#include <bits/stdc++.h>
using namespace std;

void bubbleSort(int array[], int n) {
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n - i; j++) {
            if (array[j] > array[j + 1]) 
                swap(array[j],array[j+1]);
        }
    }
}

int main() {
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sort arr using bubble sort
    bubbleSort(arr, n - 1);

    for (auto i : arr)
        cout << i << " ";

    return 0;
}

```
### Inversions

Algorithm that always swaps *consecutive* elements: the time complexity is *always* at least $O(n^2)$, because in the worst case, $O(n^2)$ swaps are required for sorting the array.

=> Useful concept to analyze sorting algorithms: inversion.

**Inversion**: a pair of array elements `(array[a], array[b])` such that `a < b` and `array[a] > array[b]`.

The number of inversions indicates how much work is needed to sort the array. An array is completely sorted when there are no inversions. On the other hand, if the array elements are in the reverse order, the number of inversions is the largest possible:

$1 + 2 + \dots + (n - 1) = \frac{n(n - 1)}{2} = O(n^2)$

Swapping a pair of consecutive elements that are in the wrong order removes exactly one inversion from the array. => sorting algorithm can only swap consecutive elements, each swap removes at most one inversion => time complexity: at least $O(n^2)$

### $O(n \log{n})$ algorithms

Using algorithms that are not limited to swapping consecutive elements. Example: merge sort.

Algorithm:

For a subarray ``[a ... b]``
1. if a = b => do nothing. already sorted
2. calculate the position of the middle element $k = \lfloor (a + b)/2 \rfloor$
3. recursively sort the subarray ``array[a ... k]``
4. recursively sort the subarray ``array[k + 1 ... b]``
5. Merge the sorted subarrays into a sorted subarray ``array[a ... b]``

=> Efficient algorithm, because it halves the size of the subarray at each step.

- Recursion consists of $O(\log n)$ levels.
- Processing each level takes $O(n)$ time.
- Merge the subarrays can be done in linear time.

### Sorting lower bound
It's not possible to sort an array faster than $O(n \log n)$ time when we restrict ourselves to sorting algorithms that are based on comparing array elements.

The lower bound (time complexity) can be proved by considering sorting as a process where each comparison of two elements gives more information about the contents of the array. The process creates the following tree:

```
      x < y?
      /    \
    Yes    No
    /        \
x < y?    x < y?
 /  \      /  \
Yes No   Yes  No
 │  │     │   │
... ...  ... ...
```

``x < y?`` is comparison x, y. If ``x < y``, the process continues to the left, and otherwise to the right. The results of the process are the possible ways to sort the array, a total of $n!$ ways. For this reason, the height of the tree must be at least:

$\log_2{(n!)} = \log_2(1) + \log_2(2) + \dots + \log_2(n)$

We get a lower bound for this sum by choosing the last `n/2` elements and changing the value of each element to $\log_2(n/2)$. This yields an estimate

$\log_2(n!) \ge (n/2)\cdot\log_2(n/2)$

so the height of the tree and the minimum possible number of steps in a sorting algorithm in the worst case is at least $n\log{n}$

### Counting sort
$O(n)$ time, assuming that every element in the array is an integer between 0...c and c = O(n).

Create a *bookkeeping* array, whose indices are elements of the original array. The algorithm iterates through the original array and calculates how many times each element appears in the array.

For example, `[1, 3, 6, 9, 9, 3, 5, 9]` corresponds to the following bookkeeping array `{1 -> 1; 2 -> 0; 3 -> 2; 4 -> 0; 5 -> 1; 6 -> 1; 7 -> 0; 8 -> 0; 9 -> 3}`

Bookkeeping array: O(n)
Create the sorted array: O(n) 
=> O(n) time complexity.

This is a good algorithm, but don't use it if the c is too large.

## Sorting in C++
In reality, no one write their own sorting algorithm in a contest. We use the built-in one.

Sort a vector in increasing order:
```cpp
vector<int> v = {4, 2, 5, 3, 5, 8, 3};
sort(v.begin(), v.end());
```

In reverse order:

```cpp 
sort(v.rbegin(), v.rend());
```

Ordinary array sort:
```cpp
int n = 7;
int a[] = {4, 2, 5, 3, 5, 8, 3};
sort(a, a+n);
```

String s sort:
```cpp
string s = "monkey";
sort(s.begin(), s.end());
```

### Comparison operators
Operator for:
Numbers: values
String: alphabetical order
Pair: first, then second.
```cpp
vector<pair<int,int>> v;
v.push_back({1, 5});
v.push_back({2, 3});
v.push_back({1, 2});
sort(v.begin(), v.end());
```

Tuple: first, then second, then third
```cpp
vector<tuple<int, int, int>> v;
v.push_back({2, 1, 4});
v.push_back({1, 5, 3});
v.push_back({2, 1, 3});
sort(v.begin(), v.end());
```

For user-defined structs, use function `operator<` to define the comparison operator, whose parameter is another element of the same type. The operator should return true if the element is smaller than the parameter, and false otherwise.

```cpp
struct P {
  int x, y;
  bool operator<(const P &p) {
    if (x != p.x) return x < p.x;
    else return y < p.y;
  }
};
```
### Comparison functions
It is possible to give an external **comparison function** to the sort function as a callback function.

```cpp
bool comp(string a, string b) {
  if (a.size() != b.size()) return a.size() < b.size();
  return a < b;
}

sort(v.begin(), v.end(), comp);
```
## Binary search
For searching an element in an array, a general method is to use a for loop that iterates through the elements of the array.

```cpp
for (int i = 0; i < n; i++) {
  if (array[i] == x) {
    // x found at index i 
  }
}
```

Time complexity: `O(n)`

If the order of the array is arbitrary, this is simply the best approach. If the array is sorted, well, binary search is much better with `O(log n)` time.

Method 1:
```cpp
int a = 0, b = n - 1;
while (a <= b) {
  int k = (a + b)/2;
  if (array[k] == x) {
    // x found at index k
  }
  if (array[k] > x) b = k - 1;
  else a = k + 1;
}

```

- Check the middle element of the array.
- If it is, terminate.
- Otherwise, search left and right.

Method 2:
```cpp
int k = 0;
for (int b = n/2; b >= 1; b /= 2) {
  while (k+b < n && array[k+b] <= x) k += b;
}
if (array[k] == x) {
  // x found at index k
}
```
- Search from left to right, initial jump length n/2
- After that, the jump length will be halved until 1.
- Found or not found.

### C++ functions
`lower_bound` returns a pointer to the first array element whose value is at least x.

`upper_bound` returns a pointer to the first array element whose value is larger than x.

`equal_range` returns both above pointers.

Assume the array is sorted.

If there is no such element, the pointer points to the element after the last array element. 

```cpp
auto k = lower_bound(array,array + n,x) - array;
if (k < n && array[k] == x) {
  // x found at index k 
}
```

Count the number of elements whose value is x.


```cpp
auto a = lower_bound(array, array+n, x);
auto b = upper_bound(array, array+n, x);
cout << b - a << "\n";

// or 
auto r = equal_range(array, array+n, x);
cout << r.second - r.first << "\n";

```

### Smallest solution
Important use for binary search: find the position where the value of a function changes.

Suppose that we wish to find the smallest value k that is a valid solution for a problem. 

Given a function `ok(x)` returns true when the solution is valid and vice versa, false. `ok(x)` is false when x < k and true when x >= k.

Something like this 

| x | 0 | 1 | k - 1 | k | k + 1 |
| ------------- | -------------- | -------------- | ------------- | -------------- | --------------|
| ok(x) | false | false | false | true | false |

The value of k can be found using binary search:

```cpp
int x = -1;
for (int b = z; b >= 1; b /= 2) {
  while (!ok(x + b)) x += b;
}
int k = x + 1;
```

The search finds the largest value of x for which ok(x) is false. Thus, the next value k = x + 1 is the smallest possible value for which ok(k) is true. 

The initial jump length z has to be large enough, for example some value for which we know beforehand that ok(z) is true.

The algorithm calls the function ok O(log z) times, so the total time complexity depends on the function ok. For example, if the function works in O(n) time, the total time complexity is O(n log z).

### Maximum value
Binary search can also be used to find the max value for a function that is first increasing and then decreasing. 

Find a position k such that:

```
f(x) < f(x + 1) when x < k
f(x) > f(x + 1) when x >= k 
```

Idea: find the largest value of x for which f(x) < f(x + 1) => k = x + 1 because f(x + 1) > f(x + 2)

```cpp
int x = -1;
for (int b = z; b >= 1; b /= 2) {
  while (f(x + b) < f(x+b+1)) x += b;
}

int k = x + 1;
```

> [!WARNING]
> It is not allowed that consecutive values
> of the function are equal.
> It'd not be possible to know how to continue the search.
