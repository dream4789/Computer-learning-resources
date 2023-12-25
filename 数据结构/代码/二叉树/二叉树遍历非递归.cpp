//
// Created by xulon on 2023/6/26.
//
#include <stdio.h>
#include <stdlib.h>

// 二叉树节点结构体
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 创建新的二叉树节点
struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 先序遍历二叉树(非递归)
void printPreorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 创建栈并将根节点压入栈中
    struct TreeNode* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        // 弹出栈顶节点并输出节点值
        struct TreeNode* cur = stack[top--];
        printf("%d ", cur->val);

        // 将右子树入栈，保证左子树先于右子树被访问
        if (cur->right) {
            stack[++top] = cur->right;
        }
        // 将左子树入栈
        if (cur->left) {
            stack[++top] = cur->left;
        }
    }
}

// 中序遍历二叉树(非递归)
void printInorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 创建栈
    struct TreeNode* stack[100];
    int top = -1;

    // 指向当前节点的指针
    struct TreeNode* cur = root;

    while (cur != NULL || top >= 0) {
        // 左子树入栈
        while (cur != NULL) {
            stack[++top] = cur;
            cur = cur->left;
        }

        // 弹出栈顶并输出其节点值
        cur = stack[top--];
        printf("%d ", cur->val);

        // 处理右子树
        cur = cur->right;
    }
}

// 后序遍历二叉树(非递归)
void printPostorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 创建两个栈
    struct TreeNode* stack1[100];
    struct TreeNode* stack2[100];

    int top1 = -1;
    int top2 = -1;

    // 将根节点入栈1
    stack1[++top1] = root;

    // 循环直到栈1为空
    while (top1 >= 0) {
        // 弹出栈1的栈顶
        struct TreeNode* cur = stack1[top1--];

        // 将弹出节点入栈2
        stack2[++top2] = cur;

        // 将左子树和右子树依次入栈1
        if (cur->left) {
            stack1[++top1] = cur->left;
        }
        if (cur->right) {
            stack1[++top1] = cur->right;
        }
    }

    // 输出栈2中的节点值
    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->val);
    }
}

int main() {
    // 构造二叉树
    struct TreeNode* root = createNode(3);
    root->left = createNode(2);
    root->right = createNode(5);
    root->left->left = createNode(1);
    root->left->right = createNode(4);
    root->right->left = createNode(6);
    root->right->right = createNode(8);
    root->right->right->left = createNode(7);

    // 使用非递归遍历算法输出二叉树节点值
    printf("Preorder  traversal results: ");
    printPreorder(root);
    printf("\n");

    printf("Inorder   traversal results: ");
    printInorder(root);
    printf("\n");

    printf("postorder traversal results: ");
    printPostorder(root);
    printf("\n");

    return 0;
}