//
// Created by xulon on 2023/6/6.
//
#include <stdio.h>

int main(void) {
    int a[1001];
    int n, i, j, t;
    scanf("%d", &n);// n为要排序的数的个数

    for (i = 0; i < n; ++i)    // 输入要排序的数
        scanf("%d", a + i);

    //接下来进行排序
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
        for (j = 0; j < n; ++j)
            printf("%-3d ", a[j]);
        printf("\n");
    }
    return 0;
}
/*
5
3 2 6 1 4

2   3   1   4   6
2   1   3   4   6
1   2   3   4   6
1   2   3   4   6
 */