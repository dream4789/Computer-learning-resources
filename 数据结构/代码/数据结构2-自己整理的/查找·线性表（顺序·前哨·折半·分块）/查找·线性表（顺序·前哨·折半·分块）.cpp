//  ���ҡ����Ա�˳��ǰ�ڡ��۰롤�ֿ飩
//
//

#include <stdio.h>
#include <stdlib.h>
#define maxsize 100    //���ұ���󳤶�
typedef int  KeyType;  //����

//˳��ǰ�ڣ��۰�
typedef struct
{
    KeyType key;
}DataType;

typedef struct
{
    DataType r[maxsize];  //����Ԫ�ش洢�ռ�
    int length;  //��ĳ���
}Sqlist;

//�ֿ�
#define MAXL 100     //˳������󳤶�
#define MAXI 20      //���������󳤶�
typedef int KeyType;

typedef struct
{
    KeyType key;  //˳�������
}NodeType;
typedef NodeType SeqList[MAXL];  //˳���
typedef struct
{
    KeyType key;  //���������ؼ���
    int link;  //ÿ�����ʼ�±�
}IdxType;
typedef IdxType IDX[MAXI];   //������

void init_Idxtype(SeqList R,IDX I)  //�ֿ鴦��
{
    int a[]={8,14,6,9,10,22,34,18,19,31,40,38,54,66,46,71,78,68,80,85,100,94,88,96,87};
    for(int i=0;i<25;i++)    //����˳���
        R[i].key=a[i];
    //  8   <14>  6   9    10       0  -> 4
    //  22   34   18  19  <31>      5  -> 9
    //  40   38   54 <66>  46       10 -> 14
    //  71   78   68  80  <85>      15 -> 19
    // <100> 94   88  96   87       20 -> 24
    I[0].key=14;I[0].link=0;  //��ʼ�ֿ�
    I[1].key=34;I[1].link=5;
    I[2].key=66;I[2].link=10;
    I[3].key=85;I[3].link=15;
    I[4].key=100;I[4].link=20;
}

Sqlist init_strlist(void)
{//�������ұ�
    Sqlist *s;
    s=(Sqlist *)malloc(sizeof(Sqlist));
    printf("��������Ա��ȣ�ǰ�ڳ���+1����");
    scanf("%d",&s->length);
    printf("��������Ա�Ԫ�أ�\n");
    for(int i=0;i<s->length;i++)
        scanf("%d",&s->r[i].key);
    return *s;
}

//˳������㷨
int SeqSearch(Sqlist s,KeyType k)
{//�ڱ�s��˳����ҹؼ���k�������ҳɹ�������ֵΪ��Ԫ���ڱ��е�λ�ã�������ʧ�ܣ�����-1
    int i;
    for(i=0;i<s.length;i++)
        if(s.r[i].key==k)
            return i;   //���ҳɹ�
    return -1;   //����ʧ��
}

//��ǰ��վ��˳����ҸĽ��㷨
int SeqSearch_gai(Sqlist s,KeyType k)
{
    s.length+=1; // ��s.length���ȼ�1����ǰ��
    int i=0,n;
    n= s.length;
    s.r[n].key=k;   //����ǰ��վ��Ҫ�࿪��һ���洢�ռ�
    while(s.r[i].key!=k)  //�ӱ��׿�ʼ���ɨ��
        i++;
    return i;
}

//�۰�����㷨
int BinSearch(Sqlist s , KeyType k)
{//�ڱ�s�����۰���ҷ����ҹؼ���k�������ҳɹ�������ֵΪ��Ԫ���ڱ��е�λ�ã�������ʧ�ܣ�����-1
    int low,mid,high;
    low = 0;
    high = s.length-1;
    while(low<=high)
    {
        mid=(low+high)/2;       //ȡ�����е�
        if (s.r[mid].key==k)
            return mid;      //���ҳɹ�
        else if (s.r[mid].key>k)
            high=mid-1;       //���������в���
        else
            low=mid+1;        //���������в���
     }
    return -1;   //����ʧ��
}

//�۰���ҡ����ݹ��㷨
int BinSearch1(Sqlist s, KeyType k, int low, int high)
{//�ڱ�s�����۰���ҷ����ҹؼ���k�������ҳɹ�������ֵΪ��Ԫ���ڱ��е�λ�ã�������ʧ�ܣ�����-1
    int mid;
    while(low <= high)
    {
        mid=(low+high)/2;       //ȡ�����е�
        if(s.r[mid].key==k)
            return mid;      //���ҳɹ�
        else if(s.r[mid].key>k)
            return BinSearch1(s, k, low, mid-1);  //���������в���
        else
            return BinSearch1(s, k, mid+1, high);  //���������в���
     }
    return -1;   //����ʧ��
}

int IdxSearch(IDX I,int m,SeqList R,int n,KeyType k)
{//�ֿ�����㷨�� m Ϊ�ֿ��������n Ϊ˳������ݵĸ���
    int low=0,high=m-1,mid,i;
    int b=n/m;     //bΪÿ�����ݵĸ���
    
    //���������н��ж��ֲ���,�ҵ�����ڵĶ�Ӧ�ֿ�
    printf("1.���ֲ���key����һ�ֿ飺\n");
    while (low<=high)
    {
        mid=(low+high)/2;
        //printf("�� %d -> %d �ֿ��бȽ�Ԫ��R[%d]:%d\n",low+1,high+1,mid,R[mid-1].key);
        if (I[mid].key>=k)
            high=mid-1;
        else
            low=mid+1;
    }
    if (low<m)//���������в��ҳɹ���,�������Ա��н���˳�����
    {
        printf("   �� key=%d ��������ĵ� %d �ֿ���\n",k,low+1);
        i=I[low].link-1;
        printf("2.˳�����key�ڷֿ�ĵڼ�����\n");
        printf("   �÷ֿ������Ϊ��");
        while (i<=I[low].link+b-1 && R[i].key!=k)
        {
            i++;
            printf("%d ",R[i].key);
        }
        printf("\n   �� key=%d ��˳���ĵ� %d λ\n",k,i);
        if (i<=I[low].link+b-1)
            return i;
        else
            return -1;
    }
    return -1;
}

int main(int argc, const char * argv[])
{

    Sqlist str1=init_strlist();  //��������
    //Sqlist str2=init_strlist();  //�ഴ��һ���ռ�

    int key;
    printf("����������ҵ�key��");
    scanf("%d",&key);
    
    printf("˳����� %d �ڵ� %d λ\n",key,SeqSearch(str1, key)+1);     //��ǰ�ڣ�˳�����
    printf("ǰ��˳����� %d �ڵ� %d λ\n",key,SeqSearch_gai(str1, key)+1);    //��ǰ��
    
    printf("ѭ�������۰���� %d �ڵ� %d λ\n",key,BinSearch(str1, key)+1);    //ѭ�������۰����
    printf("�ݹ顪���۰���� %d �ڵ� %d λ\n",key,BinSearch1(str1, key, 0, str1.length)+1);   //�ݹ顪���۰����

    
    printf("\n�ֿ����:\n");
    
    KeyType k=46;  //�ֿ����Ҫ���ҵ�Ԫ��k
    SeqList R;     //����˳���
    IDX I;         //����������
    int i;
    init_Idxtype(R,I);   //��ʼ����������˳�����зֿ鴦��
    if((i=IdxSearch(I,5,R,25,k))!=-1)
        printf("\n�ֿ���� key=%d �ڵ� %d λ\n",k,i);
    else
        printf("\n�ֿ���� key=%d ���ڱ���\n",k);
    printf("\n");

    
}
/*
 
 ��������Ա��ȣ�ǰ�ڳ���+1����5
 ��������Ա�Ԫ�أ�
 1
 2
 3
 4
 5
 ����������ҵ�key��4
 ˳������ڵ� 4 λ
 ǰ��˳������ڵ� 4 λ
 ѭ�������۰�����ڵ� 4 λ
 �ݹ顪���۰�����ڵ� 4 λ
 
 �ֿ����:
 1.���ֲ���key����һ�ֿ飺
    �� key=46 ��������ĵ� 3 �ֿ���
 2.˳�����key�ڷֿ�ĵڼ�����
    �÷ֿ������Ϊ��40 38 54 66 46
    �� key=46 ��˳���ĵ� 14 λ

 �ֿ���� key=46 �ڵ� 14 λ
 
 */
