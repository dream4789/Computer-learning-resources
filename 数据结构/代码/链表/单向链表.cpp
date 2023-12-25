#include <stdio.h>
#include <stdlib.h>

// 定义单向链表节点结构体
typedef struct Node {
    int data;           // 数据域
    struct Node *next;  // 指针域
} Node;

// 初始化链表（创建头节点）
Node *initList() {
    Node *head = (Node *)malloc(sizeof(Node));
    head->data = 0;
    head->next = head;
    return head;
}

// 添加节点
void addNode(Node *head, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head->next;
    head->next = newNode;
}

// 删除节点
void deleteNode(Node *head, int data) {
    Node *p = head->next;
    Node *pre = head;
    while (p != head) {
        if (p->data == data) {
            pre->next = p->next;
            free(p);
            return;
        }
        pre = p;
        p = p->next;
    }
}

// 修改节点
void modifyNode(Node *head, int oldData, int newData) {
    Node *p = head->next;
    while (p != head) {
        if (p->data == oldData) {
            p->data = newData;
            return;
        }
        p = p->next;
    }
}

// 查找节点
Node *findNode(Node *head, int data) {
    Node *p = head->next;
    while (p != head) {
        if (p->data == data) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void printList(Node *head) {
    Node *p = head->next;
    while (p != head) {
        printf("-> %d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    Node *head = initList();  // 创建链表
    addNode(head, 1);         // 添加节点
    addNode(head, 2);
    addNode(head, 3);
    printList(head);  // 输出链表

    deleteNode(head, 2);  // 删除节点
    printList(head);      // 输出链表

    modifyNode(head, 1, 4);  // 修改节点
    printList(head);         // 输出链表

    Node *node = findNode(head, 3);  // 查找节点
    if (node != NULL) {
        printf("Node %d exist!\n", node->data);
    } else {
        printf("Node does not exist!\n");
    }
}