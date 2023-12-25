//
// Created by xulon on 2023/6/6.
//
#include <stdio.h>

int main(void) {
    int a[1001];
    int n, i, j, t;
    scanf("%d", &n); // 排序的个数
    for (i = 0; i < n; ++i) // 输入需要排序的数
        scanf("%d", a + i);

    // 选择排序
    for (i = 0; i < n - 1; ++i) {
        for (j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
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

1  3  6  2  4
1  2  6  3  4
1  2  3  6  4
1  2  3  4  6
 */