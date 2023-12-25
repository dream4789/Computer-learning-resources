#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100  //˳������󳤶�,�ٶ�˳���ĳ���Ϊ 100

typedef int KeyType;  //�ٶ��ؼ�������Ϊ��������
typedef int OtherType;
typedef struct
{
    KeyType key;  //�ؼ�����
    OtherType other;  //������
}DataType;  //����Ԫ������
typedef struct
{
    DataType r[MAXSIZE+1];  //r[0]���û�䵱ǰ��վ
    int length;  //˳�����
}SqList;  //˳�������

SqList init_sqlist(void)
{
    int a[10]={10,23,45,31,8,37,16,67,26,14};
    SqList * L=(SqList*)malloc(sizeof(SqList));
    //printf("���봮����");
    L->length=10;// ��ʱ
    //scanf("%d",&L->length);
    //printf("���봮��Ԫ�أ�\n");
    for(int i=1;i<=L->length;i++)
    {
        L->r[i].key=a[i-1];  //��ʱ
        //scanf("%d",&L->r[i].key);
    }
    return *L;
}

void Merge(DataType r[],DataType rf[],int u,int v,int t)
{//������� r[u����v]�� r[v+1����t]�鲢Ϊ����� rf[u����t]
    int i,j,k;
    for(i=u,j=v+1,k=u;i<=v && j<=t;k++)  //��r�м�¼��С���󲢵�tf
    {
        if(r[i].key<=r[j].key)
        { rf[k]=r[i];i++;}  //j���i
        else
        { rf[k]=r[j];j++;}  //i���j
    }
    while(i<=v){rf[k++]=r[i++];}  //��ʣ��� r[i����v]���Ƶ�tf
    while(j<=t){rf[k++]=r[j++];}  //��ʣ��� r[j����t]���Ƶ�tf
}
//��·�鲢������Ҫ���������л���Ϊ��������������У�Ȼ�������������н���
//�鲢����
void MSort(DataType p[],DataType p1[],int n,int t)
{//�� p[n����t]�鲢����Ϊ p1[n����t]
    int m;
    DataType p2[MAXSIZE+1];  //�м����,��Ų���������
    if(n==t)
        p1[n]=p[n];  //P��ֻ��һ��Ԫ�أ�����Ҫ���й鲢����
    else
    {
        m=(n+t)/2;  //ƽ�ִ����������
        MSort (p,p2,n,m);    //�� p[n����m]�鲢Ϊ����� p2[n����m],���õݹ����ʵ��
        MSort (p,p2,m+1,t);  //�� p[m+1����t]�鲢Ϊ����� p2[m+1����t],���õݹ����ʵ��
        Merge (p2,p1,n,m,t); //�� p2[n����m]�� p2[m+1����t]�鲢�� p1[n����t]
    }
}
void MergeSort(SqList * S)
{//��˳��� S ���鲢����
    MSort(S->r,S->r,1,S->length);
}
int main()
{
    SqList L=init_sqlist();
	int i;
    
    MergeSort(&L);
    printf("�鲢����");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
}
/*
 ���鸳ֵ������
 int z[5]={1,1,2,4};
 int n[10]={0};  //��n�������ȫ����ʼ��Ϊ0
 char z[]="zhinanzhen";
 char t[6]={'s','t','u','d','e','n','t','\0'};
 char x[]="can l with you ?";
 
 ���봮����10
 ���봮��Ԫ�أ�
 10
 23
 45
 31
 8
 37
 16
 67
 26
 14
 �鲢����8 10 14 16 23 26 31 37 45 67
 */
