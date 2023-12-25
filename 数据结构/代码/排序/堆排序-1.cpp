
// ����

#include <stdio.h>
#include <stdlib.h>

#define ElementType int

void Swap(ElementType* a, ElementType* b) {
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

// ��ĳ���ڵ��³�
void SiftDown(ElementType a[], int j, int Size) {
    int MaxSon;  // ���ڼ�¼����ӵ��±��ַ��
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

// ��󻯶�����
void MaxHeapSort(ElementType a[], int Size) {
    for (int j = Size / 2; j > 0; --j)  // �� a[1], a[2 ], ��,a[Size]������󻯶ѡ�
        SiftDown(a, j, Size);
    for (int k = Size; k > 1; --k) {  // ���� a[1] �� a[k ]�����Ԫ�ط��� a[k]��
        Swap(&a[1], &a[k]);
        SiftDown(a, 1, k - 1);  // �� a[1], a[2 ], ��,a[k-1]����Ϊ��󻯶ѡ�
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
