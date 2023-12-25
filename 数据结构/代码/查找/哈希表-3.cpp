#include <stdio.h>
#include <stdlib.h>

enum KindofCell { Active, Empty, Deleted };

typedef int Type;

struct HashCell {
    Type Element;
    enum KindofCell info;
};

struct HashTable {
    int DefaultSize;
    int ArrSize;
    int CurrentSize;
    int LastFindOk;
    struct HashCell* Arr;
};

void AllocateArr(struct HashTable* hashTable);
unsigned int FindPos(const struct HashTable* hashTable, const Type* x);

struct HashTable* CreateHashTable() {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));

    hashTable->DefaultSize = 11;
    hashTable->ArrSize = hashTable->DefaultSize;
    hashTable->CurrentSize = 0;
    hashTable->LastFindOk = 0;
    AllocateArr(hashTable);

    return hashTable;
}

void DestroyHashTable(struct HashTable* hashTable) {
    free(hashTable->Arr);
    free(hashTable);
}

int Insert(struct HashTable* hashTable, const Type* x) {
    unsigned int pos = FindPos(hashTable, x);

    if (hashTable->Arr[pos].info == Active) {
        return 0; // Element already present
    }

    hashTable->Arr[pos].Element = *x;
    hashTable->Arr[pos].info = Active;
    hashTable->CurrentSize++;
    return 1;
}

int Remove(struct HashTable* hashTable, const Type* x) {
    unsigned int pos = FindPos(hashTable, x);

    if (hashTable->Arr[pos].info != Active) {
        return 0; // Element not found
    }

    hashTable->Arr[pos].info = Deleted;
    hashTable->CurrentSize--;
    return 1;
}

const Type* Find(struct HashTable* hashTable, const Type* x) {
    unsigned int pos = FindPos(hashTable, x);

    if (hashTable->Arr[pos].info == Active) {
        hashTable->LastFindOk = 1;
        return &hashTable->Arr[pos].Element;
    }

    hashTable->LastFindOk = 0;
    return NULL;
}

//int Find(struct HashTable* hashTable, const Type* x, Type* result) {
//    unsigned int pos = FindPos(hashTable, x);
//
//    if (hashTable->Arr[pos].info == Active) {
//        hashTable->LastFindOk = 1;
//        *result = hashTable->Arr[pos].Element;
//        return 1; // 返回1表示找到元素
//    }
//
//    hashTable->LastFindOk = 0;
//    return 0; // 返回0表示未找到元素
//}

int IsFound(const struct HashTable* hashTable, const Type* x) {
    unsigned int pos = FindPos(hashTable, x);

    if (hashTable->Arr[pos].info == Active) {
        return 1;
    }

    return 0;
}

int WasFound(const struct HashTable* hashTable) {
    return hashTable->LastFindOk;
}

int IsEmpty(const struct HashTable* hashTable) {
    return hashTable->CurrentSize == 0 ? 1 : 0;
}

void MakeEmpty(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->ArrSize; i++) {
        hashTable->Arr[i].info = Empty;
    }
    hashTable->CurrentSize = 0;
}

void AllocateArr(struct HashTable* hashTable) {
    hashTable->Arr = (struct HashCell*)calloc(hashTable->ArrSize, sizeof(struct HashCell));
}

unsigned int FindPos(const struct HashTable* hashTable, const Type* x) {
    unsigned int hashVal = 0;
    for (int i = 0; i < sizeof(Type); i++) {
        char byte = *((char*)x + i);
        hashVal = (hashVal << 5) + byte;
    }
    return hashVal % hashTable->ArrSize;
}

int main() {
    struct HashTable* hashTable = CreateHashTable();

    Type element1 = 11;  // Initialize element1 with appropriate value
    Insert(hashTable, &element1);

    Type element2 = 12;  // Initialize element2 with appropriate value
    Insert(hashTable, &element2);

    if (IsFound(hashTable, &element2)) {
        printf("Element found in the hash table.\n");
    }

    const Type* result = Find(hashTable, &element1);
    if (result != NULL) {
        printf("Found element: %d\n", *result);
    } else {
        printf("Element not found.\n");
    }

    Remove(hashTable, &element2);

    if (!IsFound(hashTable, &element2)) {
        printf("Element successfully removed from the hash table.\n");
    }

    if (IsEmpty(hashTable)) {
        printf("Hash table is empty.\n");
    } else {
        printf("Hash table is not empty.\n");
    }

    MakeEmpty(hashTable);

    if (IsEmpty(hashTable)) {
        printf("Hash table is empty.\n");
    } else {
        printf("Hash table is not empty.\n");
    }

    DestroyHashTable(hashTable);

    return 0;
}
