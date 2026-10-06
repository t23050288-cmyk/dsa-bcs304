# 6. Polynomials using Linked Lists

Covers: "linked representation of polynomial", "algorithm to add two
polynomials represented using linked list", "add two polynomials using SLL".

---

## 6.1 Representing a Polynomial with a Linked List

**Definition:** A polynomial like `3x^2 + 2x + 1` is stored as a linked list
with one node per term — each node has a **coefficient**, an **exponent**, and
a link to the next term.

### Node Structure
```c
typedef struct polyNode {
    int coef;                  /* coefficient, e.g. 3 in 3x^2 */
    int exp;                   /* exponent, e.g. 2 in 3x^2     */
    struct polyNode *link;
} Poly;
```

### Diagram — 3x^2 + 2x + 1
```
[coef=3, exp=2] -> [coef=2, exp=1] -> [coef=1, exp=0] -> NULL
```

### Points
1. Terms are stored in **decreasing order of exponent** (highest first).
2. Zero-coefficient terms are not stored at all.
3. Advantage over array: no wasted space for missing terms — e.g. x^1000 +
   1 needs only 2 nodes, not 1001 array cells.

---

## 6.2 Adding Two Polynomials

### Algorithm (exam version)
```
1. Point p1 at the first list, p2 at the second list, result = empty.
2. While both p1 and p2 exist:
   a. If p1->exp > p2->exp      -> copy p1's term into result; p1 = p1->link
   b. If p1->exp < p2->exp      -> copy p2's term into result; p2 = p2->link
   c. If exponents are EQUAL    -> add the coefficients;
                                   if the sum is not 0, store the term;
                                   advance BOTH p1 and p2
3. Copy whatever terms remain in p1 or p2.
4. Return result.
```

### Worked example (write this in the exam)
```
p1 = 3x^2 + 2x + 1
p2 = 4x^3 + 1x^2 + 5

Step 1: 4x^3 (only in p2)         -> take it
Step 2: 3x^2 vs 1x^2 -> 3+1 = 4   -> 4x^2
Step 3: 2x (only in p1)           -> take it
Step 4: 1 + 5 = 6                 -> 6
Sum = 4x^3 + 4x^2 + 2x + 6
```

### Diagram
```
p1:  [3,2] -> [2,1] -> [1,0] -> NULL
p2:  [4,3] -> [1,2] -> [5,0] -> NULL
                      |
     compare exps term by term, add equal exps
                      v
Sum: [4,3] -> [4,2] -> [2,1] -> [6,0] -> NULL
```

### Easiest Program (`programs/PolynomialAddition.c`) — compiled & verified
```c
#include <stdio.h>
#include <stdlib.h>
typedef struct polyNode { int coef, exp; struct polyNode *link; } Poly;

Poly *insert(Poly *head, int coef, int exp) {
    Poly *n = malloc(sizeof(Poly)), *t = head;
    n->coef = coef; n->exp = exp; n->link = NULL;
    if (head == NULL) return n;
    while (t->link) t = t->link;
    t->link = n;
    return head;
}

Poly *add(Poly *p1, Poly *p2) {
    Poly *res = NULL;
    while (p1 && p2) {
        if (p1->exp > p2->exp)      { res = insert(res, p1->coef, p1->exp); p1 = p1->link; }
        else if (p1->exp < p2->exp) { res = insert(res, p2->coef, p2->exp); p2 = p2->link; }
        else {
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
    while (p) { printf("%dx^%d", p->coef, p->exp); p = p->link; if (p) printf(" + "); }
    printf("\n");
}

int main() {
    Poly *p1 = NULL, *p2 = NULL, *sum;
    p1 = insert(p1, 3, 2); p1 = insert(p1, 2, 1); p1 = insert(p1, 1, 0);
    p2 = insert(p2, 4, 3); p2 = insert(p2, 1, 2); p2 = insert(p2, 5, 0);
    display(p1); display(p2);
    sum = add(p1, p2);
    printf("Sum   : "); display(sum);
    return 0;
}
```
**Verified output:**
```
3x^2 + 2x^1 + 1x^0
4x^3 + 1x^2 + 5x^0
Sum   : 4x^3 + 4x^2 + 2x^1 + 6x^0
```

### Circular representation (extra point)
Polynomials can also be stored as a **circular list** with a **header node**
holding the polynomial's name — then erasing the whole polynomial takes fixed
time (just reconnect its nodes to an avail list, no traversal needed).
