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

### Points
1. **Primitive** — basic machine-operable types (Integer, Float, Character, Pointer).
2. **Non-Primitive** — derived types, split into:
   - **Linear** (Arrays via sequential memory, Linked Lists via pointers).
   - **Non-Linear** (Trees, Graphs — hierarchical relationships).

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
