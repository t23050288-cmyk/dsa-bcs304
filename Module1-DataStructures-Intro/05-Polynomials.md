# 5. Polynomials (Array Representation)

**Definition:** A polynomial is a sum of terms, where each term has the form `a·xᵉ`
(`a` = coefficient, `x` = variable, `e` = exponent). The **degree** of a polynomial is
its largest (leading) exponent.

**Example:** `A(x) = 3x²⁰ + 2x⁵ + 4` and `B(x) = x⁴ + 10x³ + 3x² + 1`

**Points:**
1. Two common array-based representations exist, each with tradeoffs.
2. **Method 1 — Dense representation:** store the polynomial as `{degree, coef[MAX_DEGREE]}`,
   with `coef[i]` = coefficient of `x^(degree-i)`.
   - Simple, but **wastes space** if the polynomial is *sparse* (few non-zero terms
     relative to its degree) — e.g. `2x¹⁰⁰⁰+1` would need 1001 storage slots.
3. **Method 2 — Sparse/triple representation:** store only the non-zero terms as
   `{coef, expon}` pairs in a shared array, tracked with `start`/`finish` indices.
   - Solves the wasted-space problem for sparse polynomials.
   - Costs about twice the space when *all* terms are non-zero (dense case).
4. Adding two polynomials `A(x) + B(x)`: compare leading exponents term by term;
   whichever has the larger exponent is copied to the result; if exponents are equal,
   coefficients are added (and the term is dropped if the sum is 0).
5. The overall computing time to add two polynomials with `m` and `n` non-zero terms
   is **O(m + n)** — a single linear pass through both.

### Syntax (Method 2 — sparse representation)
```c
#define MAX_TERMS 100
typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;   /* index of next free slot */
```

### Easiest Program (add two polynomials using array representation)
```c
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
    term A[] = {{3, 20}, {2, 5}, {4, 0}};      /* 3x^20 + 2x^5 + 4 */
    term B[] = {{1, 4}, {10, 3}, {3, 2}, {1, 0}}; /* x^4 + 10x^3 + 3x^2 + 1 */
    term result[10];

    int n = addPoly(A, 3, B, 4, result);

    printf("Result polynomial: ");
    for (int i = 0; i < n; i++) printf("%.0fx^%d ", result[i].coef, result[i].expon);
    printf("\n");
    return 0;
}
```

**Smallest Program (add two same-degree polynomials, hardcoded):**
```c
#include <stdio.h>
int main() { int a[]={1,2,3}, b[]={4,5,6}, i, r[3]; for(i=0;i<3;i++) r[i]=a[i]+b[i]; for(i=0;i<3;i++) printf("%d ", r[i]); return 0; }
```
