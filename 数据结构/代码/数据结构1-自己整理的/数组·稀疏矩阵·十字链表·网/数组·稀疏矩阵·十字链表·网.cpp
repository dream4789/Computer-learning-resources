#include<stdio.h>
#include<stdlib.h>
typedef struct OLNode
{
    int i,j,e;       //������Ԫ��i������ j������ e����ǰλ�õ�����
    struct OLNode *right,*down; //ָ���� ��ָ�� ��ָ��
}OLNode, *OLink;

typedef struct
{
    OLink *rhead,*chead; //�к�������ͷָ��
    int mu,nu,tu;       //���������,�����ͷ���Ԫ�ĸ���
}CrossList;

CrossList CreateMatrix_OL(CrossList M)
{
    int m, n, t;
    int i, j, e;
    OLNode *p, *q;
    printf("�������������������ͷ�0Ԫ�ظ�����\n");
    scanf("%d%d%d", &m, &n, &t);
    M.mu = m;
    M.nu = n;
    M.tu = t;
    M.rhead = (OLink*)malloc((m + 1) * sizeof(OLink));
    M.chead = (OLink*)malloc((n + 1) * sizeof(OLink));
    if(!M.rhead||!M.chead)
    {
        printf("��ʼ������ʧ��");
        exit(0);
    }
    for (i = 1; i <= m; i++)
        M.rhead[i] = NULL;
    for (j = 1; j <= n; j++)
        M.chead[j] = NULL;
    printf("������Ԫ��:\n");
    for(scanf("%d%d%d", &i, &j, &e);0!=i;scanf("%d%d%d", &i, &j, &e))
    {//��i=0ʱ��������
        p=(OLNode*)malloc(sizeof(OLNode));
        if(!p)
        {
            printf("��ʼ����Ԫ��ʧ��");
            exit(0);
        }
        p->i = i;
        p->j = j;
        p->e = e;
        //���ӵ��е�ָ��λ��
        if (NULL == M.rhead[i] || M.rhead[i]->j>j)
        {
            p->right = M.rhead[i];
            M.rhead[i] = p;
        }
        else
        {
            for (q = M.rhead[i]; (q->right) && q->right->j<j;q=q->right);
            p->right = q->right;
            q->right = p;
        }
        //���ӵ��е�ָ��λ��
        if (NULL==M.chead[j]||M.chead[j]->i>i)
        {
            p->down = M.chead[j];
            M.chead[j] = p;
        }
        else
        {
            for (q = M.chead[j];(q->down)&&q->down->i<i;q=q->down);
            p->down = q->down;
            q->down = p;
        }
    }
    return M;
}
void display(CrossList M)
{
    for (int i = 1; i <= M.nu; i++)
    {
        if (NULL != M.chead[i])
        {
            OLink p = M.chead[i];
            while (NULL != p)
            {
                printf("%d  %d  %d\n", p->i, p->j, p->e);
                p = p->down;
            }
        }
    }
}
int main()
{
    CrossList M;
    M.rhead = NULL;
    M.chead = NULL;
    M = CreateMatrix_OL(M);
    printf("�������M:\n");
    display(M);
    return 0;
}
/*
 ��Ҳ��֪�����������ô�ܵģ�����������

 �������������������ͷ�0Ԫ�ظ�����
 3 3 3
 ������Ԫ��:
 2 2 3
 2 3 4
 3 2 5
 0 0 0
 �������M:
 2  2  3
 3  2  5
 2  3  4
 */
