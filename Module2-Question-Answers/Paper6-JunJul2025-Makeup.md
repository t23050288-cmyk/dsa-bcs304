# BCS304 — June/July 2025 Makeup Exam
## Module 2: Stacks, Stack Applications & Queues

---

## Q.2 a) Write a C function to evaluate postfix expression. Evaluate 2 3 1 * + 9 - using the same. [8]

### Algorithm
1. Scan left to right; push operands.
2. On an operator, pop `op2` then `op1`, compute `op1 <op> op2`, push result.

### Worked Trace — `2 3 1 * + 9 -`

| Token | Action | Stack after |
|---|---|---|
| 2 | push | [2] |
| 3 | push | [2, 3] |
| 1 | push | [2, 3, 1] |
| * | 3*1=3 | [2, 3] |
| + | 2+3=5 | [5] |
| 9 | push | [5, 9] |
| - | 5-9=-4 | [-4] |

**Result: -4**

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
    printf("2 3 1 * + 9 - = %d\n", evalPostfix("2 3 1 * + 9 -"));
    return 0;
}
```

---

## Q.2 b) Implement push(), pop() and display operations of stack using array. [8]

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
