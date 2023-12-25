#include <stdio.h>

int ARRAY_SIZE;

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void QuickSort(int array[], int low, int high) {
    if (low >= high) return;

    int i = low;
    int j = high;
    int temp = array[low];

    while (i != j) {
        while (array[j] >= temp && i < j) j--;
        while (array[i] <= temp && i < j) i++;
        if (i < j) swap(&array[i], &array[j]);
    }

    // 将基准temp放于自己的位置，（第i个位置）
    swap(&array[low], &array[i]);

    for (j = 0; j < ARRAY_SIZE; ++j)
        printf("%-4d", array[j]);
    printf("\n");

    QuickSort(array, low, i - 1);
    QuickSort(array, i + 1, high);
}

void Quick_Sort(int *arr, int begin, int end) {
    if (begin > end) return;

    int i = begin;
    int j = end;
    int tmp = arr[begin];

    while (i != j) {
        while (arr[j] >= tmp && j > i) j--;
        while (arr[i] <= tmp && j > i) i++;
        if (j > i) {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    arr[begin] = arr[i];
    arr[i] = tmp;

    for (j = 0; j < ARRAY_SIZE; ++j)
        printf("%-4d", arr[j]);
    printf("\n");

    Quick_Sort(arr, begin, i - 1);
    Quick_Sort(arr, i + 1, end);
}


int main(void) {
    ARRAY_SIZE = 10;
    int a[] = {4, 2, 5, 8, 3, 1, 9, 7, 0, 6}, b[ARRAY_SIZE];
//    scanf("%d", &ARRAY_SIZE);
//    int a[ARRAY_SIZE], b[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
//        scanf("%d", a + i);
        b[i] = a[i];
    }


    QuickSort(a, 0, ARRAY_SIZE - 1);
//    for (j = 0; j < ARRAY_SIZE; ++j)
//        printf("%-4d", a[j]);
//    printf("\n\n");

    printf("\n");

    Quick_Sort(b, 0, ARRAY_SIZE - 1);
//    for (j = 0; j < ARRAY_SIZE; ++j)
//        printf("%-3d", b[j]);
//    printf("\n");

    return 0;
}

/*
10
4 2 5 8 3 1 9 7 0 6


 */
