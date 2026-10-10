#include <stdio.h>
#define MAX 5
int stack[MAX], top = -1;
int isEmpty() { return top == -1; }
int isFull()  { return top == MAX - 1; }
void push(int x) {
    if (isFull()) { printf("Stack Overflow\n"); return; }
    stack[++top] = x;
    printf("%d pushed\n", x);
}
int pop() {
    if (isEmpty()) { printf("Stack Underflow\n"); return -1; }
    return stack[top--];
}
int peek() {
    if (isEmpty()) { printf("Stack is empty\n"); return -1; }
    return stack[top];
}
int main() {
    push(10); push(20); push(30); push(40); push(50);
    push(60);                              /* overflow */
    printf("peek = %d\n", peek());
    printf("popped %d\n", pop());
    while (!isEmpty()) pop();
    pop();                                 /* underflow */
    return 0;
}
