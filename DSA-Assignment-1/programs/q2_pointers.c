#include <stdio.h>
#include <stdlib.h>
int main() {
    int a = 10;
    int *p = &a;                          /* declaration + initialization */
    printf("a = %d, *p = %d\n", a, *p);   /* dereferencing */
    *p = 20;
    printf("a after *p = 20 : %d\n", a);

    int arr[3] = {10, 20, 30};
    int *q = arr;
    printf("%d %d %d\n", *q, *(q + 1), *(q + 2));   /* pointer arithmetic */
    q++;
    printf("after q++ : %d\n", *q);

    int *m = (int *)malloc(3 * sizeof(int));
    int *c = (int *)calloc(3, sizeof(int));
    m[0] = 5; m[1] = 6; m[2] = 7;
    printf("malloc: %d %d %d | calloc: %d %d %d\n", m[0], m[1], m[2], c[0], c[1], c[2]);
    m = (int *)realloc(m, 5 * sizeof(int));
    m[3] = 8; m[4] = 9;
    printf("realloc: %d %d %d %d %d\n", m[0], m[1], m[2], m[3], m[4]);
    free(m);
    free(c);
    return 0;
}
