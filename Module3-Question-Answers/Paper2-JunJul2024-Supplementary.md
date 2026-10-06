# BCS304 — June/July 2024 Supplementary Exam
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.3 a) List the disadvantages of linear queue and how is it solved in circular queues. Give the algorithm to insert and delete an element in circular queues. [12]

### Disadvantages of linear queue
1. **Space waste:** once elements are deleted from the front, those slots can
   NEVER be used again — insertion happens only at `rear++`.
2. **False overflow:** when `rear == MAX-1` the queue says FULL even if front
   slots are empty. Example: size-5 queue full (10-50), delete 10 and 20 → 2
   slots free, but insertion is impossible.
3. Memory utilization is poor.

### How the circular queue solves it
1. `rear = (rear + 1) % SIZE` — wraps to index 0 when it crosses the end.
2. Freed front slots get reused automatically.
3. Full only when genuinely full: `(rear + 1) % SIZE == front`.

### Insert algorithm
```
1. If (rear + 1) % SIZE == front -> queue FULL, return
2. If front == -1  -> front = rear = 0
   Else           -> rear = (rear + 1) % SIZE
3. queue[rear] = item
```

### Delete algorithm
```
1. If front == -1 -> queue EMPTY, return
2. item = queue[front]
3. If front == rear -> front = rear = -1
   Else             -> front = (front + 1) % SIZE
4. Return item
```
Verified program: `programs/CircularQueue.c`.

---

## Q.3 b) Explain in detail about multiple queues with relevant functions in 'C'. [8]

### Definition
Multiple queues = several queues sharing ONE array, instead of each queue
having its own separate fixed array.

### The 2-queues-in-1-array method
1. Queue 1 uses the array from the LEFT: front1/rear1, inserts move right.
2. Queue 2 uses the array from the RIGHT: front2/rear2, inserts move left.
3. Full (for both) only when the two queues meet in the middle — so a long
   queue can borrow space a short queue isn't using.

### Diagram
```
[ Q1 | Q1 | Q1 | free | Q2 | Q2 ]
 rear1 moving -->        <-- rear2 moving
```

### Functions in C
```c
#define SIZE 10
int q[SIZE];
int front1 = 0, rear1 = -1;          /* queue 1: left side  */
int front2 = SIZE - 1, rear2 = SIZE; /* queue 2: right side */

void insert1(int v) {
    if (rear1 + 1 == front2) { printf("Q1 FULL\n"); return; }
    q[++rear1] = v;
}
void insert2(int v) {
    if (rear2 - 1 == front2) { printf("Q2 FULL\n"); return; }
    q[--rear2] = v;
}
int delete1(void) { return (rear1 < front1) ? -1 : q[front1++]; }
int delete2(void) { return (rear2 > front2) ? -1 : q[front2--]; }
```

---

## Q.4 a) Develop a linked list with the basic operations performed on Singly Linked List (SLL) and different types of linked list. [12]

### Definition + basic operations
A singly linked list is a chain of nodes, each with `data` and a `link` to the
next node; the last link is NULL, and `head` points to the first node.

Structure:
```c
typedef struct node { int data; struct node *link; } Node;
```

Basic operations:
1. **Insert front** — new node points to old head; head = new node. O(1).
2. **Insert end** — travel to last node; last->link = new node.
3. **Delete front** — head moves to second node; free old head. O(1).
4. **Delete end** — travel with prev; prev->link = NULL; free last.
5. **Display** — print each node travelling until NULL.

All five with verified output in `programs/SLLBasicOps.c`.

### Different types of linked lists
1. **Singly linked list** — one link per node, one-way travel.
```
[10|*]->[20|*]->[30|NULL]
```
2. **Doubly linked list (DLL)** — prev + next links, two-way travel.
```
NULL<-[10]<->[20]<->[30]->NULL
```
3. **Circular linked list** — last node points back to first (no NULL).
```
┌>[10]->[20]->[30]-┐
└──────────────────┘
```

---

## Q.4 b) Examine a node structure for linked representation of polynomial. Explain algorithm to add two polynomial represented using linked list. [8]

### Node structure
```c
typedef struct polyNode {
    int coef;                   /* coefficient: 3 in 3x^2 */
    int exp;                    /* exponent: 2 in 3x^2     */
    struct polyNode *link;
} Poly;
```
Representation of `3x^2 + 2x + 1`:
```
[3|2] -> [2|1] -> [1|0] -> NULL     (coef|exp per node)
```

### Addition algorithm
```
1. While both lists have terms:
   - p1->exp > p2->exp : copy p1 term, advance p1
   - p1->exp < p2->exp : copy p2 term, advance p2
   - equal exponents   : add coefficients; if sum != 0 store it;
                         advance BOTH
2. Append remaining terms of whichever list is left.
```

Worked example: (3x^2+2x+1) + (4x^3+x^2+5) = 4x^3+4x^2+2x+6.
Verified program: `programs/PolynomialAddition.c`.

---

## Q.5 a) Summarize Sparse Matrix. For the given sparse matrix, write the diagrammatic linked list representation. [8]

### Summary (definition + points)
1. A sparse matrix is a matrix in which MOST elements are zero.
2. Storing all the zeros wastes memory — a 100x100 matrix with 50 non-zeros
   wastes 9,950 slots.
3. So we store ONLY the non-zero elements.
4. **Linked representation:** one node per non-zero element with
   (row, col, value) + a link, plus a header node (rows, cols, non-zero count).

### Diagrammatic representation (example matrix)
```
Matrix:        15  0  0
                0  0  6
                0  9  0

head -> [3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
         ^header (3 rows, 3 cols, 3 non-zero)
```
For the exam: draw the given matrix, circle the non-zero elements, then draw
this chain. Verified program: `programs/SparseMatrixLinked.c`.

---

## Q.5 b) Define Doubly linked list. Write functions to perform: (i) Insert a node at rear end (ii) Delete a node at rear end (iii) Search a node with a given key value. [12]

### Definition
A doubly linked list is a linear list where each node has TWO links — `prev`
to the previous node and `next` to the next node — so it can be travelled in
both directions.
```c
typedef struct dnode { int data; struct dnode *prev, *next; } DNode;
```

### (i) Insert at rear end
```c
void insertRear(DNode **h, int v) {
    DNode *n = malloc(sizeof(DNode)), *t = *h;
    n->data = v; n->next = NULL;
    if (*h == NULL) { n->prev = NULL; *h = n; return; }
    while (t->next) t = t->next;      /* find last node */
    t->next = n; n->prev = t;
}
```

### (ii) Delete at rear end
```c
void deleteRear(DNode **h) {
    DNode *t = *h;
    if (*h == NULL) return;
    while (t->next) t = t->next;
    if (t->prev == NULL) *h = NULL;   /* only node */
    else t->prev->next = NULL;
    free(t);
}
```

### (iii) Search a node with key
```c
void search(DNode *h, int key) {
    int pos = 1;
    while (h) {
        if (h->data == key) { printf("Found %d at position %d\n", key, pos); return; }
        h = h->next; pos++;
    }
    printf("%d not found\n", key);
}
```
Verified program: `programs/DLLBasicOps.c`.
