# Note for the Chapter 4 - Competitive Programmer's Handbook

## Dynamic Arrays
Array whose size can be changed during the execution of the program.

In C++, commonly used is `vector`, which can be used almost like an ordinary array.

Demo on how to use it:

Adding elements:
```cpp
vector<int> v;
v.push_back(3);
v.push_back(2);
v.push_back(5);

// after push_back a few times, the array looks like this
// [3, 2, 5]

// EXTRAS: push_front can also be used to push the element
// in the front of the vector

v.push_front(3); // [3, 3, 2, 5]

// insert() can be used to customize the position of the element pushed

v.insert(v.begin() + 2, 4) // [3, 3, 4, 2, 5]

// other cool things
v.pop_back(); // delete the last elemenet
v.clear(); // clear the whole vector
v.erase(v.begin()); // erase an element in a vector
// v.front() and v.back() are just pure values, not iterators
v.front(); // first element
v.back(); // last element
// begin() and end() are fun, but rbegin() and rend() are extremely useful
// they are also iterators, but reverse.
v.empty(); // check if the vector is empty
v.resize(); // resize the array, simply put, this is a faster way to shrink or expand it.
std::reverse(v.begin(), v.end()); // reverse the whole vector
std::count(v.begin(), v.end(), 3); // check the occurence of 3
// to find an element, you can also use std::find
std::find(v.begin(), v.end(), 3);
// or since c++20, you can also use binary_search built-in function
// which is pretty cool
std::shuffle(v.begin(), v.end()); // shuffle the whole vector
std::sort(v.begin(), v.end()); // sort the whole vector
// for mapping and stuff, here is the suggestion
// use something like erase-remove idiom
//  for example
std::erase(remove_if(v.begin(), v.end(), [](int x) {
    return x % 2 != 0;
}), v.end());
```

Access the elements:
```cpp
cout << v[0] << "\n";
cout << v[1] << "\n";
cout << v[2] << "\n";
```

Function `size` returns the number of elements in the vector

```cpp
for (int i = 0; i < v.size(); i++) {
    cout << v[i] << "\n";
}

// or
for (auto x : v) {
    cout << x << "\n";
}

```

Initialize a vector:
```cpp
vector<int> v = {2, 4, 2, 5, 1};
// size 10, initial 0
vector<int> v(10);
// size 10, initial 5
vector<int> v(10, 5);
// iota is quite useful, but i don't think we would use it often

vector<int> v(5); // size restricted to 5
std::iota(v.begin(), v.end(), 1) // add elements incremented by 1
// output: [1, 2, 3, 4, 5]
```

String is also a dynamic array. Here's an example

```cpp
string a = "hatti";
string b = a + a;
cout << b << "\n"; // hattihatti
b[5] = 'v';
cout << b << "\n"; // hattivatti
string c = b.substr(3, 4);
cout << c << "\n"; // tiva
```

## Set structures

A **set** is a data structure that maintains a collection of elements. The basic operations of sets are element insertion, search and removal.

> [!IMPORTANT]
> This definition is quite ambiguous in my opinion, so to make it precise
> it should be: a set is a container that stores unique elements in sorted order

C++ STL contains two set implementations: The structure `set` is based on a balanced binary tree and its operatons work in $O(\log n)$ time. The structure `unordered_set` (simply say, it doesn't record the order) uses hashing, and its operations work in $O(1)$ time on average.

Choice: `set` maintains the order of the elements and provdes functions that are not available in `unordered_set`. But `unordered_set` can also be more efficient.

Some operations:
```cpp
set<int> s;
// insert elements
s.insert(3);
s.insert(2);
s.insert(5);
s.insert(5); // this operation would be ignored, because 
// every single element in set is unique.
// 
// you can init like this
set<int> s = {2, 5, 6, 8};
// you can also sort in descend order
set<int, greater<int>> s = {2, 5, 6, 8};

cout << s.count(3) << "\n"; // 1
cout << s.count(4) << "\n"; // 0
s.erase(3); 
s.insert(4);

cout << s.count(3) << "\n"; // 0
cout << s.count(4) << "\n"; // 1

// the unique thing about sets, just like in most other programming languages
// is that you can't access via indexing []. you can loop through it, however.

cout << s.size() << "\n"; // size (length) of a set
for (auto x: s) {
    cout << x << "\n";
}

// EXTRAS:
// You can find elements with find() 
s.find(5);
s.swap(sec) // swap set content, bruh :)
```

C++ also contains `multiset` and `unordered_multiset`.

They work just like `set` and `unordered_set`, but they can contain multiple instances of an element.

```cpp
multiset<int> s;
s.insert(5);
s.insert(5);
s.insert(5);
cout << s.count(5) << "\n"; // 3
```

The function `erase` now will remove all instances of an element from a multiset

```cpp
s.erase(5);
cout << s.count(5) << "\n"; // 0
```

Often, only one instance should be remove, which can be done as follows 

```cpp
s.erase(s.find(5));
cout << s.count(5) << "\n"; // 2
```

## Map structures
A generalized array that consists of key-value-pairs.

C++ STL: `map` and `unordered_map` (same like `set` and `unordered_set`).

Code snippets:

```cpp
map<string, int> m;
m["monkey"] = 4;
m["banana"] = 3;
m["harpsichord"] = 9;

cout << m["banana"] << "\n"; // 3
// if the key is requested but the map does not contain it
// => automatically added to the map with a default value.

cout << m["aybabtu"] << "\n"; // 0

// count() or find() to find the element
if (m.count("aybabtu")) {
    // key exists
}

for (auto x : m) {
    cout << x.first << " " << x.second << "\n";
}

```

(You can also use `multimap` and `unordered_multimap` because `map` and `unordered_map` are also unique)

## Iterators and ranges
An iterator is a variable that points to an element in a data structure.

`begin()` and `end()` define a range all elements in the data structure. Quite like this

```
{ 3, 4, 6, 8, 12, 13, 14, 17 }
  |                          |
  s.begin()                  s.end()
```

### Working with ranges

Iterators are used to give ranges, like this:

```cpp
sort(v.begin(), v.end());
reverse(v.begin(), v.end());
random_shuffle(v.begin(), v.end());
```

In ordinary array:

```cpp
sort(a, a+n);
reverse(a, a+n);
random_shuffle(a, a+n);
```

### Set iterators
Iterators can be used to access elements of a set.

```cpp
set<int>::iterator it = s.begin();
// or much shorter
auto it = s.begin();
```

Data in the iterator can be retrieved via

```cpp
auto it = s.begin();
cout << *it << "\n";
```

Operators `++` and `--` to move `forward` or `backward`

```cpp
for (auto it = s.begin(); it != s.end(); it++) {
    cout << *it << "\n";
}
```

The following code prints the largest element in the set:
```cpp
auto it = s.end(); it--;
cout << *it << "\n";
```

The function `find(x)` returns an iterator that points to an element whose value is `x`. If the set does not contain x, the iterator will be `end`

```cpp
auto it = s.find(x);
if (it == s.end())
{
   // x is not found
}
```

`lower_bound()` and `upper_bound` quite the same. These functions are not supported by the `unordered_set` structure which does not maintain the order of the elements.

```cpp
auto it = s.lower_bound(x);
if (it == s.begin()) {
    cout << *it << "\n";
} else if (it == s.end()) {
    it--;
    cout << *it << "\n";
} else {
    int a = *it; it--;
    int b = *it;
    if (x - b < a - x) cout << b << "\n";
    else cout << a << "\n";
}
// assuming that the set is not empty
```

## Other structures
### Bitset
An array whose each value is either 0 or 1

```cpp
bitset<10> s;
s[1] = 1;
s[3] = 1;
s[4] = 1;
s[7] = 1;
cout << s[4] << "\n"; // 1
cout << s[5] << "\n"; // 0
```

Require less memory than ordinary arrays, because each element in a bitset only uses one bit of memory. Also, bitset can be efficiently manipulated using bit operators, which makes it possible to optimize algorithms using bit sets.

```cpp
// another way to create bitset
bitset<10> s(string("0010011010")); // from right to left
cout << s[4] << "\n"; // 1
cout << s[5] << "\n"; // 0

// well because of big/small endian thing.
// count returns the number of ones in the bitset
cout << s.count() << "\n"; // 4

// bit operations
bitset<10> a(string("0010110110"));
bitset<10> b(string("1011011000"));
cout << (a&b) << "\n"; // 0010010000
cout << (a|b) << "\n"; // 1011111110
cout << (a^b) << "\n"; // 1001101110
```

### Deque

A dynamic array whose size can be efficiently changed at both ends of the array. Deque is slower than vector, but still takes O(1) time on average at both ends. 

```cpp
deque<int> d;
d.push_back(5); // [5]
d.push_back(2); // [5, 2]
d.push_front(3); // [3, 5, 2]
d.pop_back();  // [3, 5]
d.pop_front(); // [5] 
```

### Stack

A data structure that provides two O(1) time operations: adding an element to the top, and removing an element from the top. It's only possible to access the top element of a stack.

```cpp
stack<int> s;
s.push(3);
s.push(2);
s.push(5);
cout << s.top(); // 5
s.pop();
cout << s.top(); // 2
```

### Queue
Like a stack, also providing two O(1) operations: adding an element to the end of the queue, and removing the first element in the queue. Only possible to access the first and last element of a queue.

```cpp
queue<int> q;
q.push(3);
q.push(2);
q.push(5);
cout << q.front(); // 3
q.pop();
cout << q.front(); // 2
```

### Priority queue
A priority queue maintains a set of elements. The supported operations are insertion and, depending on the type of the queue, retrieval and removal of either the minimum or maximum element. Insertion and removal take O(log n) time, and retrieval takes O(1) time.

(An ordered set can do it too but)

Benefit: smaller constant factors. A priority queue is usually implemented using a heap structure that is much simpler than a balanced binary tree used in an ordered set.

Default: sort in decreasing order

```cpp
priority_queue<int> q;
q.push(3);
q.push(5);
q.push(7);
q.push(2);
cout << q.top() << "\n"; // 7
q.pop();
cout << q.top() << "\n"; // 5
q.pop();
q.push(6);
cout << q.top() << "\n"; // 6
q.pop();

// if we want smallest element, this would be greater
priority_queue<int, vector<int>, greater<int>> q;
```

### Policy-based data structures
Note: this thing is GNU-only

Basically means those data structures that g++ (a part of GNU C Compiler (gcc)) supports.

Those 2 magic lines will help us gain this power:

```cpp
#include <ext/pb_ds/assoc_container.hpp>
using namespace  __gnu_pbds;
```

Now we can define some fun things, for example
```cpp
typedef tree<int, 
    null_type, 
    less<int>, 
    rb_tree_tag, 
    tree_order_statistics_node_update> 
indexed_set;
// create a set as follows
indexed_set s;
s.insert(2);
s.insert(3);
s.insert(7);
s.insert(9);
// as the name suggested, we can get the element through indexing
auto x = s.find_by_order(2);
cout << *x << "\n"; // 7
cout << s.order_of_key(7) << "\n"; // 2

// if the element does not appear in the set, we get the position
// that the element would have in the set
cout << s.order_of_key(6) << "\n"; // 2
cout << s.order_of_key(8) << "\n"; // 3
// work in logarithmic time

```

(I have tried to dive into the PBDS, here what I've learnt [extra.md](./extra.md))

## Comparison to sorting

It is often possible to solve a problem using either data structure or sorting. 

For example, let's say we are given two lists A and B, and we need to calculate the number of elements that belong to both of the lists.

Straightforward solution: go through all pairs of elements in `O(n^2)` time, but we will focus on more efficient algorithms.

### Algorithm 1
Using the `set` data structure. 

Construct the `set` from A then iterate through the elements of B and check for each elements if it also belongs to A.

Time complexity: `O(n log n)`

### Algorithm 2
We don't need an ordered set, so `unordered_set` would be fine as well.

Time complexity: `O(n)`

### Algorithm 3
Sort both lists A and B. After this, we iterate through both the lists at the same time and find the common elements. Sorting has the time complexity of `O(n log n)`, and the rest of the algorithm works in `O(n)` time, so the total time complexity is `O(n log n)`

### Efficiency comparison
When we compare the effiency of these algorithms we found out an interesting result: Algorithm 3 is much faster than Algorithm 1 and 2. Though Algorithm 1 and 3 both have `O(n log n)` time complexity, again Algorithm 3 is 10x faster than Algorithm 1.

This can be explained by the fact that sorting is a simple procedure and it is done  only once at the beginning of Algorithm 3, and the rest of the algorithm works in linear tie. On the other hand, Algorithm 1 maintains a complex balanced binary tree during the whole algorithm.