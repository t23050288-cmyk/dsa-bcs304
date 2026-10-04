# BCS304 — Dec 2024/Jan 2025 Exam
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.1 a) Define Data Structures. Explain the classification of data structures with a neat diagram. [8]

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

### Easiest Program
```c
#include <stdio.h>
int main() {
    int a = 10; char c = 'A'; float f = 3.14;
    int arr[5] = {1,2,3,4,5};
    printf("int=%d char=%c float=%.2f array[2]=%d\n", a, c, f, arr[2]);
    return 0;
}
```

---

## Q.1 c) Differentiate structures and unions. [5]

### Definitions
**Structure**: each member gets its **own** memory space. **Union**: all members
**share** the same memory space.

### Comparison Table

| Basis | Structure | Union |
|---|---|---|
| Memory | Each member independent | All members overlap |
| Size | Sum of all members | Size of largest member |
| Active members | All valid at once | Only one at a time |

### Program (`programs/StructVsUnion.c`)
```c
#include <stdio.h>
struct S { int i; float f; char c; };
union U { int i; float f; char c; };
int main() {
    struct S s; union U u;
    printf("struct size: %lu, union size: %lu\n", sizeof(s), sizeof(u));
    return 0;
}
```

---

## Q.2 b) Explain the dynamic memory allocation function in detail. [8]

### Definition
Dynamic Memory Allocation reserves memory at **run-time** on the **heap**, used
when storage requirements are unpredictable at compile time.

### The 4 Functions
1. **malloc(byte_size)** — allocates a block; uninitialized content.
2. **calloc(n, size)** — allocates `n` blocks of `size` bytes; zero-initialized.
3. **realloc(ptr, new_size)** — resizes a previously allocated block.
4. **free(ptr)** — deallocates memory back to the system.

### Syntax
```c
int *p = (int*) malloc(sizeof(int));
int *arr = (int*) calloc(5, sizeof(int));
arr = (int*) realloc(arr, 10 * sizeof(int));
free(p); free(arr);
```

### Easiest Program (`programs/DynamicMemoryDemo.c`)
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1 = (int*) malloc(sizeof(int));
    *p1 = 1024;
    printf("malloc: %d\n", *p1);

    int *p2 = (int*) calloc(5, sizeof(int));
    printf("calloc: ");
    for (int i = 0; i < 5; i++) printf("%d ", p2[i]);
    printf("\n");

    p2 = (int*) realloc(p2, 10 * sizeof(int));
    printf("realloc succeeded, block now holds 10 ints\n");

    free(p1); free(p2);
    return 0;
}
```

---

## Q.2 c) What is Sparse matrix? Give the triplet form of a given matrix and find its transpose. [5]

### Definition
A sparse matrix has **most elements zero**. Instead of storing all cells, only
non-zero elements are stored as `<row, col, value>` triplets.

### Points
1. Header triple (index 0): `row`=total rows, `col`=total cols, `value`=non-zero count.
2. **Transpose**: `a[i][j]` becomes `b[j][i]` — swap row and column for every triple.

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
