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

### Points
1. **Primitive** — basic types directly operated by machine instructions;
   cannot be divided further. Examples: Integer, Float, Character, Pointer.
2. **Non-Primitive** — derived from primitives; further split into:
   - **Linear** — sequence-based (Arrays via sequential memory, Linked Lists via
     pointers). Examples: Arrays, Queues, Stacks, Linked Lists.
   - **Non-Linear** — hierarchical relationships. Examples: Trees, Graphs.

### The 7 Primitive Operations
1. **Create** — reserves memory for the structure.
2. **Destroy** — releases allocated memory.
3. **Selection** — accessing a particular data item.
4. **Updating** — modifying data.
5. **Searching** — finding a desired item.
6. **Sorting** — arranging items in order.
7. **Merging** — combining two sorted lists into one.

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
