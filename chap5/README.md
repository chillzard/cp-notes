# Note for the Chapter 5 - Competitive Programmer's Handbook

# Complete search
Complete search is a general method that can be used to solve almost any algorithm problem. The idea is to generate all possible solutions to the problem using brute force, and then select the best solution or count the number of solutions, depending on the problem.

This technique is good if we have enough time to go through all the possible solutions. If it's too slow, other techniques, such as greedy algorithms or dynamic programming, may be needed.

## Generating subsets
### Method 1
Using a recursive search

```cpp
void search(int k) {
    if (k == n) {
        // process subset
    } else {
        search(k + 1);
        subset.push_back(k);
        search(k + 1);
        subset.pop_back();
    }
}
```

The idea is to decide whether to include or exclude the element $k$, in both cases, call itself with $k + 1$. However, if $k = n$, the function notices that all elements have been processed and a subset has been generated.

This is how it would look like:

```
search(0)
├── Exclude 0 → search(1)
│   ├── Exclude 1 → search(2)
│   │   ├── Exclude 2 → search(3) → Process subset: {}
│   │   └── Include 2 → search(3) → Process subset: {2}
│   └── Include 1 → search(2)
│       ├── Exclude 2 → search(3) → Process subset: {1}
│       └── Include 2 → search(3) → Process subset: {1, 2}
└── Include 0 → search(1)
    ├── Exclude 1 → search(2)
    │   ├── Exclude 2 → search(3) → Process subset: {0}
    │   └── Include 2 → search(3) → Process subset: {0, 2}
    └── Include 1 → search(2)
        ├── Exclude 2 → search(3) → Process subset: {0, 1}
        └── Include 2 → search(3) → Process subset: {0, 1, 2}
```

### Method 2
Based on the bit representation of integers.

Each subset of a set of n elements can be epresented as a sequence of n bits, which corresponds to an integer between $0...2^n-1$. The ones in the bit sequence indicate which elements are included in the subset.

The usual convention is that the last bit corresponds to element 0, the second last bit corresponds to element 1, and so on. For example, the bit representation of 25 is 11001, which corresponds to the subset {0, 3, 4}.

The following code goes through the subsets of a set of n elements
```cpp
for (int b = 0; b < (1<<n); b++) {
    // process subset
}
```

The following code shows how we can find the elements of a subset that corresponds to a bit sequence. When processing each subset, the code builds a vector that contains the elements in the subset

```cpp
for (int b = 0; b < (1 << n); b++) {
    vector<int> subset;
    for (int i = 0; i < n; i++) {
        if (b & (1 << i)) subset.push_back(i);
    }
}
```
## Generating permutations
### Method 1
Using recursion
```cpp
void search() {
    if (permutation.size() == n) {
        // process permutation
    }
    else {
        for (int i = 0; i < n; i++) {
            if (chosen[i]) continue;
            chosen[i] = true;
            permutation.push_back(i);
            search();
            chosen[i] = false;
            permutation.pop_back(i);
        }
    }
}
```

Each function call adds a new element to `permutation`. The array `chosen` indicates which elements are already included in the permutation. If the size of `permutation` equals the size of the set, a permuttion has been generated.
### Method 2

`next_permutation` utility

```cpp
vector<int> permutation;
for (int i = 0; i < n; i++) {
    permutation.push_back(i);
}
do {
    // process permutation
} while (next_permutation(permutation.begin(), permutation.end()));
```

## Backtracking

A backtracking algorithm begins with an empty solution and extends the solution step by step. The search recursively goes through all different ways how a solution can be constructed

Example: backtracking on a n x n Queen problem.

The problem can be solved using backtracking by placing queens to the board row by row. When all n queens have been placed on the board, a solution has been found.

The algorithm can be implemented as follows:

```cpp
void search(int y) {
    if (y == n) {
        count++;
        return;
    }
    for (int x = 0; x < n; x++) {
        if (column[x] || diag1[x+y] || diag2[x-y+n-1]) continue;
        column[x] = diag1[x+y] = diag2[x-y+n-1] = 1;
        search(y+1);
        column[x] = diag1[x+y] = diag2[x-y+n-1] = 0;
    }
}
```

The search begins by calling `search(0)`. The size of the board is n x n, and the code calculates the number of solutions to `count`.

Place a queen on row y, then call itself with parameter y + 1. If y = n, a solution has been found and the variable count is increased by one.

Array `columns`: columns that contain a queen

Array `diag1`, `diag2`: diagonals

It is not allowed to add another queen to a column or diagonal that already contains a queen.

For example:

```
column: {
    {0, 1, 2, 3},
    {0, 1, 2, 3},
    {0, 1, 2, 3},
    {0, 1, 2, 3},
}

diag1: {
    {0, 1, 2, 3},
    {1, 2, 3, 4},
    {2, 3, 4, 5},
    {3, 4, 5, 6},
}

diag2: {
    {3, 4, 5, 6},
    {2, 3, 4, 5},
    {1, 2, 3, 4},
    {0, 1, 2, 3},
}
```

When n increases, the search quickly becomes slow, because the number of solutions increases exponentially.

## Pruning the search
We can often optimize backtracking by pruning the search tree. The idea is to add "intelligence" to the algorithm so that it will notice as soon as possible if a partial solution cannot be extended to a complete solution. Such optimizations can have a tremendous effect on the efficiency of the search.

Consider the problem of calculating the number of paths in an n x n grid from the upper-left corner to the lower-right corner such that the path visits each square exactly once. 

Focus on 7x7 case, because its level of difficulty is appropriate to our needs.

Begin with a straight-forward backtracking algorithm, and then optimize it step by step using observations of how the search can be pruned. After each optimization, we measure the running time of the algorithm and the number of recursive calls, so that we clearly see the effect of each optimization on the efficiency of the search.

### Basic Algorithm
Just use backtracking.

Generate all possible paths from the upper-left corner to the lower-right corner and count the number of such paths.

- running time: 483 seconds
- number of recursive calls: 76 billion

### Optimization 1
In any solution, we first move one step down or right. There are always two paths that are symmetric about the diagonal of the grid after the first step. Hence, we can decide that we always first move one step down (or right), and finally multiply the number of solutions by two

- running time: 244 seconds
- number of recursive calls: 38 billion 

### Optimization 2
If the path reaches the lower-right square before it has visited all other squares of the grid, it is clear that it will not be possible to complete the solution. We can terminate the search immediately if we reach the lower-right square too early.

- running time: 119 seconds
- number of recursive calls: 20 billion

### Optimization 3
If the path touches a wall and can turn either left or right, the grid splits into two parts that contain unvisited squares. In this case, we cannot visit all squares anymore, so we can terminate the search.

- running time: 1.8 seconds
- number of recursive calls: 221 million

### Optimization 4
Idea of optimization 3 can be generalized: if the path cannot continue forward but can turn either left or right, the grid splits into two parts that both contain unvisited squares. It is clear that we cannot visit all squares anymore, so we can terminate the search. 

- running time: 0.6 seconds
- number of recursive calls: 69 million

Now is a good moment to stop optimizing the algorithm and see what we have achieved. The running time of the original algorithm was 483 seconds, and now after the optimizations, the running time is only 0.6 seconds. Thus, the algorithm became nearly 1000 times faster after the optimizations.

This is a usual phenomenon in backtracking, because the search tree is usually large and even simple observations can effectively prune the search. Especially useful are optimizations that occurs during the first steps of the algorithm, i.e., at the top of the search tree.

## Meet in the middle
A technique where the search space is divided into two parts of about equal size. A separate search is performed for both of the parts, and finally the results of the searches are combined.

Can be used: if there is an efficient way to combine the results of the searches. In such a situation, the two searches may require less time than one large search. Typically, we can turn a factor of $2^n$ into a factor of $2^{n/2}$ using the meet in the middle technique.

Example: a list of n numbers and a number x, and we want to find out if it is possible to choose some numbers from the list so that their sum is x.

Simple algorithm: go through all subsets of the elements and check if the sum of any of the subsets is x.

Running time: $O(2^{n/2})$

However, MITM => achieve a more efficient $O(2^{n/2})$ time algorithm.

Note: they ($O(2^n)$ and $O(2^{n/2})$) are different complexities, because $2^{n/2}$ equals $\sqrt{2^n}$

Idea: divide the list into two lists A and B, both lists contain about half of the numbers.

First search: generate all subsets of A and store their sums to a list $S_A$.

Second search: all subsets of B and store their sums to a list $S_B$.

It suffices to check if it is possible to choose one element from $S_A$ and anothher element from $S_B$ such that their sum is x. This is possible exactly when there is a way to form the sum x using the numbers of the original list.

We can implement the algorithm so that its time complexity is $O(2^{n/2})$. First, we generate *sorted* lists $S_A$ and $S_B$, which can be done in $O(2^{n/2})$ using a merge-like technique. After this, since the lists are sorted, we can check in $O(2^{n/2})$ time if the sum $x$ can be created from $S_A$ and $S_B$