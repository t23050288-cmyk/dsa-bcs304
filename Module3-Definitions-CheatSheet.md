# Module 3 — All Definitions Cheat Sheet (Easy to Understand & Tell to Ma'am/Sir)

> Each concept: **simple definition → key points → tiny diagram where useful**
> Read this once before the exam and you can explain any term confidently.

---

## 1. Circular Queue

**What it is:** A queue where the last position connects back to the first,
so both `front` and `rear` wrap around using `% SIZE` — freed front slots get
reused.

**Why it's needed:**
- Linear queue: once rear hits the end, no more insertion — even if the
  front is empty (**false overflow**).
- Circular queue: `rear = (rear+1) % SIZE` wraps and reuses freed slots.

**Key conditions:** Empty: `front == -1`. Full: `(rear+1) % SIZE == front`.

---

## 2. Multiple Stacks and Queues

**Multiple stacks:** Two or more stacks in ONE array. Stack 1 grows up from
the left (`top1 = -1`), stack 2 grows down from the right (`top2 = SIZE`);
both full when `top1 + 1 == top2`.

**Multiple queues:** Same idea — queue 1 fills from the left, queue 2 from
the right; the array is full only when they meet.

---

## 3. Linked List

**What it is:** A chain of nodes; each node has a **data part** and a
**link (pointer) part** to the next node. Nodes are scattered in memory,
connected only by links. `head` points to the first node; last link = NULL.

**Points:**
1. No continuous memory needed.
2. Size grows/shrinks at run time (malloc/free).
3. Insert/delete without shifting elements — only pointers change.
4. No random access: must travel from head (this is the cost).
5. Extra memory needed for the link field.

---

## 4. Types of Linked Lists

| Type | Links | Travel | Last node |
|---|---|---|---|
| Singly (SLL) | 1 (next) | one-way | link = NULL |
| Doubly (DLL) | 2 (prev, next) | both ways | next = NULL |
| Circular (CLL) | 1 | loops forever | link = first node |

```
SLL:  [10|*]->[20|*]->[30|NULL]
DLL:  NULL<-[10]<->[20]<->[30]->NULL
CLL:  ┌>[10]->[20]->[30]-┐
      └──────────────────┘
```

---

## 5. Node Structures (must memorize)

```c
/* SLL node */
typedef struct node { int data; struct node *link; } Node;
/* DLL node */
typedef struct dnode { int data; struct dnode *prev, *next; } DNode;
/* Polynomial node */
typedef struct polyNode { int coef, exp; struct polyNode *link; } Poly;
/* Sparse matrix node */
typedef struct smNode { int row, col, val; struct smNode *link; } SM;
```

---

## 6. SLL Basic Operations — one line each

1. **insertFront:** new node points to old head; head = new node.
2. **insertEnd:** travel to last node; last->link = new node.
3. **deleteFront:** head = head->link; free old head.
4. **deleteEnd:** travel with prev; prev->link = NULL; free last.
5. **deleteByValue:** find node with prev; prev->link = t->link; free t.
6. **search:** travel node by node comparing data with key.
7. **invert:** 3 pointers (prev, cur, next): flip every link; head = prev.
8. **concatenate:** last node of list1 points to head of list2.

---

## 7. Linked Stack and Linked Queue

**Linked stack:** top = head of SLL. push = insertFront, pop = deleteFront.
Never full (heap memory). Empty when top == NULL.

**Linked queue:** front + rear pointers on an SLL. enqueue at rear (O(1),
rear is remembered), dequeue at front. No false-overflow problem at all.

---

## 8. Polynomial with Linked List

**Representation:** one node per term `[coef | exp | link]`, exponents in
decreasing order; zero-coefficient terms are not stored.

**Addition rule:** compare exponents — bigger one goes first to result;
equal exponents → add coefficients (skip if sum is 0).

Example: (3x^2+2x+1) + (4x^3+x^2+5) = **4x^3 + 4x^2 + 2x + 6**.

---

## 9. Sparse Matrix — Linked Representation

**What it is:** a mostly-zero matrix stored as one linked node per
NON-ZERO element: `[row | col | value | link]`, plus a header node
`(rows, cols, count of non-zeros)`.

```
[3|3|3] -> [0|0|15] -> [1|2|6] -> [2|1|9] -> NULL
 header
```

---

## 10. Doubly Linked List (DLL)

**What it is:** each node has prev + next, so travel is possible in BOTH
directions.

**Advantages over SLL:**
1. Both-way travel.
2. Delete a given node in O(1) (node knows its previous; SLL must search
   for it, O(n)).
3. Easy to insert before a given node.
**Cost:** one extra pointer per node; every operation updates BOTH links.

**Concatenation of two DLLs:** join BOTH directions — last1->next = head2
AND head2->prev = last1.

---

## 11. Circular Linked List (CLL)

**What it is:** an SLL whose last node points back to the FIRST node — no
NULL anywhere, the chain is a ring.

**Key tricks:**
1. Insert front: update the LAST node too (it must point to the new first).
2. Counting: use a **do-while** loop, stop when you return to head.
3. Uses: round-robin scheduling, repeat playlists.

---

## 12. Circular Doubly Linked List

Both ideas combined: prev + next links AND last->next = head,
head->prev = last. No NULLs at all; travel wraps in both directions.
Bonus: head->prev directly gives the LAST node — rear access in O(1).

---

## Quick Memory Summary (one-liners)

| Term | One-line definition |
|---|---|
| Circular queue | Queue whose rear wraps around with % SIZE to reuse freed slots |
| False overflow | Linear queue reporting FULL while front slots are empty |
| Multiple stacks | 2+ stacks sharing one array, growing towards each other |
| Linked list | Chain of data+pointer nodes scattered in memory |
| SLL / DLL / CLL | one-way / both-way / ring-shaped linked lists |
| Linked stack | Stack on an SLL: push and pop at the head (top) |
| Linked queue | Queue on an SLL: enqueue at rear, dequeue at front |
| Polynomial node | One node per term: coefficient + exponent + link |
| Sparse matrix (linked) | One node per non-zero element: row + col + value |
| Invert SLL | Flip every link with prev/cur/next pointers |
| Concatenate | Join list 2 to the tail of list 1 |
