# BCS304 — Dec 2025/Jan 2026 Exam
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.3 a) Discuss the implementation of circular queue (following disadvantages of ordinary queue). [8]

### Disadvantages of ordinary queue (why circular is needed)
1. Insertion only at `rear++` — once rear hits the last index, insertion stops
   forever.
2. Front slots freed by deletion are never reusable — wasted memory.
3. False overflow: "FULL" is reported even when empty cells exist.

### Circular queue implementation
```c
#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

void insert(int item) {
    if ((rear + 1) % SIZE == front) { printf("FULL\n"); return; }
    if (front == -1) front = rear = 0;
    else rear = (rear + 1) % SIZE;     /* wraps to 0 after last index */
    queue[rear] = item;
}
void delete(void) {
    if (front == -1) { printf("EMPTY\n"); return; }
    if (front == rear) front = rear = -1;
    else front = (front + 1) % SIZE;   /* front wraps too */
}
void display(void) {
    int i;
    for (i = front; ; i = (i + 1) % SIZE) {
        printf("%d ", queue[i]);
        if (i == rear) break;
    }
}
```
Everything hinges on `(index + 1) % SIZE` — the modulo makes both pointers
wrap around like a circle, so freed slots are reused. Verified:
`programs/CircularQueue.c`.

---

## Q.3 b) Write a note on multiple stacks and priority queue. [6]

> Priority queue as a full topic is Module 5 — the multiple-stacks part is
> here.

### Multiple stacks
1. Two or more stacks share ONE array: stack 1 grows up from the left
   (top1 = -1), stack 2 grows down from the right (top2 = SIZE).
2. Both-full condition: `top1 + 1 == top2` (they meet in the middle).
3. C: `void push1(int v){ if(top1+1==top2) return; stack[++top1]=v; }`
   `void push2(int v){ if(top2-1==top1) return; stack[--top2]=v; }`
4. Verified program: `programs/MultipleStacks.c`.

### Priority queue (intro)
5. A queue where every element carries a priority; the HIGHEST priority
   element leaves first, regardless of arrival order.
6. Example: OS process scheduling, hospital triage.
7. Can be implemented with arrays (shift needed) or heaps (efficient) — full
   treatment in Module 5.

---

## Q.4 a) What are Linked list? Explain the different types of Linked List with neat diagram. [4]

### Definition
A linked list is a linear data structure made of nodes; each node stores data
and a pointer to the next node, and the nodes are stored at scattered memory
locations connected only by these pointers.

### Types
```
Singly:    head -> [10|*] -> [20|*] -> [30|NULL]
Doubly:    NULL <- [10] <-> [20] <-> [30] -> NULL
Circular:  ┌-> [10] -> [20] -> [30] -┐
           └─────────────────────────┘  (last points back to first)
```
1. **Singly** — one link, one-way travel, last link NULL.
2. **Doubly** — prev + next, both-way travel.
3. **Circular** — no NULL; last node loops to the first.

---

## Q.4 b) Give the structure definition for Singly Linked List (SSL). Write a C function: (i) Insert an element at the end of SSL (ii) Delete a node at the end of SSL. [8]

### Structure definition
```c
typedef struct node {
    int data;
    struct node *link;
} Node;
Node *head = NULL;
```

### (i) Insert at end
```c
void insertEnd(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v; n->link = NULL;
    if (head == NULL) { head = n; return; }
    while (t->link) t = t->link;
    t->link = n;
}
```

### (ii) Delete at end
```c
void deleteEnd(void) {
    Node *t = head, *prev = NULL;
    if (!head) { printf("List empty\n"); return; }
    while (t->link) { prev = t; t = t->link; }
    if (prev == NULL) head = NULL;   /* single node case */
    else prev->link = NULL;
    free(t);
}
```
Both verified in `programs/SLLBasicOps.c`.

---

## Q.4 c) Write a C function to add two polynomials, show the Linked list representation. [8]

### Representation (coef | exp | link)
```
p1 = 3x^2 + 2x + 1 : [3|2] -> [2|1] -> [1|0] -> NULL
p2 = 4x^3 + x^2 + 5: [4|3] -> [1|2] -> [5|0] -> NULL
Sum                : [4|3] -> [4|2] -> [2|1] -> [6|0] -> NULL
```

### Function
```c
Poly *add(Poly *p1, Poly *p2) {
    Poly *res = NULL;
    while (p1 && p2) {
        if (p1->exp > p2->exp)      { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
        else if (p1->exp < p2->exp) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
        else { int c = p1->coef + p2->coef;
               if (c) res = insert(res, c, p1->exp);
               p1 = p1->link; p2 = p2->link; }
    }
    while (p1) { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
    while (p2) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
    return res;
}
```
Verified: `programs/PolynomialAddition.c`.

---

## Q.5 a) Write a C-function for DLL: (i) Addition of a DLL node (ii) Concatenation of two DLL. [8]

### (i) Addition (insertion) of a node at the front
```c
void insertFront(DNode **h, int v) {
    DNode *n = malloc(sizeof(DNode));
    n->data = v; n->prev = NULL; n->next = *h;
    if (*h) (*h)->prev = n;
    *h = n;
}
```

### (ii) Concatenation of two DLLs
```c
void concatenate(void) {
    DNode *t = head;
    if (!head) { head = head2; return; }
    while (t->next) t = t->next;   /* last node of list 1 */
    t->next = head2;               /* forward join */
    if (head2) head2->prev = t;    /* backward join — don't forget! */
}
```
```
Before: [10] <-> [20]    [100] <-> [200]
After:  [10] <-> [20] <-> [100] <-> [200]
```
Verified: `programs/DLLBasicOps.c`.

---

## Q.5 b) Write a C-function for circular Linked List: (i) Inserting at the front (ii) Find the number of nodes in circular list. [8]

### (i) Insert at front
```c
void insertFront(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v;
    if (!head) { n->link = n; head = n; return; }
    while (t->link != head) t = t->link;  /* find last node */
    n->link = head; t->link = n;          /* last node updated too */
    head = n;
}
```

### (ii) Count nodes
```c
int count(void) {
    int c = 0;
    Node *t = head;
    if (!head) return 0;
    do { c++; t = t->link; } while (t != head);
    return c;
}
```
do-while so the head is counted; stop when back at head. Verified:
`programs/CircularLinkedList.c` (3 nodes).

---

## Q.5 c) Represent the given Sparse matrix using linked list representation. [4]

1. Find every non-zero element of the given matrix: (row, col, value).
2. Header node = (rows, cols, non-zero count).
3. One linked node per non-zero element.
```
Matrix:  15  0  0
          0  0  6
          0  9  0

head -> [3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
```
Verified: `programs/SparseMatrixLinked.c`.
