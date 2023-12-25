//
//  main.c
//  ������ʽ�洢

#include <stdio.h>
#include <stdlib.h>

//�������� ɾ�� ����

typedef char datatype;
typedef struct node
{
    datatype  data;
    struct node *next;
}node;

typedef node *linkstr;


void createstr(linkstr *s)//�����ַ���
{
    char ch;
    node *p,*r; //p,r,linkstr(*s)���ǽڵ�
    *s=NULL;  //*s��¼��һ���ڵ�
    r=NULL;//��ʼ���ڵ�Ϊ��
    while((ch=getchar())!='\n')
    {
        //p=(linkstr)malloc(sizeof(node));
        p=(node*)malloc(sizeof(node));
        p->data=ch;
        if(*s==NULL)//ִ�е�һ��
        {
            *s=p;
            r=p;
        }
        else
        {
            r->next=p;//����
            r=p;
        }
    }
    if(r!=NULL)
        r->next=NULL;
}
linkstr strinsert(linkstr *s,int i,linkstr t)//����
{//ԭʼ�ַ���������λ�ã���i����ĸ���棩��Ҫ������ַ���
    int k=1;
    linkstr p,q;
    p = *s;//pΪs���ĵ�һ���ڵ�
    while(p&&k<i-1)//��p���ҵ�i-1��λ��
    {
        p=p->next;
        k++;
    }
    if(!p)//��i-1��Ԫ�ز�����,�����
    {
        puts("error!");
        exit(1);
    }
    else
    {
       q=t;
       while(q&&q->next)  //��q����t�����һ��Ԫ�ص�λ
           q=q->next;
       if(i==1)
       {
           q->next=p;//q�����һ��ָ��s
           *s=t;//sͷ����t
           return *s;
       }
        q->next=p->next; //n��d   ��t���ӵ�s�еĵ�i��λ��
        p->next=t;//c��m����
    }
    return *s;
}

void del(linkstr *s,int i,int length)//ɾ��
{//ԭʼ�ַ�������i���ַ���ʼɾ����ɾ����Ϊlength
    int k=1;
    linkstr p,q,r;
    p=*s;
    q=NULL;  //q=nullɾ����һ������ʼֵ
    //��i��λ�õ�һ��λ��
    while(p&&k<i)  //��p����s�ĵ�i��Ԫ�أ�qʼ�ո���p��ǰ���ڵ�
    {
        q=p;
        p=p->next;
        ++k;
    }
    if(!p)//*s�ӵ�i��Ԫ�ز����������
        printf("error!");
    else
    {
        k=1;
        while(k<length&&p)  //p�ӵ�i��Ԫ�ؿ�ʼ���ҳ���Ϊlen�Ӵ������Ԫ��
        {
            p=p->next;
            ++k;
        }
        if(!p)
            printf("two error!");
        else
        {
            if(!q)     //��ɾ�����Ӵ�λ��s
            {
                r=*s;//��r��¼ԭ�ַ�����һ���ڵ�
                *s=p->next;//*s��¼ɾ���������ʼ�ڵ�
            }
            else   //��ɾ�������ַ���λ��s���м������������
            {
               r=q->next;  //��r��¼Ҫɾ���Ӵ��ĵ�һ���ڵ�
               q->next=p->next;
            }
            p->next=NULL;
            while(r!=NULL)    //�������ַ���ռ�õĿռ�
            {
                p=r;
                r=r->next;
                free(p);
            }
        }
    }
}

void concatstr(linkstr *s1,linkstr s2)//����
{//�Ѵ�s2���ӵ�s1��
    linkstr p;
    if(!(*s1))//���Ǵ�s1Ϊ�մ�ʱ
    {
        *s1=s2;
        return ;
    }
    else
    {
        if(s2) //s1��s2����Ϊ�մ�ʱ
        {
            p=*s1;//��p����s1�����һ���ַ���λ��
            while(p->next)
            {
                p=p->next;
            }
            p->next=s2;//����s2���ӵ���s1֮��
        }
    }
}

linkstr substring(linkstr *s,int i,int len)//ȡ��ʽ�����Ӵ�
{//ԭʼ�ַ�������i���ַ���ʼ��ȡ����len���Ӵ�
    int k=1;//pΪԭ�ַ�����һ���ڵ㣬��p��¼s�еĵ�i��λ��
    linkstr p=*s,q,r,t;
    while(p&&k<i)
    {
        p=p->next;
        ++k;
    }
    if(!p)
    {
        printf("error!");
        return NULL;
    }
    else
    {//r�����һ���ڵ�
        r=(node*)malloc(sizeof(node));
        r->data=p->data;
        r->next=NULL;
        k=1;
        q=r;
        while(p->next&&k<len)
        {
            p=p->next;//p�ڶ����ڵ�
            ++k;
            t=(node*)malloc(sizeof(node));//����ڶ����ڵ�t++�ڵ�
            t->data=p->data;
            q->next=t; //��һ���͵ڶ����ڵ㻮��
            q=t;      //qָ���ַ������һ��λ��
        }
        if(k<len)
        {
            printf("two error!");
            return NULL;
        }
        else
        {
            q->next=NULL;
            return r;
        }
    }
}
void dispaly(linkstr *s)
{
    node *p;
    //linkstr p;
    p=*s;
    while(p)
    {
        printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}
int main()
{
    linkstr s,t;
    printf("�����ʼ�ַ���1��");
    createstr(&s);//����ԭʼ�ַ���
    printf("   1.����������ַ���s: ");
    dispaly(&s);


    printf("����Ҫ������ַ�����");//����
    createstr(&t);//����Ҫ������ַ���
    strinsert(&s,5,t);
    printf("   2.����������ַ���s: ");
    dispaly(&s);

    del(&s,2,2);//ɾ��,�ӵ�2λ��ʼ����2λ����ɾ��
    printf("   3.���ɾ������ַ���s: ");
    dispaly(&s);
    printf("\n");

    printf("����Ҫ���ӵ��ַ���2��");
    createstr(&t);
    concatstr(&s,t);//����
    printf("   4.������Ӻ���ַ���s: ");
    dispaly(&s);

    t=substring(&s,1,1);//ȡ�Ӵ����ӵ�1λ��ʼ����1λ����ȡ�Ӵ�
    printf("   5.����Ӵ�s: ");
    dispaly(&t);
    
    return 0;
}
/*
 
�������ݣ�
(ע�⣺��һ���������ո����һ����ǰ��һ���ո�
 
mzt  student
is a sun
 forever

��������
 
 �����ʼ�ַ���1��mzt  student
    1.����������ַ���s: mzt  student
 ����Ҫ������ַ�����is a sun
    2.����������ַ���s: mzt is a sun student
    3.���ɾ������ַ���s: m is a sun student

 ����Ҫ���ӵ��ַ���2�� forever
    4.������Ӻ���ַ���s: m is a sun student forever
    5.����Ӵ�s: m
 




 ���������������������ˣ�������������ġ�
 
 */
