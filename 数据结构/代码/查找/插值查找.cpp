//
// Created by xulon on 2023/6/27.
//
#include <stdio.h>

int interpolation_search(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // 根据插值公式计算下标估计值
        int pos = low + (target - arr[low]) * (high - low) / (arr[high] - arr[low]);

        if (arr[pos] == target) {
            return pos;
        } else if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;  // 表示未找到目标元素
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;

    int index = interpolation_search(arr, n, target);
    if (index != -1) {
        printf("%d found at index %d.\n", target, index);
    } else {
        printf("%d not found in the array.\n", target);
    }

    return 0;
}
