# BCS304 — June/July 2025 Makeup Exam
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.3 a) Explain the need of Circular Queue. Implement Insert(), delete() and display() operations on the circular queue. [10]

### Need for a circular queue
1. In a linear queue, insertion is always `rear++` — once rear reaches the
   last index, NO more insertion is possible.
2. Even after deleting from the front, the freed slots can never be reused —
   that memory is simply wasted.
3. False overflow: the queue cries "FULL" while it actually has empty cells.
4. Circular queue fixes this by connecting the last position back to the
   first: `rear = (rear + 1) % SIZE` wraps around and reuses freed slots.

### Implementation
```c
#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

void insert(int item) {
    if ((rear + 1) % SIZE == front) { printf("Queue FULL\n"); return; }
    if (front == -1) front = rear = 0; else rear = (rear + 1) % SIZE;
    queue[rear] = item;
}
void delete(void) {
    if (front == -1) { printf("Queue EMPTY\n"); return; }
    if (front == rear) front = rear = -1;   /* queue became empty */
    else front = (front + 1) % SIZE;
}
void display(void) {
    int i;
    if (front == -1) return;
    for (i = front; ; i = (i + 1) % SIZE) {
        printf("%d ", queue[i]);
        if (i == rear) break;
    }
    printf("\n");
}
```
Verified: `programs/CircularQueue.c`.

---

## Q.3 b) Implement operations on Single Linked List: (i) Delete a node at the end of SLL (ii) Insert a node at the beginning of SLL. [10]

```c
typedef struct node { int data; struct node *link; } Node;
Node *head = NULL;

void deleteEnd(void) {                    /* (i) */
    Node *t = head, *prev = NULL;
    if (!head) { printf("List empty\n"); return; }
    while (t->link) { prev = t; t = t->link; }   /* reach last node */
    printf("Deleted %d\n", t->data);
    if (prev == NULL) head = NULL;     /* only one node existed */
    else prev->link = NULL;            /* second-last becomes last */
    free(t);
}
void insertFront(int v) {                  /* (ii) */
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = head;
    head = n;
}
```
Verified: `programs/SLLBasicOps.c` (output shows 10 -> 20 -> 30 -> 40, delete
front 10, delete end 40, remaining 20 -> 30).

---

## Q.4 a) Explain and write a C function to implement Multiple Stack. [10]

### Explanation
1. A multiple stack stores SEVERAL stacks in ONE shared array.
2. For two stacks: stack 1 starts at the left (top1 = -1) growing UP;
   stack 2 starts at the right (top2 = SIZE) growing DOWN.
3. They grow towards each other; both-full when `top1 + 1 == top2`.
4. Advantage: one array serves two stacks — better memory use, and either
   stack can use more than "its half" if the other is small.

```
[10][20][30]  . . .  [80][90]
 ^top1 = 2           top2 = 7^
```

### C function
```c
#define SIZE 10
int stack[SIZE], top1 = -1, top2 = SIZE;

void push1(int v) {
    if (top1 + 1 == top2) { printf("Stack 1 FULL\n"); return; }
    stack[++top1] = v;
}
void push2(int v) {
    if (top2 - 1 == top1) { printf("Stack 2 FULL\n"); return; }
    stack[--top2] = v;
}
int pop1(void) { return stack[top1--]; }
int pop2(void) { return stack[top2++]; }
```
Verified: `programs/MultipleStacks.c`.

---

## Q.4 b) Develop a C function to add two polynomials using Single Linked List. [10]

### Representation
Each term = one node: `[coef | exp | link]`, exponents in decreasing order.
```
p1 = 3x^2+2x+1:  [3|2] -> [2|1] -> [1|0] -> NULL
p2 = 4x^3+x^2+5: [4|3] -> [1|2] -> [5|0] -> NULL
```

### Function
```c
Poly *add(Poly *p1, Poly *p2) {
    Poly *res = NULL;
    while (p1 && p2) {
        if (p1->exp > p2->exp)      { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
        else if (p1->exp < p2->exp) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
        else {
            int c = p1->coef + p2->coef;
            if (c != 0) res = insert(res, c, p1->exp);
            p1 = p1->link; p2 = p2->link;
        }
    }
    while (p1) { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
    while (p2) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
    return res;      /* 4x^3 + 4x^2 + 2x + 6 */
}
```
Verified: `programs/PolynomialAddition.c`.

---

## Q.5 a) Give the diagrammatical representation of below sparse matrix using Linked List. [5]

### Method
1. From the given matrix, list the non-zero elements with (row, col, value).
2. Header node = (total rows, total cols, count of non-zeros).
3. One linked node per non-zero element.

### Example
```
Matrix:  15  0  0
          0  0  6
          0  9  0

head -> [3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
```
Each node: `row | col | value | link`. Verified:
`programs/SparseMatrixLinked.c`.

---

## Q.6 a) Define Double Linked List. Create a C function for DLL operations: (i) Inserting a node at front (ii) Deleting a node at end. [8]

### Definition
A doubly linked list is a list in which every node has two links — `prev`
pointing to the previous node and `next` pointing to the next node — allowing
movement in both directions.

```c
typedef struct dnode { int data; struct dnode *prev, *next; } DNode;

void insertFront(DNode **h, int v) {         /* (i) */
    DNode *n = malloc(sizeof(DNode));
    n->data = v; n->prev = NULL; n->next = *h;
    if (*h) (*h)->prev = n;
    *h = n;
}
void deleteEnd(DNode **h) {                 /* (ii) */
    DNode *t = *h;
    if (!*h) return;
    while (t->next) t = t->next;
    if (t->prev == NULL) *h = NULL;
    else t->prev->next = NULL;
    free(t);
}
```
Verified: `programs/DLLBasicOps.c`.
