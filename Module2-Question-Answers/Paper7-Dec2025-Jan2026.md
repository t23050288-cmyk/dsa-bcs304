# BCS304 — Dec 2025/Jan 2026 Exam
## Module 2: Stacks, Stack Applications & Queues

---

## Q.2 a) Define stack. Give the implementation of push(), POP() and Display() functions by considering its empty and full conditions. [7]

### Program (`programs/StackArray.c`)
```c
#include <stdio.h>
#define MAX_STACK_SIZE 5

int stack[MAX_STACK_SIZE];
int top = -1;

void push(int item) {
    if (top >= MAX_STACK_SIZE - 1) { printf("Stack overflow, cannot push %d\n", item); return; }
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

## Q.2 b) Write an algorithm to evaluate a postfix expression and apply the same for the given postfix expression. [7]

### Algorithm
1. Scan left to right; push operands onto the stack.
2. On an operator, pop `op2` then `op1`, compute `op1 <op> op2`, push result.
3. At the end, the value left on the stack is the result.

### Worked Trace — example `6 2 / 3 - 4 2 * +`

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
int main() { printf("%d\n", evalPostfix("6 2 / 3 - 4 2 * +")); return 0; }
```

---

## Q.2 c) Write the postfix form of the following using stack: (i) A*(B*C+D*E)+F (ii) (A+(B*C)/(D-E)). [6]

### (i) A*(B*C+D*E)+F
```
(B*C) -> BC*
(D*E) -> DE*
(B*C+D*E) -> BC*DE*+
A*(...) -> ABC*DE*+*
(...)+F -> ABC*DE*+*F+
```
**Result: `A B C * D E * + * F +`**

### (ii) (A+(B*C)/(D-E))
```
(B*C) -> BC*
(D-E) -> DE-
(B*C)/(D-E) -> BC*DE-/
A+(...) -> ABC*DE-/+
```
**Result: `A B C * D E - / +`**

---

## Q.3 a) What are the disadvantages of ordinary queue? Discuss the implementation of circular queue. [8]

> ⚠️ **Module split note**: Only the "disadvantages of ordinary queue" part is a
> Module 2 topic — the circular queue implementation itself is covered under
> **Module 3: Circular Queues**.

### Disadvantages of Ordinary (Linear) Queue
1. The queue gradually shifts right — `front` increases, but freed slots before
   it are never reused.
2. `rear` reaches `MAX_QUEUE_SIZE-1` → queue reports **"full"** even if space is
   free at the front.
3. Fixing this by shifting the whole queue left on every deletion costs **O(n)**
   per deletion — slow for large queues.
4. This is exactly the motivation for the **Circular Queue** — see Module 3 for
   its full implementation.

---

## Q.3 c) Define Queue. Discuss how to represent Queue using dynamic arrays. [6]

### Definition
A queue (FIFO list) can use a **dynamically allocated array** for storage,
growing its capacity via `realloc` instead of a fixed size.

### Program (`programs/QueueDynamicArray.c`)
```c
#include <stdio.h>
#include <stdlib.h>
int *queue;
int front = -1, rear = -1, capacity = 2;

void insert(int item) {
    if (rear == capacity - 1) {
        capacity *= 2;
        queue = (int*) realloc(queue, capacity * sizeof(int));
    }
    queue[++rear] = item;
    if (front == -1) front = 0;
}

int main() {
    queue = (int*) malloc(capacity * sizeof(int));
    for (int i = 1; i <= 5; i++) insert(i * 10);
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
    free(queue);
    return 0;
}
```
