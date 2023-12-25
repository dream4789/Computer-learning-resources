//
// Created by xulon on 2023/6/21.
//
#include <stdio.h>
#include <stdlib.h>

// 双向链表节点结构体
typedef struct Node {
    int data;
    struct Node* prev;   // 指向前一个节点的指针
    struct Node* next;   // 指向后一个节点的指针
}Node;

// 创建新节点
Node* CreateNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 添加节点到链表尾部
void Append(Node** headRef, int data) {
    Node* newNode = CreateNode(data);
    if (*headRef == NULL) { // 如果链表为空，将新节点设置为头结点
        *headRef = newNode;
        return;
    }
    Node* curr = *headRef;
    while (curr->next != NULL) {  // 遍历链表，找到最后一个节点
        curr = curr->next;
    }
    curr->next = newNode;   // 将新节点添加到链表尾部
    newNode->prev = curr;
}

// 删除链表中的指定节点
void Delete(Node** headRef, Node* nodeToDelete) {
    if (*headRef == NULL || nodeToDelete == NULL) { // 如果链表或要删除的节点为空，直接返回
        return;
    }
    if (*headRef == nodeToDelete) { // 要删除的节点是头结点，更新头结点
        *headRef = nodeToDelete->next;
    }
    if (nodeToDelete->next != NULL) { // 更新被删除节点的下一个节点的prev指针
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    if (nodeToDelete->prev != NULL) { // 更新被删除节点的上一个节点的next指针
        nodeToDelete->prev->next = nodeToDelete->next;
    }
    free(nodeToDelete);   // 释放要删除的节点的内存空间
}

// 修改链表中指定节点的数据
void Modify(Node** headRef, Node* nodeToModify, int newData) {
    if (*headRef == NULL || nodeToModify == NULL) { // 如果链表或要修改的节点为空，直接返回
        return;
    }
    nodeToModify->data = newData;   // 修改节点数据
}

// 查找链表中指定数据对应的节点
Node* Search(Node* head, int dataToSearch) {
    Node* curr = head;
    while (curr != NULL) {  // 遍历链表
        if (curr->data == dataToSearch) { // 找到对应节点，返回节点指针
            return curr;
        }
        curr = curr->next;
    }
    return NULL;    // 链表中没有对应数据的节点，返回NULL
}

// 打印双向链表
void PrintList(Node* head) {
    printf("Current List: ");
    Node* curr = head;
    while (curr != NULL) {  // 遍历链表，输出每个节点的数据
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;

    // 添加一些节点到链表，初始链表为 2 -> 4 -> 6 -> 8
    Append(&head, 2);
    Append(&head, 4);
    Append(&head, 6);
    Append(&head, 8);

    // 打印当前链表
    PrintList(head);

    // 查找链表中数据为 4 的节点
    Node* nodeToSearch = Search(head, 4);
    if (nodeToSearch != NULL) { // 如果找到对应节点，则删除该节点并修改节点数据，重新打印链表
        printf("Found the node with data: %d\n", nodeToSearch->data);
        Delete(&head, nodeToSearch);
        Modify(&head, head, 10);
        PrintList(head);
    } else {
        printf("Can't find the node with data: 4\n");
    }

    // 查找链表中数据为 5 的节点
    nodeToSearch = Search(head, 5);
    if (nodeToSearch != NULL) { // 如果找到对应节点，修改该节点数据并重新打印链表
        printf("Found the node with data: %d\n", nodeToSearch->data);
        Modify(&head, nodeToSearch, 20);
        PrintList(head);
    } else {
        printf("Can't find the node with data: 5\n");
    }

    // 删除链表头结点，并重新打印链表
    Delete(&head, head);
    PrintList(head);

    // 清空链表，释放所有节点的内存空间
    while (head != NULL) {
        Node* next = head->next;
        free(head);
        head = next;
    }
    return 0;
}