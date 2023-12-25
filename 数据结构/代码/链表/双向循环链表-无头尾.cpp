#include <stdio.h>
#include <stdlib.h>

// 双向循环链表结构体
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 初始化链表
Node* initList() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->prev = head;
    head->next = head;
    return head;
}

// 插入节点
void insertNode(Node* head, int index, int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    if (head->next == head) {   // 链表为空时
        temp->next = head;
        temp->prev = head;
        head->next = temp;
        head->prev = temp;
    } else if (index == 1) {    // 插入到头节点之后
        temp->prev = head;
        temp->next = head->next;
        head->next->prev = temp;
        head->next = temp;
    } else {                    // 插入到其他位置
        Node* p = head->next;
        int i = 1;
        while (p != head && i < index - 1) {
            p = p->next;
            i++;
        }
        if (i == index - 1) {
            temp->prev = p;
            temp->next = p->next;
            p->next->prev = temp;
            p->next = temp;
        } else {
            printf("Insertion position %d is invalid!\n", index);
        }
    }
}

// 删除节点
void deleteNode(Node* head, int index) {
    if (head->next == head) {   // 链表为空时
        printf("The linked list is empty and cannot be deleted\n");
    } else if (index == 1) {    // 删除头节点之后的节点
        Node* temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        free(temp);
    } else {                    // 删除其他位置的节点
        Node* p = head->next;
        int i = 1;
        while (p != head && i < index - 1) {
            p = p->next;
            i++;
        }
        if (i == index - 1 && p->next != head) {
            Node* temp = p->next;
            p->next = temp->next;
            temp->next->prev = p;
            free(temp);
        } else {
            printf("Illegal delete location %d!\n", index);
        }
    }
}

// 修改节点
void modifyNode(Node* head, int index, int value) {
    Node* p = head->next;
    int i = 1;
    while (p != head && i < index) {
        p = p->next;
        i++;
    }
    if (i == index) {
        p->data = value;
    } else {
        printf("Modify location %d is invalid!\n", index);
    }
}

// 查询节点
void queryNode(Node* head, int index) {
    Node* p = head->next;
    int i = 1;
    while (p != head && i < index) {
        p = p->next;
        i++;
    }
    if (i == index) {
        printf("Value of node %d is:%d\n", index, p->data);
    } else {
        printf("Query location %d is invalid!\n", index);
    }
}

// 输出链表
void printList(Node* head) {
    Node* p = head->next;
    while (p != head) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    Node* head = initList();    // 初始化链表

    // 插入节点
    insertNode(head, 1, 1);
    insertNode(head, 2, 2);
    insertNode(head, 3, 3);
    insertNode(head, 4, 4);
    printList(head);

    deleteNode(head, 2);    // 删除节点
    printList(head);

    modifyNode(head, 2, 5);   // 修改节点
    printList(head);

    queryNode(head, 3);    // 查询节点

    // 释放链表内存
    Node* p = head->next;
    while (p != head) {
        Node* temp = p;
        p = p->next;
        free(temp);
    }
    free(head);

    return 0;
}