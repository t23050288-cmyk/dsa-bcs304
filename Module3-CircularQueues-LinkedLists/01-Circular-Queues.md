# 1. Circular Queues

Covers: "advantage of circular queue over ordinary queue", "disadvantages of
linear queue", "implementation of circular queue operations", "circular queues
using dynamic arrays".

---

## 1.1 Why do we need a Circular Queue? (Disadvantages of Linear Queue)

**Definition:** A circular queue is a linear queue in which the last position is
connected back to the first position, making the array "wrap around" like a
circle — so the empty spaces created after deletions can be reused.

### Disadvantages of an ordinary (linear) queue — the 3 main problems
1. **Wasted memory that cannot be reused.** In a linear queue, insertion
   happens only at `rear++`. After a few deletions, the front slots become
   empty, but we can still insert ONLY at the rear.
2. **"Queue full" even when it is NOT actually full.** Example: in a queue of
   size 5, insert 10, 20, 30, 40, 50 (full), then delete 10 and 20. Two slots
   are now free, but `rear` is already at the last index — so the queue reports
   FULL even though 2 positions are empty!
3. **False full condition.** The condition `rear == MAX-1` becomes true even
   though the queue physically has empty cells. This is called the *false
   overflow* problem.

### How the circular queue solves it
1. Use **modulo arithmetic**: `rear = (rear + 1) % SIZE` instead of `rear++`.
2. Now when `rear` reaches the end, the next insertion wraps around to index 0
   and reuses the freed front slots.
3. Result: every array slot stays usable until the queue is *genuinely* full.

### Diagram
```
LINEAR QUEUE (problem):                CIRCULAR QUEUE (solution):
 [10][20][30][40][50]                     rear
 delete 10, 20 ->                        ┌────┐
 [  ][  ][30][40][50]                 0  │    │← empty slot reused
 rear at end -> cannot insert,         1  │    │
 but 2 slots are free!                 2  │ 30 │ front
                                       3  │ 40 │
   front moves up, rear stuck          4  │ 50 │ rear
                                       └────┘
                            rear = (rear + 1) % 5 -> wraps to index 0
```

---

## 1.2 Operations of a Circular Queue

**Points (the 4 conditions that matter):**
1. **Empty check:** `front == -1` (nothing inserted yet).
2. **Full check:** `(rear + 1) % SIZE == front`.
3. **Insert (enqueue):** move `rear` circularly, place the item.
4. **Delete (dequeue):** take the item at `front`, move `front` circularly.

### Insert Algorithm
```
1. If (rear + 1) % SIZE == front  -> queue FULL, return
2. If front == -1  -> front = rear = 0        (first element)
   Else           -> rear = (rear + 1) % SIZE (move rear circularly)
3. queue[rear] = item
```

### Delete Algorithm
```
1. If front == -1 -> queue EMPTY, return
2. item = queue[front]
3. If front == rear -> front = rear = -1      (queue became empty)
   Else             -> front = (front + 1) % SIZE
4. Return item
```

### Easiest Program (`programs/CircularQueue.c`) — compiled & verified
```c
#include <stdio.h>
#define SIZE 5
int queue[SIZE], front = -1, rear = -1;

void insert(int item) {
    if ((rear + 1) % SIZE == front) { printf("Queue is FULL\n"); return; }
    if (front == -1) front = rear = 0; else rear = (rear + 1) % SIZE;
    queue[rear] = item;
    printf("Inserted %d\n", item);
}

void delete(void) {
    if (front == -1) { printf("Queue is EMPTY\n"); return; }
    printf("Deleted %d\n", queue[front]);
    if (front == rear) front = rear = -1; else front = (front + 1) % SIZE;
}

void display(void) {
    int i;
    if (front == -1) { printf("Queue is EMPTY\n"); return; }
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
    insert(60); insert(70);   /* reuses the freed front slots */
    display();
    return 0;
}
```
**Verified output:**
```
Inserted 10 ... Inserted 50
Queue: 10 20 30 40 50
Deleted 10
Deleted 20
Inserted 60
Inserted 70
Queue: 30 40 50 60 70
```
Note: 60 and 70 went into the slots freed by deleting 10 and 20 — this is
exactly what a linear queue cannot do.

---

## 1.3 Circular Queue using Dynamic Arrays

**Definition:** Instead of a fixed-size array declared at compile time, the
circular queue's array is allocated at run time with `malloc`, so the size can
be decided while the program runs (and even grown with `realloc`).

**Points:**
1. `int *queue = (int *)malloc(sizeof(int) * capacity);`
2. All logic (modulo wrap-around) stays the same; only the array comes from the
   heap instead of static memory.
3. Advantage: no fixed MAX limit — we can create a queue of exactly the size
   the program needs.
