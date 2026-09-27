# BCS304 — June/July 2025 Exam
## Module 2: Stacks, Stack Applications & Queues

---

## Q.2 a) Define stack. With suitable example write the array representation of stack. [5]

### Definition
A stack is a LIFO ordered list represented by a linear array `stack[]` and an
integer `top` pointing to the current top element.

### Points
1. `top = -1` = empty. `top >= MAX_STACK_SIZE-1` = full.
2. `push`: `stack[++top] = item`. `pop`: `return stack[top--]`.

### Example
```
push 10 -> stack=[10], top=0
push 20 -> stack=[10,20], top=1
push 30 -> stack=[10,20,30], top=2
```

### Smallest Program
```c
#include <stdio.h>
int s[5], t = -1;
int main() { s[++t]=1; s[++t]=2; printf("%d\n", s[t--]); return 0; }
```

---

## Q.2 b) Write a C functions to implement push(), pop() and display() operations for stack using array. [5]

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
    printf("Stack (top to bottom): ");
    for (int i = top; i >= 0; i--) printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    push(10); push(20); push(30);
    display();
    return 0;
}
```

---

## Q.2 c) Translate the following infix expressions to postfix form using stack: (i) ((A*B)+C)/D (ii) A*B*C+D. [10]

### (i) ((A*B)+C)/D
```
(A*B) -> AB*
(A*B)+C -> AB*C+
((A*B)+C)/D -> AB*C+D/
```
**Result: `A B * C + D /`**

### (ii) A*B*C+D
```
A*B -> AB*
(A*B)*C -> AB*C*
(A*B*C)+D -> AB*C*D+
```
**Result: `A B * C * D +`**

### Program (`programs/InfixToPostfix.c`)
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
    infixToPostfix("((A*B)+C)/D", p1);
    infixToPostfix("A*B*C+D", p2);
    printf("(i)  %s\n(ii) %s\n", p1, p2);
    return 0;
}
```

---

## Q.3 a) What are the disadvantages of linear queue? [5]

### Points
1. The queue gradually shifts right as elements are inserted/deleted — `front`
   keeps increasing but slots before it are never reused.
2. Eventually `rear` reaches `MAX_QUEUE_SIZE-1` → reported **"full"** even if
   unused space exists at the front.
3. Naive fix (shift entire queue left on delete) costs O(n) per deletion — slow.
4. Solved properly by a **Circular Queue** (Module 3), which reuses freed slots
   without shifting.

---

## Q.3 b) With suitable example discuss the representation of linear queue with array. [5]

### Definition
A queue is maintained with array `queue[]` and two variables: `front` (front
element's index) and `rear` (rear element's index).

### Points
1. `front = rear = -1` → empty.
2. **IsFull**: `rear == MAX_QUEUE_SIZE-1`.
3. `addq`: increment `rear`, store item. `deleteq`: increment `front`, return item.

### Program (`programs/LinearQueueArray.c`)
```c
#include <stdio.h>
#define MAX_QUEUE_SIZE 5

int queue[MAX_QUEUE_SIZE];
int front = -1, rear = -1;

void insert(int item) {
    if (rear == MAX_QUEUE_SIZE - 1) { printf("Queue full\n"); return; }
    queue[++rear] = item;
    if (front == -1) front = 0;
}

int deleteFront() {
    if (front == -1 || front > rear) { printf("Queue empty\n"); return -1; }
    int item = queue[front++];
    if (front > rear) front = rear = -1;
    return item;
}

int main() {
    insert(10); insert(20); insert(30);
    printf("Deleted: %d\n", deleteFront());
    printf("Queue: ");
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
    return 0;
}
```
