/* Add two polynomials represented as linked lists */
#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode {
    int coef, exp;
    struct polyNode *link;
} Poly;

Poly *insert(Poly *head, int coef, int exp) {
    Poly *n = malloc(sizeof(Poly)), *t = head;
    n->coef = coef; n->exp = exp; n->link = NULL;
    if (head == NULL) return n;
    while (t->link) t = t->link;
    t->link = n;
    return head;
}

/* adds p1 and p2 into result (assumes terms in decreasing exp order) */
Poly *add(Poly *p1, Poly *p2) {
    Poly *res = NULL;
    while (p1 && p2) {
        if (p1->exp > p2->exp)      { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
        else if (p1->exp < p2->exp) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
        else {                        /* same exponent: add coefficients */
            int c = p1->coef + p2->coef;
            if (c != 0) res = insert(res, c, p1->exp);
            p1 = p1->link; p2 = p2->link;
        }
    }
    while (p1) { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
    while (p2) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
    return res;
}

void display(Poly *p) {
    while (p) {
        printf("%dx^%d", p->coef, p->exp);
        p = p->link;
        if (p) printf(" + ");
    }
    printf("\n");
}

int main() {
    /* p1 = 3x^2 + 2x + 1,  p2 = 4x^3 + x^2 + 5 */
    Poly *p1 = NULL, *p2 = NULL, *sum;
    p1 = insert(p1, 3, 2); p1 = insert(p1, 2, 1); p1 = insert(p1, 1, 0);
    p2 = insert(p2, 4, 3); p2 = insert(p2, 1, 2); p2 = insert(p2, 5, 0);
    display(p1); display(p2);
    sum = add(p1, p2);
    printf("Sum   : "); display(sum);
    return 0;
}
