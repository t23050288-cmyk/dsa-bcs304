/* Stack using array: push, pop, display with empty/full conditions.
   Answers: "Implement push, pop and display operations for stacks using arrays" */
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
    push(10);
    push(20);
    push(30);
    display();

    printf("Popped: %d\n", pop());
    display();

    return 0;
}
