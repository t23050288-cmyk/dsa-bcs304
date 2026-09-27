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

### Points
1. **Primitive** — Integer, Float, Character, Pointer (machine-operable, indivisible).
2. **Non-Primitive** — Linear (Arrays, Linked Lists, Stacks, Queues) and
   Non-Linear (Trees, Graphs).

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

### Points
1. Header triple: `row`=total rows, `col`=total cols, `value`=non-zero count.
2. Transpose: swap row/col for every triple (`a[i][j] -> b[j][i]`).

### Example
```
Original matrix (3x3, non-zero entries: (0,0,15), (1,2,22), (2,1,-6)):
row col value
0   0   15
1   2   22
2   1  -6

Transpose:
row col value
0   0   15
1   2  -6
2   1   22
```

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
