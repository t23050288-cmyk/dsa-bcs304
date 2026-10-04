# BCS304 — Model Question Paper (2023-24 CBCS Scheme)
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.01 a) Define data structures. With a neat diagram, explain the classification of data structures with examples. [5]

### Definition
A data structure is the logical or mathematical model of a particular organization
of data — representing relationships between data elements.

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

---

## Q.01 b) What do you mean by pattern matching? Outline the KMP algorithm and illustrate it. [8]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Definition
Pattern matching finds whether/where a **pattern** occurs within a **text**.

### KMP Failure Function Example (`pat = abcabcacab`)

| j | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|---|---|---|---|---|---|---|---|---|---|---|
| pat | a | b | c | a | b | c | a | c | a | b |
| f | -1 | -1 | -1 | 0 | 1 | 2 | 3 | -1 | 0 | 1 |

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
        failure[j] = (pat[j] == pat[i + 1]) ? i + 1 : -1;
    }
}
int pmatch(char *text, char *pat) {
    int i = 0, j = 0, lenT = strlen(text), lenP = strlen(pat);
    computeFailure(pat);
    while (i < lenT && j < lenP) {
        if (text[i] == pat[j]) { i++; j++; }
        else if (j == 0) i++;
        else j = failure[j - 1] + 1;
    }
    return (j == lenP) ? (i - lenP) : -1;
}
int main() {
    int pos = pmatch("abxabcabcaby", "abcaby");
    printf(pos != -1 ? "Found at %d\n" : "Not found\n", pos);
    return 0;
}
```

---

## Q.02 a) Explain in brief the different functions of dynamic memory allocation. [5]

### Definition
Dynamic Memory Allocation reserves memory at **run-time**, on the **heap**.

### The 4 Functions
1. `malloc(size)` — allocate, uninitialized.
2. `calloc(n, size)` — allocate n blocks, zero-initialized.
3. `realloc(ptr, newsize)` — resize existing block.
4. `free(ptr)` — deallocate.

### Program (`programs/DynamicMemoryDemo.c`)
```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *p = (int*) malloc(sizeof(int)); *p = 5;
    int *arr = (int*) calloc(3, sizeof(int));
    arr = (int*) realloc(arr, 6 * sizeof(int));
    printf("malloc=%d, calloc[0]=%d, realloc done\n", *p, arr[0]);
    free(p); free(arr);
    return 0;
}
```

---

## Q.02 b) Write functions in C (without built-in functions): (i) Compare two strings (ii) Concatenate two strings (iii) Reverse a string. [8]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Points
1. **Compare**: walk both strings char by char; return 0 if all match and both
   end together, else the difference of the first mismatched chars.
2. **Concatenate**: find the end (`\0`) of the first string, then copy the second
   string's characters starting there.
3. **Reverse**: swap characters from both ends inward.

### Program (`programs/StringFunctions.c`)
```c
#include <stdio.h>

int myStrcmp(char *s1, char *s2) {
    while (*s1 && *s2) { if (*s1 != *s2) return *s1 - *s2; s1++; s2++; }
    return *s1 - *s2;
}

void myStrcat(char *dest, char *src) {
    while (*dest) dest++;
    while (*src) *dest++ = *src++;
    *dest = '\0';
}

void myStrrev(char *s) {
    int i = 0, j = 0;
    while (s[j] != '\0') j++;
    j--;
    while (i < j) { char t = s[i]; s[i] = s[j]; s[j] = t; i++; j--; }
}

int main() {
    char a[50] = "Hello", b[] = "World";
    printf("Compare: %d\n", myStrcmp(a, b));
    myStrcat(a, b);
    printf("Concat: %s\n", a);
    myStrrev(a);
    printf("Reverse: %s\n", a);
    return 0;
}
```
