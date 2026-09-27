/* Demonstrates malloc, calloc, realloc, free — and static vs dynamic allocation.
   Answers: "Discuss four dynamic memory allocation functions",
            "Differentiate static vs dynamic; syntax for malloc/calloc/realloc/free" */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int staticArr[5] = {1, 2, 3, 4, 5};   /* static allocation: fixed size, compile-time */

    int *p1 = (int*) malloc(sizeof(int));      /* malloc: uninitialized memory */
    *p1 = 1024;
    printf("malloc: %d\n", *p1);

    int *p2 = (int*) calloc(5, sizeof(int));   /* calloc: zero-initialized memory */
    printf("calloc (should all be 0): ");
    for (int i = 0; i < 5; i++) printf("%d ", p2[i]);
    printf("\n");

    p2 = (int*) realloc(p2, 10 * sizeof(int)); /* realloc: resize existing block */
    if (p2 == NULL) { printf("realloc failed\n"); return 1; }
    printf("realloc succeeded, block now holds 10 ints\n");

    free(p1);   /* free: release memory back to the system */
    free(p2);

    printf("static array: ");
    for (int i = 0; i < 5; i++) printf("%d ", staticArr[i]);
    printf("\n");

    return 0;
}
