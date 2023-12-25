//
// Created by xulon on 2023/6/7.
//
#include <stdio.h>

int ARRAY_SIZE = 10;

void Merge(int a[], int b[], int s, int m, int e) {
    int i = s, j = m + 1, k = s;
    while (i != m + 1 && j != e + 1) {
        if (a[i] > a[j])
            b[k++] = a[j++];
        else
            b[k++] = a[i++];
    }
    while (i != m + 1)
        b[k++] = a[i++];
    while (j != e + 1)
        b[k++] = a[j++];
    for (i = s; i <= e; i++)
        a[i] = b[i];
}

//内部使用递归
void MergeSort(int a[], int b[], int s, int e) {
    if (s < e) {
        int m = s + (e - s) / 2;//避免溢出int
        MergeSort(a, b, s, m);
        MergeSort(a, b, m + 1, e);
        Merge(a, b, s, m, e);
    }
}


int main() {
    int a[] = {4, 2, 5, 8, 3, 1, 9, 7, 0, 6};
    int b[ARRAY_SIZE];
    MergeSort(a, b, 0, ARRAY_SIZE-1);
    for (int i = 0; i < 8; i++)
        printf("%d ", a[i]);
    printf("\n");
}