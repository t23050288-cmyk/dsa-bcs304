# BCS304 — June/July 2025 Makeup Exam
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.1 a) Differentiate between static and dynamic memory allocation. Write syntax for malloc(), calloc(), realloc() and free() functions. [8]

### Definitions
**Static allocation** reserves memory at **compile-time** with a fixed size.
**Dynamic allocation** reserves memory at **run-time** with a size decided while
the program executes.

### Comparison Table

| Basis | Static Allocation | Dynamic Allocation |
|---|---|---|
| When allocated | Compile-time | Run-time |
| Size | Fixed | Can grow/shrink (via realloc) |
| Memory area | Stack | Heap |
| Example | `int arr[10];` | `int *arr = malloc(10*sizeof(int));` |
| Risk | Wastes memory if overestimated | Memory leak if not freed |

### Syntax for the 4 Functions
```c
ptr = (cast_type*) malloc(byte_size);        /* uninitialized memory */
ptr = (cast_type*) calloc(n, size);           /* n blocks, zero-initialized */
ptr = realloc(ptr, new_size);                 /* resize existing block */
free(ptr);                                     /* deallocate */
```

### Program (comparing static vs dynamic array; `programs/DynamicMemoryDemo.c`)
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int staticArr[5] = {1, 2, 3, 4, 5};    /* static */

    int n;
    printf("Enter size for dynamic array: ");
    scanf("%d", &n);
    int *dynamicArr = (int*) malloc(n * sizeof(int));   /* dynamic */

    for (int i = 0; i < n; i++) dynamicArr[i] = i + 1;

    printf("Static array: ");
    for (int i = 0; i < 5; i++) printf("%d ", staticArr[i]);
    printf("\nDynamic array: ");
    for (int i = 0; i < n; i++) printf("%d ", dynamicArr[i]);
    printf("\n");

    free(dynamicArr);
    return 0;
}
```

---

## Q.1 b) Write KMP pattern matching algorithm and apply the same to search the pattern in the text. [8]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Definition
Pattern matching finds whether/where a **pattern** occurs within a **text**. KMP
(Knuth-Morris-Pratt) does this efficiently using a precomputed **failure function**.

### Points
1. Naive method: O(n·m). KMP: **O(n + m)**.
2. `f(j)` = largest `i < j` where the pattern's prefix of length `i+1` matches the
   suffix ending at `j` — or `-1`.
3. On mismatch at pattern position `j`, jump to `f(j-1)+1` instead of restarting.

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

---

## Q.1 c) Differentiate between Structure and Union. [4]

### Comparison Table

| Basis | Structure | Union |
|---|---|---|
| Memory | Each member gets its own space | All members share the same space |
| Size | Sum of all members (+ padding) | Size of the largest member only |
| Active members | All valid at once | Only one at a time |

### Program (`programs/StructVsUnion.c`)
```c
#include <stdio.h>
struct StructExample { int i; float f; char c; };
union UnionExample { int i; float f; char c; };
int main() {
    struct StructExample s; union UnionExample u;
    printf("struct: %lu bytes, union: %lu bytes\n", sizeof(s), sizeof(u));
    return 0;
}
```

---

## Q.2 c) Write a C function to perform transpose of a given sparse matrix. [4]

### Definition
Transposing a sparse matrix means swapping row and column for every stored
`<row, col, value>` triple.

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
```
