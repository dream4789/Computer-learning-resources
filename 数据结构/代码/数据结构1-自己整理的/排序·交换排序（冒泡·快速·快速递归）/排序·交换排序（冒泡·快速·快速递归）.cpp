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

void BubbleSort(SqList * s)
{//��˳��� s ��ð������
    int i,j;
    for(i=1;i<=s->length-1;i++)  //���� n-1 ������
        for(j=2;j<=1+s->length-i;j++)
            if(s->r[j].key < s->r[j-1].key)  //S->r[j]��s->r[j-1]����
            {
                s->r[0]=s->r[j];
                s->r[j]=s->r[j-1];
                s->r[j-1]=s->r[0];
            }
}

//һ�˿�������
int QuickSort1(SqList* s,int low,int high)
{//����˳��� S���ӱ� r[lowhigh���ļ�¼,ʹ��ֵ(֧��)��¼��λ,������������λ��
//��ʱ,����֮ǰ(��)�ļ�¼������(С)����
    KeyType pivotkey;
    s->r[0]=s->r[low];  //���ӱ�ĵ�һ����¼��Ϊ��ֵ(֧��)��¼
    pivotkey=s->r[low].key;  //ȡ��ֵ(֧��)��¼�ؼ���
    while(low<high)  //�ӱ�����˽�������м�ɨ��
    {
        while(low<high && s->r[high].key>=pivotkey)
            high--;
        s->r[low]=s->r[high];
        while(low<high && s->r[low].key<=pivotkey)
            low++;  //������ֵ(֧��)��¼С�Ľ������Ͷ�
        s->r[high]=s->r[low];  //������ֵ(֧��)��¼��Ľ������߶�
    }
    s->r[low]=s->r[0];  //��ֵ(֧��)��¼��λ
    return low;  //������ֵ(֧��)��¼����λ��
}

//���������㷨�ĵݹ�
void QuickSort(SqList* s,int low,int high)  //�ݹ���ʽ�Ŀ�������
{//��˳��� s �е������� r[low��high)����������
    int pivotloc;
    if(low<high)
    {
        pivotloc=QuickSort1(s,low,high);  //������������һ��Ϊ��
        QuickSort(s,low,pivotloc-1);  //��С����ֵ����ʵ�ֵݹ�����
        QuickSort(s,pivotloc+1,high);  //�Դ�����ֵ����ʵ�ֵݹ�����
    }
}

int main()
{
    SqList L=init_sqlist();
    SqList S=L;
	int i;
    
    BubbleSort(&L);
    printf("ð������");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
    
    QuickSort(&S, 1, S.length);
    printf("��������");
    for(i=1;i<=L.length;i++)
        printf("%d ",S.r[i].key);
    printf("\n");
    
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
ð������8 10 14 16 23 26 31 37 45 67
��������8 10 14 16 23 26 31 37 45 67
 
 */
