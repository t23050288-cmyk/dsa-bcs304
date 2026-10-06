# BCS304 — Dec 2023/Jan 2024 Exam
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.3 b) Write a note on multiple stacks and priority queue. [6]

> Note: priority queue as a full topic belongs to Module 5 — this answer gives
> the multiple-stacks part fully plus a short priority-queue intro.

### Multiple stacks
1. Storing two or more stacks inside ONE array so memory is shared.
2. Classic method: stack 1 grows up from the left (`top1 = -1`), stack 2 grows
   down from the right (`top2 = SIZE`).
3. Both full only when they meet: `top1 + 1 == top2`.
```c
void push1(int v) { if (top1 + 1 == top2) return; stack[++top1] = v; }
void push2(int v) { if (top2 - 1 == top1) return; stack[--top2] = v; }
```
Verified program: `programs/MultipleStacks.c`.

### Priority queue (short note — full answer in Module 5)
4. A queue where every element has a PRIORITY; the highest-priority element
   is served first, not the earliest one.
5. Example: hospital emergency — a serious patient (high priority) is treated
   before a patient who arrived earlier with a minor issue.

---

## Q.4 a) What is a linked list? Explain the different types of linked lists with neat diagram. [4]

### Definition
A linked list is a linear collection of nodes, each holding data and a
pointer to the next node; nodes sit at scattered memory locations and are
connected only by links.

### Types with diagrams
1. **Singly linked list** — one link, one-way travel:
```
head -> [10|*] -> [20|*] -> [30|NULL]
```
2. **Doubly linked list** — prev + next, two-way travel:
```
NULL <- [10] <-> [20] <-> [30] -> NULL
```
3. **Circular linked list** — last node points back to the first:
```
  ┌-> [10] -> [20] -> [30] -┐
  └─────────────────────────┘
```

---

## Q.4 b) Give the structure definition for singly linked list (SLL). Write a C function to: (i) Insert an element at the end of SLL (ii) Delete a node at the beginning of SLL. [8]

### Structure definition
```c
typedef struct node {
    int data;
    struct node *link;
} Node;
Node *head = NULL;
```

### (i) Insert at the end
```c
void insertEnd(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v; n->link = NULL;
    if (head == NULL) { head = n; return; }   /* empty list case */
    while (t->link != NULL) t = t->link;       /* reach last node */
    t->link = n;
}
```

### (ii) Delete at the beginning
```c
void deleteFront(void) {
    Node *t = head;
    if (head == NULL) { printf("List empty\n"); return; }
    head = head->link;
    free(t);
}
```
Verified program: `programs/SLLBasicOps.c`.

---

## Q.4 c) Write a C function to add two polynomials, show the linked list representation of the two polynomials. [8]

### Linked representation
Each term = one node (coefficient, exponent, link), terms in decreasing
exponent order:
```
p1 = 3x^2 + 2x + 1:  [3|2] -> [2|1] -> [1|0] -> NULL
p2 = 4x^3 + x^2 + 5: [4|3] -> [1|2] -> [5|0] -> NULL
```

### C function
```c
Poly *add(Poly *p1, Poly *p2) {
    Poly *res = NULL;
    while (p1 && p2) {
        if (p1->exp > p2->exp)      { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
        else if (p1->exp < p2->exp) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
        else {                              /* equal exponents */
            int c = p1->coef + p2->coef;
            if (c != 0) res = insert(res, c, p1->exp);
            p1 = p1->link; p2 = p2->link;
        }
    }
    while (p1) { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
    while (p2) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
    return res;
}
```
Result: `4x^3 + 4x^2 + 2x + 6`. Verified program:
`programs/PolynomialAddition.c`.

---

## Q.5 a) Write a C function for the following operations on Doubly Linked List (DLL): (i) addition of a node (ii) concatenation of two DLL. [8]

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
    while (t->next) t = t->next;    /* last node of list 1 */
    t->next = head2;                /* forward link */
    if (head2) head2->prev = t;     /* backward link — BOTH must be set! */
}
```
Key point: in a DLL you must join BOTH directions (20->next=100 AND
100->prev=20).
Verified program: `programs/DLLBasicOps.c`.

---

## Q.5 b) Write C functions for circular linked list: (i) Inserting at the front of a list (ii) Finding the length of a circular list. [8]

### (i) Insert at front
```c
void insertFront(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v;
    if (head == NULL) { n->link = n; head = n; return; }  /* ring of one */
    while (t->link != head) t = t->link;    /* find LAST node */
    n->link = head;
    t->link = n;        /* last node must also point to new node! */
    head = n;
}
```

### (ii) Length of the list
```c
int count(void) {
    int c = 0;
    Node *t = head;
    if (!head) return 0;
    do { c++; t = t->link; } while (t != head);   /* stop back at head */
    return c;
}
```
Use do-while so the head node itself is counted. Verified program:
`programs/CircularLinkedList.c` (output: 3 nodes).

---

## Q.5 c) For the given sparse matrix, give the diagrammatic linked representation. [4]

### Method (apply to the given matrix)
1. Write the matrix; identify the NON-ZERO elements and their (row, col).
2. Draw a header node: (total rows, total cols, count of non-zeros).
3. Draw one node per non-zero element: (row, col, value), all connected by
   links.

### Example
```
Matrix:  15  0  0          head -> [3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
          0  0  6
          0  9  0
```
Verified program: `programs/SparseMatrixLinked.c`.
