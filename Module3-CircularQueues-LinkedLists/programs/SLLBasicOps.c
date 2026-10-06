/* Singly Linked List: insert front, insert end, delete front, delete end, display */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} Node;

Node *head = NULL;

void insertFront(int v) {
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = head;
    head = n;
}

void insertEnd(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v; n->link = NULL;
    if (head == NULL) { head = n; return; }
    while (t->link != NULL) t = t->link;
    t->link = n;
}

void deleteFront(void) {
    Node *t = head;
    if (head == NULL) { printf("List empty\n"); return; }
    printf("Deleted %d\n", head->data);
    head = head->link;
    free(t);
}

void deleteEnd(void) {
    Node *t = head, *prev = NULL;
    if (head == NULL) { printf("List empty\n"); return; }
    while (t->link != NULL) { prev = t; t = t->link; }
    printf("Deleted %d\n", t->data);
    if (prev == NULL) head = NULL; else prev->link = NULL;
    free(t);
}

void display(void) {
    Node *t = head;
    if (head == NULL) { printf("List empty\n"); return; }
    while (t != NULL) { printf("%d -> ", t->data); t = t->link; }
    printf("NULL\n");
}

int main() {
    insertFront(20); insertFront(10); insertEnd(30); insertEnd(40);
    display();                /* 10 -> 20 -> 30 -> 40 -> NULL */
    deleteFront();            /* removes 10 */
    deleteEnd();              /* removes 40 */
    display();                /* 20 -> 30 -> NULL */
    return 0;
}
