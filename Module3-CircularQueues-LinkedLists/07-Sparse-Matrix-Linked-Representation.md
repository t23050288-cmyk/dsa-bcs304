# 7. Sparse Matrix — Linked List Representation

Covers: "diagrammatic linked list representation of sparse matrix",
"represent the given sparse matrix using linked list".

---

## 7.1 Why a linked representation?

**Definition:** A sparse matrix (mostly zeros) can be stored as a linked list
with one node per NON-ZERO element, each node storing the element's row,
column and value — plus a header node holding the matrix's dimensions and the
count of non-zero elements.

### Points
1. A 100 x 100 matrix with 50 non-zero elements wastes 9,950 array slots.
2. The triplet (array) representation stores only the non-zeros in 3 columns.
3. The LINKED version goes further: nodes can be scattered in memory and
   connected by pointers, and the count can grow freely (no fixed array
   size).
4. Insertion of a new non-zero element does not need shifting — just link a
   new node in.

### Node Structure
```c
typedef struct smNode {
    int row, col, val;         /* position + value of one non-zero element */
    struct smNode *link;
} SM;
```

### Diagram — for the matrix
```
        15   0   0
         0   0   6
         0   9   0

head -> [3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
         ^header: 3 rows, 3 cols, 3 non-zero elements
```
(Each node drawn as row | col | value.)

### Easiest Program (`programs/SparseMatrixLinked.c`) — compiled & verified
```c
#include <stdio.h>
#include <stdlib.h>
typedef struct smNode { int row, col, val; struct smNode *link; } SM;

SM *insert(SM *head, int r, int c, int v) {
    SM *n = malloc(sizeof(SM)), *t = head;
    n->row = r; n->col = c; n->val = v; n->link = NULL;
    if (!head) return n;
    while (t->link) t = t->link;
    t->link = n;
    return head;
}

int main() {
    int a[3][3] = {{15,0,0},{0,0,6},{0,9,0}};
    SM *head = NULL;
    int i, j;
    head = insert(head, 3, 3, 3);            /* header node */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (a[i][j] != 0)
                head = insert(head, i, j, a[i][j]);
    printf("row col val\n");
    for (SM *t = head; t; t = t->link)
        printf("%3d %4d %4d\n", t->row, t->col, t->val);
    return 0;
}
```
**Verified output:**
```
row col val
  3    3    3      <- header
  0    0   15
  1    2    6
  2    1    9
```

### Exam tip
When the question says "for the GIVEN matrix", first draw the matrix on the
answer sheet, mark the non-zero elements, THEN draw the linked list node by
node in the exact form above — full marks come from the correct diagram.
