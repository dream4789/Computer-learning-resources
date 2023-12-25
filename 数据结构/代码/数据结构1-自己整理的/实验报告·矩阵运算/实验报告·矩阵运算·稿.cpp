#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100

typedef struct
{
    int line,row;        //line为行,row为列
    int data[MAXSIZE];
}Matrix;

//矩阵初始化，赋值
Matrix initMatrix(void)
{
    Matrix *matrix=(Matrix *)malloc(sizeof(Matrix));
    printf("输入矩阵的行数和列数：");
    scanf("%d %d",&matrix->line,&matrix->row);
    printf("输入矩阵元素：");
    for(int i=0;i<matrix->line*matrix->row;i++)
        scanf("%d",&matrix->data[i]);
    return *matrix;
}
//打印矩阵
void PrintMatrix(Matrix *matrix)
{
    for(int i=0 ; i<matrix->line*matrix->row ; i++)
    {
        printf("%4d", matrix->data[i]);
        if((i+1)%matrix->row == 0)
            printf("\n");
    }
}
//矩阵加减法
Matrix jisuanMatrix(Matrix *matrix1,Matrix *matrix2,int muo)
{
    Matrix *matrix3=(Matrix *)malloc(sizeof(Matrix));
    matrix3->line=matrix1->line;
    matrix3->row=matrix1->row;
    
    for(int i=0 ; i < matrix1->line*matrix1->row ; i++)
    {
        if(muo==0)  //输0 相加
            matrix3->data[i]=matrix1->data[i]+matrix2->data[i];
        else        //输1 相减
            matrix3->data[i]=matrix1->data[i]-matrix2->data[i];
    }
    PrintMatrix(matrix3);
    return *matrix3;
}
//矩阵乘法
Matrix mulMatrix(Matrix *matrix1,Matrix *matrix2)
{
    Matrix *matrix3=(Matrix *)malloc(sizeof(Matrix));
    matrix3->line=matrix1->line;
    matrix3->row=matrix2->row;
    int m=0,n=0;  //m为数组2增量服务，n为数组1增量服务
    for(int i=0 ; i < matrix1->line*matrix2->row ; i++)  //大循环，i为新数组下标
    {
        matrix3->data[i]=0;  //在赋值新数组元素前，初始化每个元素为0
        int k=0;
        if(m == matrix2->row)  //每当数组2的一列乘完，m归零，数组1换下一行
        {
            m=0;
            n+=matrix1->row;
        }
        for(int j=0; j<matrix1->row ; j++)
        {
            matrix3->data[i]+=matrix1->data[j+n]*matrix2->data[k+m];
            k+=matrix2->row;  //矩阵2同列换行乘
        }
        m++;
    }
    PrintMatrix(matrix3);
    return *matrix3;
}
//矩阵置换
Matrix TransMatrix(Matrix *matrix)
{
    Matrix *matrix1=(Matrix *)malloc(sizeof(Matrix));
    matrix1->line=matrix->row;
    matrix1->row=matrix->line;
    int m=0,n=0,k=0;
    for(int i=0;i<matrix1->row*matrix1->line;i++)   //大循环，i为新数组下标
    {
        if(n==matrix->line)  //原矩阵的一列全部放置到矩阵1中的一行，执行
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

    printf("矩阵1为：\n");
    PrintMatrix(&matrix1);
    printf("矩阵2为：\n");
    PrintMatrix(&matrix2);
    
    if(matrix1.row==matrix2.row && matrix1.line==matrix2.line)
    {
        printf("矩阵一 和 矩阵二 相加为：\n");
        jisuanMatrix(&matrix1,&matrix2, 0);
        
        printf("矩阵一 和 矩阵二 相减为：\n");
        jisuanMatrix(&matrix1,&matrix2, 1);
    }
    else
        printf("两个矩阵的行数或列数不对应，无法计算加减！\n");
    if(matrix1.row==matrix2.line)
    {
        printf("矩阵一 和 矩阵二 相乘为：\n");
        mulMatrix(&matrix1, &matrix2);
    }
    else
        printf("两个矩阵的行数或列数不对应，无法计算乘法！\n");
    printf("矩阵一 的置换为：\n");
    TransMatrix(&matrix1);
    return 0;
}
/*
 
 3 3    1 2 3 4 5 6 7 8 9
 3 3    9 8 7 6 5 4 3 2 1
 
 3 4    1 2 3 4 5 6 7 8 9 10 11 12
 4 3    12 11 10 9 8 7 6 5 4 3 2 1
 
 输入矩阵的行数和列数：3 3
 输入矩阵元素：1 2 3 4 5 6 7 8 9
 输入矩阵的行数和列数：3 3
 输入矩阵元素：9 8 7 6 5 4 3 2 1
 矩阵1为：
    1   2   3
    4   5   6
    7   8   9
 矩阵2为：
    9   8   7
    6   5   4
    3   2   1
 矩阵一 和 矩阵二 相加为：
   10  10  10
   10  10  10
   10  10  10
 矩阵一 和 矩阵二 相减为：
   -8  -6  -4
   -2   0   2
    4   6   8
 矩阵一 和 矩阵二 相乘为：
   30  24  18
   84  69  54
  138 114  90
 矩阵一 的置换为：
    1   4   7
    2   5   8
    3   6   9
 
 输入矩阵的行数和列数：3 4
 输入矩阵元素：1 2 3 4 5 6 7 8 9 10 11 12
 输入矩阵的行数和列数：4 3
 输入矩阵元素：12 11 10 9 8 7 6 5 4 3 2 1
 矩阵1为：
    1   2   3   4
    5   6   7   8
    9  10  11  12
 矩阵2为：
   12  11  10
    9   8   7
    6   5   4
    3   2   1
 矩阵一 和 矩阵二 相乘为：
   48  42  36
  129 114  99
  210 186 162
 矩阵一 的置换为：
    1   5   9
    2   6  10
    3   7  11
    4   8  12
 */