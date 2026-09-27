/* Stack using a dynamically allocated array (grows via realloc / array doubling).
   Answers: "Stacks using Dynamic Arrays" syllabus topic */
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
