/* Self-referential structure with a suitable example (3-node chain).
   Answers: "With suitable example, discuss self-referential structures" */
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    char data;
    struct list *link;   /* pointer to another structure of the SAME type */
} list;

int main() {
    list *item1 = (list*) malloc(sizeof(list));
    list *item2 = (list*) malloc(sizeof(list));
    list *item3 = (list*) malloc(sizeof(list));

    item1->data = 'a';
    item2->data = 'b';
    item3->data = 'c';

    item1->link = item2;
    item2->link = item3;
    item3->link = NULL;

    list *p = item1;
    printf("Chain: ");
    while (p != NULL) {
        printf("%c -> ", p->data);
        p = p->link;
    }
    printf("NULL\n");

    free(item1);
    free(item2);
    free(item3);
    return 0;
}
