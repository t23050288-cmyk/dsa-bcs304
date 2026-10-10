#include <stdio.h>
int main() {
    int a[6][6] = {
        {15,0,0,22,0,-15},
        {0,11,3,0,0,0},
        {0,0,0,-6,0,0},
        {0,0,0,0,0,0},
        {91,0,0,0,0,0},
        {0,0,28,0,0,0}};
    int t[40][3], s[40][3], k = 1, i, j, c, n;
    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++)
            if (a[i][j] != 0) { t[k][0] = i; t[k][1] = j; t[k][2] = a[i][j]; k++; }
    t[0][0] = 6; t[0][1] = 6; t[0][2] = k - 1;
    n = t[0][2];
    printf("TRIPLET\nRow Col Value\n");
    for (i = 0; i <= n; i++) printf("%3d %3d %5d\n", t[i][0], t[i][1], t[i][2]);
    /* simple transpose: column by column */
    s[0][0] = t[0][1]; s[0][1] = t[0][0]; s[0][2] = n;
    k = 1;
    for (c = 0; c < t[0][1]; c++)
        for (i = 1; i <= n; i++)
            if (t[i][1] == c) { s[k][0] = t[i][1]; s[k][1] = t[i][0]; s[k][2] = t[i][2]; k++; }
    printf("TRANSPOSE\nRow Col Value\n");
    for (i = 0; i <= n; i++) printf("%3d %3d %5d\n", s[i][0], s[i][1], s[i][2]);
    return 0;
}
