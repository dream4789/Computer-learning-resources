#include <stdio.h>

int count = 0;
int queen[8][8]={0};

int find(int row,int col)
{
    int i,k;
    for(i=0;i<8;i++)  // �ж��з���
        if(queen[i][col]==1)
            return 0;
    for(i=row,k=col;i>=0&&k>=0;i--,k--)  // �ж���Խ���(\)
        if(queen[i][k]==1)
            return 0;
    for(i=row,k=col;i>=0&&k<8;i--,k++ )  // �ж��ҶԽ���(/)
        if(queen[i][k]==1)
            return 0;
    return 1;
}

void show(void)  //��ӡ���
{
    int row,col;
    printf("�� %d ��\n", count+1);
    for(row=0;row<8;row++)
    {
        for(col=0;col<8;col++)
            printf("%d ",queen[row][col]);
        printf("\n");
    }
    printf("\n");
}

void Eight_Queen(int row)
{
    int col;
    if(row==8)    //�����������ж��ҵ����ûʺ��λ�����ӡ
    {
        show();    //��ӡ�˻ʺ�Ľ�
        count++;
        return ;
    }
    for(col=0;col<8;col++)   //���ݣ��ݹ�
    {
        if(find(row,col))    //�ж��Ƿ�Σ��
        {
            queen[row][col]=1;
            Eight_Queen(row+1);
            queen[row][col]=0;    //����
        }
    }
}

int main()
{
    Eight_Queen(0);
    return 0;
}
//һ��92��
//���ֻչʾ����������㡰���С��󣬳������п��ڿ����һ�����������ԡ����ҵ������֡�,���ڡ���Ļ����߶ȡ�Ϊ1000�Ϳ�����
