#include <stdio.h>
#include <stdlib.h>

const int ARRAY_SIZE = 5;

void ArrayCopy(void *ori, void *cop, int Length) {
    char *o = ori;
    char *c = cop;
    for (int i = 0; i < Length; ++i) {
        *(c + i) = *(o + i);
    }
}

int main() {
    // C语言中，不允许使用变量来初始化静态数组。需要使用编译时常量来定义数组的大小，然后将其用于声明数组
    // 通过将数组声明为动态数组，并使用 malloc() 在运行时分配内存并初始化数组
    int *a = (int *) malloc(sizeof(int) * ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        a[i] = i;
    }

    int *b = (int *) malloc(sizeof(int) * ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        b[i] = a[i];
    }
    b[1] = 11;

    int *c = (int *) malloc(sizeof(int) * ARRAY_SIZE);
    ArrayCopy(a, c, sizeof(int) * ARRAY_SIZE);
    c[2] = 22;

    int *d = (int *) calloc(ARRAY_SIZE, sizeof(int)), i; // 令指针指向一块新内存区，该内存区大小刚好可以容纳旧数组所有元素
    for (i = 0; i < ARRAY_SIZE; i++)
        *d++ = a[i];
    *d = '\0'; // 为新数组手动添上结束标记
    d -= ARRAY_SIZE; // 指针归首位

    printf("a    b    c\n");
    for (int j = 0; j < ARRAY_SIZE; ++j) {
        printf("%-4d %-4d %-4d %-4d\n", a[j], b[j], c[j], d[j]);
    }

    free(a);
    free(b);
    free(c);
    free(d);

    return 0;
}

/*
a    b    c
0    0    0
1    11   1
2    2    22
3    3    3
4    4    4
 */