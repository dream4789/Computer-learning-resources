#include<stdio.h>

int main() {
    int a[5][5] = {
            1, 0, 0, 0, 0,
            5, 9, 0, 0, 0,
            4, 6, 8, 0, 0,
            2, 3, 44, 55, 0,
            7, 11, 12, 13, 14
    };

    int len = sizeof(a[5]) / sizeof(int);
    int b[len * (len + 1) / 2], x, y, k;

    printf("原二维数组：\n");    //输出原二维数组

    for (x = 0; x < len; x++) {
        for (y = 0; y < len; y++) {
            if (a[x][y] < 10) { // 使得输出更加整齐
                printf("%d  ", a[x][y]);
            } else {
                printf("%d ", a[x][y]);
            }
        }

        printf("\n");

    }

    printf("压缩后的一维数组:\n");

    for (int i = 0; i < len; i++) {         //将二维数组中非0值压缩至一维数组中
        for (int j = 0; j < len; j++) {
            if (i >= j) {   //特殊矩阵，只压下三角的值
                k = i * (i + 1) / 2 + j;  // 二维数组和一维数组中原值的对应关系
                b[k] = a[i][j];
            } else break; // 提升性能
        }
    }

    for (int l = 0; l < len * (len + 1) / 2; l++) {      //输出一维数组
        printf("%d ", b[l]);
    }

    printf("\n");
    printf("输入要查询的 行号&&列号 : ");   //输出要查询的数据
    scanf("%d%d", &x, &y);
    printf("\n");
    printf("您查询的数据是: ");

    if (x < y) printf("0\n");  //如果上三角直接输出0
    else printf("%d\n", b[(x - 1) * (x) / 2 + y - 1]);  // 下三角输出一维数组中对应的值

    return 0;
}