#include <stdio.h>
#include <string.h>
#define MaxSize 100

void mult_largenum(char A[], char B[])
{
    int i,j,num;
    int x=0;
    int m=(int)strlen(A);//（int）为类型强制转化，strlen(A)本为 char型 强制转为 int型
    int n=(int)strlen(B);
    //char result[m+n+1];//在vc6上不给这样写
	char result[MaxSize]; //直接给个大树组
    for(i=0;i<m+n;i++)  //初始化
        result[i]='0';
    
    for(i=m-1;i>=0;i--)
    {
        for(j=n-1;j>=0;j--)
        {
            num=(A[j]-48)*(B[i]-48);
            if(num<10)  //相同位次相乘 <10 的
            {
                result[x]=result[x]+num;
                if(result[x]-48>9)  //本位达到 10，下一位进 1
                {
                    result[x+1]++;  //下一位 进位
                    result[x]=result[x]-10;  //处理 本位
                }
            }
            else    //相同位次相乘 >10 的
            {
                result[x]=num%10+result[x];
                if(result[x]-48>9)  //本位达到 10，下一位进 1
                {
                    result[x+1]++;  //下一位 进位
                    result[x]=result[x]-10;  //处理 本位
                }
                result[x+1]=num/10+result[x+1];
                if(result[x+1]-48>9)  //本位达到 10，下一位进 1
                {
                    result[x+2]++;  //下一位 进位
                    result[x+1]=result[x+1]-10;   //处理 本位
                }
            }
            x++;
        }
        x=x-n+1;  //返回到 上一周期位次 的 下一位
    }
    printf("最终结果为：\n");
    for(i=m+n-1;i>=0;i--)
        printf("%c",result[i]);
    printf("\n");
}

int main()
{
    char A[MaxSize]="999999999999999999999999999";
    char B[MaxSize]="999999999999999999999999999";
    /*
    printf("输入第一个乘数：");
    scanf("%s",A);
    printf("输入第二个乘数：");
    scanf("%s",B);
    */
    mult_largenum(A, B);
	return 0;
}
/*
 输出：
 最终结果为：
 999999999999999999999999998000000000000000000000000001

A和B的位数最好要一样
不然会输出"烫烫烫烫"是因为vc会自动把未用函数的局部变量空间按字节全部初始化为CC
而定义的字符数组空间不够，所以就占用了那部分不属于自己的空间
因为输出char*是要遇到空字符才停止的，所以便把那些垃圾都打出来了
即是说在最后没有字符串结束标志'\0'
/*/

