#include <stdio.h>
int main() {
    int a[4][5] = {{0,0,3,0,0},{0,4,0,0,0},{5,0,0,0,8},{0,0,0,6,0}};
    int t[20][3], k = 1, i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++)
            if (a[i][j] != 0) { t[k][0] = i; t[k][1] = j; t[k][2] = a[i][j]; k++; }
    t[0][0] = 4; t[0][1] = 5; t[0][2] = k - 1;
    printf("Row Col Value\n");
    for (i = 0; i < k; i++) printf("%3d %3d %5d\n", t[i][0], t[i][1], t[i][2]);
    return 0;
}
