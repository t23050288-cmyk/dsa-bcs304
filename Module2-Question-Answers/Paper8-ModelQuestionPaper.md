# BCS304 — Model Question Paper (2023-24 CBCS Scheme)
## Module 2: Stacks, Stack Applications & Queues

---

## Q.01 c) Write a program in C to implement push, pop and display operations for stacks using arrays. [7]

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

## Q.02 c) Write a function to evaluate the postfix expression. Illustrate the same for the given postfix expression: ABC-D*+E$F+ and assume A=6, B=3, C=2, D=5, E=1 and F=7. [7]

### Definition
`$` denotes exponentiation here (classic textbook Polish-notation symbol,
equivalent to `^`).

### Worked Trace — `ABC-D*+E$F+` with A=6, B=3, C=2, D=5, E=1, F=7

| Token | Action | Stack after |
|---|---|---|
| A(6) | push | [6] |
| B(3) | push | [6, 3] |
| C(2) | push | [6, 3, 2] |
| - | 3-2=1 | [6, 1] |
| D(5) | push | [6, 1, 5] |
| * | 1*5=5 | [6, 5] |
| + | 6+5=11 | [11] |
| E(1) | push | [11, 1] |
| $ | 11^1=11 | [11] |
| F(7) | push | [11, 7] |
| + | 11+7=18 | [18] |

**Result: 18**

### Program (`programs/PostfixEval.c` — adapted with variable substitution and `$`)
```c
#include <stdio.h>

int stack[20], top = -1;
void push(int x) { stack[++top] = x; }
int pop() { return stack[top--]; }

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

int main() {
    int A=6, B=3, C=2, D=5, E=1, F=7;
    /* postfix: A B C - D * + E $ F + */
    push(A); push(B); push(C);
    int b = pop(), a = pop(); push(a - b);      /* B C - */
    push(D);
    b = pop(); a = pop(); push(a * b);          /* D * */
    b = pop(); a = pop(); push(a + b);          /* + */
    push(E);
    b = pop(); a = pop(); push(power(a, b));    /* E $ */
    push(F);
    b = pop(); a = pop(); push(a + b);          /* F + */

    printf("Result = %d\n", pop());
    return 0;
}
```

---

## Q.03 a) Develop a C program to implement insertion, deletion and display operations on Linear queue. [10]

### Program (`programs/LinearQueueArray.c`)
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
    if (front == -1) front = 0;
}

int deleteFront() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue[front++];
    if (front > rear) front = rear = -1;
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
