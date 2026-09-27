# BCS304 — June/July 2024 Exam
## Module 2: Stacks, Stack Applications & Queues

---

## Q.2 b) Explain ADT stack. [7]

### Definition
A stack is an ordered list in which insertions and deletions happen at only **one
end**, called the **top** — making it a **Last-In-First-Out (LIFO)** structure. An
ADT defines *what* operations it supports, without specifying implementation.

### Points
1. **Main operations:** `push(data)` — insert; `pop()` — remove and return top.
2. **Auxiliary operations:** `top()` — peek without removing; `size()` — count of
   elements; `isEmptyStack()`; `isFullStack()`.
3. `CreateS(max_stack_size)` — creates an empty stack.
4. Trying to `pop` an empty stack = **underflow**; `push` onto a full stack =
   **overflow**.
5. Used internally by programs as a **system stack** for function calls
   (activation records).

### Syntax
```c
Stack CreateS(max_stack_size);
Boolean IsFull(stack);
Stack Add(stack, item);      /* push */
Boolean IsEmpty(stack);
Element Delete(stack);       /* pop */
```

### Smallest Program
```c
#include <stdio.h>
int stack[10], top = -1;
void push(int x) { stack[++top] = x; }
int pop() { return stack[top--]; }
int main() { push(5); push(10); printf("%d\n", pop()); return 0; }
```

---

## Q.2 c) Define Stack. Implement the operations of stack using arrays. [7]

### Definition
A stack implemented with a one-dimensional array `stack[MAX_STACK_SIZE]`, tracked
by a single variable `top` pointing to the current top element's index.

### Points
1. `top = -1` → empty stack.
2. **IsEmpty**: `top < 0`. **IsFull**: `top >= MAX_STACK_SIZE - 1`.
3. `push`: increment `top`, store item at `stack[top]`.
4. `pop`: return `stack[top]`, decrement `top`.

### Easiest Program (`programs/StackArray.c`)
```c
#include <stdio.h>
#define MAX_STACK_SIZE 5

int stack[MAX_STACK_SIZE];
int top = -1;

void push(int item) {
    if (top >= MAX_STACK_SIZE - 1) { printf("Stack overflow\n"); return; }
    stack[++top] = item;
}

int pop() {
    if (top < 0) { printf("Stack underflow\n"); return -1; }
    return stack[top--];
}

void display() {
    if (top < 0) { printf("Stack is empty\n"); return; }
    printf("Stack (top to bottom): ");
    for (int i = top; i >= 0; i--) printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    push(10); push(20); push(30);
    display();
    printf("Popped: %d\n", pop());
    display();
    return 0;
}
```
