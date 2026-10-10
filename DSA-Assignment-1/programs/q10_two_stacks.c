#include <stdio.h>
#define SIZE 10
int a[SIZE], top1 = -1, top2 = SIZE;
void push1(int x) {
    if (top1 + 1 == top2) { printf("Overflow\n"); return; }
    a[++top1] = x;
}
void push2(int x) {
    if (top2 - 1 == top1) { printf("Overflow\n"); return; }
    a[--top2] = x;
}
int pop1() { if (top1 == -1) { printf("Underflow 1\n"); return -1; } return a[top1--]; }
int pop2() { if (top2 == SIZE) { printf("Underflow 2\n"); return -1; } return a[top2++]; }
int main() {
    push1(10); push1(20); push1(30);
    push2(90); push2(80);
    printf("pop1 = %d, pop2 = %d\n", pop1(), pop2());
    return 0;
}
