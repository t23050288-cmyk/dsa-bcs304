/* Two stacks stored in ONE array (multiple stacks) */
#include <stdio.h>
#define SIZE 10

int stack[SIZE];
int top1 = -1, top2 = SIZE;          /* stack1 grows up, stack2 grows down */

void push1(int v) {
    if (top1 + 1 == top2) { printf("Stack 1 FULL\n"); return; }
    stack[++top1] = v;
}
void push2(int v) {
    if (top2 - 1 == top1) { printf("Stack 2 FULL\n"); return; }
    stack[--top2] = v;
}
int pop1(void) { return (top1 == -1) ? (printf("Stack 1 EMPTY\n"), -1) : stack[top1--]; }
int pop2(void) { return (top2 == SIZE) ? (printf("Stack 2 EMPTY\n"), -1) : stack[top2++]; }

int main() {
    push1(10); push1(20); push1(30);
    push2(90); push2(80);
    printf("pop1 = %d\n", pop1());
    printf("pop2 = %d\n", pop2());
    printf("Array now: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", stack[i]);
    printf("\n");
    return 0;
}
