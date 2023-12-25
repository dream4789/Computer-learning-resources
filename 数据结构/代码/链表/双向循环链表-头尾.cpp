#include <stdio.h>
#include <stdlib.h>

// 双向循环链表结点类型定义
typedef struct Node {
    int data;
    struct Node *prev;  // 指向前驱结点的指针
    struct Node *next;  // 指向后继结点的指针
} Node;

// 双向循环链表类型定义
typedef struct DoublyList {
    Node *head;  // 头指针
    Node *tail;  // 尾指针
} DoublyList;

// 初始化双向循环链表
void init(DoublyList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// 在双向循环链表的尾部插入新结点
void insertAtTail(DoublyList *list, int value) {
    Node *node = (Node *) malloc(sizeof(Node));  // 创建新结点
    node->data = value;
    node->next = NULL;
    if (list->tail == NULL) {  // 如果链表为空，则插入的结点为头结点
        node->prev = NULL;
        list->head = node;
        list->tail = node;
        node->next = node;
    } else {  // 否则将结点插入到尾结点之后
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        node->next = list->head;
        list->head->prev = node;
    }
}

// 删除双向循环链表中的指定结点
void deleteNode(DoublyList *list, Node *node) {
    if (node == NULL || list->head == NULL)  // 如果指定结点为空或者链表为空，则直接返回
        return;
    if (node == list->head) {  // 如果要删除的结点是头结点
        list->head = node->next;  // 将头结点指向下一个节点
        list->tail->next = list->head;  // 将新的尾节点的后继指针设置为头结点
        list->head->prev = list->tail;  // 将新的头结点的前驱指针设置为尾节点
    } else if (node == list->tail) {  // 如果要删除的结点是尾节点
        list->tail = node->prev;  // 将尾节点指向前一个节点
        list->tail->next = list->head;  // 将新的尾节点的后继指针设置为头结点
        list->head->prev = list->tail;  // 将新的头结点的前驱指针设置为尾节点
    } else {  // 如果要删除的结点是中间节点
        node->prev->next = node->next;  // 将该节点的前驱节点的后继指针指向该节点的后继节点
        node->next->prev = node->prev;  // 将该节点的后继节点的前驱指针指向该节点的前驱节点
    }
    free(node);  // 释放被删除结点的内存空间
}

// 查找双向循环链表中指定值的结点
Node *search(DoublyList *list, int value) {
    if (list->head == NULL)  // 如果链表为空，则返回NULL
        return NULL;
    Node *current = list->head;  //从头结点开始遍历
    do {
        if (current->data == value)
            return current;
        current = current->next;
    } while (current != list->head);
    return NULL;  // 如果没有找到，则返回NULL
}

// 修改双向循环链表中的指定结点的值
void modifyNode(DoublyList *list, Node *node, int newValue) {
    if (node == NULL)  // 如果要修改的结点为空，则直接返回
        return;
    node->data = newValue;
}

// 打印双向循环链表中所有结点的值（从头结点开始）
void printList(DoublyList *list) {
    if (list->head == NULL) {  // 如果链表为空，则直接返回
        printf("Empty list.\n");
        return;
    }
    Node *current = list->head;  // 从头结点开始遍历
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

int main() {
    DoublyList list;
    init(&list);  // 初始化链表
    insertAtTail(&list, 1);
    insertAtTail(&list, 2);
    insertAtTail(&list, 3);
    insertAtTail(&list, 4);
    printf("Original list: ");
    printList(&list);

    // 查找节点
    Node *node = search(&list, 3);
    if (node != NULL) {
        printf("Found the node with data %d\n", node->data);
    } else {
        printf("The node with data %d is not found\n", 3);
    }

    // 修改节点的值
    modifyNode(&list, list.head, 10);
    printf("List after modifying the first node: ");
    printList(&list);

    deleteNode(&list, list.head->next);
    printf("List after deleting the second node: ");
    printList(&list);
    return 0;
}