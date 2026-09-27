# 2. Array Representation of Stacks (+ Dynamic Arrays)

Covers: "Define Stack. Implement the operations of stack using arrays", "Write a C
Function to implement pop, push and display operations for stacks using arrays",
"Give the implementation of Push(), POP() and display() functions by considering its
empty and full conditions", "Write a program in C to implement push, pop and display
operations for stacks using arrays".

---

## 2.1 Array Representation

**Definition:** The simplest way to implement a stack is a one-dimensional array
`stack[MAX_STACK_SIZE]`, tracked by a single integer variable `top` that points to
the index of the current top element.

**Points:**
1. `top = -1` represents an **empty** stack.
2. The bottom element is stored at `stack[0]`, the `i`th element at `stack[i-1]`.
3. **IsEmpty** condition: `top < 0`.
4. **IsFull** condition: `top >= MAX_STACK_SIZE - 1`.
5. `push`: increment `top`, then store the item at `stack[top]`.
6. `pop`: return `stack[top]`, then decrement `top`.
7. Always check empty/full conditions **before** popping/pushing to avoid
   underflow/overflow errors.

### Syntax
```c
#define MAX_STACK_SIZE 100
typedef struct { int key; } element;
element stack[MAX_STACK_SIZE];
int top = -1;
```

### Easiest Program (push, pop, display — considers empty and full conditions)
```c
#include <stdio.h>
#define MAX_STACK_SIZE 5

int stack[MAX_STACK_SIZE];
int top = -1;

void push(int item) {
    if (top >= MAX_STACK_SIZE - 1) {          /* full condition */
        printf("Stack overflow, cannot push %d\n", item);
        return;
    }
    stack[++top] = item;
}

int pop() {
    if (top < 0) {                             /* empty condition */
        printf("Stack underflow\n");
        return -1;
    }
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

**Smallest Program:**
```c
#include <stdio.h>
int s[5], t = -1;
int main() { s[++t]=1; s[++t]=2; printf("%d\n", s[t--]); return 0; }
```

---

## 2.2 Stacks Using Dynamic Arrays

**Definition:** Instead of a fixed-size array (which forces you to guess
`MAX_STACK_SIZE` in advance), a stack can use a **dynamically allocated array**
whose size grows automatically (via `realloc`) whenever it becomes full.

**Points:**
1. Shortcoming of the static array: you must know a good bound on stack size at
   compile-time — too small wastes function calls with overflow errors, too large
   wastes memory.
2. Fix: start with a small `capacity` (e.g. 1), and when the stack becomes full,
   **double the capacity** using `realloc()`.
3. **Array doubling**: whenever the array is full, allocate a new block of
   `2 * capacity` and copy the old elements across.
4. **Analysis:** Even though each individual doubling costs O(capacity) time, the
   *total* time spent on all doublings across `n` pushes is **O(n)** — this is
   called **amortized O(1)** per push.

### Syntax
```c
int capacity = 1;
int *stack = (int*) malloc(capacity * sizeof(int));
int top = -1;

/* when full: */
capacity *= 2;
stack = (int*) realloc(stack, capacity * sizeof(int));
```

### Easiest Program
```c
#include <stdio.h>
#include <stdlib.h>

int *stack;
int top = -1;
int capacity = 1;

void push(int item) {
    if (top >= capacity - 1) {              /* full: double the capacity */
        capacity *= 2;
        stack = (int*) realloc(stack, capacity * sizeof(int));
        printf("(capacity doubled to %d)\n", capacity);
    }
    stack[++top] = item;
}

int pop() {
    if (top < 0) { printf("Stack underflow\n"); return -1; }
    return stack[top--];
}

int main() {
    stack = (int*) malloc(capacity * sizeof(int));
    for (int i = 1; i <= 5; i++) push(i * 10);   /* triggers doubling as it grows */

    printf("Stack (top to bottom): ");
    for (int i = top; i >= 0; i--) printf("%d ", stack[i]);
    printf("\n");

    free(stack);
    return 0;
}
```
