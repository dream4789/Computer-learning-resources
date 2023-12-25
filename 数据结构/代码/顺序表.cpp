//
// Created by xulon on 2023/6/30.
//
#include "stdio.h"
#include "stdlib.h"

#define  MAXSIZE 100
struct SeqList {
    int data[MAXSIZE];
    int length;               /* 表长 */
};
typedef struct SeqList *PSeqList;

PSeqList creaeNullList_seq()/* 创建空线性表*/
{
    PSeqList palist = (PSeqList) malloc(sizeof(struct SeqList));
    if (palist != NULL) {
        palist->length = 0;
        return (palist);
    }
    printf("Out of space!!\n");
    return NULL;
}

int isNullList_seq(PSeqList palist){/* 判断是否空线性表*/
    return (palist->length == 0);
}

int insertPre_seq(PSeqList palist, int p, int x) {
    int q;
    if (palist->length >= MAXSIZE) {
        printf("overflow!\n");
        return (0);
    }
    if (p < 0 || p > palist->length) {
        printf("Not exist!\n");
        return (0);
    }
    if (isNullList_seq(palist)) {
        palist->data[0] = x;
        palist->length = 1;
        return (1);
    }
    for (q = palist->length - 1; q >= p; q--)
        palist->data[q + 1] = palist->data[q];
    palist->data[p] = x;
    palist->length = palist->length + 1;
    return (1);
}

int main() {
    int i;
    PSeqList list;
    list = creaeNullList_seq();   /* 创建空线性表*/
    printf("The sequence table before insertion is: \n ");
    for (i = 0; i <= 9; i++) {
        insertPre_seq(list, i, i * i);
        printf(" %d ", list->data[i]);
    }
    insertPre_seq(list, 5, 55);/*在下标为5的元素之前插入元素55*/
    printf("\n\nThe sequence table after insertion is: \n ");
    for (i = 0; i < list->length; i++)
        printf(" %d ", list->data[i]);
    printf("\n\n");
}
