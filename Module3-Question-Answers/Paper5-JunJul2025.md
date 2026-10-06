# BCS304 — June/July 2025 Exam
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.3 c) Develop functions in C to implement insertion, deletion and display operations on circular queue of integers. [10]

```c
#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

void insert(int item) {
    if ((rear + 1) % SIZE == front) { printf("Queue FULL\n"); return; }
    if (front == -1) front = rear = 0;
    else rear = (rear + 1) % SIZE;
    queue[rear] = item;
    printf("Inserted %d\n", item);
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
```
The `% SIZE` is the whole trick — it makes the rear wrap to index 0 and reuse
deleted front slots. Verified: `programs/CircularQueue.c` (60 and 70 inserted
into the slots freed by deleting 10 and 20).

---

## Q.4 a) What is linked list? With suitable examples explain different types of linked lists. [5]

### Definition
A linked list is a collection of nodes where each node stores data and a
pointer to the next node; nodes live in scattered memory and are connected
only by these pointers.

### Types (with examples)
1. **Singly linked list** — one link, forward travel only.
   Example: `10 -> 20 -> 30 -> NULL` (like a one-way street).
2. **Doubly linked list** — prev + next links, travel both ways.
   Example: browser back/forward history (`NULL <- [page1] <-> [page2] -> NULL`).
3. **Circular linked list** — last node points back to first.
   Example: a music playlist on repeat; turn-based multiplayer games.

---

## Q.4 b) Write a C functions to implement a stack of integers using a Singly Linked List (SLL). [5]

```c
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
```
push = insertFront, pop = deleteFront — top is the head. Never becomes full
(heap memory). Verified: `programs/LinkedStack.c`.

---

## Q.4 c) Develop functions in C: (i) Insert an element at end of SLL (ii) Delete an element at end of SLL (iii) Concatenation of two SLL. [10]

```c
typedef struct node { int data; struct node *link; } Node;

void insertEnd(Node **h, int v) {             /* (i) */
    Node *n = malloc(sizeof(Node)), *t = *h;
    n->data = v; n->link = NULL;
    if (*h == NULL) { *h = n; return; }
    while (t->link) t = t->link;
    t->link = n;
}
void deleteEnd(Node **h) {                    /* (ii) */
    Node *t = *h, *prev = NULL;
    if (*h == NULL) { printf("List empty\n"); return; }
    while (t->link) { prev = t; t = t->link; }
    printf("Deleted %d\n", t->data);
    if (prev == NULL) *h = NULL;   /* only one node */
    else prev->link = NULL;
    free(t);
}
void concatenate(Node *l1, Node *l2) {        /* (iii) */
    Node *t = l1;
    if (!l1) return l2;      /* (in exam: head = head2) */
    while (t->link) t = t->link;
    t->link = l2;
}
```
Verified: `programs/SLLBasicOps.c` (insert/delete end) and
`programs/SLLAdditionalOps.c` (concatenate).

---

## Q.5 a) Write a structure definition for Doubly Linked List (DLL) of integers. Advantages of DLL over SLL? [4]

### Structure definition
```c
typedef struct dnode {
    int data;                    /* integer data */
    struct dnode *prev, *next;   /* links to both neighbours */
} DNode;
```

### Advantages over SLL
1. Travel in BOTH directions (SLL: forward only).
2. Deleting a given node is O(1) — the node itself knows its previous node;
   in SLL you must search for the previous node from the head, O(n).
3. Insert before a given node is easy — no need to find the predecessor by
   traversal.
(Cost: one extra pointer per node.)

---

## Q.5 b) Develop C functions: (i) Insert a node at front of DLL (ii) Delete a node at end of DLL. [10]

```c
void insertFront(DNode **h, int v) {          /* (i) */
    DNode *n = malloc(sizeof(DNode));
    n->data = v; n->prev = NULL; n->next = *h;
    if (*h) (*h)->prev = n;    /* old first node's prev = new node */
    *h = n;
}
void deleteEnd(DNode **h) {                  /* (ii) */
    DNode *t = *h;
    if (!*h) { printf("List empty\n"); return; }
    while (t->next) t = t->next;
    printf("Deleted %d\n", t->data);
    if (t->prev == NULL) *h = NULL;   /* only node was there */
    else t->prev->next = NULL;        /* second-last becomes last */
    free(t);
}
```
Verified: `programs/DLLBasicOps.c`.

---

## Q.5 c) For the given sparse matrix design the linked list representation. [6]

### Steps (apply to the given matrix)
1. Draw the matrix; find every NON-ZERO element's (row, col, value).
2. Create a header node: (rows, cols, number of non-zeros).
3. Create one node per non-zero element and link them all.

### Example
```
Matrix:  15  0  0
          0  0  6
          0  9  0

head -> [3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
```
Why: only non-zeros are stored, so a mostly-zero big matrix needs very little
memory. Verified: `programs/SparseMatrixLinked.c`.
