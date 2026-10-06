/* SLL: search, invert (reverse), concatenate two lists, delete node by value */
#include <stdio.h>
#include <stdlib.h>

typedef struct node { int data; struct node *link; } Node;
Node *head = NULL, *head2 = NULL;

void insertEnd(Node **h, int v) {
    Node *n = malloc(sizeof(Node)), *t = *h;
    n->data = v; n->link = NULL;
    if (*h == NULL) { *h = n; return; }
    while (t->link) t = t->link;
    t->link = n;
}

void search(int key) {
    Node *t = head; int pos = 1;
    while (t) {
        if (t->data == key) { printf("Found %d at position %d\n", key, pos); return; }
        t = t->link; pos++;
    }
    printf("%d not found\n", key);
}

void invert(void) {
    Node *prev = NULL, *cur = head, *next;
    while (cur) { next = cur->link; cur->link = prev; prev = cur; cur = next; }
    head = prev;
}

void concatenate(void) {
    Node *t = head;
    if (head == NULL) { head = head2; return; }
    while (t->link) t = t->link;
    t->link = head2;
}

void deleteByValue(int key) {
    Node *t = head, *prev = NULL;
    while (t && t->data != key) { prev = t; t = t->link; }
    if (!t) { printf("%d not found\n", key); return; }
    printf("Deleted node with value %d\n", key);
    if (prev == NULL) head = t->link; else prev->link = t->link;
    free(t);
}

void display(Node *h) {
    while (h) { printf("%d -> ", h->data); h = h->link; }
    printf("NULL\n");
}

int main() {
    insertEnd(&head, 10); insertEnd(&head, 20); insertEnd(&head, 30);
    insertEnd(&head2, 100); insertEnd(&head2, 200);
    display(head);
    search(20);
    invert(); display(head);           /* 30 -> 20 -> 10 */
    concatenate(); display(head);      /* 30 20 10 100 200 */
    deleteByValue(20); display(head);
    return 0;
}
