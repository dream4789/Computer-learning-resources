#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define r 6//��
#define c 6//��

int *Compress(int arr_before[][c])
{//ѹ���洢
    int *arr_after = (int *)malloc(sizeof(int)*((c*(c+1))/2));
    int row=1;//��ά�����б�
    int a=0;//һά�����±�
    for(int m=0;m<r;m++)
    {
        for(int n=0;n<row;n++)
        {
            arr_after[a] = arr_before[m][n];
            a++;
        }
        row++;//��һ��
    }
    return arr_after;//����һά����
}
int arr_show(int *arr_after,int m,int n)
{//ѹ���������
    assert(m>=0&&m<r&&n>=0&&n<c);//���ԣ���������������ֱ���˳�����
    if(m>=n)//������
        return arr_after[(m*(m+1))/2+n];
    else//������
        return arr_after[(n*(n+1))/2+m];
}
int *Compress1(int arr_before[][c])
{//ѹ���洢
    int *arr_after = (int *)malloc(sizeof(int)*((c*(c+1))/2));
    int row=1;//��ά�����б�
    int a=0;//һά�����±�
    for(int m=0;m<r;m++)
    {
        for(int n=0;n<row;n++)
        {
            arr_after[a] = arr_before[m][n];
            a++;
        }
        row++;//��һ��
    }
    arr_after[(c*(c+1))/2]=0;//�����ǵ�ֵ
    return arr_after;//����һά����
}
int arr_show1(int *arr_after,int m,int n)
{//ѹ���������
    assert(m>=0&&m<r&&n>=0&&n<c);//���ԣ���������������ֱ���˳�����
    if(m>=n)//������
        return arr_after[(m*(m+1))/2+n];
    else//������
        return arr_after[(c*(c+1))/2];
}

int main()
{
	int m;
	//���Ǿ���
    int arr_before[r][c] = {
        {1, 0, 0, 0, 0, 0},
        {2, 2, 0, 0, 0, 0},
        {3, 3, 3, 0, 0, 0},
        {4, 4, 4, 3, 0, 0},
        {5, 4, 4, 3, 2, 0},
        {6, 5, 4, 3, 2, 1}
    };//�����Ƕ�Ϊ0
    int *arr_after=Compress1(arr_before);
    for(m=0;m<r;++m)
    {
        for(int n=0;n<c;n++)
            printf( "%d ",arr_show1(arr_after,m,n));
        printf("\n");
	}
	printf("\n");

	//�Գƾ���
    int arr_before1[r][c] = {
        {1, 2, 3, 4, 5, 6},
        {2, 2, 3, 4, 4, 5},
        {3, 3, 3, 4, 4, 4},
        {4, 4, 4, 3, 3, 3},
        {5, 4, 4, 3, 2, 2},
        {6, 5, 4, 3, 2, 1}
    };
    int *arr_after1=Compress(arr_before1);
    for(m=0;m<r;++m)
    {
        for(int n=0;n<c;n++)
            printf( "%d ",arr_show(arr_after1,m,n));
        putchar('\n');
    }
    return 0;
}
/*
 1 2 3 4 5 6
 2 2 3 4 4 5
 3 3 3 4 4 4
 4 4 4 3 3 3
 5 4 4 3 2 2
 6 5 4 3 2 1
 */