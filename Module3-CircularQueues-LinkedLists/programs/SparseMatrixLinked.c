/* Sparse matrix: linked list representation (only non-zero elements stored) */
#include <stdio.h>
#include <stdlib.h>

typedef struct smNode { int row, col, val; struct smNode *link; } SM;

SM *insert(SM *head, int r, int c, int v) {
    SM *n = malloc(sizeof(SM)), *t = head;
    n->row = r; n->col = c; n->val = v; n->link = NULL;
    if (!head) return n;
    while (t->link) t = t->link;
    t->link = n;
    return head;
}

int main() {
    /* matrix:  15  0  0
                0  0  6
                0  9  0                       */
    int a[3][3] = {{15,0,0},{0,0,6},{0,9,0}};
    SM *head = NULL;
    int i, j;

    /* header node: (rows, cols, count of non-zero) */
    head = insert(head, 3, 3, 3);
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (a[i][j] != 0)
                head = insert(head, i, j, a[i][j]);

    printf("row col val\n");
    for (SM *t = head; t; t = t->link)
        printf("%3d %4d %4d\n", t->row, t->col, t->val);
    return 0;
}
