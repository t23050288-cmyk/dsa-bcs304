# 5. Queue — Definition, Array Representation & Operations

Covers: "Define Queue", "What are the disadvantages of linear queue?", "With
suitable example discuss the representation of linear queue with array", "Discuss
how to represent queue using dynamic arrays", "Develop a C program to implement
insertion, deletion and display operations on Linear queue".

> Note: This file covers the **basic/linear (non-circular) queue only** — matching
> the "linear queue" scope of Module 2 (circular queues are a Module 3 topic).

---

## 5.1 What is a Queue?

**Definition:** A queue is an ordered list in which insertions take place at one end
(the **rear**) and deletions take place at the other end (the **front**). Since the
first element inserted is the first one removed, a queue is also called a
**First-In-First-Out (FIFO)** list.

**Points:**
1. Given queue `Q = (a0, a1, ..., an-1)`: `a0` is the front element, `an-1` is the
   rear element.
2. Insertion is called `addq`/`push`; deletion is called `deleteq`/`pop`.
3. Real-world example: a line of people at a ticket counter — first person in line
   is served (removed) first.
4. Used in **job scheduling** by operating systems — jobs are processed in the order
   they enter the system (if no priorities are used).

---

## 5.2 Array Representation of a Linear Queue

**Definition:** A queue is maintained using a linear array `queue[]` and two
pointer variables: `front` (location of the front element) and `rear` (location of
the rear element).

**Points:**
1. Initial condition: `front = rear = -1` means the queue is **empty**.
2. **IsEmpty**: `front == rear`.
3. **IsFull**: `rear == MAX_QUEUE_SIZE - 1`.
4. `addq` (insert): increment `rear`, then store the item at `queue[rear]`.
5. `deleteq` (remove): increment `front`, then return `queue[front]`.

### Syntax
```c
#define MAX_QUEUE_SIZE 100
typedef struct { int key; } element;
element queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;
```

### Easiest Program (insertion, deletion, display on a linear queue)
```c
#include <stdio.h>
#define MAX_QUEUE_SIZE 5

int queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;

void insert(int item) {
    if (rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full, cannot insert %d\n", item);
        return;
    }
    queue[++rear] = item;
    if (front == -1) front = 0;    /* first element inserted */
}

int deleteFront() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue[front++];
    if (front > rear) front = rear = -1;   /* queue emptied, reset */
    return item;
}

void display() {
    if (front == -1 || front > rear) { printf("Queue is empty\n"); return; }
    printf("Queue (front to rear): ");
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    insert(10); insert(20); insert(30);
    display();
    printf("Deleted: %d\n", deleteFront());
    display();
    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
int q[5], f=0, r=-1;
int main() { q[++r]=1; q[++r]=2; printf("%d\n", q[f++]); return 0; }
```

---

## 5.3 Disadvantages of a Linear (Ordinary) Queue

**Points:**
1. As elements are inserted and deleted, the queue **gradually shifts to the
   right** — `front` keeps increasing, but the array slots to its left (positions
   `0` to `front-1`) are never reused.
2. Eventually `rear` reaches `MAX_QUEUE_SIZE - 1` — the queue reports **"full"** —
   even though there may still be plenty of *unused* space at the front of the
   array.
3. This wastes memory that could otherwise be reused.
4. **Naive fix**: shift the entire queue left every time an element is deleted, so
   the first element returns to `queue[0]`. But shifting is **O(n)** per deletion
   in the worst case — very time-consuming for large queues.
5. **Better fix**: use a **Circular Queue** (Module 3 topic) — the array "wraps
   around" so slots freed at the front are reused automatically without any
   shifting.

---

## 5.4 Representing a Queue Using Dynamic Arrays

**Definition:** Instead of a fixed-size array with a hardcoded `MAX_QUEUE_SIZE`, a
queue can use a **dynamically allocated array** so its capacity can grow at
run-time as more elements are inserted.

**Points:**
1. Start with a small `capacity` and a dynamically allocated array via `malloc`.
2. When the queue becomes full, use `realloc()` to **double the capacity** — same
   "array doubling" idea used for dynamic stacks (see file 02).
3. This avoids the two extremes of static arrays: wasting memory by
   over-allocating, or running out of space by under-allocating.
4. A full **circular** + dynamic-array queue implementation (handling wrap-around
   during doubling) is a more advanced version of this idea, covered under
   **Module 3: Circular Queues**.

### Easiest Program (basic dynamic-array linear queue)
```c
#include <stdio.h>
#include <stdlib.h>

int *queue;
int front = -1, rear = -1;
int capacity = 2;

void insert(int item) {
    if (rear == capacity - 1) {                 /* full: grow the array */
        capacity *= 2;
        queue = (int*) realloc(queue, capacity * sizeof(int));
        printf("(capacity doubled to %d)\n", capacity);
    }
    queue[++rear] = item;
    if (front == -1) front = 0;
}

int deleteFront() {
    if (front == -1 || front > rear) { printf("Queue is empty\n"); return -1; }
    int item = queue[front++];
    if (front > rear) front = rear = -1;
    return item;
}

int main() {
    queue = (int*) malloc(capacity * sizeof(int));
    for (int i = 1; i <= 5; i++) insert(i * 10);   /* triggers doubling as it grows */

    printf("Queue: ");
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");

    free(queue);
    return 0;
}
```
