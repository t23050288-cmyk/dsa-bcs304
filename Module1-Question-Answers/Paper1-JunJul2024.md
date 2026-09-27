# BCS304 — June/July 2024 Exam
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.1 a) What is data structure? List and explain data structure operations. [8]

### Definition
A data structure is the logical or mathematical model of a particular organization
of data — it represents the relationships that exist between individual data
elements, not just the elements themselves.

### Points
1. A data structure is a way of organizing data that considers both the elements
   stored **and** their relationship to each other.
2. Choice of a data structure depends on two things: it must mirror real-world
   relationships in the data, and it must be simple enough to process efficiently.

### The 7 Data Structure Operations
1. **Create** — reserves memory for the program elements; may happen at
   compile-time or run-time.
2. **Destroy** — releases the memory space allocated for the data structure.
3. **Selection** — accessing a particular data item within the structure.
4. **Updating** — modifying/updating the data in the structure.
5. **Searching** — finding whether a desired data item is present.
6. **Sorting** — arranging all data items in a particular order (ascending/descending).
7. **Merging** — combining the data items of two different sorted lists into one list.

### Easiest Program (create, update, search, sort on an array)
```c
#include <stdio.h>
#define SIZE 5

int main() {
    int arr[SIZE] = {40, 10, 30, 20, 50};   /* Create */
    int i, j, temp, key = 30, found = -1;

    arr[2] = 35;                             /* Updating */

    for (i = 0; i < SIZE; i++) {             /* Searching */
        if (arr[i] == key) { found = i; break; }
    }
    printf("Search result for %d: %s\n", key, found != -1 ? "Found" : "Not found");

    for (i = 0; i < SIZE - 1; i++)           /* Sorting (bubble sort) */
        for (j = 0; j < SIZE - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
            }

    printf("Sorted array: ");
    for (i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
int main() { int a[]={4,8,15,16},i,idx=-1; for(i=0;i<4;i++) if(a[i]==15){idx=i;break;} printf("%d\n",idx); return 0; }
```

---

## Q.1 b) Discuss four dynamic memory allocation functions. [8]

### Definition
Dynamic Memory Allocation is the process of allocating memory space during
**execution/run-time**, typically used when storage requirements are unpredictable
in advance. Memory is allocated on the **heap**.

### Points
1. Four main functions: `malloc`, `calloc`, `realloc`, `free`.
2. On success, they return a pointer to the allocated block; on failure, they
   return `NULL`.
3. `free()` deallocates memory previously allocated by `malloc()`/`calloc()`.
4. Always check the return value against `NULL` before using the pointer.

### 1. malloc() — Memory Allocate
**Syntax:** `ptr = (cast_type*) malloc(byte_size);`
- Allocates a single block; content is **uninitialized** (garbage values).

### 2. calloc() — Contiguous Memory Allocate
**Syntax:** `ptr = (cast_type*) calloc(n, size);`
- Allocates `n` blocks of `size` bytes each; memory is **initialized to 0**.

### 3. realloc() — Resize Memory
**Syntax:** `ptr = realloc(ptr, new_size);`
- Resizes a block previously allocated by `malloc`/`calloc`.

### 4. free() — Deallocate Memory
**Syntax:** `free(ptr);`
- Releases memory back to the system for reuse.

### Easiest Program
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1, *p2, i;

    p1 = (int*) malloc(sizeof(int));
    *p1 = 1024;
    printf("malloc: %d\n", *p1);

    p2 = (int*) calloc(5, sizeof(int));
    printf("calloc initial values: ");
    for (i = 0; i < 5; i++) printf("%d ", p2[i]);
    printf("\n");

    p2 = realloc(p2, 10 * sizeof(int));
    printf("realloc succeeded, new block can hold 10 ints\n");

    free(p1);
    free(p2);
    printf("memory freed\n");
    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
#include <stdlib.h>
int main() { int *p = malloc(sizeof(int)); *p = 5; printf("%d\n", *p); free(p); return 0; }
```

---

## Q.1 c) With suitable example, discuss self-referential structures. [4]

### Definition
A self-referential structure is a structure that contains, as one of its own
members, a **pointer to another structure of the same type**. This is the
foundation of linked lists, trees, and other linked data structures.

### Points
1. Requires dynamic storage management (`malloc`/`free`) to explicitly get and
   release memory for each node.
2. The pointer field is often named `link` or `next`.
3. Each structure instance ("node") points to the next node, chaining them together.
4. The last node's pointer is set to `NULL` to mark the end of the chain.

### Syntax
```c
typedef struct list {
    char data;
    struct list *link;   /* pointer to another structure of the SAME type */
} list;
```

### Easiest Program (`programs/SelfReferentialStruct.c`)
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    char data;
    struct list *link;
} list;

int main() {
    list *item1 = (list*) malloc(sizeof(list));
    list *item2 = (list*) malloc(sizeof(list));
    list *item3 = (list*) malloc(sizeof(list));

    item1->data = 'a'; item2->data = 'b'; item3->data = 'c';
    item1->link = item2;
    item2->link = item3;
    item3->link = NULL;

    list *p = item1;
    printf("Chain: ");
    while (p != NULL) {
        printf("%c -> ", p->data);
        p = p->link;
    }
    printf("NULL\n");

    free(item1); free(item2); free(item3);
    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
struct N { int data; struct N *next; };
int main() { struct N a = {1, NULL}, b = {2, &a}; printf("%d %d\n", b.data, b.next->data); return 0; }
```

---

## Q.2 a) What is sparse matrix? Give the triplet form for given matrix and also find its transpose. [6]

### Definition
A sparse matrix is a matrix in which **most of the elements are zero** — the
number of non-zero entries is small compared to the total size of the matrix.

### Points
1. Storing a sparse matrix as a normal 2D array wastes a lot of memory. A
   100×100 matrix with only 100 non-zero entries wastes 9,900 of 10,000 slots.
2. **Solution:** store only the non-zero elements, using the triplet
   `<row, column, value>` for each.
3. Header triple (index 0) stores: `row` = total rows, `col` = total columns,
   `value` = total non-zero count.
4. **Transpose**: every element `a[i][j]` becomes `b[j][i]` — rows/columns swap.

### Syntax
```c
#define MAX_TERMS 101
typedef struct { int row, col, value; } term;
term a[MAX_TERMS];
```

### Example (3x3 sparse matrix with 3 non-zero terms)
```
Original:               Transpose:
row col value           row col value
0   0   15               0   0   15
1   2   22                1   2  -6
2   1  -6                 2   1  22
```

### Easiest Program (`programs/SparseMatrixTranspose.c`)
```c
#include <stdio.h>

typedef struct { int row, col, value; } term;

void transpose(term a[], term b[]) {
    int n = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;

    if (n > 0) {
        int currentb = 1;
        for (int i = 0; i < a[0].col; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}

int main() {
    term a[10] = { {3, 3, 3}, {0, 0, 15}, {1, 2, 22}, {2, 1, -6} };
    term b[10];

    transpose(a, b);

    printf("Transpose triplets:\n");
    for (int i = 1; i <= b[0].value; i++)
        printf("row=%d col=%d value=%d\n", b[i].row, b[i].col, b[i].value);

    return 0;
}
```
