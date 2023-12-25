#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef int KeyType;
typedef struct
{
    KeyType key;
}DataType;
typedef struct BinSTreeNode
{
    DataType  elem;   //elem���йؼ�����
    struct BinSTreeNode  *lchild;
    struct BinSTreeNode  *rchild;
}*BinSTree;

//���������������㷨
BinSTree BSTreeSearch(BinSTree t ,KeyType k )
{//�ڸ�ָ��Ϊt�Ķ����������в��ҹؼ���Ϊk�Ľ�㣬�����ҳɹ����򷵻�ָ��ý���ָ�룻���򷵻ؿ�ָ��
    if (t==NULL)
        return NULL;
    if (t->elem.key==k)
        return t; //���ҳɹ�,����ֵtһֱ���ܴ����������ǵݹ�ԭ��
    if (t->elem.key>k)
        BSTreeSearch(t->lchild ,k); //���������в���
    else
        BSTreeSearch(t->rchild ,k); //���������в���
    return NULL;//����ֵһֱΪNULL
}
//����
BinSTree BSTreeSearch1(BinSTree t ,KeyType k )
{//������Ĳ���BSTreeSearch()�У�����ֵtһֱ���ܴ����������ǵݹ�ԭ����������BSTreeSearch1()
    if (t==NULL)
    {
        printf("\n����������δ���ҵ�\n");//����ʧ��
        return NULL;
    }
    if (t->elem.key==k)
    {
        printf("\n������������ҵ���: %d\n",t->elem.key);//���ҳɹ�
        return t;
    }
    if (t->elem.key>k)
        BSTreeSearch1(t->lchild ,k); //���������в���
    else
        BSTreeSearch1(t->rchild ,k); //���������в���
    return NULL;
}

//���������������㷨
BinSTree BSTreeInsert (BinSTree *t , KeyType k)
{//�ڶ����������в���ؼ���Ϊk�Ľ�㣬*tָ������������ĸ����
    BinSTree r;
    if (*t==NULL)
    {
        r=(BinSTree)malloc(sizeof(struct BinSTreeNode));
        r->elem.key=k;
        r->lchild=r->rchild=NULL;
        *t=r;     //������������Ϊ�գ���������Ϊ���ĸ����
        return *t;
    }
    else if(k<((*t)->elem.key))
        BSTreeInsert(&((*t)->lchild),k);  //���뵽p����������
    else
        BSTreeInsert(&((*t)->rchild),k);  //���뵽p����������
    return NULL;
}

//�����������Ľ��ɾ���㷨
int BSTreeDelete (BinSTree bt , KeyType k)
{//�ڶ�����������ɾ���ؼ���Ϊk�Ľ�㣬*btָ������������ĸ���㡣ɾ���ɹ�����1�����ɹ�����0
    BinSTree f,p,q,s;
    p=bt;
    f=NULL;
    while (p&& p ->elem.key!=k)
    {
        f=p;         //fΪָ����*p��˫�׽���ָ��
        if (p->elem.key>k)
            p=p->lchild;   //����������
        else
            p=p->rchild;   //����������
    }
    if (p==NULL)
        return 0;    //�Ҳ�����ɾ�Ľ��ʱ����
    if (p->lchild==NULL)     //��ɾ����������Ϊ��
    {
        if (f==NULL)     //��ɾ���Ϊ�����
            bt=p->rchild;
        else if (f->lchild==p)  //��ɾ������丸��������
            f->lchild=p->rchild ;
        else             //��ɾ������丸�����Һ���
            f->rchild=p->rchild;
        free (p);
    }
    else     //��ɾ�����������
    {
        q=p;
        s=p->lchild;
        while(s->rchild)   //�ڴ�ɾ�����������в��������½��
        {
            q=s;
            s=s->rchild;
        }
        if (q==p)       //�������½���������������ɾ�����
            q->lchild=s->lchild;
        else
            q->rchild=s->lchild;
        p->elem.key=s->elem.key;
        free (s) ;
        return 1;
   }
    return 0;
}

void inorder1(BinSTree t)
{//��������ĵݹ��㷨
    if(t)
    {
        inorder1(t->lchild);
        printf("%d ",t->elem.key);
        inorder1(t->rchild);
    }
}

int main()
{
    BinSTree t=NULL,r=NULL;
    int i,j=0;
    int a[10],b[10];
    
    srand((unsigned)time(NULL));
    int randnum=rand()%9+1;  //�� 1 ����9+1-1���������
    printf("����������Ҫ���ҵ����ڵ� %d λ\n",randnum);
    
    printf("����������Ҫ�������Ϊ��");
    for(i = 0; i<10;i++)
    {
        a[i]=rand()%90+10;  //���������
        b[i]=a[i];
        printf("%d ",a[i]);
    }
    
    //���������룬���������˳�����
    for(i=0;i<10;i++)
    {
        if(j==0)  //ֻ����һ�Σ���¼�����r
        {
            r=BSTreeInsert(&t, a[i]);
            j++;
        }
        else
            t=BSTreeInsert(&r, a[i]);  //tΪ����ʱ���ڽ�㣬û�ô�
        //printf("\n");  //������
        //inorder1(r);  //������
    }
    printf("\n����������������Ϊ��");
    inorder1(r);
    
    //���ҽ��
    BSTreeSearch1(r, a[randnum]);
    
    //ɾ�����
    BSTreeDelete(r, a[randnum]);
    printf("����������ɾ�� %d Ϊ��",a[randnum]);
    inorder1(r);
    
    //���ҽ��
    BSTreeSearch1(r, a[randnum]);
    return 0;
}
/*
 
 ����������Ҫ���ҵ����ڵ� 8 λ
 ����������Ҫ�������Ϊ��57 10 43 23 45 59 37 97 53 41
 ����������������Ϊ��10 23 37 41 43 45 53 57 59 97
 ������������ҵ���: 53
 ����������ɾ�� 53 Ϊ��10 23 37 41 43 45 57 59 97
 ����������δ���ҵ�
 
 */
