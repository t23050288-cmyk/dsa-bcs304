# BCS304 — Dec 2023/Jan 2024 Exam
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.1 a) Define Data Structures. Explain with neat block schematic different types of data structures with examples. What are the primitive operations that can be performed? [10]

### Definition
A data structure is the logical or mathematical model of a particular organization
of data — it represents the relationships that exist between individual data
elements, not just the elements themselves.

### Classification Diagram
```
                         ┌──────────► Void
                         │
              ┌─Primitive├──────────► Character
              │          │
              │          ├──────────► Integer
              │          │
Data          │          ├──────────► Float
Structures ───┤          │
              │          └──────────► Double
              │
              │              ┌─Linear────► Arrays
              │              │        ├──► Structures
              └─Non-Primitive┤        ├──► Stacks
                             │        ├──► Queues
                             │        └──► Linked Lists
                             │
                             └─Non-Linear─► Trees
                                        └──► Graphs
```

### Full Explanation — Primitive Data Structures

**Primitive data structures** are the basic data types that a machine can directly
operate on. Each one can hold only a **single value** and cannot be divided further.

1. **Integer (int)** — stores whole numbers (no decimal point).
   Example: `int age = 21;` Takes 2 or 4 bytes.
2. **Float (float)** — stores real numbers WITH a decimal point.
   Example: `float price = 99.75;` Takes 4 bytes, about 6 digits accuracy.
3. **Double (double)** — same as float but with double accuracy.
   Example: `double pi = 3.141592653589;` Takes 8 bytes. Used when high precision
   is needed.
4. **Character (char)** — stores ONE letter, digit or symbol inside single quotes.
   Example: `char grade = 'A';` Takes 1 byte.
5. **Void** — means "no value / no type". Used for functions that return nothing,
   e.g. `void display() { ... }`.
6. **Pointer** — a special variable that stores the ADDRESS of another variable.
   Example: `int x = 10; int *p = &x;`

### Full Explanation — Non-Primitive Data Structures

**Non-primitive data structures** are derived from primitive types. They store
**many values together** and define how the values are related to each other.
They are divided into **Linear** and **Non-Linear**.

**A) Linear Data Structures** — elements are arranged in a sequence, one after
another. Each element has exactly one element before it and one after it
(except the first and last).

1. **Array** — a collection of SAME-type elements stored one after another in
   continuous memory locations. Any element is accessed directly by its index.
   Example: `int marks[5] = {90, 80, 85, 70, 95};` — `marks[0]` is 90,
   `marks[1]` is 80, and so on. Size is fixed at creation.
2. **Structure** — a collection of DIFFERENT-type data items grouped under one
   name. Example: a student structure having name (char), age (int) and marks
   (float) together.
3. **Stack** — a LIFO (Last-In First-Out) list. Both insertion (push) and
   deletion (pop) happen at ONE end only, called the top. Real example: a stack
   of plates in a canteen — the last plate kept is taken out first. Used for:
   undo feature, function calls, expression conversion.
4. **Queue** — a FIFO (First-In First-Out) list. Insertion happens at the REAR,
   deletion at the FRONT. Real example: a line of people at a ticket counter —
   the first person to join is served first. Used for: printer job scheduling,
   CPU scheduling.
5. **Linked List** — a collection of nodes, where each node has a data part and
   a pointer part. The pointer stores the address of the NEXT node, so the
   elements need NOT be in continuous memory. Size grows or shrinks at run time.
   Example: `struct node { int data; struct node *next; };`

Note: a linear data structure can be stored in memory in TWO ways — using
**arrays** (continuous locations) or using **linked lists** (connected by
pointers).

**B) Non-Linear Data Structures** — elements are NOT arranged in a sequence.
One element can be connected to MANY elements, showing hierarchical
(parent-child type) relationships.

1. **Tree** — a hierarchical structure starting from one ROOT node at the top.
   Every node (except the root) has exactly ONE parent but can have many
   children. Real examples: a family tree, the folder structure of a computer
   (C:\ → Users → Documents), an organization chart.
2. **Graph** — a collection of VERTICES (points) connected by EDGES (lines).
   Any vertex can connect to any other vertex — no hierarchy. Real examples:
   Google Maps (cities = vertices, roads = edges), a social network (people =
   vertices, friendships = edges).

### Summary Table

| Category | Types | How elements are arranged |
|---|---|---|
| Primitive | int, float, double, char, void, pointer | Single value only |
| Non-Primitive, Linear | Array, Structure, Stack, Queue, Linked List | Sequence, one after another |
| Non-Primitive, Non-Linear | Tree, Graph | Hierarchy or network |

### The 7 Primitive Operations (each explained)
1. **Create** — reserves memory space for the elements of the data structure.
   This can happen at compile-time (e.g. `int a[10];`) or run-time (e.g.
   `malloc`). The structure is created but empty.
2. **Destroy** — releases (deletes) the memory space allocated to the data
   structure, so the memory can be reused. In C this is done using `free()`.
3. **Selection** — accessing a particular data item from the structure when
   needed. Example: accessing `marks[3]` from an array.
4. **Updating** — changing (modifying) the value of an existing data item in
   the structure. Example: `marks[3] = 95;`
5. **Searching** — finding out whether a given data item is present in the
   structure, and if so, where. Example: searching for roll number 25 in a
   student list.
6. **Sorting** — arranging all data items of the structure in a particular
   order (ascending or descending). Example: arranging marks from lowest to
   highest.
7. **Merging** — combining the data items of TWO different sorted lists into
   ONE single sorted list. Example: merging two sorted batches of exam marks
   into one list.

### Easiest Program
```c
#include <stdio.h>
int main() {
    int a = 10; char c = 'A'; float f = 3.14;           /* primitive types */
    int arr[5] = {1,2,3,4,5};                             /* non-primitive: linear */
    printf("int=%d char=%c float=%.2f array[2]=%d\n", a, c, f, arr[2]);
    return 0;
}
```

---

## Q.1 b) Differentiate between structures and unions with examples for both. [5]

### Definitions
**Structure**: a collection of data items where each has its own type/name, and
each member gets its **own** separate memory space.
**Union**: similar, but all members **share** the same memory — only one is
"active" at a time.

### Comparison Table

| Basis | Structure | Union |
|---|---|---|
| Memory | Each member gets its own space | All members share the same space |
| Size | Sum of all members (+ padding) | Size of the largest member only |
| Active members | All valid simultaneously | Only one valid at a time |
| Keyword | `struct` | `union` |

### Program (`programs/StructVsUnion.c`)
```c
#include <stdio.h>

struct StructExample { int i; float f; char c; };
union UnionExample { int i; float f; char c; };

int main() {
    struct StructExample s;
    union UnionExample u;

    printf("Size of struct: %lu bytes\n", sizeof(s));
    printf("Size of union : %lu bytes\n", sizeof(u));

    s.i = 10; s.f = 3.14; s.c = 'A';
    printf("Struct: i=%d f=%.2f c=%c (all still valid)\n", s.i, s.f, s.c);

    u.i = 10;
    printf("Union after setting i: i=%d\n", u.i);
    u.f = 3.14;
    printf("Union after setting f: f=%.2f (i is now garbage: %d)\n", u.f, u.i);

    return 0;
}
```

---

## Q.1 c) What do you mean by pattern matching? Outline Knuth Morris Pratt (KMP) pattern matching algorithm. [5]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Definition
Pattern matching is the process of finding whether (and where) a smaller string
(the **pattern**) occurs within a larger string (the **text**).

### Points
1. Naive method checks every text position character-by-character — O(n·m) time.
2. **KMP** avoids re-checking matched characters by precomputing a **failure
   function** `f(j)` for the pattern.
3. `f(j)` = largest `i < j` such that the pattern's first `i+1` characters match
   the `i+1` characters ending at position `j` — or `-1` if none exists.
4. On a mismatch at pattern position `j`, KMP jumps to `f(j-1)+1` instead of
   restarting — skipping unnecessary comparisons.
5. Overall time: **O(n + m)** — much faster than the naive method.

### Program (`programs/KMPPatternMatch.c`)
```c
#include <stdio.h>
#include <string.h>

int failure[100];

void computeFailure(char *pat) {
    int n = strlen(pat);
    failure[0] = -1;
    for (int j = 1; j < n; j++) {
        int i = failure[j - 1];
        while (pat[j] != pat[i + 1] && i >= 0) i = failure[i];
        if (pat[j] == pat[i + 1]) failure[j] = i + 1;
        else failure[j] = -1;
    }
}

int pmatch(char *text, char *pat) {
    int i = 0, j = 0;
    int lenT = strlen(text), lenP = strlen(pat);
    computeFailure(pat);
    while (i < lenT && j < lenP) {
        if (text[i] == pat[j]) { i++; j++; }
        else if (j == 0) i++;
        else j = failure[j - 1] + 1;
    }
    return (j == lenP) ? (i - lenP) : -1;
}

int main() {
    char text[] = "abxabcabcaby";
    char pat[]  = "abcaby";
    int pos = pmatch(text, pat);
    if (pos != -1) printf("Pattern found at index %d\n", pos);
    else printf("Pattern not found\n");
    return 0;
}
```
