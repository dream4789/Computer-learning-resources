//
// Created by xulon on 2023/6/26.
//
#include<iostream>
using namespace std;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char lElemType;

typedef struct BiTNode {
    lElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef BiTree SElemType;

typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

//建立一个栈
int InitStack(SqStack &S) {
    S.base = (SElemType *) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!(S.base)) exit(-1);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 0;
}

//将元素e插入栈中
int Push(SqStack &S, SElemType e) {
    if (S.top - S.base >= S.stacksize) {
        if (!(S.base = (SElemType *) realloc(S.base, (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType))))
            exit(-1);
        S.top = S.base + STACKINCREMENT;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return 0;
}

//出栈，将栈顶元素赋值给e返回
int Pop(SqStack &S, SElemType &e) {
    if (S.base == S.top)
        return false;
    e = *--S.top;
    return 0;
}

//判定栈是否为空
int StackEmpty(SqStack &S) {
    if (S.base == S.top)
        return true;
    else
        return false;
}

//取栈顶元素赋值给e
int GetTop(SqStack S, BiTree &e) {
    if (S.top == S.base) return false;
    e = *(S.top - 1);
    return 0;
}

//先序建立一棵二叉树
void CreateBiTree(BiTree &T) {
    lElemType ch;
    cin >> ch;
    if (ch == '*') T = NULL;
    else {
        if (!(T = (BiTNode *) malloc(sizeof(BiTNode))))
            exit(-1);
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);

    }
}

// 先序递归遍历
int PreOrderTraverse1(BiTree T) {
    if (T) {
        cout << T->data;
        PreOrderTraverse1(T->lchild);
        PreOrderTraverse1(T->rchild);
        return 0;
    } else
        return false;
}

// 中序递归遍历
int InOrderTraverse1(BiTree T) {
    if (T) {
        InOrderTraverse1(T->lchild);
        cout << T->data;
        InOrderTraverse1(T->rchild);
        return true;
    } else
        return false;
}

// 后续递归遍历
int PostOrderTraverse1(BiTree T) {
    if (T) {
        PostOrderTraverse1(T->lchild);
        PostOrderTraverse1(T->rchild);
        cout << T->data;
        return true;
    } else
        return false;
}

// 前序非递归遍历
int PreOrderTraverse2(BiTree T) {
    SqStack S;
    InitStack(S);
    BiTree p = T;
    while (p || !StackEmpty(S)) {
        if (p) {
            Push(S, p);
            cout << p->data; // fixed this line
            p = p->lchild;
        } else {
            Pop(S, p);
            p = p->rchild;
        }
    }
    return 0;
}


// 后序遍历非递归
int PostOrderTraverse2(BiTree T) {
    SqStack S;
    InitStack(S);
    BiTree p = T, cur = NULL;
    Push(S, p);
    while (!StackEmpty(S)) {
        GetTop(S, p);
        if ((p->lchild == NULL && p->rchild == NULL) || (cur == p->lchild || cur == p->rchild)) {
            cout << p->data;
            Pop(S, p);
            cur = p;
        } else {
            if (p->rchild != NULL)
                Push(S, p->rchild);
            if (p->lchild != NULL)
                Push(S, p->lchild);
        }
    }
    return 0;
}

// 中序非递归遍历
int InOrederTraverse2(BiTree T) {
    SqStack S;
    InitStack(S);
    BiTree p = T;
    while (p || !StackEmpty(S)) {
        if (p) {
            Push(S, p);
            p = p->lchild;
        } else {
            Pop(S, p);
            cout << p->data;
            p = p->rchild;
        }
    }
    return 0;
}

int main() {
    BiTree T;
    CreateBiTree(T);
    cout << "PreOrderTraverse1:";
    PreOrderTraverse1(T);
    cout << "\nInOrderTraverse1:";
    InOrderTraverse1(T);
    cout << "\nPostOrderTraverse1:";
    PostOrderTraverse1(T);
    cout << endl;

    cout << "\nPreOrderTraverse2:";
    PreOrderTraverse2(T);
    cout << "\nInOrederTraverse2:";
    InOrederTraverse2(T);
    cout << "\nPostOrderTraverse2:";
    PostOrderTraverse2(T);
    cout << endl;

    return 0;
}
// ABD**EF***CGH***I**

/*

ABD**EF***CGH***I**
PreOrderTraverse1:ABDEFCGHI
InOrderTraverse1:DBFEAHGCI
PostOrderTraverse1:DFEBHGICA

PreOrderTraverse2:ABDEFCGHI
InOrederTraverse2:DBFEAHGCI
PostOrderTraverse2:DFEBHGICA

 */