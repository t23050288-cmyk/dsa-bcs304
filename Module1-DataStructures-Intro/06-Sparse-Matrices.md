# 6. Sparse Matrices — Representation & Transpose

Covers: "What is sparse matrix? Give the triplet form for given matrix and also find
its transpose", "Write a C function to perform transpose of a given sparse matrix".

---

## 6.1 What is a Sparse Matrix?

**Definition:** A sparse matrix is a matrix in which **most of the elements are
zero** — the number of non-zero entries is small compared to the total size of the
matrix.

**Points:**
1. Storing a sparse matrix as a normal 2D array wastes a lot of memory. Example:
   a 100×100 matrix with only 100 non-zero entries wastes 9,900 of the 10,000
   memory slots on zeros.
2. **Solution:** store only the non-zero elements, using the **triplet**
   `<row, column, value>` for each one.
3. This triplet uniquely identifies any non-zero element's position and value.

---

## 6.2 Triplet Representation

**Definition:** In triplet representation, a sparse matrix is stored as an array of
`<row, col, value>` triples — one triple per non-zero element — plus one extra
"header" triple at index 0 that stores the matrix's overall dimensions and count.

**Points:**
1. `a[0].row` = total number of rows in the matrix.
2. `a[0].col` = total number of columns in the matrix.
3. `a[0].value` = total number of non-zero terms.
4. From index `1` onward, each entry is `<row, col, value>` for one non-zero element,
   typically stored in **row-major order** (row, then column, ascending).

### Syntax
```c
#define MAX_TERMS 101
typedef struct {
    int row;
    int col;
    int value;
} term;

term a[MAX_TERMS];
```

### Example
For a 6×6 sparse matrix with 8 non-zero entries:

```
row col value
a[0]  6   6    8      <- header: 6 rows, 6 cols, 8 non-zero terms
a[1]  0   0   15
a[2]  0   3   22
a[3]  0   5  -15
a[4]  1   1   11
a[5]  1   2    3
a[6]  2   3   -6
a[7]  4   0   91
a[8]  5   2   28
```

---

## 6.3 Transposing a Sparse Matrix

**Definition:** To transpose a matrix, every element `a[i][j]` becomes element
`b[j][i]` in the result — rows and columns are interchanged.

**Points (algorithm):**
1. The transpose's row count = original's column count (and vice versa).
2. A **naive** approach scans column-by-column in the original and appends matches
   to the result — this correctly produces the transpose already sorted by row,
   but runs in **O(columns × terms)** time.
3. A **fast transpose** (using extra bookkeeping arrays to track where each row of
   the result starts) can do this in **O(columns + terms)** time — asked about at
   a more advanced level, but the simple version below is sufficient for most exams.

### Algorithm (simple/naive version)
```
for each column i of the original matrix:
    scan through all triples
    if a triple's column == i:
        add it to the result with row and column swapped
```

### Easiest Program (transpose function, matches the triplet format above)
```c
#include <stdio.h>

typedef struct { int row, col, value; } term;

void transpose(term a[], term b[]) {
    int n = a[0].value;        /* total number of non-zero elements */
    b[0].row = a[0].col;       /* rows in b = columns in a */
    b[0].col = a[0].row;       /* columns in b = rows in a */
    b[0].value = n;

    if (n > 0) {
        int currentb = 1;
        for (int i = 0; i < a[0].col; i++) {      /* for each column of a */
            for (int j = 1; j <= n; j++) {          /* scan all non-zero terms */
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
    /* 3x3 sparse matrix: {0,0,15}, {1,2,22}, {2,1,-6} as non-zero terms */
    term a[10] = {
        {3, 3, 3},     /* header: 3 rows, 3 cols, 3 non-zero terms */
        {0, 0, 15},
        {1, 2, 22},
        {2, 1, -6}
    };
    term b[10];

    transpose(a, b);

    printf("Transpose triplets:\n");
    for (int i = 0; i <= b[0].value; i++)
        printf("row=%d col=%d value=%d\n", b[i].row, b[i].col, b[i].value);

    return 0;
}
```

**Smallest Program (transpose a plain 2x2 matrix, not triplet form):**
```c
#include <stdio.h>
int main() { int m[2][2]={{1,2},{3,4}}, t[2][2], i, j; for(i=0;i<2;i++) for(j=0;j<2;j++) t[j][i]=m[i][j]; printf("%d %d %d %d\n", t[0][0],t[0][1],t[1][0],t[1][1]); return 0; }
```
