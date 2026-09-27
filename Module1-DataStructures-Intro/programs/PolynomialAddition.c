/* Polynomial addition using array (sparse/triple) representation.
   Answers: polynomial add operation from the Polynomials ADT syllabus topic */
#include <stdio.h>

typedef struct { float coef; int expon; } term;

/* returns number of resulting terms, filling res[] */
int addPoly(term a[], int na, term b[], int nb, term res[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i].expon > b[j].expon) {
            res[k++] = a[i++];
        } else if (a[i].expon < b[j].expon) {
            res[k++] = b[j++];
        } else {
            float sum = a[i].coef + b[j].coef;
            if (sum != 0) { res[k].coef = sum; res[k].expon = a[i].expon; k++; }
            i++; j++;
        }
    }
    while (i < na) res[k++] = a[i++];
    while (j < nb) res[k++] = b[j++];
    return k;
}

int main() {
    term A[] = {{3, 20}, {2, 5}, {4, 0}};          /* 3x^20 + 2x^5 + 4 */
    term B[] = {{1, 4}, {10, 3}, {3, 2}, {1, 0}};   /* x^4 + 10x^3 + 3x^2 + 1 */
    term result[10];

    int n = addPoly(A, 3, B, 4, result);

    printf("Result polynomial: ");
    for (int i = 0; i < n; i++) printf("%.0fx^%d ", result[i].coef, result[i].expon);
    printf("\n");

    return 0;
}
