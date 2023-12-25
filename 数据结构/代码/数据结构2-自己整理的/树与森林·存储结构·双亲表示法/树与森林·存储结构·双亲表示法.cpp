//
//  main.c
//  树与森林·存储结构·双亲表示法
//
//

#include <stdio.h>
#include <stdlib.h>
#define MaxNodeNum  100

typedef char datatype;

typedef struct
{
    datatype data;   //结点的值
    int parent;      //双亲的下标
}Parentlist;

typedef struct
{
    Parentlist elem[MaxNodeNum];
    int n;    //树中当前的结点数目
}ParentTree;

ParentTree InitPNode(ParentTree tree)
{
    int i, j;
    char ch;
    printf("请输出节点个数:\n");
    scanf("%d", &(tree.n));
    printf("请输入结点的值其双亲位于数组中的位置下标:\n");
    for (i = 0; i < tree.n; i++)
    {
        getchar();  //”吃掉“ 按下的 回车键（scanf会识别回车键，所以要消除回车键）（键盘缓冲区的知识点）
        scanf("%c %d", &ch, &j);
        tree.elem[i].data = ch;
        tree.elem[i].parent = j;
    }
    return tree;
}
void FindParent(ParentTree tree)
{
    char a;
    int isfind = 0;
    printf("请输入要查询的结点值:\n");
    getchar();
    scanf("%c", &a);
    for (int i = 0; i < tree.n; i++)
    {
        if (tree.elem[i].data == a)
        {
            isfind = 1;
            int ad = tree.elem[i].parent;
            printf("%c的父节点为 %c,存储位置下标为 %d\n", a, tree.elem[ad].data, ad);
            break;
        }
    }
    if (isfind == 0)
        printf("树中无此节点\n");
}
int main()
{
    ParentTree *tree;
    tree=(ParentTree *)malloc(sizeof(ParentTree));
    for (int i = 0; i < MaxNodeNum; i++)
    {
        tree->elem[i].data = ' ';
        tree->elem[i].parent = 0;
    }
    *tree=InitPNode(*tree);
    FindParent(*tree);
    return 0;
}

/*
请输出节点个数:
10
请输入结点的值其双亲位于数组中的位置下标:
r -1
a 0
b 0
c 0
d 1
e 1
f 3
g 6
h 6
k 6
请输入要查询的结点值:
c
c的父节点为 r,存储位置下标为 0
*/
