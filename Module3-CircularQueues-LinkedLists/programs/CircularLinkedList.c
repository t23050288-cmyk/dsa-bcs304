/* Circular Linked List: insert at front, count nodes, display */
#include <stdio.h>
#include <stdlib.h>

typedef struct node { int data; struct node *link; } Node;
Node *head = NULL;

void insertFront(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v;
    if (head == NULL) { n->link = n; head = n; return; }
    while (t->link != head) t = t->link;   /* find last node */
    n->link = head;
    t->link = n;
    head = n;
}

int count(void) {
    int c = 0;
    Node *t = head;
    if (head == NULL) return 0;
    do { c++; t = t->link; } while (t != head);
    return c;
}

void display(void) {
    Node *t = head;
    if (head == NULL) { printf("List empty\n"); return; }
    do { printf("%d -> ", t->data); t = t->link; } while (t != head);
    printf("(back to head)\n");
}

int main() {
    insertFront(10); insertFront(20); insertFront(30);
    display();                 /* 30 -> 20 -> 10 -> (back to head) */
    printf("Number of nodes = %d\n", count());
    return 0;
}
