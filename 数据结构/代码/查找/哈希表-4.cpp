#include <stdio.h>
#include <stdlib.h>

// 定义哈希表节点的状态
enum KindofCell { Active, Empty, Deleted };

struct HashTable {
    // 结点的数据类型
    int Element;
    enum KindofCell info;
};

struct HashTable* arr;  // 哈希表数组
int ArrSize;            // 哈希表大小
int CurrentSize;        // 当前存储的结点个数
int LastFindOk;         // 上次查找是否成功

void AllocateArr(int size) {
    arr = (struct HashTable*)malloc(size * sizeof(struct HashTable));
}

void InitializeHashTable(int size) {
    ArrSize = size;
    AllocateArr(ArrSize);
    CurrentSize = 0;
}

void MakeEmpty() {
    int i;
    for (i = 0; i < ArrSize; i++) {
        arr[i].info = Empty;
    }
    CurrentSize = 0;
}

unsigned int FindPos(int x) {
    unsigned int k = 0;
    unsigned int CurrentPos = x % ArrSize;
    while (arr[CurrentPos].info != Empty && arr[CurrentPos].Element != x) {
        CurrentPos += 2 * (++k) - 1;
        while (CurrentPos >= ArrSize) {
            CurrentPos -= ArrSize;
        }
    }
    return CurrentPos;
}

const int* Find(int x) {
    unsigned int CurrentPos = FindPos(x);
    LastFindOk = arr[CurrentPos].info == Active;
    return &(arr[CurrentPos].Element);
}

int WasFound() {
    return LastFindOk;
}

int IsFound(int x) {
    unsigned int CurrentPos = FindPos(x);
    return arr[CurrentPos].info == Active;
}

int Remove(int x) {
    unsigned int CurrentPos = FindPos(x);
    if (arr[CurrentPos].info != Active) {
        return 0;
    }
    arr[CurrentPos].info = Deleted;
    return 1;
}

int Insert(int x) {
    unsigned int CurrentPos = FindPos(x);
    if (arr[CurrentPos].info == Active) {
        return 0;
    }
    arr[CurrentPos].Element = x;
    arr[CurrentPos].info = Active;
    return 1;
}

int main() {
    InitializeHashTable(11);

    Insert(10);
    Insert(20);
    Insert(30);

    printf("Is 20 found? %d\n", IsFound(20));  // 应该打印 1

    Remove(20);
    printf("Is 20 found? %d\n", IsFound(20));  // 应该打印 0

    free(arr);
    return 0;
}
