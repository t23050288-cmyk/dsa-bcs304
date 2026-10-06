# BCS304 — June/July 2024 Exam
## Module 3: Circular Queues, Multiple Stacks/Queues & Linked Lists

---

## Q.3 a) What is the advantage of circular queue over ordinary queue? Discuss the implementation of circular queue operations. [8]

### Definition
A circular queue is a linear queue where the last position connects back to
the first, so the array wraps around and freed front slots get reused.

### Advantages over ordinary queue
1. **No wasted space:** after deletions, the empty front slots are reused — a
   linear queue can never use them again.
2. **No false overflow:** a linear queue reports "full" when `rear` reaches
   the last index even if the front is empty; circular queue is full only
   when it is genuinely full.
3. All operations still O(1).

### Implementation (the 3 key operations)
```c
#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

void insert(int item) {                        /* ENQUEUE */
    if ((rear + 1) % SIZE == front) { printf("FULL\n"); return; }
    if (front == -1) front = rear = 0; else rear = (rear + 1) % SIZE;
    queue[rear] = item;
}
void delete(void) {                            /* DEQUEUE */
    if (front == -1) { printf("EMPTY\n"); return; }
    if (front == rear) front = rear = -1; else front = (front + 1) % SIZE;
}
void display(void) {                           /* DISPLAY */
    int i;
    if (front == -1) return;
    for (i = front; ; i = (i + 1) % SIZE) {
        printf("%d ", queue[i]);
        if (i == rear) break;
    }
}
```

Full verified program: `programs/CircularQueue.c` (compiled, runs — output
shows slots being reused after wrap-around).

---

## Q.3 b) Demonstrate multiple stacks and queues with suitable examples. [12]

### Definition
Multiple stacks/queues = storing TWO or more stacks (or queues) inside ONE
shared array, so the memory is used efficiently.

### Multiple stacks (2 stacks in 1 array)
1. Stack 1 grows from the LEFT end upward: `top1` starts at -1.
2. Stack 2 grows from the RIGHT end downward: `top2` starts at SIZE.
3. They grow towards each other; FULL for both when `top1 + 1 == top2`.

```
index:  0    1    2   ...  7    8    9
      [10] [20] [30]      [80] [90]
       ^stack1 (up)        stack2(down)^
```
```c
void push1(int v) { if (top1 + 1 == top2) return; stack[++top1] = v; }
void push2(int v) { if (top2 - 1 == top1) return; stack[--top2] = v; }
```

### Multiple queues (2 queues in 1 array)
1. Queue 1 starts at the left, inserts at its rear (moves right).
2. Queue 2 starts at the right, inserts at its rear (moves left).
3. The array is full only when the two queues meet in the middle.

Verified program: `programs/MultipleStacks.c` — output shows pop1=30, pop2=80.

---

## Q.4 a) Explain Linked Stacks and Queues operations. [10]

### Linked Stack (stack using linked list)
1. `top` = head of the list; **push** = insert node at front; **pop** =
   delete front node.
2. Empty when `top == NULL`; NEVER full (heap memory), unlike array stacks.
```c
void push(int v) {
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = top;   /* new node on top */
    top = n;
}
int pop(void) {
    Node *t = top; int v = top->data;
    top = top->link; free(t);
    return v;
}
```

### Linked Queue (queue using linked list)
1. Two pointers kept: `front` and `rear`.
2. **enqueue** = insert at rear (O(1) — no traversal, rear is remembered);
   **dequeue** = delete at front.
3. Empty when `front == NULL`. No circular trick needed — a linked queue has
   no fixed array, so false overflow never happens.
```
front -> [10] -> [20] -> [30] <- rear
  ^delete                        insert^
```
Verified program: `programs/LinkedStack.c`.

---

## Q.4 b) Give the C functions for the following on singly linked list with example: (i) Insert a node at the beginning (ii) Delete a node at the front (iii) Display. [10]

### Structure
```c
typedef struct node { int data; struct node *link; } Node;
Node *head = NULL;
```

### (i) Insert at beginning
```c
void insertFront(int v) {
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = head;
    head = n;
}
```
Example: list `20 -> NULL`; insertFront(10) gives `10 -> 20 -> NULL`.

### (ii) Delete at front
```c
void deleteFront(void) {
    Node *t = head;
    if (!head) return;
    head = head->link;
    free(t);
}
```

### (iii) Display
```c
void display(void) {
    Node *t = head;
    while (t) { printf("%d -> ", t->data); t = t->link; }
    printf("NULL\n");
}
```
Verified program: `programs/SLLBasicOps.c` (output: 10 -> 20 -> 30 -> 40 ->
NULL, deletes 10 and 40 correctly).

---

## Q.5 a) Define linked list? Implement C function for the following circular Doubly linked list: (i) Insert a node at the beginning (ii) Delete a node at the end (iii) Display. [10]

### Definition
A linked list is a chain of nodes where each node stores data plus pointer(s)
to its neighbour nodes; nodes are scattered in memory and connected only by
links. A **circular doubly linked list** has both `prev` and `next` links, and
the last node's `next` points back to the head while the head's `prev` points
to the last node — no NULL anywhere.

```c
typedef struct dnode { int data; struct dnode *prev, *next; } DNode;
DNode *head = NULL;
```

### (i) Insert at beginning
```c
void insertFront(int v) {
    DNode *n = malloc(sizeof(DNode)), *last;
    n->data = v;
    if (!head) { n->prev = n->next = n; head = n; return; } /* alone: circle */
    last = head->prev;                 /* the last node (via head->prev!) */
    n->next = head; n->prev = last;
    head->prev = n; last->next = n;
    head = n;
}
```

### (ii) Delete at end
```c
void deleteEnd(void) {
    DNode *last;
    if (!head) return;
    last = head->prev;                  /* last node directly available */
    if (last == head) { free(head); head = NULL; return; }  /* only node */
    last->prev->next = head;            /* second-last points to head */
    head->prev = last->prev;
    free(last);
}
```

### (iii) Display
```c
void display(void) {
    DNode *t = head;
    if (!head) return;
    do { printf("%d <-> ", t->data); t = t->next; } while (t != head);
    printf("(back to head)\n");
}
```

---

## Q.5 b) Develop a function to delete a node whose information field is specified in singly linked list. [10]

### Algorithm
1. Travel with two pointers: `t` (current) and `prev` (previous).
2. Stop when `t->data == key` (found) or `t == NULL` (not found).
3. If found: bypass the node — `prev->link = t->link` — then `free(t)`.
4. Edge case: key in the FIRST node → `head = t->link`.

### Function
```c
void deleteByValue(int key) {
    Node *t = head, *prev = NULL;
    while (t && t->data != key) { prev = t; t = t->link; }
    if (!t) { printf("%d not found\n", key); return; }
    if (prev == NULL) head = t->link;   /* key was in first node */
    else prev->link = t->link;          /* bypass the node */
    free(t);
}
```
Example: `10 -> 20 -> 30`, delete 20 → `10 -> 30`.
Verified inside `programs/SLLAdditionalOps.c`.
