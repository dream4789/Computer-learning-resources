//
// Created by xulon on 2023/6/26.
//

#include <stdio.h>
#include <stdlib.h>


typedef char DataType;
/*二叉树的二叉链表结点结构定义*/
typedef struct Node {     // 结点结构
    DataType data;        // 结点数据
    struct Node *LChild;  // 左孩子指针
    struct Node *RChild;  // 右孩子指针
    int Ltag;             // 左标记位
    int Rtag;             // 右标记位
} BiTNode, *BiTree;

BiTree pre = NULL;  // pre始终指向刚访问过的结点，其初值为NULL

// 建立中序线索树
// 对root所指的二叉树进行中序线索化，其中pre始终指向刚访问过的结点，其初值为NULL
void Inthread(BiTree root) {
    if (root != NULL) {
        Inthread(root->LChild);  // 线索化左子树
        /*加线索操作*/
        if (root->LChild == NULL) {  // 置前驱线索
            root->Ltag = 1;
            root->LChild = pre;
        }
        if (pre != NULL && pre->RChild == NULL) {  // 置后继线索
            pre->RChild = root;
            pre->Rtag = 1;
        }
        pre = root;  // 当前访问结点为下一个访问结点的前驱
        Inthread(root->RChild);  // 线索化右子树
    }
}

// 在中序线索树中找结点前驱
// 在中序线索二叉树中查找p的中序前驱，并用pre指针返回结果
BiTree InPre(BiTree p) {
    BiTree Pre;
    if (p->Ltag == 1)
        Pre = p->LChild;  // 直接利用线索
    else {                // 在p的左子树中查找“最右下端”结点
        // 不能写Pre->Rtag==0
        for (Pre = p->LChild; Pre->Rtag != 1; Pre = Pre->RChild);
    }
    return Pre;
}

// 在中序线索树中找结点后继
// 在中序线索二叉树中查找p的中序后继结点，并用Next指针返回结果
BiTree InNext(BiTree p) {
    BiTree Next;
    if (p->Rtag == 1 ||
        p->RChild ==
        NULL)  // 直接利用线索(注意：一定要加上p->RChild==NULL，不然在调用TInOrder(T)时，程序会停不下来)
        Next = p->RChild;
    else {  // 在p的右子树中查找“最左下端”结点
        // 不能写Next->Ltag==0
        for (Next = p->RChild; Next->Ltag != 1; Next = Next->LChild);
    }
    return Next;
}

// 遍历中序线索树
// 在中序线索树上求中序遍历的第一个结点
BiTree InFirst(BiTree Bt) {
    BiTree p = Bt;
    if (!p) return NULL;
    while (p->Ltag != 1) p = p->LChild;
    return p;
}

// 遍历中序二叉线索树
void TInOrder(BiTree Bt) {
    BiTree p;
    p = InFirst(Bt);
    while (p) {
        printf("%c", p->data);
        p = InNext(p);
    }
}

// 中序线索二叉树上查找值为x的结点
BiTree Search(BiTree t, DataType x) {
    BiTree p;
    p = t;
    if (p) {
        while (p->Ltag == 0) p = p->LChild;      /* 找第一个结点 */
        while (p && p->data != x) p = InNext(p); /* 寻找结点p的后继结点 */
    }
    return p;
}

// 用扩展先序遍历序列创建二叉链表
// 这边的bt是指针的指针
void CreateBiTree(BiTree *bt) {
    char ch;
    ch = getchar();
    if (ch == '#')
        *bt = NULL;
    else {
        *bt = (BiTree) malloc(sizeof(BiTNode));  // 用(*bt)指针开辟结点空间
        (*bt)->data = ch;
        CreateBiTree(&((*bt)->LChild));
        CreateBiTree(&((*bt)->RChild));
    }
}

int main() {
    BiTree T;          // 开辟一个指向树的T指针
    CreateBiTree(&T);  // 传址建树
    Inthread(T);       // 建立中序线索树
    TInOrder(T);       // 遍历中序二叉线索树
    printf("\n");

    BiTree tmp = InFirst(T);
    printf("InFirst: %c\n", tmp->data);  // 在中序线索树上求中序遍历的第一个结点

    tmp = InNext(tmp);
    printf("InNext: %c\n", tmp->data);  // 在中序线索树中找结点后继

    tmp = InPre(tmp);
    printf("InPre: %c\n", tmp->data);  // 在中序线索树中找结点前驱

    tmp = Search(T, 'C');
    printf("Search -> C: %c\n", tmp->data);  // 在中序线索树中找结点前驱

    return 0;
}

// AB#DF##G##C#E#H##

/*

AB#DF##G##C#E#H##
BFDGACEH
B
F
B

 */
