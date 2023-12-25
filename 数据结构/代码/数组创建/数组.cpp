//
// Created by xulon on 2023/6/23.
//
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows = 3;
    int cols = 4;

    // ��̬�����ά����
    // ��̬���� rows �� cols �еĶ�ά����������ڴ�ռ�
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // ��������г�ʼ��
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }

    // ���ú���������������Ϊ��������
    printMatrix(matrix, rows, cols);

    // �ͷŶ�̬������ڴ�ռ�
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}