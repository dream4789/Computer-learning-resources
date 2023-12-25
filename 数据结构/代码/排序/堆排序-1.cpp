
// 错误

#include <stdio.h>
#include <stdlib.h>

#define ElementType int

void Swap(ElementType* a, ElementType* b) {
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

// 将某个节点下沉
void SiftDown(ElementType a[], int j, int Size) {
    int MaxSon;  // 用于记录大儿子的下标地址。
    a[0] = a[j];
    for (; j * 2 <= Size; j = MaxSon) {
        MaxSon = 2 * j;
        if (MaxSon != Size && a[MaxSon + 1] > a[MaxSon])
            MaxSon++;
        if (a[MaxSon] > a[0])
            a[j] = a[MaxSon];
        else
            break;
    }
    a[j] = a[0];
}

// 最大化堆排序
void MaxHeapSort(ElementType a[], int Size) {
    for (int j = Size / 2; j > 0; --j)  // 将 a[1], a[2 ], …,a[Size]建成最大化堆。
        SiftDown(a, j, Size);
    for (int k = Size; k > 1; --k) {  // 交换 a[1] 和 a[k ]，最大元素放在 a[k]。
        Swap(&a[1], &a[k]);
        SiftDown(a, 1, k - 1);  // 将 a[1], a[2 ], …,a[k-1]调整为最大化堆。
    }
}

int main() {
    ElementType a[] = {2, 3, 1, 5, 6, 8, 7, 4};
    int Size = sizeof(a) / sizeof(ElementType) - 1;

    printf("Before sorting: ");
    for (int i = 1; i <= Size; ++i) {
        printf("%d ", a[i]);
    }

    MaxHeapSort(a, Size);

    printf("\nAfter sorting: ");
    for (int i = 1; i <= Size; ++i) {
        printf("%d ", a[i]);
    }

    return 0;
}
