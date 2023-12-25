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

//��ѡ������
void SelectSort(SqList * s)
{
    int i,j,t;
    DataType tmp;
    for(i=1;i<s->length;i++)  //�� S->length-1 ��ѡȡ
    {
        for(j=i+1,t=i;j<=s->length;j++)
        {//��i��ʼ�� length-i+1���������¼��ѡ�ؼ�����С�ļ�¼*1
            if(s->r[t].key>s->r[j].key)
            t=j;  //t�д�Źؼ�����С�ļ�¼�±�
        }
        tmp=s->r[t];
        s->r[t]=s->r[i];
        s->r[i]=tmp;  //�ؼ�����С�ļ�¼��� i����¼����
    }
}

//�󶥶�
void HeapAdjust(SqList* s,int n,int len)
{//S->r[n��len]�еļ�¼�ؼ��ֳ� r[n]�������ѵĶ���,���������Ե� n�����Ϊ��������ɸѡ,ʹ���Ϊ�󶥶�
    int j;
    DataType rc=s->r[n];  //�ȶԲ���λ���ϵĽ�����ݽ��б��棬���ú����ƶ�Ԫ�ض�ʧ��
    for(j=2*n;j<=len;j=j*2)  //�عؼ��ֽϴ�ĺ��ӽ������ɸѡ
    {
        if(j<len && s->r[j].key < s->r[j+1].key)
            j++;  //�����ǰ�������ĺ��ӽ���ֵ��������
        if(rc.key > s->r[j].key)  //rcӦ������λ��i��
            break;
        s->r[n]=s->r[j];
        n=j;  //ʹn�������Ѷ���
    }
    s->r[n]=rc;
    /*
    for(j=1;j<=s->length;j++)//������
        printf("%d ",s->r[j].key);
    printf("\n");
	*/
}
    
//������ʵ�����Ƕ��������в��Ͻ��Ѻ͵����ѵĹ���
//�������㷨
void HeapSort(SqList *s)
{
    int i;
    DataType tmp;
    for(i=s->length/2;i>0;i--)  //��r[1..length]���ɶ�
        HeapAdjust(s,i,s->length);
    //printf("\n");  //������
    for(i=s->length;i>1;i--)  //���󶥶Ѹĳ�С����
    {
        tmp=s->r[1];  //�Ѷ���ѵ�Ԫ�ؽ���,�����Ԫ���Ƶ�����
        s->r[1]=s->r[i];
        s->r[i]=tmp;
        HeapAdjust(s,1,i-1);  //��r[1..i-1]���µ���Ϊ��
    }
}

int main()
{
    SqList L=init_sqlist();
    SqList S=L;
	int i;
    
    SelectSort(&L);
    printf("��ѡ������");
    for(i=1;i<=L.length;i++)
        printf("%d ",L.r[i].key);
    printf("\n");
    
    HeapSort(&S);
    printf("������-�󶥶ѣ�");
    for(i=1;i<=S.length;i++)
        printf("%d ",S.r[i].key);
    printf("\n");
    
    return 0;
}
/*

���봮����5
���봮��Ԫ�أ�
5
12
9
23
18
��ѡ������5 9 12 18 23
������-�󶥶ѣ�5 9 12 18 23


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
*/
