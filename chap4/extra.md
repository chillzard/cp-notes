# Extra notes, way more beyond

## Policy-based data structures
Policy-based data structures (or in short, PBDS) support more than just what the CP book said, so I'll try to explore in depth about PBDS itself.

PBDS, offered by GNU, provide more structures to solve problems but relying on them is not really advised. Because not all contests support g++, some may use different C compiler. However, for the sake of curiosity, I will take a deeper path into the massive rabbit hole of PBDS to show how powerful it can be to solve lots of problems.

The best way to learn G++ PBDS is to go to gcc official mirror here:
[GCC PBDS mirror](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/ext/pb_ds) and read through those header files. But of course if that's the case I wouldn't have to write all these things down like this, so to save time for the future I will summarize all the things I have learnt here.

### Basic
Let's start with the very basic overview. Just create an ordered_set through PBDS and it would look like this

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // associative containers, all the containers you want will be here
#include <ext/pb_ds/tree_policy.hpp> // for methods for tree data structure, which is essential to build up ordered_set

using namespace __gnu_pbds;
using namespace std;

// for general declaration, it will look like this 
template <typename T> // template for generic type T
// and this is the main declaration
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

// from here we can do a lot of things like this
// here are just the core operations of ordered_set
// this won't be possible without the support of tree_policy.hpp
int main() {
    ordered_set<int> s;

    s.insert(10);
    s.insert(5);
    s.insert(20);

    // Print the 0th, 1st, 2nd smallest elements
    cout << *s.find_by_order(0) << "\n";  // 5
    cout << *s.find_by_order(1) << "\n";  // 10
    cout << *s.find_by_order(2) << "\n";  // 20

    // Number of elements strictly less than 15
    cout << s.order_of_key(15) << "\n";   // 2 (5 and 10)

    // Number of elements strictly less than 10
    cout << s.order_of_key(10) << "\n";   // 1 (only 5)

    // Erase an element
    s.erase(10);
    cout << s.order_of_key(20) << "\n";   // now it's 1
}

```

So we can see, this is our skeleton on the use case of PBDS in real code. In fact, we only need to concern two main things when looking at this code snippet:

- How can we declare our structures? For example, `ordered_set` is declared through this code snippet

```cpp
template <typename T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
```

But what do all these mean to us? And how can we replicate a declaration just like that?

- How can we use our structures? `ordered_set` supports `insert`, `order_of_key` and `find_by_order`, but are there really all the things PBDS support? Sure there must be more, right?

This whole note will capture all the important details and knowledge I (and you) should know about Policy-based Data Structures based on two concerns I have declared.

### Declaration
`<ext/pb_ds/assoc_container.hpp>` is the main recipe to enable PBDS in your code. After declaring this, you can start using PBDS that you need.

Make sure to `using namespace __gnu_pbds` to get all the essential utilities in the `__gnu_pbds` namespace (apparently). Note that there are no other external utils outside this namespace, so don't worry that you would miss anything.

As the name suggested, `assoc_container.hpp` means "associative container". Associative containers are the core of the PBDS (Policy-based Data Structures), so that's why we have to declare them first, then we can add the policy and tag layer to make it usable. There are four associative containers supported by PBDS.

#### Tree-based Containers (tree)

It's just basically tree, and this container is the most popular one, since it can be used to declare literally everything.

This is the declaration of tree in the `<ext/pb_ds/assoc_container.hpp>`

```cpp
/**
   *  A tree-based container.
   *
   *  @tparam Key 	 	    Key type.
   *  @tparam Mapped 	    Map type.
   *  @tparam Cmp_Fn	    Comparison functor.
   *  @tparam Tag 	 	    Instantiating data structure type,
   *                            see container_tag.
   *  @tparam Node_Update 	Updates tree internal-nodes,
   *                            restores invariants when invalidated.
   *                    XXX See design::tree-based-containers::node invariants.
   *  @tparam _Alloc 	 	Allocator type.
   *
   *  Base tag choices are: ov_tree_tag, rb_tree_tag, splay_tree_tag.
   *
   *  Base is basic_branch.
   */
```

For example, the `ordered_set` data type that we've just declared is also based on the tree container.

Let's take a look

```cpp
template <typename T>
using ordered_set = tree<
    T, // as we have declared in the template, this is going to be our Key type 
    null_type, // Map type, here `null_type` means that this tree is a set
    less<T>, // Comparison **functor**, here it indicates that the set will be sorted in the increasing order
    rb_tree_tag, // Red-black tree tag, this is a tag, which will cover in the later session
    tree_order_statistics_node_update // how we updated our data structure, this won't be possible without the import of `<ext/pb_ds/tree_policy.hpp>`
    // again, we'll discuss deeper on this policy in the later session
>; 
```

Tree of course offers extra functionalities through tags and policies via `<ext/pb_ds/tree_policy.hpp>`. They will be discussed in depth in the later session.

From now on, we need to just take a quick look at how it's supposed to look like, and what we can do with it. Tree has a lot of use cases because of its nature: it will structurize a custom defined data structure into a tree (Red-Black tree by default). Much like `set` for example which is also based on a balancing binary tree, the same thing happens when we define `ordered_set` through Tree PBDS.

Tree containers are particularly useful in these scenarios (note that it might be slower because of metadata):
- `ordered_set`, `ordered_map`, `ordered_multiset` and `ordered_multimap`. Since this tree is ordered associative container, this is simply perfect
```cpp
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                              tree_order_statistics_node_update>;

template<typename Key, typename Value>
using ordered_map = tree<
    Key, Value, less<Key>, rb_tree_tag,
    tree_order_statistics_node_update>;

template<typename Key, typename Value>
using ordered_multimap = tree<
    Key, Value, less_equal<Key>, rb_tree_tag,
    tree_order_statistics_node_update>;
```  
- Finding the K-th Smallest/Largest element in Dynamic Data
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

ordered_set<int> s;
s.insert(10);
s.insert(20);
s.insert(30);

// Find the 2nd smallest element (0-based)
cout << *s.find_by_order(1); // Output: 20
```
- Rank Queries
```cpp
ordered_set<int> s;
s.insert(5);
s.insert(2);
s.insert(6);

// Number of elements < 4
cout << s.order_of_key(4); // Output: 1 (only 2 is less than 4)

// Get 1st smallest element (0-based)
cout << *s.find_by_order(1); // Output: 5
``` 
- Count inversions
```cpp
ordered_set<int> s;
int inversions = 0;
for (int i = 0; i < n; i++) {
    inversions += s.size() - s.order_of_key(arr[i]);
    s.insert(arr[i]);
}
cout << inversions;
```

#### Hash-based Containers (hash)

Hash can be used to declare data structures that are based on hashing. Like `unordered_set` for example, with better performance and better control.

Hash also supports its policies via `<ext/pb_ds/hash_policy.hpp>`, which will be covered in the later session.

There are two types of hash containers that you should remember: `cc_hash_table` (through chaining) and `gp_hash_table` (through Linear Probing, faster for CP)

Here's the definition of `cc_hash_table` and `gp_hash_table`

```cpp

// this is cc_hash_table
  /**
   *  A collision-chaining hash-based associative container.
   *
   *  @tparam Key 	    	Key type.
   *  @tparam Mapped 	    	Map type.
   *  @tparam Hash_Fn	    	Hashing functor.
   *  @tparam Eq_Fn	    	Equal functor.
   *  @tparam Comb_Hash_Fn	Combining hash functor.
   *                            If Hash_Fn is not null_type, then this
   *                            is the ranged-hash functor; otherwise,
   *                            this is the range-hashing functor.
   *                    XXX(See Design::Hash-Based Containers::Hash Policies.)
   *  @tparam Resize_Policy 	Resizes hash.
   *  @tparam Store_Hash    	Indicates whether the hash value
   *                            will be stored along with each key.
   *                            If Hash_Fn is null_type, then the
   *                            container will not compile if this
   *                            value is true
   *  @tparam _Alloc 	    	Allocator type.
   *
   *  Base tag choices are: 	cc_hash_tag.
   *
   *  Base is basic_hash_table.
   */
```

```cpp
// this is gp_hash_table
  /**
   *  A general-probing hash-based associative container.
   *
   *  @tparam Key 	    	Key type.
   *  @tparam Mapped 	    	Map type.
   *  @tparam Hash_Fn	    	Hashing functor.
   *  @tparam Eq_Fn	    	Equal functor.
   *  @tparam Comb_Probe_Fn	Combining probe functor.
   *                            If Hash_Fn is not null_type, then this
   *                            is the ranged-probe functor; otherwise,
   *                            this is the range-hashing functor.
   *                    XXX See Design::Hash-Based Containers::Hash Policies.
   *  @tparam Probe_Fn		Probe functor.
   *  @tparam Resize_Policy 	Resizes hash.
   *  @tparam Store_Hash    	Indicates whether the hash value
   *                            will be stored along with each key.
   *                            If Hash_Fn is null_type, then the
   *                            container will not compile if this
   *                            value is true
   *  @tparam _Alloc 	    	Allocator type.
   *
   *  Base tag choices are: 	gp_hash_tag.
   *
   *  Base is basic_hash_table.
   */
```

As you can see, the core difference of `cc_hash_table` and `gp_hash_table` is the hashing method: collision-chaining or general-probing.

This will be discussed deeper with Tree containers and other containers in another session. From now on I don't want to dive into the technical understanding, what we all need to grasp in our mind is the fact that they exist and in what case we will use them.

As I said before, hash-based containers are used for structures that need hashing, for example `unordered_set` and `unordered_map`. This can result in a faster implementation and execution time, which is beneficial in contests.

The most basic use cases of hash-based containers will be:
- Frequency Maps: much faster than `unordered_map` and useful in subarray problems, frequency queries, etc.
```cpp
gp_hash_table<int, int> freq;
for (int x : arr) freq[x]++;
```
- Hash set with large domain: custom structs and data structures with custom hash, useful in checking duplicates or visited states 
```cpp
gp_hash_table<long long, null_type> seen;
```
- Graph problems: for adjacency lists like this one:
```cpp
gp_hash_table<int, vector<int>> graph;
// Also for visited maps in BFS/DFS with large sparse graphs
```
- Dynamic Programming with Hashing: `dp[state] = value` where state is a tuple, string or mask
```cpp
// custom hash: faster and safer
gp_hash_table<pair<int,int>, int, hash_pair> dp;
```
- Subarray Hashing (for strings): Store prefix hashes in gp_hash_table to check for duplicates or repeats

#### Trie-based Containers (trie)

Trie, or prefix trees, digital trees, are the data structure used for fast string and prefix lookups. It's most commonly used in finding strings in dictionary or set for example.

Here is the definition of trie:

```cpp
 /**
   *  A trie-based container.
   *
   *  @tparam Key 	  	Key type.
   *  @tparam Mapped 	  	Map type.
   *  @tparam _ATraits	  	Element access traits.
   *  @tparam Tag 	  	Instantiating data structure type,
   *                            see container_tag.
   *  @tparam Node_Update 	Updates trie internal-nodes,
   *                            restores invariants when invalidated.
   *                     XXX See design::tree-based-containers::node invariants.
   *  @tparam _Alloc 	  	Allocator type.
   *
   *  Base tag choice is pat_trie_tag.
   *
   *  Base is basic_branch.
   */
```

Trie supports its policies via `<ext/pb_ds/trie_policy.hpp>`. This will be discussed in the later session.

Since trie are specialized in string search, it can be used to:
- Prefix search (Autocomplete, for example): Search for strings through prefixes
```cpp
trie<
    string, null_type,
    trie_string_access_traits<>,
    pat_trie_tag,
    trie_prefix_search_node_update
> words;

words.insert("apple");
words.insert("application");
words.insert("banana");

auto range = words.prefix_range("app");
for (auto it = range.first; it != range.second; ++it)
    cout << *it << "\n";  // Output: apple, application

```
Or maybe make a trie that keeps track how many words share a given prefix.
- Lexicographic Sorting by default, which is great in case you need alphabetical ordered structure.
- String set with collisions: much safer and ofter faster

#### List-update Containers (list_update)

This is a self-organizing list, where every elements are reordered based on access patterns. It is used in rarely-seen cases like move-to-front lists.

Here is the definition:
```cpp
  /**
   *  A list-update based associative container.
   *
   *  @tparam Key 	    	Key type.
   *  @tparam Mapped 	    	Map type.
   *  @tparam Eq_Fn	    	Equal functor.
   *  @tparam Update_Policy	Update policy, determines when an element
   *                            will be moved to the front of the list.
   *  @tparam _Alloc 	    	Allocator type.
   *
   *  Base is detail::lu_map.
   */
```

List-update policies can be accessed via `<ext/pb_ds/list_update_policy.hpp>`

List-update containers are great because they can reorganize themselves given the base pattern without us explicitly reordering them. Here are their use cases:
- LRU Cache Simulation (Least Recently Used)
```cpp
// Goal: Evict the least recently used item when cache is full.
// Strategy: Move the accessed item to the front. If cache is full, delete the last.

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

list_update<int> cache;  // default policy is move-to-front

void access(int x) {
    auto it = cache.find(x);
    if (it == cache.end()) {
        if (cache.size() == 3) // let's say capacity = 3
            cache.erase(--cache.end()); // remove least recently used
        cache.insert(x);
    }
    else {
        cache.modify(it, x); // moves x to front
    }
}

int main() {
    access(1);
    access(2);
    access(3);
    access(2); // Access 2 again → move it to front
    access(4); // Insert 4, evict 1 (least recently used)
    
    for (int x : cache) cout << x << " "; 
    // Output: 4 2 3
}

``` 
- Self-Optimizing Dictionary
```cpp
// Goal: Frequently searched words become easier/faster to access.
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

list_update<string> dictionary;

int main() {
    dictionary.insert("apple");
    dictionary.insert("banana");
    dictionary.insert("carrot");

    dictionary.find("banana"); // Access banana → moves to front

    for (auto word : dictionary)
        cout << word << " "; 
    // Output: banana apple carrot
}

```
- Move-to-front Encoding
```cpp
// Goal: When you access a symbol, bring it to the front to reduce redundancy.
// This idea is used in compression algorithms like BWT + MTF.

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

list_update<char> symbols;

int main() {
    for (char c = 'a'; c <= 'e'; ++c)
        symbols.insert(c);

    symbols.find('c'); // access 'c', moves to front
    symbols.find('a'); // access 'a', moves to front

    for (auto ch : symbols)
        cout << ch << " ";
    // Output: a c b d e
}

```
- Dynamic Task Prioritization
```cpp
// Goal: Tasks that are accessed more often should bubble to the top.
// Imagine an operating system’s task scheduler.
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

list_update<int> tasks;

int main() {
    tasks.insert(1); // Task 1
    tasks.insert(2); // Task 2
    tasks.insert(3); // Task 3

    tasks.find(2);   // Task 2 accessed
    tasks.find(3);   // Task 3 accessed
    tasks.find(3);   // Task 3 accessed again

    for (auto task : tasks)
        cout << task << " ";
    // Output: 3 2 1
}
```

### Utilization
Now we will come to the more technical part. After having a brief overview of what PBDS might look like and also its declaration, it's time to dive deeper into what these things are actually meant to be.

Specifically, we will discuss deeper about tags, traits and policies of each associative containers (since I made them too ambiguous because we only needed to have a first glance at it). We will also have some insights on each types of data structures, like Red-Black tree, so it might end up becoming a lecture in data structures (maybe, it will overlap the content of the later chapters in Competitive Programmer's Handbook). But since the whole note was written by a learner myself, I will take this chance to learn as much as I can do through this note, so that it will be useful for me in the future.

We will cover each of the four containers like we did in the last session, so if you want to, let's say, learn a container in the whole not splitting in half like I do now, be aware. 

Now let's start again

#### Tree-based Containers (tree)

Let's take a look at the definition of tree again.

```cpp
/**
   *  A tree-based container.
   *
   *  @tparam Key 	 	    Key type.
   *  @tparam Mapped 	    Map type.
   *  @tparam Cmp_Fn	    Comparison functor.
   *  @tparam Tag 	 	    Instantiating data structure type,
   *                            see container_tag.
   *  @tparam Node_Update 	Updates tree internal-nodes,
   *                            restores invariants when invalidated.
   *                    XXX See design::tree-based-containers::node invariants.
   *  @tparam _Alloc 	 	Allocator type.
   *
   *  Base tag choices are: ov_tree_tag, rb_tree_tag, splay_tree_tag.
   *
   *  Base is basic_branch.
   */
```

Usually when we declare the tree, we will do quite like this:

```cpp
// TODO: READ THE COMMMENTS BELOW TO UNDERSTAND
// DEEPER ON HOW THINGS ACTUALLY WORK

typedef tree<
    int, // our key type
    int, // our map type, so this tree will have each node containing a pair of key-map value (int-int to be exact), 
    // like an element in a normal map
    // we learnt that if we declare `null_type`, then it's a set. Well clearly, because each keys are all unique
    // so a tree with an element that only have the key value, the map value in null, it's just basically, a set
    less<int>, // comparison functor that indicates that we will sort keys with the previous value being `less`
    // than the next value, a.k.a sort in an increasing order
    // 
    // now the real part is here
    rb_tree_tag, // our tree tag
    tree_order_statistics_node_update, // our policy
    // tag and policy will be explained after you have read all of these comments 
> sample_map;
```

What we really concern about when we declare tree is our tag and our policy to use. They are important, because they are required.

But what are tags and policy anyway?

Technically, tags are the defined description on how the tree might behave. In other words, what kind of the tree will be. 

Meanwhile, policies are extra functionalities that go along with tree, so that the tree can actually do something.

In tree, we have three base tags: `rb_tree_tag` for Red-Black tree, `splay_tree_tag` for Splay Tree Tag, and `ov_tree_tag` for Ordered-Vector Tree. We also have two policy: `tree_order_statistics_node_update` and `null_node_update`.

##### (Tag) Red-Black Tree

For those who knows about Red-Black Tree: you can enable your tree type with `rb_tree_tag` to specify that your tree will be a red-black tree, much like this:

```cpp
typedef tree<
// ....
rb_tree_tag, // no extra code, just this
// .... 
> sample;
```

For those who doesn't know about Red-Black Tree: here we will have a crash course on it

Red-Black Tree is a self-balancing binary search tree data structure noted for fast storage and retrieval of ordered information. The nodes of the tree are colored as "black" or "red", and with a set of rules, they can ensure to keep the tree balanced while also providing a logarithmic time complexity of each operations.

Visualize and it will look like this (source: wiki):

![Red-Black Tree demonstration - source from Wiki](https://upload.wikimedia.org/wikipedia/commons/thumb/c/ce/Red-black_tree_example_with_sockets.svg/330px-Red-black_tree_example_with_sockets.svg.png)

Basically it's just a binary tree (meaning it's ordered, internal node less than right and greater than left whatever), but Red-Black Tree has some more requirements to ensure it's always balanced:

1. Every node is either red or black
2. All null nodes are considered black
3. A red node does not have a red child
4. Every path from a given node to any of its leaf nodes goes through the same number of black nodes
5. (Conclusion) If a node N has exactly one child, the child must be red. If the child were black, its leaves would sit at a different black depth than N's null node (which is considered black by rule 2), violating requirement 4

Because of requirement 4, we have two terminologies: black depth and black height. Black depth of a node is the number of black nodes from the root to that node (the number of black ancestors). Black height of a red-black tree is the number of black nodes in any path from the root to the leaves. The black height of a node is the black height of the subtree rooted by it. 

(some also claims that root node is black, but wiki omitted it because it's quite redundant)

Violate requirement 3 is called red-violation, whereas violate requirement 4 is called black-violation. 

Search and tree traversal, do not effect any of the requirements. In contrast, the modifying operations insert and delete easily maintain requirements 1 and 2, but with respect to the other requirements some extra effort must be made to avoid red-violation or black-violation.

Red-Black tree is height-balanced, because it ensures: *the path from the root to the farthest leaf is no more than twice as long as the path from the root to the nearest leaf*.

Since this is just a note in PBDS not a data structure note, I won't go in depth on how to implement a red-black tree. We just know that it exists, and we take it for grant in PBDS via `rb_tree_tag`. If you wish to learn more about Red-Black Tree here's the link heading to its official wiki page: [Red-Black Tree Wiki](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)

##### (Tag) Splay Tree 

You can use the Splay Tree structure via this tag `splay_tree_tag`. Here's the pseudo code to demonstrate how to use it

```cpp
typedef tree<
/// ....
splay_tree_tag, // tag here
// ....
> sample;
```

![Splay Tree demonstration - original from https://cs.lmu.edu/~ray/notes/splaytrees/](https://cs.lmu.edu/~ray/images/splay.png)

Splay Tree is also a binary search tree with the additional property that recently accessed elements are quick to access again. 

The most recently accessed or inserted element will be brought to the root of tree by performing a sequence of tree rotations, called *splaying*.

Splay tree does not guarantee a balanced tree structure, and its tree height can be linear, which may lead to performance degradation in worst-case scenarios.

Operations for Splay Tree are split, join, insertion, deletion, search and  rotation. Rotations in Splay Tree can be a combination Zig, Zig-Zig or Zig-Zag.

1. Zig Rotation (Single)
Occurs when the node is a direct child of the root.

```
      x                y
     /    or           \
    y                   x
```

2. Zig-Zig Rotation (Double)
Occurs when both the node and its parent are either left or right children

```
      z              x
     /              \
    y      =>        y
   /                  \
  x                    z
```

3. Zig-Zag Rotation (Double)
Occurs when the node is a left child of a right child or vice versa

```
      z                 x
     / \              / \
        y     =>     z   y
       /                 \
      x                   x
```

For more information, head over to [Splay Tree Wiki](https://en.wikipedia.org/wiki/Splay_tree)

##### (Tag) Ordered-Vector Tree
Well, it's advised not to use `ov_tree_tag` for declaration, technically this tag tells PBDS to implement the tree structure using a flat, vector-based storage model rather than a dynamically balanced binary tree, allowing cache locality optimization as well as sequential access (you rarely insert or delete but rather just read the data). But this tag is not well-supported as well as potential errors might occur. Consider using another tag rather than this.

##### Policy: null_node_update

This is basically just nothing, practically.

Normally, PBDS has augmented information (metadata) at each node. `null_node_update` basically says that there's no need for such things like that.

It's used to make a fast, minimal, clean tree with no extra functionalities embedded into it, or basically, barebones, just a basic ordered set/map.

##### Policy: tree_order_statistics_node_update

This is the most frequently used tree policy and the only policy that's declared in `tree_policy.hpp`

Two of the most important operations are `order_of_key` and `find_by_order`

##### Note

For some utilities like `insert`, `erase`, `erase_if`, `erase_node`, `remove_node`, etc. well they are pretty much the same as other data structures supported in the STL so it's not really worth mentioning here. However, you can still find the available methods inside `<ext/pb_ds/detail/?>` where `?` is your desired type of tree. For example let's say I want to find some of the utilities that I need for Red-Black Tree, well when I viewed the source code of [PBDS](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/ext/pb_ds) I found out the directory called `rb_tree_map_` in the `detail` directory, which was pretty all I needed for Red-Black Tree. Here you can see all the `.hpp` files for declaration of every single functionalities that Red-Black Tree has, which is very convenient.

#### Hash-based Containers (hash)

Now we already had the prior knowledge about tags and policies, here I'm going to quickly go through every single things we need to concern about when we use Hash-based Containers.

There are two hash-based containers, `cc_hash_table` and `gp_hash_table`. 

`cc_hash_table` stands for Collision-Chaining Hash Table, while `gp_hash_table` stands for General-Probing Hash Table.

Revision: Hashing is the process of converting **data** into a **fixed-size integer** (called a **hash** or a **hash code**)

This hash is then used as an **index** in an array (called a **hash table**) to store or retrieve values.

Based on this definition, there will be a chance two things hash to the same index, which is called "collision".

Collision-Chaining handles this by "chaining" those values into a linked list. Quite like this:

```
[0] : 0
[1] : 2 -> 3
[2] : 3
[3] : 1

// index (key) 1 has a collision, so those values chain to become a linked list stored in [1]
// so technically every single keys here just store a linked list.
```

General Probing: the value is placed in the next available slot when a collision occurs.

```
hash("apple") = 5
Index 5 is full → Try 6 → Try 7 → ...
```

In general, we would prefer `gp_hash_table` more than `cc_hash_table` because of efficiency and no overload memory.

Technically when you use Hash table you only need to write like this:

```cpp
cc_hash_table<int, string> cc_map;
gp_hash_table<int, string> gp_map;
```

However, if you want to have more customizability, you need to consider tags and policies here.

For tags, usually we don't need to declare, because `cc_hash_table` and `gp_hash_table` already have a base tag in its implementation.

What we really care is policies, and not surprisingly, Hash tables policies are really, really varied to document all of them. As usual, this would be your best source to search for all the features that they have [PBDS](https://github.com/gcc-mirror/gcc/tree/master/libstdc%2B%2B-v3/include/ext/pb_ds). For the sake of this note, I will just extract some reference that is worth noticing.

Generally, this is our declaration:

```cpp
gp_hash_table<
    Key,
    Mapped,
    Hash_Fn,             
    Eq_Fn,               
    Probe_Fn,            
    Resize_Policy,       
    Store_Hash,          
    Allocator            
>
```

From here we have:

##### Hash Function (Hash_Fn)

- `std::hash<Key> (default)`

- Custom example:
```cpp
struct custom_hash {
    size_t operator()(Key x) const {
        return ...;
    }   
};
```

##### Equality Function (Eq_Fn)

- `std::equal_to<Key> (default)`

##### Probe Function / Collision Resolution (Probe_Fn)

- `linear_probe_fn<>`

- `quadratic_probe_fn<>`

Supporting range hashing:

- `direct_mask_range_hashing<>`

- `direct_mod_range_hashing<>`

##### Resize Policy (Resize_Policy)

- `hash_standard_resize_policy<SizePolicy, TriggerPolicy>`

SizePolicy options:

- `hash_exponential_size_policy<>`
- `hash_prime_size_policy<>`

TriggerPolicy options:

- `hash_load_check_resize_trigger<>`
- `cc_hash_max_collision_check_resize_trigger<>` (for cc_hash_table)

##### Store Hash (Store_Hash)

Optional: `hash_store_hash<>`

##### Allocator

- `std::allocator<std::pair<const Key, Mapped>> (default)`

#### Trie-based Containers (trie)

For Trie, there are two tags: `trie_tag` and `pat_trie_tag` (PATRICIA Trie Tag). `trie_tag` is just basic trie structure, while `pat_trie_tag` is Patricia Trie Tag, or more commonly known as Radix Tree is by default the base tag of `trie`.

To make it simple, Standard Trie (basic/vanilla trie) just stores one character on each node, while Radix Tree stores "words", which lead to much more efficiency during runtime. Specifically, Radix Tree will group every node that only has one child each into a "word", which makes it harder to implement but it is also much more efficient than Standard Trie.

For policies, again they are varied so as I said before, we will just cover a little bit about them.

There are three policies that are declared in `trie_policy.hpp`, and there are:
- `trie_string_access_traits` (typically for `_ATraits`)
- `trie_prefix_search_node_update`: enable prefix searching in the trie
- `trie_order_statistics_node_update`: order-statistics operations

#### List-update Containers (List_update)
Well there's only one tag for List_update, it's `list_update_tag`

There are two policies that are declared in `list_update_policy.hpp`:
- `lu_move_to_front_policy`: Move-To-Front when an element is accessed
- `lu_counter_policy`: frequency-based reordering policy
