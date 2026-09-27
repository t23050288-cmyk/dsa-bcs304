# BCS304 — Dec 2024/Jan 2025 Exam
## Module 2: Stacks, Stack Applications & Queues

---

## Q.1 b) Write a C Function to implement pop, push and display operations for stacks using arrays. [7]

### Program (`programs/StackArray.c`)
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

---

## Q.2 a) Write an algorithm to evaluate a postfix expression and apply the same for the given postfix expression: 6 2 / 3 – 4 2 * +. [7]

### Algorithm
1. Scan left to right; push operands.
2. On an operator, pop `op2` then `op1`, compute `op1 <op> op2`, push result.
3. Final stack value = result.

### Worked Trace — `6 2 / 3 - 4 2 * +`

| Token | Action | Stack after |
|---|---|---|
| 6 | push | [6] |
| 2 | push | [6, 2] |
| / | 6/2=3 | [3] |
| 3 | push | [3, 3] |
| - | 3-3=0 | [0] |
| 4 | push | [0, 4] |
| 2 | push | [0, 4, 2] |
| * | 4*2=8 | [0, 8] |
| + | 0+8=8 | [8] |

**Result: 8**

### Program (`programs/PostfixEval.c`)
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int stack[50], top = -1;
void push(int x) { stack[++top] = x; }
int pop() { return stack[top--]; }

int evalPostfix(char *expr) {
    int i = 0; char token[10]; top = -1;
    while (sscanf(expr + i, "%s", token) == 1) {
        if (isdigit(token[0])) push(atoi(token));
        else {
            int op2 = pop(), op1 = pop();
            switch (token[0]) {
                case '+': push(op1 + op2); break;
                case '-': push(op1 - op2); break;
                case '*': push(op1 * op2); break;
                case '/': push(op1 / op2); break;
            }
        }
        i += strlen(token);
        while (expr[i] == ' ') i++;
        if (expr[i] == '\0') break;
    }
    return pop();
}

int main() {
    printf("Result = %d\n", evalPostfix("6 2 / 3 - 4 2 * +"));
    return 0;
}
```

---

## Q.3 a) Define Queue. Discuss how to represent a queue using dynamic arrays. [8]

### Definition
A queue is a FIFO ordered list — insertions at the **rear**, deletions at the
**front**. Representing it with a dynamic array means the underlying storage
grows via `realloc` instead of using a fixed `MAX_QUEUE_SIZE`.

### Points
1. Start with a small `capacity`; on full, double it with `realloc`.
2. Avoids the two extremes of static arrays: over-allocating wastes memory,
   under-allocating causes overflow errors.
3. Full circular-queue + dynamic-array handling (wrap-around during doubling) is
   covered under Module 3: Circular Queues.

### Program (`programs/QueueDynamicArray.c`)
```c
#include <stdio.h>
#include <stdlib.h>

int *queue;
int front = -1, rear = -1;
int capacity = 2;

void insert(int item) {
    if (rear == capacity - 1) {
        capacity *= 2;
        queue = (int*) realloc(queue, capacity * sizeof(int));
        printf("(capacity doubled to %d)\n", capacity);
    }
    queue[++rear] = item;
    if (front == -1) front = 0;
}

int main() {
    queue = (int*) malloc(capacity * sizeof(int));
    for (int i = 1; i <= 5; i++) insert(i * 10);
    printf("Queue: ");
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
    free(queue);
    return 0;
}
```
