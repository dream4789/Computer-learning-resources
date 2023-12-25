#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ��ĳ���ڵ��³�
void siftDown(int* heap, int currentIndex, int heapSize) {
    int leftChild = 2 * currentIndex + 1;
    int rightChild = 2 * currentIndex + 2;
    int largest = currentIndex;

    if (leftChild < heapSize && heap[leftChild] > heap[largest]) {
        largest = leftChild;
    }
    if (rightChild < heapSize && heap[rightChild] > heap[largest]) {
        largest = rightChild;
    }

    if (largest != currentIndex) {
        swap(&heap[currentIndex], &heap[largest]);
        siftDown(heap, largest, heapSize);
    }
}

// ���������
void buildHeap(int* heap, int heapSize) {
    for (int i = heapSize / 2; i >= 0; --i) {
        siftDown(heap, i, heapSize);
    }
}

void heapSort(int* array, int length) {
    buildHeap(array, length);    // ���������
    for (int i = length - 1; i >= 0; --i) {    // �Դ��������
        swap(&array[0], &array[i]);
        siftDown(array, 0, i);
    }
}

int main() {
    int array[] = { 2, 3, 1, 5, 6, 8, 7, 4 };
    int length = sizeof(array) / sizeof(int);
    printf("Before sorting: ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }

    heapSort(array, length);

    printf("\nAfter sorting: ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    return 0;
}
