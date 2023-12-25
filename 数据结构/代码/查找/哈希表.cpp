#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// ��ϣ��ڵ�
typedef struct Node {
    int key;
    int value;
    struct Node *next;  // ��һ���ڵ�ָ��
} Node;

// ��ϣ��
typedef struct {
    Node **nodes;  // �洢�ڵ������
    int size;      // ��ϣ���С
} HashTable;

// ��������ʼ����ϣ��
HashTable *createHashTable() {
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));
    table->nodes = (Node **) calloc(TABLE_SIZE, sizeof(Node *));
    table->size = TABLE_SIZE;
    return table;
}

// ��ϣ����
int hash(int key, int size) {
    return key % size;
}

// ���Ҳ���
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

// �������
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

// ɾ������
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

// ��ӡ��ϣ��
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

// ���ٹ�ϣ��
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
���ȣ������˼�ֵ��(1, 10)��(2, 20)��(11, 30)��(12, 40)��Ȼ��ɾ���˼�Ϊ2�Ľڵ㡣
��������ͨ������find(table, 1)���в��Ҳ������ҵ��˼�Ϊ1�Ľڵ㣬����ӡ���ýڵ�ļ���ֵ��
��󣬵���printHashTable(table)��ӡ������ϣ������ݡ�
 ����ɾ���˼�Ϊ2�Ľڵ㣬��Ӧ������Ϊ�գ����������2��ֻ��һ���ڵ�(12, 40)������������û�нڵ㣬������ʾΪ��
 */