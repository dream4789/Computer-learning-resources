//
//��������������ȫ
//
#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>  //һ��stdbool.hͷ�ļ��У�����bool��ͷ������ֵΪ1��0��false��true
#define maxsize 100

typedef char datatype;

int count=0;//ȫ�ֱ���

typedef struct tnode{//���������壬�ݹ����
    datatype data;
    struct tnode *lchild;
    struct tnode *rchild;
}tnode,*bintree;

typedef struct snode{//˳��ջ����,�ǵݹ����
    bintree data[maxsize];
    int top;
}seqstack,*pseqstack;

typedef struct qnode{//˳����ж��壬��α���
    bintree data[maxsize];
    int front;
    int rear;
}seqqueue,*pseqqueue;


//*******����������********//
bintree create(void)
{//����������
    bintree t;
    datatype ch;
    ch=getchar();
    if(ch=='#')
        t=NULL;
    else
    {
        t=(bintree)malloc(sizeof(tnode));
        t->data=ch;
        t->lchild=create();
        t->rchild=create();
    }
    return t;
}

//*******˳��ջ����********//
pseqstack init(void)
{//����˳��ջ
    pseqstack s;
    s=(pseqstack)malloc(sizeof(seqstack));
    if(s)
        s->top=-1;
    return s;
}
bool empty(pseqstack s)
{//�ж�ջ�Ƿ�Ϊ��
    if(s->top==-1)
        return 1;
    else
        return 0;
}
bool push(pseqstack s,bintree x)
{//ջ��������Ԫ��x
    if(s->top==maxsize-1)
        return 0;//ջ���޷���ջ
    else
    {
        s->top++;
        s->data[s->top]=x;
        return 1;
    }
}
bool pop(pseqstack s,bintree *x)
{//ɾ��ջ��Ԫ�أ���������*x
    if(empty(s))
        return 0;//ջ�ղ��ܳ�ջ
    else
    {
        *x=s->data[s->top];
        s->top--;
        return 1;
    }
}

//*******���в���********//
pseqqueue initqueue(void)
{//��ʼ������
    pseqqueue q;
    if (!(q=(pseqqueue)malloc(sizeof(seqqueue))))
    {
        printf("�ڴ����ʧ�ܣ�");
        exit(-1);
    }
    q->front=q->rear=-1;
    return q;
}
bool emptyqueue(pseqqueue q)
{//�����п�
    if(q->front==q->rear)
        return 1;//�ӿ�
    return 0;
}
bool inqueue(pseqqueue q,bintree t)
{//���
    if(q->rear==maxsize-1)
        return 0;//����
    q->rear++;
    q->data[q->rear]=t;
    return 1;
}
bool outqueue(pseqqueue q,bintree *t)
{//����
    if(q->front==q->rear)
        return 0;
    q->front++;
    *t=q->data[q->front];
    return 1;
}

//*******��������********//
void perorder1(bintree t)
{//��������ĵݹ��㷨
    if(t)
    {
        printf("%c ",t->data);
        perorder1(t->lchild);
        perorder1(t->rchild);
    }
}
void inorder1(bintree t)
{//��������ĵݹ��㷨
    if(t)
    {
        inorder1(t->lchild);
        printf("%c ",t->data);
        inorder1(t->rchild);
    }
}
void postorder1(bintree t)
{//��������ĵݹ��㷨
    if(t)
    {
        postorder1(t->lchild);
        postorder1(t->rchild);
        printf("%c ",t->data);
    }
}

void preorder2(bintree t)
{//ջ����������ķǵݹ��㷨
    pseqstack s;
    bintree p=t;
    s=init();
    while (p||!empty(s))
    {
        if(p)
        {
            push(s,p);
            printf("%c ",p->data);
            p=p->lchild;
        }
        else
        {
            pop(s,&p);
            p=p->rchild;
        }
    }
}
void inorder2(bintree t)
{//ջ����������ķǵݹ��㷨
    pseqstack s;
    bintree p=t;
    s=init();
    while (p||!empty(s))
    {
        if(p)
        {
            push(s,p);
            p=p->lchild;
        }
        else
        {
            pop(s,&p);
            printf("%c ",p->data);
            p=p->rchild;
        }
    }
}
void postorder2(bintree t)
{//ջ�ĺ�������ķǵݹ��㷨
    pseqstack s1;//���ս��ջ
    pseqstack s2;//����ջ
    bintree p=t;
    s1=init();
    s2=init();
    while (p||!empty(s2))
    {
        if(p)
        {
            push(s1,p);
            push(s2,p);
            p=p->rchild;
        }
        else
        {
            pop(s2,&p);
            p=p->lchild;
        }
    }
    while (!empty(s1))
    {
        pop(s1,&p);
        printf("%c ",p->data);
    }
}

void preorder3(bintree t)
{//����ǵݹ�-��ջ��
    bintree p=t;
    bintree s[maxsize];
    int top=-1;
    do{
        while(p){
            top++;
            s[top]=p;//������ǰ p �����ջ s ��
            printf("%c ",p->data);
            p=p->lchild;//ת����ǰ p ��������
        }
        p=s[top];//ȡ p ����һ�����
        top--;//��ͷָ�롱�� 1
        p=p->rchild;//ת����ǰ p �����Һ���
    }while(top!=-1||p);
}
void inorder3(bintree t)
{//����ǵݹ�-��ջ��
    bintree p=t;
    bintree s[maxsize];
    int top=-1;
    do{
        while (p)
        {
            top++;
            s[top]=p;//������ǰ p �����ջ s ��
            p=p->lchild;//ת����ǰ p ��������
        }
        p=s[top];//ȡ p ����һ�����
        top--;//��ͷָ�롱�� 1
        printf("%c ",p->data);
        p=p->rchild;
    }while(top!=-1||p);
}
void postorder3(bintree t)
{//����ǵݹ�-��ջ��
    bintree p=t;
    bintree s1[maxsize];//���ս��ջ
    bintree s2[maxsize];//����ջ
    int top1=-1;
    int top2=-1;
    do{
        while (p){
            top1++;
            top2++;
            s1[top1]=p;//������ǰ p �����ջ s1 ��
            s2[top2]=p;//������ǰ p �����ջ s2 ��
            p=p->rchild;//ת����ǰ p ��������
        }
        p=s2[top2];//ȡ p ����һ�����
        top2--;//��ͷָ�롱�� 1
        p=p->lchild;//ת����ǰ p ��������
    }while(top2!=-1||p);
    while (top1!=-1)
    {
        p=s1[top1];//s1 �Ӻ���ǰ��� p ���
        printf("%c ",p->data);
        top1--;
    }
}

void levelorder(bintree t)
{//��α���
    pseqqueue q;
    q=initqueue();//��������
    if(t!= NULL)//ִ��һ��
        inqueue(q,t);//����һ����� t ���������
    while (!emptyqueue(q))
    {
        outqueue(q,&t);// ����ʱ�Ľڵ�
        printf("%c ",t->data);// ����ڵ�洢��ֵ
        if(t->lchild!= NULL)//������ʱ���ýڵ������
            inqueue(q,t->lchild);
        if(t->rchild != NULL)//���Һ���ʱ���ýڵ������
            inqueue(q,t->rchild);
    }
}

int main()
{
    bintree t;
    printf("�������ַ���:");
    t=create();
    
    printf("\n����ݹ�: ");
    perorder1(t);
    printf("\n����ݹ�: ");
    inorder1(t);
    printf("\n����ݹ�: ");
    postorder1(t);
    
    printf("\n����ǵݹ�-ջ: ");
    preorder2(t);
    printf("\n����ǵݹ�-ջ: ");
    inorder2(t);
    printf("\n����ǵݹ�-ջ: ");
    postorder2(t);
    
    printf("\n����ǵݹ�-��ջ��: ");
    preorder3(t);
    printf("\n����ǵݹ�-��ջ��: ");
    inorder3(t);
    printf("\n����ǵݹ�-��ջ��: ");
    postorder3(t);

    printf("\n��α���-����: ");
    levelorder(t);
    
    printf("\n");
}
/*
�������ݣ�
ABDH###E##CF##G##
1248###5##36##7##
1248##9##50###36##7##
 
 
 
�������ַ���:1248##9##50###36##7##

����ݹ�: 1 2 4 8 9 5 0 3 6 7
����ݹ�: 8 4 9 2 0 5 1 6 3 7
����ݹ�: 8 9 4 0 5 2 6 7 3 1
����ǵݹ�-ջ: 1 2 4 8 9 5 0 3 6 7
����ǵݹ�-ջ: 8 4 9 2 0 5 1 6 3 7
����ǵݹ�-ջ: 8 9 4 0 5 2 6 7 3 1
����ǵݹ�-��ջ��: 1 2 4 8 9 5 0 3 6 7
����ǵݹ�-��ջ��: 8 4 9 2 0 5 1 6 3 7
����ǵݹ�-��ջ��: 8 9 4 0 5 2 6 7 3 1
��α���-����: 1 2 3 4 5 6 7 8 9 0

 */

