//
// Created by xulon on 2023/6/6.
//
#include <stdio.h>

int main(void) {
    int a[1001];
    int i, j, t, n;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", a + i);

    for (i = 1; i < n; ++i) {
        t = a[i];
        for (j = i - 1; j > -1 && a[j] > t; j--) {
            a[j + 1] = a[j];
        }
        a[j + 1] = t;
        for (j = 0; j < n; ++j)
            printf("%-3d", a[j]);
        printf("\n");
    }
    return 0;
}