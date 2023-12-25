//
// Created by xulon on 2023/6/21.
//
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建新节点
Node* create_node(int data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// 插入节点到链表尾部
void insert_node(Node** head, int data) {
    Node* node = create_node(data);
    if (*head == NULL) {
        // 如果链表为空，则将头指针指向新节点，并让其自己指向自己形成循环
        *head = node;
        node->next = node;
        return;
    }
    // 不为空，找到尾节点并将其next指向新节点
    Node* tail = *head;
    while (tail->next != *head) {
        tail = tail->next;
    }
    tail->next = node;
    node->next = *head;
}

// 删除节点
void delete_node(Node** head, int data) {
    Node* curr = *head;
    Node* prev = NULL;
    while (curr->data != data) {
        if (curr->next == *head) {  // 遍历完一圈后未找到
            printf("%d not found in the list.\n", data);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    if (curr == *head && curr->next == *head) {  // 如果只有一个节点
        *head = NULL;
    } else if (curr == *head) {  // 如果是头节点
        Node* tail = *head;
        while (tail->next != *head) {
            tail = tail->next;
        }
        *head = curr->next;
        tail->next = *head;
    } else if (curr->next == *head) {  // 如果是尾节点
        prev->next = *head;
    } else {  // 中间节点
        prev->next = curr->next;
    }
    free(curr);
}

// 修改节点
void update_node(Node** head, int old_data, int new_data) {
    Node* curr = *head;
    while (curr->data != old_data) {
        if (curr->next == *head) {  // 遍历完一圈后未找到
            printf("%d not found in the list.\n", old_data);
            return;
        }
        curr = curr->next;
    }
    curr->data = new_data;
}

// 查找节点
void search_node(Node* head, int data) {
    Node* curr = head;
    int found = 0;
    do {
        if (curr->data == data) {
            printf("%d found in the list.\n", data);
            found = 1;
            break;
        }
        curr = curr->next;
    } while (curr != head);
    if (!found) {
        printf("%d not found in the list.\n", data);
    }
}

// 打印链表
void print_list(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    Node* curr = head;
    do {
        printf("%d ", curr->data);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}

int main() {
    Node* head = NULL;

    // 插入节点
    insert_node(&head, 1);
    insert_node(&head, 2);
    insert_node(&head, 3);
    insert_node(&head, 4);
    print_list(head);

    // 删除节点
    delete_node(&head, 2);
    print_list(head);

    // 修改节点
    update_node(&head, 3, 5);
    print_list(head);

    // 查找节点
    search_node(head, 5);
    search_node(head, 2);

    return 0;
}