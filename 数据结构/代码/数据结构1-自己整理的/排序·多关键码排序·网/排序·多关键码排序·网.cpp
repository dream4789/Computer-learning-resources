#include <stdio.h>
#include <stdlib.h>

#define RADIX 101 //������������ 101 �ֿ���
#define K 3 //�ؼ��֣��� 3 ���ؼ���

struct tagMark
{
    int key[K]; //�� K ���ؼ���
}a[8]={
    {1,2,3},
    {0,2,3},
    {5,4,6},
    {6,2,6},
    {4,4,1},
    {0,1,4},
    {60,30,6},
    {60,20,6}};

/*
 a��������������ַ
 size��Ԫ������
 radix������
 k���ؼ�������
 */

void LSDSort(struct tagMark *a, int size,int k)
{//���λ����
    int i;
    struct tagMark *tmp=(struct tagMark *)malloc(sizeof(struct tagMark) *size); //������ļ�¼������
    while (k--)
    {
        int cnt[RADIX]={0};
        //����
        for(i=size;i>0;)
            ++cnt[a[--i].key[k]];
        //�ۼ�cnt
        for(i=0;i<RADIX;i++)
            cnt[i+1]+=cnt[i];
        //��˳���a[i]����tmp��
        for(i=size;i>0;)
        {
            --i;
            tmp[--cnt[a[i].key[k]]] = a[i];
        }
        //��a[i]����ĳһλ�źõ�����������
        for(i=size;i>0;)
        {
            --i;
            a[i] = tmp[i];
        }
    }
}

int main()
{
    int i, j;
    LSDSort(a, 8, K); //��8����¼��������
    for(i=0;i<8;i++)
    {
        for(j=0;j<K;j++)
            printf("%d ",a[i].key[j]);
        printf("\n");
    }
    return 0;
}
/*
�������в��ˣ���֪��Ϊʲô
�����
0 1 4 
0 2 3 
1 2 3 
4 4 1 
5 4 6 
6 2 6 
60 20 6 
60 30 6 
*/