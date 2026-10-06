# BCS304 — Dec 2024/Jan 2025 Exam
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.3 b) Write a C Function to implement insertion(), deletion() and display() operations on circular queue. [6]

```c
#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

void insertion(int item) {
    if ((rear + 1) % SIZE == front) { printf("FULL\n"); return; }
    if (front == -1) front = rear = 0; else rear = (rear + 1) % SIZE;
    queue[rear] = item;
}
void deletion(void) {
    if (front == -1) { printf("EMPTY\n"); return; }
    printf("Deleted %d\n", queue[front]);
    if (front == rear) front = rear = -1; else front = (front + 1) % SIZE;
}
void display(void) {
    int i;
    if (front == -1) { printf("EMPTY\n"); return; }
    for (i = front; ; i = (i + 1) % SIZE) {
        printf("%d ", queue[i]);
        if (i == rear) break;
    }
    printf("\n");
}
```
Key lines: rear/front always move with `% SIZE` (wrap-around); full when
`(rear+1)%SIZE == front`. Verified: `programs/CircularQueue.c`.

---

## Q.3 c) Write a note on Multiple stacks and queues with suitable diagram. [6]

### Multiple stacks (one array, two stacks)
1. Stack 1 grows UP from the left end (`top1 = -1`).
2. Stack 2 grows DOWN from the right end (`top2 = SIZE`).
3. Both full only when they meet: `top1 + 1 == top2`.
```
[10][20][30] . . . [80][90]
 ^stack1 up        stack2 down^
```

### Multiple queues (one array, two queues)
4. Queue 1 fills from the left, queue 2 from the right.
5. Space is shared flexibly — the array is full only when the queues meet.
```
[Q1|Q1|Q1| . . . |Q2|Q2]
  rear1 ->        <- rear2
```
Verified program: `programs/MultipleStacks.c`.

---

## Q.4 a) What is a linked list? Explain the different types of linked list with neat diagram. [6]

### Definition
A linked list is a linear data structure of nodes, each containing data and a
link to the next node; the nodes occupy non-contiguous memory connected by
pointers, with `head` marking the first node.

### Types
1. **Singly linked list:** one link per node; travel forward only; last link
   is NULL.
```
head -> [10|*] -> [20|*] -> [30|NULL]
```
2. **Doubly linked list:** `prev` + `next` links; travel both directions.
```
NULL <- [10] <-> [20] <-> [30] -> NULL
```
3. **Circular linked list:** last node links back to the first; no NULL.
```
┌-> [10] -> [20] -> [30] -┐
└─────────────────────────┘
```

---

## Q.4 b) Write a C function for the following on singly linked list with example: (i) Insert a node at the beginning (ii) Delete a node at the front (iii) Display. [8]

```c
typedef struct node { int data; struct node *link; } Node;
Node *head = NULL;

void insertFront(int v) {              /* (i) */
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = head;
    head = n;
}
void deleteFront(void) {               /* (ii) */
    Node *t = head;
    if (!head) return;
    head = head->link;
    free(t);
}
void display(void) {                  /* (iii) */
    Node *t = head;
    while (t) { printf("%d -> ", t->data); t = t->link; }
    printf("NULL\n");
}
```
Example: insertFront(30), insertFront(20), insertFront(10) →
`10 -> 20 -> 30 -> NULL`; deleteFront() removes 10. Verified:
`programs/SLLBasicOps.c`.

---

## Q.4 c) Write the C function to add two polynomials. [6]

```c
Poly *add(Poly *p1, Poly *p2) {
    Poly *res = NULL;
    while (p1 && p2) {
        if (p1->exp > p2->exp)      { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
        else if (p1->exp < p2->exp) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
        else {
            int c = p1->coef + p2->coef;   /* same exponent: add */
            if (c != 0) res = insert(res, c, p1->exp);
            p1 = p1->link; p2 = p2->link;
        }
    }
    while (p1) { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
    while (p2) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
    return res;
}
```
Each polynomial is a linked list of (coef, exp) nodes. Verified:
`programs/PolynomialAddition.c` (3x^2+2x+1) + (4x^3+x^2+5) = 4x^3+4x^2+2x+6.

---

## Q.5 c) Write the C function for additional list operations: (i) Inverting Singly linked list (ii) Concatenating Singly linked list. [8]

### (i) Invert (reverse) the SLL — 3-pointer method
```c
void invert(void) {
    Node *prev = NULL, *cur = head, *next;
    while (cur) {
        next = cur->link;     /* save next */
        cur->link = prev;     /* flip the link */
        prev = cur;           /* advance prev */
        cur = next;           /* advance cur  */
    }
    head = prev;              /* old last = new head */
}
```
Before: `10 -> 20 -> 30`. After: `30 -> 20 -> 10`.

### (ii) Concatenate two SLLs
```c
void concatenate(void) {
    Node *t = head;
    if (!head) { head = head2; return; }
    while (t->link) t = t->link;    /* last node of list 1 */
    t->link = head2;                /* join list 2 at the end */
}
```
Before: `10->20` and `100->200`. After: `10->20->100->200`.
Both verified in `programs/SLLAdditionalOps.c`.

---

## Q.6 c) Write a C function: (i) Insert a node at the beginning of doubly linked list (ii) Deleting a node at the end of the doubly linked list. [6]

```c
typedef struct dnode { int data; struct dnode *prev, *next; } DNode;

void insertFront(DNode **h, int v) {          /* (i) */
    DNode *n = malloc(sizeof(DNode));
    n->data = v; n->prev = NULL; n->next = *h;
    if (*h) (*h)->prev = n;    /* old first points back to new node */
    *h = n;
}
void deleteEnd(DNode **h) {                   /* (ii) */
    DNode *t = *h;
    if (!*h) return;
    while (t->next) t = t->next;    /* last node */
    if (t->prev == NULL) *h = NULL; /* only node */
    else t->prev->next = NULL;
    free(t);
}
```
Verified: `programs/DLLBasicOps.c`.
