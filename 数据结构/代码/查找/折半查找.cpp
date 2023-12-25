//
// Created by xulon on 2023/6/27.
//
#include <stdio.h>

typedef int Type;

// 折半查找/二分查找法
// low 所查找的那一段的下界结点的下标
// high 所查找的那一段的上界结点的下标
// mid 所查找的那一段的中间结点的下标
int BinarySearch(const Type A[], const Type key, int N) {
    int low = 0, high = N - 1, mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (A[mid] == key) {
            return mid; // 找到了，返回索引
        } else if (key < A[mid]) {
            high = mid - 1; // 在左侧继续查找
        } else {
            low = mid + 1; // 在右侧继续查找
        }
    }
    return -1; // 没有找到，返回 -1
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 5;
    int result = BinarySearch(arr, key, n);
    printf("The subscript is: %d\n", result);

    return 0;
}