# 2. Multiple Stacks and Queues

Covers: "Demonstrate multiple stacks and queues", "multiple queues with
relevant functions", "multiple stacks and priority queue" (note: priority queue
as such is a Module 5 topic — here we focus on multiple stacks).

---

## 2.1 What are Multiple Stacks?

**Definition:** Storing TWO or more stacks inside a SINGLE array, so one array
is shared between many stacks without wasting memory.

### The classic 2-stacks-in-1-array trick
1. Stack 1 starts at the **left end** (index 0) and grows **upwards**
   (`top1` starts at -1).
2. Stack 2 starts at the **right end** (index SIZE-1) and grows **downwards**
   (`top2` starts at SIZE).
3. The two stacks grow towards each other.
4. **Full condition for BOTH:** `top1 + 1 == top2` — they meet in the middle.
5. Either stack is empty when its top crosses its own boundary
   (`top1 == -1` or `top2 == SIZE`).

### Diagram
```
index:   0    1    2    3    4    5    6    7    8    9
       [10] [20] [30] [  ] [  ] [  ] [  ] [80] [90] ...
        ^top1=2                      top2=7^
   <-- stack 1 grows -->      <-- stack 2 grows -->
        (upwards)                   (downwards)
```

### Easiest Program (`programs/MultipleStacks.c`) — compiled & verified
```c
#include <stdio.h>
#define SIZE 10
int stack[SIZE];
int top1 = -1, top2 = SIZE;

void push1(int v) {
    if (top1 + 1 == top2) { printf("Stack 1 FULL\n"); return; }
    stack[++top1] = v;
}
void push2(int v) {
    if (top2 - 1 == top1) { printf("Stack 2 FULL\n"); return; }
    stack[--top2] = v;
}
int pop1(void) { return (top1 == -1) ? (printf("Stack 1 EMPTY\n"), -1) : stack[top1--]; }
int pop2(void) { return (top2 == SIZE) ? (printf("Stack 2 EMPTY\n"), -1) : stack[top2++]; }

int main() {
    push1(10); push1(20); push1(30);
    push2(90); push2(80);
    printf("pop1 = %d\n", pop1());
    printf("pop2 = %d\n", pop2());
    return 0;
}
```
**Verified output:**
```
pop1 = 30
pop2 = 80
```

### For more than 2 stacks
1. Divide the array into equal parts, one part per stack, each with its own
   top and boundary. (Simple, but a full part blocks that stack even if the
   array has space elsewhere.)
2. Or use linked lists for each stack — then no fixed boundaries at all.

---

## 2.2 What are Multiple Queues?

**Definition:** Storing several queues efficiently inside one array by sharing
the space, instead of giving each queue a separate fixed array.

### The 2-queues-in-1-array trick (mirror image of stacks)
1. Queue 1 starts at the **left** and grows **right**.
2. Queue 2 starts at the **right** and grows **left**.
3. The array is truly full only when the two queues meet.

### Points (why share one array?)
1. A single queue per array wastes the unused part of that array.
2. With multiple queues in one array, if one queue is long and another short,
   they share the free space flexibly.
3. Each queue keeps its own `front` and `rear` pointers; only the boundary
   logic changes.
4. For n queues, use n pairs of (front, rear) into one array, or give each
   queue its own linked list.

### Combined diagram
```
ONE ARRAY, TWO STACKS:          ONE ARRAY, TWO QUEUES:
[ S1 | S1 | S1 | .... | S2 | S2 ]   [ Q1 Q1 Q1 .... Q2 Q2 ]
 ^grow up^          ^grow down^      ^insert at rear^  ^insert at left^
```
