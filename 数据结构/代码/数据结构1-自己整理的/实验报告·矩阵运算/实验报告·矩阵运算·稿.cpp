#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100

typedef struct
{
    int line,row;        //lineΪ��,rowΪ��
    int data[MAXSIZE];
}Matrix;

//�����ʼ������ֵ
Matrix initMatrix(void)
{
    Matrix *matrix=(Matrix *)malloc(sizeof(Matrix));
    printf("��������������������");
    scanf("%d %d",&matrix->line,&matrix->row);
    printf("�������Ԫ�أ�");
    for(int i=0;i<matrix->line*matrix->row;i++)
        scanf("%d",&matrix->data[i]);
    return *matrix;
}
//��ӡ����
void PrintMatrix(Matrix *matrix)
{
    for(int i=0 ; i<matrix->line*matrix->row ; i++)
    {
        printf("%4d", matrix->data[i]);
        if((i+1)%matrix->row == 0)
            printf("\n");
    }
}
//����Ӽ���
Matrix jisuanMatrix(Matrix *matrix1,Matrix *matrix2,int muo)
{
    Matrix *matrix3=(Matrix *)malloc(sizeof(Matrix));
    matrix3->line=matrix1->line;
    matrix3->row=matrix1->row;
    
    for(int i=0 ; i < matrix1->line*matrix1->row ; i++)
    {
        if(muo==0)  //��0 ���
            matrix3->data[i]=matrix1->data[i]+matrix2->data[i];
        else        //��1 ���
            matrix3->data[i]=matrix1->data[i]-matrix2->data[i];
    }
    PrintMatrix(matrix3);
    return *matrix3;
}
//����˷�
Matrix mulMatrix(Matrix *matrix1,Matrix *matrix2)
{
    Matrix *matrix3=(Matrix *)malloc(sizeof(Matrix));
    matrix3->line=matrix1->line;
    matrix3->row=matrix2->row;
    int m=0,n=0;  //mΪ����2��������nΪ����1��������
    for(int i=0 ; i < matrix1->line*matrix2->row ; i++)  //��ѭ����iΪ�������±�
    {
        matrix3->data[i]=0;  //�ڸ�ֵ������Ԫ��ǰ����ʼ��ÿ��Ԫ��Ϊ0
        int k=0;
        if(m == matrix2->row)  //ÿ������2��һ�г��꣬m���㣬����1����һ��
        {
            m=0;
            n+=matrix1->row;
        }
        for(int j=0; j<matrix1->row ; j++)
        {
            matrix3->data[i]+=matrix1->data[j+n]*matrix2->data[k+m];
            k+=matrix2->row;  //����2ͬ�л��г�
        }
        m++;
    }
    PrintMatrix(matrix3);
    return *matrix3;
}
//�����û�
Matrix TransMatrix(Matrix *matrix)
{
    Matrix *matrix1=(Matrix *)malloc(sizeof(Matrix));
    matrix1->line=matrix->row;
    matrix1->row=matrix->line;
    int m=0,n=0,k=0;
    for(int i=0;i<matrix1->row*matrix1->line;i++)   //��ѭ����iΪ�������±�
    {
        if(n==matrix->line)  //ԭ�����һ��ȫ�����õ�����1�е�һ�У�ִ��
        {
            k=0;
            m++;
            n=0;
        }
        matrix1->data[i]=matrix->data[k+m];
        k+=matrix->row;
        n++;
    }
    PrintMatrix(matrix1);
    return *matrix1;
}


int main()
{
    Matrix matrix1 = initMatrix();
    Matrix matrix2 = initMatrix();

    printf("����1Ϊ��\n");
    PrintMatrix(&matrix1);
    printf("����2Ϊ��\n");
    PrintMatrix(&matrix2);
    
    if(matrix1.row==matrix2.row && matrix1.line==matrix2.line)
    {
        printf("����һ �� ����� ���Ϊ��\n");
        jisuanMatrix(&matrix1,&matrix2, 0);
        
        printf("����һ �� ����� ���Ϊ��\n");
        jisuanMatrix(&matrix1,&matrix2, 1);
    }
    else
        printf("�����������������������Ӧ���޷�����Ӽ���\n");
    if(matrix1.row==matrix2.line)
    {
        printf("����һ �� ����� ���Ϊ��\n");
        mulMatrix(&matrix1, &matrix2);
    }
    else
        printf("�����������������������Ӧ���޷�����˷���\n");
    printf("����һ ���û�Ϊ��\n");
    TransMatrix(&matrix1);
    return 0;
}
/*
 
 3 3    1 2 3 4 5 6 7 8 9
 3 3    9 8 7 6 5 4 3 2 1
 
 3 4    1 2 3 4 5 6 7 8 9 10 11 12
 4 3    12 11 10 9 8 7 6 5 4 3 2 1
 
 ��������������������3 3
 �������Ԫ�أ�1 2 3 4 5 6 7 8 9
 ��������������������3 3
 �������Ԫ�أ�9 8 7 6 5 4 3 2 1
 ����1Ϊ��
    1   2   3
    4   5   6
    7   8   9
 ����2Ϊ��
    9   8   7
    6   5   4
    3   2   1
 ����һ �� ����� ���Ϊ��
   10  10  10
   10  10  10
   10  10  10
 ����һ �� ����� ���Ϊ��
   -8  -6  -4
   -2   0   2
    4   6   8
 ����һ �� ����� ���Ϊ��
   30  24  18
   84  69  54
  138 114  90
 ����һ ���û�Ϊ��
    1   4   7
    2   5   8
    3   6   9
 
 ��������������������3 4
 �������Ԫ�أ�1 2 3 4 5 6 7 8 9 10 11 12
 ��������������������4 3
 �������Ԫ�أ�12 11 10 9 8 7 6 5 4 3 2 1
 ����1Ϊ��
    1   2   3   4
    5   6   7   8
    9  10  11  12
 ����2Ϊ��
   12  11  10
    9   8   7
    6   5   4
    3   2   1
 ����һ �� ����� ���Ϊ��
   48  42  36
  129 114  99
  210 186 162
 ����һ ���û�Ϊ��
    1   5   9
    2   6  10
    3   7  11
    4   8  12
 */