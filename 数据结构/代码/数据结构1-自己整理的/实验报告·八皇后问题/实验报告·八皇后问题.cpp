#include <stdio.h>

int count = 0;
int queen[8][8]={0};

int find(int row,int col)
{
    int i,k;
    for(i=0;i<8;i++)  // 判断列方向
        if(queen[i][col]==1)
            return 0;
    for(i=row,k=col;i>=0&&k>=0;i--,k--)  // 判断左对角线(\)
        if(queen[i][k]==1)
            return 0;
    for(i=row,k=col;i>=0&&k<8;i--,k++ )  // 判断右对角线(/)
        if(queen[i][k]==1)
            return 0;
    return 1;
}

void show(void)  //打印结果
{
    int row,col;
    printf("第 %d 种\n", count+1);
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
    if(row==8)    //如果遍历完八行都找到放置皇后的位置则打印
    {
        show();    //打印八皇后的解
        count++;
        return ;
    }
    for(col=0;col<8;col++)   //回溯，递归
    {
        if(find(row,col))    //判断是否危险
        {
            queen[row][col]=1;
            Eight_Queen(row+1);
            queen[row][col]=0;    //清零
        }
    }
}

int main()
{
    Eight_Queen(0);
    return 0;
}
//一共92种
//如果只展示部分输出，点“运行”后，出现运行框，在框上右击，点击“属性”，找到“布局“,调节”屏幕缓冲高度”为1000就可以了
