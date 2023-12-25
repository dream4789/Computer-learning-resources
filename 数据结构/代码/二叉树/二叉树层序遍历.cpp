#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int data;             // 存放数据域
    struct Tree *lchild;  // 遍历左子树指针
    struct Tree *rchild;  // 遍历右子树指针
} Tree, *BitTree;

//	队列节点定义
typedef struct QueueNode {
    BitTree data;
    struct QueueNode *next;
} QueueNode, *QueuePtr;

//	队列定义
typedef struct LinkQueue {
    QueuePtr front;  // 头指针
    QueuePtr rear;   // 尾指针
} LinkQueue;

BitTree CreateLink() {
    int data;
    int temp;
    BitTree T;

    scanf("%d", &data);  //	输入数据
    temp = getchar();    //	吸收空格

    if (data == -1) {  //	输入-1 代表此节点下子树不存数据，也就是不继续递归创建
        return NULL;
    } else {
        T = (BitTree)malloc(sizeof(Tree));  // 分配内存空间
        T->data = data;  // 把当前输入的数据存入当前节点指针的数据域中
        printf("请输入%d的左子树: ", data);
        T->lchild = CreateLink();  // 开始递归创建左子树
        printf("请输入%d的右子树: ", data);
        T->rchild = CreateLink();  // 开始到上一级节点的右边递归创建左右子树
        return T;                  // 返回根节点
    }
}

//	先序遍历
void ShowXianXu(BitTree T) {  // 先序遍历二叉树
    if (T == NULL) {          // 递归中遇到NULL，返回上一层节点
        return;
    }
    printf("%d ", T->data);
    ShowXianXu(T->lchild);  // 递归遍历左子树
    ShowXianXu(T->rchild);  // 递归遍历右子树
}

//	中序遍历
void ShowZhongXu(BitTree T) {  // 先序遍历二叉树
    if (T == NULL) {           // 递归中遇到NULL，返回上一层节点
        return;
    }
    ShowZhongXu(T->lchild);  // 递归遍历左子树
    printf("%d ", T->data);
    ShowZhongXu(T->rchild);  // 递归遍历右子树
}

//	后序遍历
void ShowHouXu(BitTree T) {  // 后序遍历二叉树
    if (T == NULL) {         // 递归中遇到NULL，返回上一层节点
        return;
    }
    ShowHouXu(T->lchild);  // 递归遍历左子树
    ShowHouXu(T->rchild);
    // 递归遍历右子树
    printf("%d ", T->data);
}

//	初始化队列
void InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QueueNode));
    if (!Q->front)
        exit(0);
    Q->front->next = NULL;
}

//	判断队列是否为空
int IsEmpty(LinkQueue Q) {
    if (Q.front == Q.rear)
        return 1;
    else
        return 0;
}

//	入队
void EnQueue(LinkQueue *Q, BitTree x) {
    QueuePtr p;
    p = (QueuePtr) malloc(sizeof(QueueNode));
    if (!p)
        exit(0);
    p->data = x;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

//	出队
BitTree DeQueue(LinkQueue *Q) {
    QueuePtr p;
    BitTree u;
    if (Q->front == Q->rear)
        exit(0);
    p = Q->front->next;
    u = p->data;
    Q->front->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);
    return u;
}

//	二叉树的层序遍历
void ShowCengXu(BitTree T) {
    LinkQueue Q;
    InitQueue(&Q);  // 初始化队列
    BitTree p = T;
    EnQueue(&Q, p);  // 根节点入队

    while (!IsEmpty(Q)) {           // 队列不为空时进行循环
        p = DeQueue(&Q);            // 取出队首元素
        printf("%d ", p->data);     // 输出队首元素
        if (p->lchild != NULL) {    // 将左子树插入队尾
            EnQueue(&Q, p->lchild);
        }
        if (p->rchild != NULL) {    // 将右子树插入队尾
            EnQueue(&Q, p->rchild);
        }
    }
}

int tu() {
    printf("      3\n");
    printf("    /   \\\n");
    printf("   2     5\n");
    printf("  / \\   / \\\n");
    printf(" 1   4 6   8\n");
    printf("      \\\n");
    printf("       7\n");
    return 0;
}


int main() {
    tu();
    BitTree S;
    printf("请输入第一个节点的数据:\n");
    S = CreateLink();  // 接受创建二叉树完成的根节点

    printf("先序遍历结果: \n");
    ShowXianXu(S);

    printf("\n中序遍历结果: \n");
    ShowZhongXu(S);

    printf("\n后序遍历结果: \n");
    ShowHouXu(S);

    printf("\n层序遍历结果: \n");
    ShowCengXu(S);

    return 0;
}
/*

      3
    /   \
   2     5
  / \   / \
 1   4 6   8
      \
       7

请输入第一个节点的数据:
3
请输入3的左子树:2
 请输入2的左子树:1
 请输入1的左子树:-1
 请输入1的右子树:-1
 请输入2的右子树:4
 请输入4的左子树:-1
 请输入4的右子树:-1

请输入3的右子树:5
 请输入5的左子树:6
 请输入6的左子树:-1
 请输入6的右子树:7
 请输入7的左子树:-1
 请输入7的右子树:-1
 请输入5的右子树:8

请输入8的左子树:-1
 请输入8的右子树:-1
 先序遍历结果:
3 2 1 4 5 6 7 8
中序遍历结果:
1 2 4 3 6 7 5 8
后序遍历结果:
1 4 2 7 6 8 5 3
层序遍历结果:
3 2 5 1 4 6 8 7
Process finished with exit code 0

 */