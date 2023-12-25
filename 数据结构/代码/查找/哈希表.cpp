#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// 哈希表节点
typedef struct Node {
    int key;
    int value;
    struct Node *next;  // 下一个节点指针
} Node;

// 哈希表
typedef struct {
    Node **nodes;  // 存储节点的数组
    int size;      // 哈希表大小
} HashTable;

// 创建并初始化哈希表
HashTable *createHashTable() {
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));
    table->nodes = (Node **) calloc(TABLE_SIZE, sizeof(Node *));
    table->size = TABLE_SIZE;
    return table;
}

// 哈希函数
int hash(int key, int size) {
    return key % size;
}

// 查找操作
Node *find(HashTable *table, int key) {
    int index = hash(key, table->size);

    Node *node = table->nodes[index];
    while (node != NULL) {
        if (node->key == key) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

// 插入操作
void insert(HashTable *table, int key, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    int index = hash(key, table->size);

    if (table->nodes[index] == NULL) {
        table->nodes[index] = newNode;
    } else {
        Node *node = table->nodes[index];
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = newNode;
    }
}

// 删除操作
void delete_h(HashTable *table, int key) {
    int index = hash(key, table->size);

    Node *node = table->nodes[index];
    Node *prev = NULL;

    while (node != NULL && node->key != key) {
        prev = node;
        node = node->next;
    }

    if (node == NULL) {
        printf("Key not found\n");
        return;
    }

    if (prev == NULL) {
        table->nodes[index] = node->next;
    } else {
        prev->next = node->next;
    }

    free(node);
}

// 打印哈希表
void printHashTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        printf("[%d]: ", i);
        Node *node = table->nodes[i];
        while (node != NULL) {
            printf("(%d, %d) ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
}

// 销毁哈希表
void destroyHashTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Node *node = table->nodes[i];
        while (node != NULL) {
            Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(table->nodes);
    free(table);
}

int main() {
    HashTable *table = createHashTable();

    insert(table, 1, 10);
    insert(table, 2, 20);
    insert(table, 11, 30);
    insert(table, 12, 40);

    delete_h(table, 2);

    Node *node1 = find(table, 1);
    if (node1 != NULL) {
        printf("Key: %d, Value: %d\n", node1->key, node1->value);
    } else {
        printf("Key not found\n");
    }

    printHashTable(table);

    destroyHashTable(table);

    return 0;
}

/*
首先，插入了键值对(1, 10)、(2, 20)、(11, 30)和(12, 40)。然后，删除了键为2的节点。
接下来，通过调用find(table, 1)进行查找操作，找到了键为1的节点，并打印出该节点的键和值。
最后，调用printHashTable(table)打印整个哈希表的内容。
 由于删除了键为2的节点，对应的链表为空，因此在索引2处只有一个节点(12, 40)。其他索引处没有节点，所以显示为空
 */