# BCS304 — Model Question Paper (2023-24 CBCS Scheme)
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.03 b) Write a program in C to implement a stack of integers using a singly linked list. [10]

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node { int data; struct node *link; } Node;
Node *top = NULL;

void push(int v) {
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = top;
    top = n;
}
int pop(void) {
    Node *t = top; int v;
    if (!top) { printf("Stack EMPTY\n"); return -1; }
    v = top->data; top = top->link; free(t);
    return v;
}
void display(void) {
    Node *t = top;
    while (t) { printf("%d -> ", t->data); t = t->link; }
    printf("NULL (top)\n");
}

int main() {
    push(10); push(20); push(30);
    display();
    printf("popped = %d\n", pop());
    display();
    return 0;
}
```
**Verified output:** `30 -> 20 -> 10 -> NULL (top)` then pop 30, remaining
`20 -> 10`. File: `programs/LinkedStack.c`.

---

## Q.04 a) Write a C program to implement insertion, deletion and display operations on a circular queue. [10]

```c
#include <stdio.h>
#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

void insert(int item) {
    if ((rear + 1) % SIZE == front) { printf("Queue FULL\n"); return; }
    if (front == -1) front = rear = 0;
    else rear = (rear + 1) % SIZE;
    queue[rear] = item;
}
void delete(void) {
    if (front == -1) { printf("Queue EMPTY\n"); return; }
    printf("Deleted %d\n", queue[front]);
    if (front == rear) front = rear = -1;
    else front = (front + 1) % SIZE;
}
void display(void) {
    int i;
    if (front == -1) { printf("Queue EMPTY\n"); return; }
    printf("Queue: ");
    for (i = front; ; i = (i + 1) % SIZE) {
        printf("%d ", queue[i]);
        if (i == rear) break;
    }
    printf("\n");
}

int main() {
    insert(10); insert(20); insert(30); insert(40); insert(50);
    display();
    delete(); delete();
    insert(60); insert(70);   /* wrap-around: reuses freed slots */
    display();
    return 0;
}
```
**Verified output:** after deleting 10, 20 the new 60, 70 fill their slots →
`Queue: 30 40 50 60 70`. File: `programs/CircularQueue.c`.

---

## Q.04 b) Write the C function to add two polynomials. Show the linked representation of the two polynomials and their addition using a circular singly linked list. [10]

### Representation
Each term is a node `[coef | exp | link]`. In a CIRCULAR singly linked list
the last term's link returns to the first node (often via a header node
holding the polynomial's name) — no NULL end.
```
p1 = 3x^2 + 2x + 1 :  ┌-> [3|2] -> [2|1] -> [1|0] -┐
                       └───────────────────────────┘
p2 = 4x^3 + x^2 + 5:  ┌-> [4|3] -> [1|2] -> [5|0] -┐
                       └───────────────────────────┘
Sum = 4x^3 + 4x^2 + 2x + 6
```

### Function (works for terms in decreasing exponent order)
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
Verified linear version: `programs/PolynomialAddition.c` (the addition
logic is identical; only the final link points back to the first node).

---

## Q.05 b) Write C functions: (i) Search an element in the singly linked list (ii) Concatenation of two singly linked list. [6]

### (i) Search
```c
void search(int key) {
    Node *t = head; int pos = 1;
    while (t) {
        if (t->data == key) { printf("Found %d at position %d\n", key, pos); return; }
        t = t->link; pos++;
    }
    printf("%d not found\n", key);
}
```

### (ii) Concatenate
```c
void concatenate(void) {
    Node *t = head;
    if (!head) { head = head2; return; }
    while (t->link) t = t->link;   /* last node of list 1 */
    t->link = head2;              /* attach list 2 */
}
```
Verified: `programs/SLLAdditionalOps.c` (Found 20 at position 2; after
concatenate: 30 -> 20 -> 10 -> 100 -> 200).

---

## Q.05 c) Define Sparse matrix. For the given sparse matrix, give the linked list representation. [6]

### Definition
A sparse matrix is a matrix in which most of the elements are ZERO. Since
storing zeros wastes memory, only the non-zero elements are stored — here,
as a linked list with one node per non-zero element.

### Linked list representation
```
Matrix:  15  0  0
          0  0  6
          0  9  0

head -> [3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
         ^header: 3 rows, 3 cols, 3 non-zero elements
```
Node structure:
```c
typedef struct smNode { int row, col, val; struct smNode *link; } SM;
```
Verified: `programs/SparseMatrixLinked.c`.

---

## Q.06 a) Write C Functions: (i) Inserting a node at the beginning of a DLL (ii) Deleting a node at the end of the DLL. [8]

```c
typedef struct dnode { int data; struct dnode *prev, *next; } DNode;

void insertFront(DNode **h, int v) {        /* (i) */
    DNode *n = malloc(sizeof(DNode));
    n->data = v; n->prev = NULL; n->next = *h;
    if (*h) (*h)->prev = n;
    *h = n;
}
void deleteEnd(DNode **h) {                /* (ii) */
    DNode *t = *h;
    if (!*h) { printf("List empty\n"); return; }
    while (t->next) t = t->next;
    if (t->prev == NULL) *h = NULL;   /* only node case */
    else t->prev->next = NULL;
    free(t);
}
```
Verified: `programs/DLLBasicOps.c`.
