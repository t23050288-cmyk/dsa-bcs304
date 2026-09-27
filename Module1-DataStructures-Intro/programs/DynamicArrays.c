/* Dynamically allocated 1D and 2D arrays.
   Answers: "Arrays, Dynamically Allocated Arrays" syllabus topic */
#include <stdio.h>
#include <stdlib.h>

int main() {
    /* 1D dynamic array */
    int n;
    printf("Enter size for 1D array: ");
    scanf("%d", &n);
    int *list = (int*) malloc(n * sizeof(int));
    if (list == NULL) { printf("insufficient memory\n"); return 1; }
    for (int i = 0; i < n; i++) list[i] = i * i;

    printf("1D dynamic array: ");
    for (int i = 0; i < n; i++) printf("%d ", list[i]);
    printf("\n");
    free(list);

    /* 2D dynamic array (array of arrays) */
    int nrows = 3, ncolumns = 4;
    int **array = (int**) malloc(nrows * sizeof(int*));
    for (int i = 0; i < nrows; i++)
        array[i] = (int*) malloc(ncolumns * sizeof(int));

    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncolumns; j++)
            array[i][j] = i * ncolumns + j;

    printf("2D dynamic array:\n");
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncolumns; j++) printf("%d\t", array[i][j]);
        printf("\n");
    }

    for (int i = 0; i < nrows; i++) free(array[i]);
    free(array);

    return 0;
}
