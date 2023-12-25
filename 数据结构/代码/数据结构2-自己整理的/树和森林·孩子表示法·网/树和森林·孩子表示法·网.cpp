//
//  main.c
//  ����ɭ�֡����ӱ�ʾ������
//

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 20
#define TElemType char

typedef struct CTNode
{
    int child;    //������ÿ�����洢�Ĳ������ݱ������������������д洢��λ���±�
    struct CTNode * next;
}ChildPtr;

typedef struct
{
    TElemType data;    //������������
    ChildPtr * firstchild;    //���������ͷָ��
}CTBox;

typedef struct
{
    CTBox nodes[MAX_SIZE];   //�洢��������
    int n, r;   //���������������λ��
}CTree;

//���ӱ�ʾ���洢��ͨ��
CTree initTree(CTree tree)
{
    printf("����ڵ�������\n");
    scanf("%d", &(tree.n));
    for (int i = 0; i < tree.n; i++)
    {
        printf("����� %d ���ڵ��ֵ��\n", i + 1);
        getchar();
        scanf("%c", &(tree.nodes[i].data));
        tree.nodes[i].firstchild = (ChildPtr*)malloc(sizeof(ChildPtr));
        tree.nodes[i].firstchild->next = NULL;

        printf("����ڵ� %c �ĺ��ӽڵ�������\n", tree.nodes[i].data);
        int Num;
        scanf("%d", &Num);
        if (Num != 0)
        {
            ChildPtr * p = tree.nodes[i].firstchild;
            for (int j = 0; j < Num; j++)
            {
                ChildPtr * newEle = (ChildPtr*)malloc(sizeof(ChildPtr));
                newEle->next = NULL;
                printf("����� %d �����ӽڵ���˳����е�λ��", j + 1);
                scanf("%d", &(newEle->child));
                p->next = newEle;
                p = p->next;
            }
        }
    }
    return tree;
}

void findKids(CTree tree, char a)
{
    int hasKids = 0;
    for (int i = 0; i < tree.n; i++)
    {
        if (tree.nodes[i].data == a)
        {
            ChildPtr * p = tree.nodes[i].firstchild->next;
            while (p)
            {
                hasKids = 1;
                printf("%c ", tree.nodes[p->child].data);
                p = p->next;
            }
            break;
        }
    }
    if (hasKids == 0)
        printf("�˽ڵ�ΪҶ�ӽڵ�");
}

int main()
{
    CTree *tree;
    tree=(CTree *)malloc(sizeof(CTree));
    for (int i = 0; i < MAX_SIZE; i++)
        tree->nodes[i].firstchild = NULL;
    *tree = initTree(*tree);
    //Ĭ�������ڵ�λ������notes[0]��
    tree->r = 0;
    printf("�ҳ��ڵ� F �����к��ӽڵ㣺");
    findKids(*tree,'F');
    return 0;
}


/*
 ����ڵ�������
 10
 ����� 1 ���ڵ��ֵ��
 R
 ����ڵ� R �ĺ��ӽڵ�������
 3
 ����� 1 �����ӽڵ���˳����е�λ��1
 ����� 2 �����ӽڵ���˳����е�λ��2
 ����� 3 �����ӽڵ���˳����е�λ��3
 ����� 2 ���ڵ��ֵ��
 A
 ����ڵ� A �ĺ��ӽڵ�������
 2
 ����� 1 �����ӽڵ���˳����е�λ��4
 ����� 2 �����ӽڵ���˳����е�λ��5
 ����� 3 ���ڵ��ֵ��
 B
 ����ڵ� B �ĺ��ӽڵ�������
 0
 ����� 4 ���ڵ��ֵ��
 C
 ����ڵ� C �ĺ��ӽڵ�������
 1
 ����� 1 �����ӽڵ���˳����е�λ��6
 ����� 5 ���ڵ��ֵ��
 D
 ����ڵ� D �ĺ��ӽڵ�������
 0
 ����� 6 ���ڵ��ֵ��
 E
 ����ڵ� E �ĺ��ӽڵ�������
 0
 ����� 7 ���ڵ��ֵ��
 F
 ����ڵ� F �ĺ��ӽڵ�������
 3
 ����� 1 �����ӽڵ���˳����е�λ��7
 ����� 2 �����ӽڵ���˳����е�λ��8
 ����� 3 �����ӽڵ���˳����е�λ��9
 ����� 8 ���ڵ��ֵ��
 G
 ����ڵ� G �ĺ��ӽڵ�������
 0
 ����� 9 ���ڵ��ֵ��
 H
 ����ڵ� H �ĺ��ӽڵ�������
 0
 ����� 10 ���ڵ��ֵ��
 K
 ����ڵ� K �ĺ��ӽڵ�������
 0
 �ҳ��ڵ� F �����к��ӽڵ㣺G H K
 */
