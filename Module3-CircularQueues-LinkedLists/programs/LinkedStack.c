/* Stack of integers implemented using a Singly Linked List (linked stack) */
#include <stdio.h>
#include <stdlib.h>

typedef struct node { int data; struct node *link; } Node;
Node *top = NULL;

void push(int v) {
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = top;
    top = n;
}
int pop(void) {
    Node *t = top; int v;
    if (top == NULL) { printf("Stack EMPTY\n"); return -1; }
    v = top->data; top = top->link; free(t);
    return v;
}
void display(void) {
    Node *t = top;
    if (!top) { printf("Stack EMPTY\n"); return; }
    while (t) { printf("%d -> ", t->data); t = t->link; }
    printf("NULL (top)\n");
}

int main() {
    push(10); push(20); push(30);
    display();
    printf("popped = %d\n", pop());
    display();
    return 0;
}
