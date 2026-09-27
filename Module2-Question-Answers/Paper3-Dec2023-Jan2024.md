# BCS304 — Dec 2023/Jan 2024 Exam
## Module 2: Stacks, Stack Applications & Queues

---

## Q.2 a) Define stack. Give the implementation of Push(), POP() and display() functions by considering its empty and full conditions. [7]

### Definition
A stack is a LIFO (Last-In-First-Out) ordered list where insertions and deletions
happen only at the **top**.

### Easiest Program (`programs/StackArray.c`)
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

## Q.2 b) Write an algorithm to evaluate a postfix expression and apply the same for the given postfix expression: 6, 2, /, 3, -, 4, 2, *, +. [7]

### Algorithm
1. Scan left to right. If token is an **operand**, push it.
2. If token is an **operator**, pop top two (`op2` then `op1`), compute
   `op1 <op> op2`, push result.
3. Continue till end; the final stack value is the result.

### Worked Trace — `6 2 / 3 - 4 2 * +`

| Token | Action | Stack after |
|---|---|---|
| 6 | push | [6] |
| 2 | push | [6, 2] |
| / | 6/2=3, push | [3] |
| 3 | push | [3, 3] |
| - | 3-3=0, push | [0] |
| 4 | push | [0, 4] |
| 2 | push | [0, 4, 2] |
| * | 4*2=8, push | [0, 8] |
| + | 0+8=8, push | [8] |

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
    printf("6 2 / 3 - 4 2 * + = %d\n", evalPostfix("6 2 / 3 - 4 2 * +"));
    return 0;
}
```

---

## Q.2 c) Write the Postfix form of the following using stack: (i) A*(B*C+D*E)+F (ii) (a+(b*c)/(d-e)). [6]

### (i) A*(B*C+D*E)+F
```
(B*C) -> BC*
(D*E) -> DE*
(B*C+D*E) -> BC*DE*+
A*(...) -> ABC*DE*+*
(...)+F -> ABC*DE*+*F+
```
**Result: `A B C * D E * + * F +`**

### (ii) (a+(b*c)/(d-e))
```
(b*c) -> bc*
(d-e) -> de-
(b*c)/(d-e) -> bc*de-/
a+(...) -> abc*de-/+
```
**Result: `a b c * d e - / +`**

### Program (`programs/InfixToPostfix.c`) — verifies both
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char stack[50]; int top = -1;
void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
int precedence(char c) { if(c=='^')return 3; if(c=='*'||c=='/')return 2; if(c=='+'||c=='-')return 1; return 0; }
void infixToPostfix(char *infix, char *postfix) {
    int i, k = 0; top = -1;
    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isalnum(c)) postfix[k++] = c;
        else if (c == '(') push(c);
        else if (c == ')') { while (top != -1 && stack[top] != '(') postfix[k++] = pop(); pop(); }
        else { while (top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(c)) postfix[k++] = pop(); push(c); }
    }
    while (top != -1) postfix[k++] = pop();
    postfix[k] = '\0';
}
int main() {
    char p1[50], p2[50];
    infixToPostfix("A*(B*C+D*E)+F", p1);
    infixToPostfix("a+(b*c)/(d-e)", p2);
    printf("(i)  %s\n(ii) %s\n", p1, p2);
    return 0;
}
```

---

## Q.3 c) Define Queue. Discuss how to represent queue using dynamic arrays. [6]

### Definition
A queue is a FIFO (First-In-First-Out) ordered list — insertions at the **rear**,
deletions at the **front**. A dynamic-array queue uses a growable array (via
`realloc`) instead of a fixed-size one.

### Points
1. Start with a small `capacity`; when full, **double** it with `realloc`.
2. Avoids wasting memory (over-allocating) or running out of space
   (under-allocating).
3. A full circular + dynamic implementation (handling wrap-around) is a Module 3 topic.

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
