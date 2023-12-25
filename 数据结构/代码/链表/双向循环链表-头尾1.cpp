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

// 初始化链表，创建一个头结点
DoublyList *init_list() {
    DoublyList *list = (DoublyList*) malloc(sizeof(DoublyList));
    Node *head = (Node*) malloc(sizeof(Node));
    head->data = -1; // 头结点数据暂定为-1
    head->prev = NULL;
    head->next = NULL;
    list->head = head;
    list->tail = head;
    return list;
}

// 打印链表中的所有结点
void print_list(DoublyList *list) {
    if(list == NULL || list->head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    printf("The list is: ");
    Node *p = list->head->next;
    while(p != NULL && p != list->head) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 在链表尾部插入一个结点
void insert_tail(DoublyList *list, int value) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = value;
    node->prev = list->tail;
    node->next = list->head;
    list->tail->next = node;
    list->tail = node;
    list->head->prev = node;
}

// 从链表中删除指定数据的结点
void delete_node(DoublyList *list, int value) {
    Node *p = list->head->next;
    while(p != NULL && p != list->head) {
        if(p->data == value) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
            return;
        }
        p = p->next;
    }
    printf("The value %d is not found in the list.\n", value);
}

// 修改链表中指定数据的结点数据
void modify_node(DoublyList *list, int old_value, int new_value) {
    Node *p = list->head->next;
    while(p != NULL && p != list->head) {
        if(p->data == old_value) {
            p->data = new_value;
            return;
        }
        p = p->next;
    }
    printf("The value %d is not found in the list.\n", old_value);
}

// 查找链表中指定数据的结点
Node* find_node(DoublyList *list, int value) {
    Node *p = list->head->next;
    while(p != NULL && p != list->head) {
        if(p->data == value) {
            return p;
        }
        p = p->next;
    }
    printf("The value %d is not found in the list.\n", value);
    return NULL;
}

int main() {
    DoublyList *list = init_list();
    insert_tail(list, 1);
    insert_tail(list, 2);
    insert_tail(list, 3);
    insert_tail(list, 4);
    print_list(list);
    delete_node(list, 3);
    print_list(list);
    modify_node(list, 2, 5);
    print_list(list);
    find_node(list, 1);
    find_node(list, 6);
    return 0;
}