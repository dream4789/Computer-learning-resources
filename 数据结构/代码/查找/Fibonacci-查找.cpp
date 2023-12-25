//
// Created by xulon on 2023/6/27.
//
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibonacciSearch(int *data, int maxSize, int targetValue) {
    // 1：构建斐波那契数列
    int fiboArray[maxSize];
    for (int i = 0; i < maxSize; i++) {
        fiboArray[i] = fibonacci(i);
        // printf("%d ", fiboArray[i]);
    }

    // 2：计算数据长度对应斐波那契数列元素
    int index = 0;
    while (fiboArray[index] < maxSize) {
        index++;
    }
    // printf("%d %d \n", index, fiboArray[index]);

    // 3：对数据进行填充
    for (int i = maxSize; i < fiboArray[index]; i++) {
        data[i] = data[maxSize - 1];
        // printf("%d ", data[i]);
    }

    // 4：对区间不断分割
    int left = 0;
    int right = data[fiboArray[index] - 1];
    while (left <= right && index >= 0) {
        // 计算中间位置
        int mid = left + fiboArray[index - 1] - 1;

        // 对三种情况分别处理
        if (data[mid] == targetValue) {  // 目标值搜索成功
            // 如果mid比原始数据长度大，则说明mid位置为填充的元素
            if (mid >= maxSize) { return maxSize - 1; }
            else { return mid; }
        } else if (data[mid] > targetValue) {  // 目标值在中间值左边，更新右边界
            right = mid - 1;
            index = index - 1;
        } else {  // 目标值在中间值右边，更新左边界
            left = mid + 1;
            index = index - 2;
        }
    }
    // 搜索失败
    return -1;
}

int main() {
    int data[] = {1, 3, 5, 7, 9, 11};
    int size = sizeof(data) / sizeof(int);
    int target = 3;
    int result = fibonacciSearch(data, size, target);
    printf("The subscript is: %d\n", result);
    return 0;
}
