# Note for the Chapter 6 - Competitive Programmer's Handbook

# Greedy algorithms
A greedy algorithm constructs a solution to the problem by always making a choice that looks the best at the moment. A greedy algorithm never takes back its choices, but directly constructs the final solution. => efficient.

Difficulty: find a greedy strategy that always produces an optimal solution to the problem. The locally optimal choices in a greedy algorithm should also be globally optimal. It is often difficult to argue that a greedy algorithm works.

## Coin problem
Problem: given a set of coins, form a sum of money $n$ using the coins. The values of the coins are `coins={c1, c2, ..., ck}` and each coin can be used as many times we want. What is the minimum number of coins needed?

For example: `{1, 2, 5, 10, 20, 50, 100, 200}`

and n = 520, we need at least four coins. The optimal solution: 200 + 200 + 100 + 20 = 520

### Greedy algorithm
A simple greedy algorithm to the problem always selects the largest possible coin, until the required sum of money has been constructed.

For example, n = 520 and `{1, 2, 5, 10, 20, 50, 100, 200}`. The algorithm works like this

```
Largest available: 200 => 520 - 200 = 320 
Largest available: 200 => 320 - 200 = 120
Largest available: 100 => 120 - 100 = 20
Largest available: 20 =>  20 - 20 = 0
=> Optimal solution: 200, 200, 100, 20
or needed 4 coins
```

But does this algorithm always work?

