//
//  main.c
//  ��������Ӧ�þ�������������
//

#include <stdio.h>
#include <stdlib.h>
#define maxsize 100

typedef char datatype;
int count=0;//ȫ�ֱ���

typedef struct tnode{
    datatype data;
    struct tnode *lchild;
    struct tnode *rchild;
}Tnode,*bintree;


bintree create(void)
{//�������������������,�Լ���ս���������������
    bintree t;
    datatype ch;
    ch=getchar();
    if(ch=='#')   //����#ʱ,����Ӧ���ָ���ÿ�
        t=NULL;
    else
    {
        t=(bintree)malloc(sizeof(Tnode));//���ɽ��ռ�
        t->data=ch;
        t->lchild=create();//�����������������
        t->rchild=create();//�����������������
    }
    return (t);
}

int count_tree(bintree t)
{//��������Ľ�����,����˼·
    if(t==NULL)
        return 0;
    if(t)
    {
        count_tree(t->lchild);
        count++;
        count_tree(t->rchild);
    }
    return count;
}

int Count(bintree t)
{//��������Ľ�����,����˼·
    int lcount,rcount;
    if (t==NULL)
        return 0;
    lcount=Count(t->lchild);     //���������Ľ�����
    rcount=Count(t->rchild);     //���������Ľ�����
    return  lcount+rcount+1;
}

int high(bintree t)
{//��������߶ȣ�����˼·
    int l,r;
    if(t==NULL)
        return 0;
    else
    {
        l=high(t->lchild);//�������߶�
        r=high(t->rchild);//�������߶�
        if(l>r)
            return l+1;
        return r+1;
    }
}

bintree CopyTree(bintree  t)
{//���ƶ������㷨
    bintree p,q,s;
    if (t==NULL)
        return NULL;
    p=CopyTree(t->lchild);    /*����������*/
    q=CopyTree(t->rchild);    /*����������*/
    s=(bintree)malloc(sizeof(Tnode));  /*���Ƹ����*/
    s->data=t->data;
    s->lchild=p;
    s->rchild=q;
    return s;
}

void Levcount(bintree t,int L,int num[])
{//�������ÿ�������㷨,����˼·
    //����ʽ�洢�Ķ�����t��ÿ�������L��ʾ��ǰt��ָ���Ĳ�Σ���t��ֵΪ��ʱ��L��ֵΪ1��num����Ԫ�س�ʼ��0
    if(t)
    {
        printf("%c",t->data); //���ʵ�ǰ���
        num[L]++;  //��ǰt��ָ���Ĳ��������1
        Levcount(t->lchild, L+1, num); //�ݹ�������
        Levcount(t->rchild, L+1, num); //�ݹ�������
     }
 }


int main(int argc, const char * argv[])
{
    printf("�������������");
    bintree t=create(),s;
    printf("�ö�����������Ϊ(����˼·)��%d\n",count_tree(t));
    printf("�ö������߶�Ϊ(����˼·)��%d\n",Count(t));
    printf("�ö������߶�Ϊ(����˼·)��%d\n",high(t));
    s=CopyTree(t);
    int num[10]={0};
    printf("������ÿ�������㷨(����˼·):");
    Levcount(s, 1, num);
    printf("\n");
    return 0;
}

/*
 
�������ݣ�
ABDH###E##CF##G##
1248###5##36##7##
1248##9##50###36##7##
 
 
 �������������1248##9##50###36##7##
 �ö�����������Ϊ(����˼·)��10
 �ö������߶�Ϊ(����˼·)��10
 �ö������߶�Ϊ(����˼·)��4
 ������ÿ�������㷨(����˼·):1248950367
 
 */
