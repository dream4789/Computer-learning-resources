#include <stdio.h>

const int ARRAY_SIZE = 5;

// 使用void*类型可以允许该函数接受任何类型的指针，并能够正确地执行内存复制
void ArrayCopy(void *ori, void *cop, int Length) {
    // C++不支持将void*类型隐式转换为其他指针类型，需要显式地进行强制类型转换
    char *o = static_cast<char *>(ori);
    char *c = static_cast<char *>(cop);
    for (int i = 0; i < Length; ++i) {
        *(c + i) = *(o + i);
    }
}

int main() {
    int a[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    int b[ARRAY_SIZE];
    int c[ARRAY_SIZE];
    int *d = a; // 指针变量 d 初始化为指向数组 a 的第一个元素的地址
    // d[3] = 44;  // 全变

    // 值传递，两个数组不同时改变
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        b[i] = a[i];
    }
    b[1] = 22;

    // 地址传递
    ArrayCopy(a, c, sizeof(a));
    c[2] = 33;

    d[3] = 44;  // a变、d变

    printf("a    b    c    d\n\n");
    for (int j = 0; j < ARRAY_SIZE; ++j) {
        printf("%-4d %-4d %-4d %-4d\n", a[j], b[j], c[j], d[j]);
    }
    return 0;
}