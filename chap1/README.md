# Note for the Chapter 1 - Competitive Programmer's Handbook

(Beginner's notes: `<<` for cout and `>>` for cin)

## I/O
When compiling, it is advised to use this command to compile:
```bash
g++ -std=c++11 -O2 -Wall test.cpp -o test
```
To speed up thing, just write 
```cpp 
#include <bits/stdc++.h>
using namespace std;

int main() {
  // this here
  ios::sync_with_stdio(0);
  cin.tie(0);
}
```

To input something, just write
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b;
  string x;
  cin >> a >> b >> x;

  // we also have C-like things 
  scanf("%d %d", &a, &b);
  printf("%d %d", &a, &b);

  // USEFUL: wanna get the next string with getline()
  // here's the thing: '\n' trailing will get out, so 
  cin.ignore();

  // and now we can safely do anything 
  string temp; getline(cin, temp);

  // unlimited stuff: while (cin >> x) { ... }
  cout << temp << endl;
}
```

Sometimes we need to input/output through file. This 
can be easily achieved through `freopen()` and `fclose()`.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  // this is how you manage input/output effectively
  freopen("input.txt", "r", stdin);
  int x;
  cin >> x;
  FILE *fp = freopen("output.txt", "w", stdout);
  cout << x << endl;
  // to make sure there's a checkpoint to end writing executions, use `fclose()`
  fclose(fp);
  return 0;
}
```

## Types
C++ supports plenty of types. For CP, here are the cautions we need.

int: (32-bit) $-2^{31}$ -> $2^{31} - 1$ or about $-2\cdot10^9$ -> $-2\cdot10^9$

long long: (64-bit) $-2^{63}$ -> $2^{63} - 1$ or about $-9\cdot10^{18}$ -> $9\cdot10^{18}$

To convert types, do this 
```cpp
#include <bits/stdc++.h>
using namespace std; 
int main() {
  int y = 12;
  long long z = 1231231231LL;
  // when doing calculations like this,
  // casting is crucial
  cout << ((long long)y) * z << endl;
}
```

This type is unlikely to have `__int128_t`

`__int128_t`: 128-bit: $-2^{127}$ -> $2^{127} - 1$
    or about $-10^{38}$ -> $10^{38}$

Modular formulas:

  $(a + b) \mod m = (a\mod m + b \mod m) \mod m$
  
  $(a - b) \mod m = (a\mod m - b \mod m) \mod m$
  
  $(a * b) \mod m = (a\mod m * b \mod m) \mod m$

C++ in actions:
```cpp
#include <bits/stdc++.h>
int main() {
  long long a = 1;
  for (int i = 2; i <= 3; i++) {
    a = (a * i)%1;
    if (a < 0) a += 1; // make sure there's no negative remainders
  }
  cout << a%1 << "\n";

  printf("%.20f", (double)a); 
  return 0;
}
```

See the `printf("%.20f", (double)a)`? This is how we format the float in C++.

To compare floats, it is advised to not use `==` operator. Instead, compare smallest difference.

Code:
```cpp 
#include <bits/stdc++.h>

int main() {
  long long a = 1e-9;
  if (abs(a - 0.1111111) < 1e-9) {
    // difference is 1e-9 
    printf("Equal\n");
  }
  return 0;
}
```

## Macros/Type aliases
This is how macros/type aliases are defined 

```cpp
typedef long long ll; // some quick shortening here
#define SQ(a) (a)*(a) // or even macros!
```

## Sum theory

Rule 1:
Each sum of the form 
$\sum_{x=1}^{n} x^k = 1^k + 2^k + 3^k + \dots + n^k$

with $k > 0$, has a closed form formula that is a **polynomial of degree $k + 1$**.

Examples:
$\sum_{x=1}^{n} x = 1 + 2 + 3 + \dots + n = \frac{n(n+1)}{2}$

$\sum_{x=1}^{n} x^2 = 1^2 + 2^2 + 3^2 + \dots + n^2 = \frac{n(n+1)(2n+1)}{6}$

(Faulhaber's formula).

Arithmetic progression: difference is constant 

$3, 7, 11, 15$

Sum:

$\underbrace{a + \dots + b}_{n \text{ numbers}} = \frac{n(a+b)}{2}$


Geometric progression: ratio is constant

$3, 6, 11, 24$ 

Sum:

$a + ak + ak^2 + \dots + b = \frac{bk - a}{k - 1}$

Special case:

$1 + 2 + 4 + 8 + \dots + 2^{n - 1} = 2^n - 1$

Harmonic sum:

$\sum_{x=1}^{n} \frac{1}{x} = 1 + \frac{1}{2} + \frac{1}{3} + \dots + \frac{1}{n}$

Upper bound $\log_{2}{n} + 1$

Approx by modifying each term $1/k$ so that $k$ becomes the nearest power of two that does not exceed k.


## Set theory 

This part is just basic maths so I'm not into wrapping all of them.

However, I will still cover all the important points, but not dive into the specific details.

Set is a collection of elements. For example, 
$X = \{1, 2, 3\}$
$\emptyset$ for empty set, and $|S|$ for size of S 

Operations:

Intersection: both A and B. $A\cap{B}$

Union: A or B or both. $A\cup{B}$

Complement: elements not in A. Depend on the universal set, if that set contains a subset called A, than the complement of A is just basically all the remaining elements that are not in A. $\overline{A}$

Difference: $A\setminus{B} = A\cap{\overline{B}}$ in A but not in B, B can contain elements that are not in A. 

Subset: A is subset of B if all the elements in A is in B. $A\subset{B}$

Set S always has $2^{|S|}$ subsets, including the empty set.

Useful sets: $\mathbb{N}$ (Natural), $\mathbb{Z}$ (integers), $\mathbb{Q}$ (Rational), $\mathbb{R}$ (Real)

(this is unusual, in Vietnam we have $\mathbb{N}^{*}$ to indicate Natural but without $0$, but it seems like you can just write $\mathbb{N}$ for both cases)

Construct a set (**important**):

Rule of the form: $\{ f(n) : n \in S \}$

## Logic

Logical expression is either **true** (1) or **false** (0).

Operations: 

$\neg$ for negation, $\neg A$ is opposite value of A.

$\wedge$ for conjunction, $A \wedge B$ is true if A and B are true.

$\vee$ for disjunction, $A \vee B$ is true if A or B or both are true

$\Rightarrow$ for implication, $A \Rightarrow B$ is true if whenever A is true, also B is true 

$\Leftrightarrow$ for equivalence, $A \Leftrightarrow B$ is true if A and B are both true or both false

Here's the table for demonstration.

| A | B | ¬A | ¬B | A ∧ B | A ∨ B | A ⇒ B | A ⇔ B |
|---|---|----|----|------|------|------|------|
| 0 | 0 |  1 |  1 |  0   |  0   |  1   |  1   |
| 0 | 1 |  1 |  0 |  0   |  1   |  1   |  0   |
| 1 | 0 |  0 |  1 |  0   |  1   |  0   |  0   |
| 1 | 1 |  0 |  0 |  1   |  1   |  1   |  1   |

A predicate is an expression that is true or false depending on its parameters. $P(x)$, for example

A quantifier connects a logical expression to the elements of a set.

Important: for all $\forall$ and there is $\exists$

## Function

$\lfloor x \rfloor$ rounds x down to an integer.

$\lceil x \rceil$ rounds x up to an integer.

`max(a, b)` and `min(a, b)` gives the smallest and the largest value of `a, b`.

Factorial $n!$ can be defined:

$\prod_{x=1}^{n} x = 1 \cdot 2 \cdot 3 \cdots n$

or recursively:

$0! = 1$
$n! = n \cdot{(n - 1)!}$

This is how it'd look like in C++

```cpp
#include <bits/stdc++.h>
using namespace std;
// this is a trivial factorial function
int factorial(int a) 
{
  // constraint a >= 0
  if (a == 0)
  {
    return 1;
  }
  return a * factorial(a - 1);

}
int main() {
   cout << factorial(4) << endl; 
}
```

The Fibonacci numbers can be defined recursively as follows:

```cpp
#include <bits/stdc++.h>
using namespace std;
// this is a trivial fibonacci function 
int fib(int a) {
  // constraint: a >= 0
  if (a == 0) {
    return 0;
  } else if (a == 1) {
    return 1;
  }

  return fib(a - 1) + fib(a - 2);
}

int main() {
   cout << fib(4) << endl; 
}
```

or through the Binet's formula $f(n) = \frac{(1 + \sqrt{5})^n - (1 - \sqrt{5})^n}{2^n \sqrt{5}}$

## Logarithm

$\log_k(x) = a$ when $k^a = x$

Useful fact: $\log_k(x)$ equals the number of times we have to divide x by k before we reach the number 1 => clue for the O(log n) later on (now we don't care).

Logarithm rules:

$\log_k(x^n) = n \cdot \log_k(x)$

$\log_k \left( \frac{a}{b} \right) = \log_k(a) - \log_k(b).$

$\log_u(x) = \frac{\log_k(x)}{\log_k(u)}$

Natural Logarithm: 

$\ln(x) = \log_e(x)$

Useful fact: the number of digits of an integer x in base b is $\lfloor \log_b (x) + 1 \rfloor$.

