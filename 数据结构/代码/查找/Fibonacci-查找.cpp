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
    // 1������쳲���������
    int fiboArray[maxSize];
    for (int i = 0; i < maxSize; i++) {
        fiboArray[i] = fibonacci(i);
        // printf("%d ", fiboArray[i]);
    }

    // 2���������ݳ��ȶ�Ӧ쳲���������Ԫ��
    int index = 0;
    while (fiboArray[index] < maxSize) {
        index++;
    }
    // printf("%d %d \n", index, fiboArray[index]);

    // 3�������ݽ������
    for (int i = maxSize; i < fiboArray[index]; i++) {
        data[i] = data[maxSize - 1];
        // printf("%d ", data[i]);
    }

    // 4�������䲻�Ϸָ�
    int left = 0;
    int right = data[fiboArray[index] - 1];
    while (left <= right && index >= 0) {
        // �����м�λ��
        int mid = left + fiboArray[index - 1] - 1;

        // ����������ֱ���
        if (data[mid] == targetValue) {  // Ŀ��ֵ�����ɹ�
            // ���mid��ԭʼ���ݳ��ȴ���˵��midλ��Ϊ����Ԫ��
            if (mid >= maxSize) { return maxSize - 1; }
            else { return mid; }
        } else if (data[mid] > targetValue) {  // Ŀ��ֵ���м�ֵ��ߣ������ұ߽�
            right = mid - 1;
            index = index - 1;
        } else {  // Ŀ��ֵ���м�ֵ�ұߣ�������߽�
            left = mid + 1;
            index = index - 2;
        }
    }
    // ����ʧ��
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
