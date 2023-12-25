// Ï£¶ûÅÅÐò
//

#include <stdio.h>

int main(void) {
    int a[1001];
    int i, j, k, t, n;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", a + i);

    // Ï£¶ûÅÅÐò
    for (i = n/ 2; i > 0; i /= 2) {
        for (j = i; j < n; j++) {
            t = a[j];
            for (k = j - i; k >= 0 && t < a[k]; k -= i) {
                a[k + i] = a[k];
            }
            a[k + i] = t;
        }
        for (j = 0; j < n; ++j)
            printf("%-3d", a[j]);
        printf("\n");
    }

    return 0;
}
/*
5
3 2 6 1 4

3  1  4  2  6
1  2  3  4  6


10
4 2 5 8 3 1 9 7 0 6

1  2  5  0  3  4  9  7  8  6
1  0  3  2  5  4  8  6  9  7
0  1  2  3  4  5  6  7  8  9
 */