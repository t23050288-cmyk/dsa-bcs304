/* Sparse matrix: triplet representation + transpose.
   Answers: "What is sparse matrix? Give the triplet form... and find its transpose",
            "Write a C function to perform transpose of a given sparse matrix" */
#include <stdio.h>

typedef struct { int row, col, value; } term;

void transpose(term a[], term b[]) {
    int n = a[0].value;          /* total number of non-zero elements */
    b[0].row = a[0].col;         /* rows in b = columns in a */
    b[0].col = a[0].row;         /* columns in b = rows in a */
    b[0].value = n;

    if (n > 0) {
        int currentb = 1;
        for (int i = 0; i < a[0].col; i++) {        /* for each column of a */
            for (int j = 1; j <= n; j++) {            /* scan all non-zero terms */
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}

int main() {
    /* 3x3 sparse matrix with 3 non-zero terms: (0,0,15), (1,2,22), (2,1,-6) */
    term a[10] = {
        {3, 3, 3},     /* header: 3 rows, 3 cols, 3 non-zero terms */
        {0, 0, 15},
        {1, 2, 22},
        {2, 1, -6}
    };
    term b[10];

    printf("Original triplets:\n");
    for (int i = 1; i <= a[0].value; i++)
        printf("row=%d col=%d value=%d\n", a[i].row, a[i].col, a[i].value);

    transpose(a, b);

    printf("Transpose triplets:\n");
    for (int i = 1; i <= b[0].value; i++)
        printf("row=%d col=%d value=%d\n", b[i].row, b[i].col, b[i].value);

    return 0;
}
