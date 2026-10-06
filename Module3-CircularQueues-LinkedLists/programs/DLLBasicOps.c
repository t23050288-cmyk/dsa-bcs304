/* Doubly Linked List: insert front, insert rear, delete front, delete rear,
   search, concatenate */
#include <stdio.h>
#include <stdlib.h>

typedef struct dnode {
    int data;
    struct dnode *prev, *next;
} DNode;

DNode *head = NULL, *head2 = NULL;

void insertFront(DNode **h, int v) {
    DNode *n = malloc(sizeof(DNode));
    n->data = v; n->prev = NULL; n->next = *h;
    if (*h) (*h)->prev = n;
    *h = n;
}

void insertRear(DNode **h, int v) {
    DNode *n = malloc(sizeof(DNode)), *t = *h;
    n->data = v; n->next = NULL;
    if (*h == NULL) { n->prev = NULL; *h = n; return; }
    while (t->next) t = t->next;
    t->next = n; n->prev = t;
}

void deleteFront(DNode **h) {
    DNode *t = *h;
    if (*h == NULL) { printf("List empty\n"); return; }
    printf("Deleted %d\n", (*h)->data);
    *h = (*h)->next;
    if (*h) (*h)->prev = NULL;
    free(t);
}

void deleteRear(DNode **h) {
    DNode *t = *h;
    if (*h == NULL) { printf("List empty\n"); return; }
    while (t->next) t = t->next;
    printf("Deleted %d\n", t->data);
    if (t->prev == NULL) *h = NULL;          /* only node */
    else t->prev->next = NULL;
    free(t);
}

void search(DNode *h, int key) {
    int pos = 1;
    while (h) {
        if (h->data == key) { printf("Found %d at position %d\n", key, pos); return; }
        h = h->next; pos++;
    }
    printf("%d not found\n", key);
}

void concatenate(void) {
    DNode *t = head;
    if (!head) { head = head2; return; }
    while (t->next) t = t->next;
    t->next = head2;
    if (head2) head2->prev = t;
}

void display(DNode *h) {
    while (h) { printf("%d <-> ", h->data); h = h->next; }
    printf("NULL\n");
}

int main() {
    insertFront(&head, 20); insertFront(&head, 10); insertRear(&head, 30);
    display(head);                        /* 10 <-> 20 <-> 30 */
    insertRear(&head2, 100); insertRear(&head2, 200);
    search(head, 20);
    deleteFront(&head);                   /* removes 10 */
    deleteRear(&head);                    /* removes 30 */
    display(head);                        /* 20 */
    concatenate(); display(head);        /* 20 <-> 100 <-> 200 */
    return 0;
}
