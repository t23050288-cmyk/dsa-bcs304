# BCS304 — June/July 2025 Exam
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.1 a) Define data structure. With a neat diagram, explain the classification of data structure. [5]

### Definition
A data structure is the logical or mathematical model of a particular organization
of data — representing relationships between data elements, not just the elements.

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

### Smallest Program
```c
#include <stdio.h>
int main() { int a[3]={1,2,3}; printf("%d\n", a[0]); return 0; }
```

---

## Q.1 b) Explain dynamic memory allocation functions with suitable examples. [5]

### Definition
Dynamic Memory Allocation reserves memory at **run-time** on the **heap** using
`malloc`, `calloc`, `realloc`, and `free`.

### Points
1. `malloc(size)` — allocates uninitialized memory.
2. `calloc(n, size)` — allocates `n` zero-initialized blocks.
3. `realloc(ptr, newsize)` — resizes existing block.
4. `free(ptr)` — releases memory.

### Easiest Program (`programs/DynamicMemoryDemo.c`)
```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *p = (int*) malloc(sizeof(int));
    *p = 100;
    printf("malloc example: %d\n", *p);

    int *arr = (int*) calloc(3, sizeof(int));
    printf("calloc example (zero-init): %d %d %d\n", arr[0], arr[1], arr[2]);

    arr = (int*) realloc(arr, 6 * sizeof(int));
    printf("realloc: array grown to 6 ints\n");

    free(p); free(arr);
    return 0;
}
```

---

## Q.1 c) For the given sparse matrix draw the triplet representation and also draw the transpose of resultant triplet. [10]

### Definition
A sparse matrix (mostly zero elements) is represented compactly as an array of
`<row, col, value>` triplets for its non-zero entries only.

### Points (why triplet representation?)
1. A sparse matrix has MOSTLY ZERO elements — storing all the zeros wastes a
   lot of memory. Example: a 100 x 100 matrix with only 100 non-zero elements
   would use 10,000 memory slots, of which 9,900 store just zero!
2. **Triplet representation** stores ONLY the non-zero elements, using three
   values for each: `<row, col, value>`.
3. The header triple (row 0 of the table) stores the size: total rows, total
   columns, and count of non-zero elements.
4. **Transpose rule**: element `a[i][j]` becomes `b[j][i]` — i.e. the row and
   column of every triple are SWAPPED. The value stays the same.

### Step 1 — The Given Matrix (3 x 3)
```
        col0   col1   col2
row0 [  15      0      0  ]
row1 [   0      0     22  ]
row2 [   0     -6      0  ]
```
Only 3 elements are non-zero: 15 at (0,0), 22 at (1,2), -6 at (2,1).

### Step 2 — Triplet Representation
```
row  col  value
 0    0     3      <- header: 3 rows, 3 cols, 3 non-zero elements
 0    0    15
 1    2    22
 2    1    -6
```

### Step 3 — Transpose of the Triplet (swap row and column of each triple)
```
row  col  value
 0    0     3      <- header: now 3 cols become 3 rows (swapped)
 0    0    15      (was row0,col0 -> stays row0,col0)
 2    1    22      (was row1,col2 -> becomes row2,col1)
 1    2    -6      (was row2,col1 -> becomes row1,col2)
```

Check: the transpose matrix is
```
        col0   col1   col2
row0 [  15      0      0  ]
row1 [   0      0     -6  ]
row2 [   0     22      0  ]
```
which matches the triplets above — so the transpose is correct.

### Program (`programs/SparseMatrixTranspose.c`)
```c
#include <stdio.h>
typedef struct { int row, col, value; } term;

void transpose(term a[], term b[]) {
    int n = a[0].value;
    b[0].row = a[0].col; b[0].col = a[0].row; b[0].value = n;
    if (n > 0) {
        int currentb = 1;
        for (int i = 0; i < a[0].col; i++)
            for (int j = 1; j <= n; j++)
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
    }
}

int main() {
    term a[10] = { {3, 3, 3}, {0, 0, 15}, {1, 2, 22}, {2, 1, -6} };
    term b[10];
    transpose(a, b);
    printf("Transpose:\n");
    for (int i = 1; i <= b[0].value; i++)
        printf("row=%d col=%d value=%d\n", b[i].row, b[i].col, b[i].value);
    return 0;
}
```
