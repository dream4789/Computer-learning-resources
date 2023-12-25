#include <stdio.h>
#include <stdlib.h>

// �����ϣ��ڵ��״̬
enum KindofCell { Active, Empty, Deleted };

struct HashTable {
    // ������������
    int Element;
    enum KindofCell info;
};

struct HashTable* arr;  // ��ϣ������
int ArrSize;            // ��ϣ���С
int CurrentSize;        // ��ǰ�洢�Ľ�����
int LastFindOk;         // �ϴβ����Ƿ�ɹ�

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

    printf("Is 20 found? %d\n", IsFound(20));  // Ӧ�ô�ӡ 1

    Remove(20);
    printf("Is 20 found? %d\n", IsFound(20));  // Ӧ�ô�ӡ 0

    free(arr);
    return 0;
}
