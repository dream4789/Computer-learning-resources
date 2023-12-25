//
//  main.c
//  ����ɭ�֡��洢�ṹ��˫�ױ�ʾ��
//
//

#include <stdio.h>
#include <stdlib.h>
#define MaxNodeNum  100

typedef char datatype;

typedef struct
{
    datatype data;   //����ֵ
    int parent;      //˫�׵��±�
}Parentlist;

typedef struct
{
    Parentlist elem[MaxNodeNum];
    int n;    //���е�ǰ�Ľ����Ŀ
}ParentTree;

ParentTree InitPNode(ParentTree tree)
{
    int i, j;
    char ch;
    printf("������ڵ����:\n");
    scanf("%d", &(tree.n));
    printf("���������ֵ��˫��λ�������е�λ���±�:\n");
    for (i = 0; i < tree.n; i++)
    {
        getchar();  //���Ե��� ���µ� �س�����scanf��ʶ��س���������Ҫ�����س����������̻�������֪ʶ�㣩
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
    printf("������Ҫ��ѯ�Ľ��ֵ:\n");
    getchar();
    scanf("%c", &a);
    for (int i = 0; i < tree.n; i++)
    {
        if (tree.elem[i].data == a)
        {
            isfind = 1;
            int ad = tree.elem[i].parent;
            printf("%c�ĸ��ڵ�Ϊ %c,�洢λ���±�Ϊ %d\n", a, tree.elem[ad].data, ad);
            break;
        }
    }
    if (isfind == 0)
        printf("�����޴˽ڵ�\n");
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
������ڵ����:
10
���������ֵ��˫��λ�������е�λ���±�:
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
������Ҫ��ѯ�Ľ��ֵ:
c
c�ĸ��ڵ�Ϊ r,�洢λ���±�Ϊ 0
*/
