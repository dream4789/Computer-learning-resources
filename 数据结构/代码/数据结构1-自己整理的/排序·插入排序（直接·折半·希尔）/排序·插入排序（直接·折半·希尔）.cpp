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
    SqList * L=(SqList*)malloc(sizeof(SqList));
    printf("���봮����");
    scanf("%d",&L->length);
    printf("���봮��Ԫ�أ�\n");
    for(int i=1;i<=L->length;i++)
        scanf("%d",&L->r[i].key);
    return *L;
}

void StraightInsertSort(SqList* S)
{//��˳��� s �е� s->r[1..length]��ֱ�Ӳ�������
    int i,j;
    for(i=2;i<=S->length;i++)
    {
        S->r[0]=S->r[i];  //���Ƶ�ǰ��վ
        j=i-1;
        while(S->r[0].key < S->r[j].key)  //��¼����
        {
            S->r[j+1]=S->r[j];
            j--;
        }
        S->r[j+1]=S->r[0];  //���뵽��ȷλ��
    }
}

void BinaryInsertsort(SqList * s)
{//��˳��� s ���۰��������
    int low,high,mid;
    for(int i=2;i<=s->length;i++)
    {
        s->r[0]=s->r[i];  //���������Ԫ��
        low=1;
        high=i-1;  //���ó�ʼ����
        while(low<=high)  //��ѭ��������ȷ������λ��
        {
            mid=(low+high)/2;
            if(s->r[0].key >= s->r[mid].key)
                low=mid+1;  //����λ���ڸ߰�����
            else
                high=mid-1;  //����λ���ڵͰ�����
        }
        for(int j=i-1;j>=high+1;j--)  //high+1 Ϊ����λ��
            s->r[j+1] = s->r[j];  //����Ԫ��,���������λ
        s->r[high+1]=s->r[0];  //��Ԫ�ز���
    }
}  //BinaryInsertSort

void ShellInsert(SqList* s,int gap)
{//һ������Ϊ gap �Ĳ�������,gap Ϊ����
    int i,j;
    for(i=gap+1 ; i<=s->length ; i++)
    {
        if(s->r[i].key < s->r[i-gap].key)  //ǰ������,С��ʱ,�轫r[i]���������
        {
            s->r[0]=s->r[i];  //Ϊͳһ�㷨���ü����ڣ��ݴ�
            for(j=i-gap ; j>0 && s->r[0].key<s->r[j].key ; j=j-gap)
                s->r[j+gap]=s->r[j];  //��¼����
            s->r[j+gap]=s->r[0];  //���뵽��ȷλ��
        }
        /*
        for(int k=0;k<=s->length;k++)  //������
            printf("%d ",s->r[k].key);
        printf("\n");
         */
    }
    //printf("\n");  //������
}
void ShellSort(SqList* s,int gaps[],int t)
{//���������� gaps[0,1,��t-1]��˳��� s ��ϣ������
    for(int k=0;k<t;k++)
    {
        ShellInsert(s,gaps[k]);   //һ������Ϊ gaps[k]�Ĳ�������
        /*
        for(int i=1;i<=s->length;i++)  //������
            printf("%d ",s->r[i].key);
        printf("\n");
         */
    }
}

int main()
{
    SqList L=init_sqlist();
    SqList S=L;
    SqList S1=L;
	int i;
    
    //ֱ�Ӳ�������
    StraightInsertSort(&L);
    printf("ֱ�Ӳ�������:");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
    
    //�۰��������
    BinaryInsertsort(&S);
    printf("�۰��������:");
    for(i=1;i<=L.length;i++)
        printf("%d ",S.r[i].key);
    printf("\n");
    
    //ϣ������
    int len=S1.length;
	int gaos[10];
    //int gaos[len];//vc6��֧������д
	int t=0;
    printf("gaos[]����(����)��");
    for(i=0;len>1;i++)
    {
        gaos[i]=len/2;  //����
        printf("%d ",gaos[i]);
        len/=2;
        t++;
    }
    printf("\n");
    ShellSort(&S1,gaos,t);
    printf("ϣ������");
    for(i=1;i<=S1.length;i++)
        printf("%d ",S1.r[i].key);
    printf("\n");
	return 0;
}
/*
 
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
 ֱ�Ӳ�������:8 10 14 16 23 26 31 37 45 67
 �۰��������:8 10 14 16 23 26 31 37 45 67
 gaos[]����(����)��5 2 1
 ϣ������8 10 14 16 23 26 31 37 45 67
 
��������㷨
* ��������
*   1.ֱ�Ӳ�������   �ȶ�
*   2.�۰��������   �ȶ�
*   3.ϣ������      ���ȶ�
* ��������:
*   4.ð������      �ȶ�
*   5.��������      ���ȶ�
* ѡ������:
*   6.��ѡ������   ���ȶ�
*   7.������        ���ȶ�
* �鲢����:
*   8.��·�鲢����   �ȶ�

 
 */
