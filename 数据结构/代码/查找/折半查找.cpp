//
// Created by xulon on 2023/6/27.
//
#include <stdio.h>

typedef int Type;

// �۰����/���ֲ��ҷ�
// low �����ҵ���һ�ε��½�����±�
// high �����ҵ���һ�ε��Ͻ�����±�
// mid �����ҵ���һ�ε��м�����±�
int BinarySearch(const Type A[], const Type key, int N) {
    int low = 0, high = N - 1, mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (A[mid] == key) {
            return mid; // �ҵ��ˣ���������
        } else if (key < A[mid]) {
            high = mid - 1; // ������������
        } else {
            low = mid + 1; // ���Ҳ��������
        }
    }
    return -1; // û���ҵ������� -1
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 5;
    int result = BinarySearch(arr, key, n);
    printf("The subscript is: %d\n", result);

    return 0;
}