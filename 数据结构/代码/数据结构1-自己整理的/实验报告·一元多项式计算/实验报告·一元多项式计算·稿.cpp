#include <stdio.h>
#include <stdlib.h>
typedef struct Polyn
{
    int coeff;   //系数
    int power;   //幂次
    struct Polyn *next;
}Polyn,*Polynomial;

Polynomial InitPolyn(void)
{
    int num;
    Polynomial p=(Polynomial)malloc(sizeof(Polyn));
    Polynomial q=p;  //保存头结点
    printf("输入多项式的项数：");
    scanf("%d",&num);
    printf("输入多项式的系数和对应幂次：\n");
    for(int i=0;i<num;i++)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        scanf("%d %d",&p->coeff,&p->power);
    }
    p->next=NULL;
    return q->next;  //直接返回一个指向第一个值的指针
}

Polynomial InitPolyn1(void)
{
    //int a[4]={7,3,9,5};   //数据组1
    //int b[4]={0,1,8,17}; //数据组2
    int a[4]={1,-1,1,2};
    int b[4]={0,1,2,3};
    Polynomial p=(Polynomial)malloc(sizeof(Polyn));
    Polynomial q=p;  //保存头结点
    for(int i=0;i<4;i++)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        p->coeff=a[i];
        p->power=b[i];
    }
    p->next=NULL;
    return q->next;  //直接返回一个指向第一个值的指针
}
Polynomial InitPolyn2(void)
{
    //int a[3]={8,22,-9};  //数据组1
    //int b[3]={1,7,8};
    int a[3]={-1,1,-1}; //数据组2
    int b[3]={0,1,3};
    Polynomial p=(Polynomial)malloc(sizeof(Polyn));
    Polynomial q=p;  //保存头结点
    for(int i=0;i<3;i++)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        p->coeff=a[i];
        p->power=b[i];
    }
    p->next=NULL;
    return q->next;  //直接返回一个指向第一个值的指针
}

void PrintPolyn1(Polynomial p)
{//输出1看的更加清晰，2可能行数会少一些
    int count=0;  //判断是否为第一个
    while (p)
    {
        if(p->power==0)
        {  //幂次为0
            printf("%d ",p->coeff);  //零次幂第一次
            count++;
            p=p->next;
        }
        if(p->power==1)
        {  //幂次为1
            if(p->coeff == 1)
            {
                if(count==0)
                {
                    printf("x ");  //一次幂第一次
                    count++;
                }
                else
                    printf("+x ");
            }
            else if (p->coeff == -1)
                printf("-x ");
            else
            {
                if(count==0)
                {
                    printf("%dx ",p->coeff);  //一次幂第一次
                    count++;
                }
                else
                    printf("%+dx ",p->coeff);
            }
            p = p->next;
        }
        else
        {  //更高幂次
            if(p->coeff == 1)
            {
                if(count==0)
                {
                    printf("x^%d ",p->power);  //高次幂第一次
                    count++;
                }
                else
                    printf("+x^%d ",p->power);
            }
            else if (p->coeff == -1)
                printf("-x^%d ",p->power);
            else
            {
                if(count==0)
                {
                    printf("%dx^%d ",p->coeff,p->power);  //高次幂第一次
                    count++;
                }else
                    printf("%+dx^%d ",p->coeff,p->power);
            }
            p = p->next;
        }
    }
    printf("\n");
}
Polynomial copyPolyn(Polynomial p2)
{
    Polynomial p1=(Polynomial)malloc(sizeof(Polyn));
    Polynomial p=p1;
    while (p2)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        p->coeff=p2->coeff;
        p->power=p2->power;
        p2=p2->next;
    }
    p->next=NULL;
    //PrintPolyn1(p1->next);   //分析行
    return p1->next;  //直接返回一个指向第一个值的指针
}

void PrintPolyn2(Polynomial p)
{//输出和1一样，只是化简一些
    int count=0;  //判断是否为第一个
    while (p)
    {
        if(p->power==0)  //幂次为0
        {
            printf("%d ",p->coeff);  //零次幂 第一次
            count++;
            p=p->next;
        }
        if(p->power==1)  //幂次为1
        {
            if(p->coeff == 1)
            {
                if(count==0) {printf("x ");count++;}  //一次幂 第一次
                else          printf("+x ");
            }
            else if (p->coeff == -1) printf("-x ");
            else
            {
                if(count==0) {printf("%dx ",p->coeff);count++;}  //一次幂 第一次
                else          printf("%+dx ",p->coeff);
            }
            p = p->next;
        }
        else            //更高幂次
        {
            if(p->coeff == 1)
            {
                if(count==0) {printf("x^%d ",p->power);count++;}  //高次幂 第一次
                else          printf("+x^%d ",p->power);
            }
            else if (p->coeff == -1) printf("-x^%d ",p->power);
            else
            {
                if(count==0) {printf("%dx^%d ",p->coeff,p->power);count++;}  //高次幂 第一次
                else          printf("%+dx^%d ",p->coeff,p->power);
            }
            p = p->next;
        }
    }
    printf("\n");
}
//加法
Polynomial AddPolyn(Polynomial p1,Polynomial p2)
{
    Polynomial p3=(Polynomial)malloc(sizeof(Polyn));
    Polynomial p=p3;  //保存头结点
    while (p1 && p2)
    {
        if(p1->power < p2->power)
        {
            p3->next=(Polynomial)malloc(sizeof(Polyn));
            p3=p3->next;
            p3->coeff=p1->coeff;
            p3->power=p1->power;
            p1=p1->next;
        }
        else if(p1->power > p2->power)
        {
            p3->next=(Polynomial)malloc(sizeof(Polyn));
            p3=p3->next;
            p3->coeff=p2->coeff;
            p3->power=p2->power;
            p2=p2->next;
        }
        else
        {
            if(p1->coeff+p2->coeff!=0)
            {
                p3->next=(Polynomial)malloc(sizeof(Polyn));
                p3=p3->next;
                p3->coeff=p1->coeff+p2->coeff;
                p3->power=p1->power;
            }
            p1=p1->next;
            p2=p2->next;
        }
    }
    while(p1)
    {
        p3->next=(Polynomial)malloc(sizeof(Polyn));
        p3=p3->next;
        p3->coeff=p1->coeff;
        p3->power=p1->power;
        p1=p1->next;
    }
    while(p2)
    {
        p3->next=(Polynomial)malloc(sizeof(Polyn));
        p3=p3->next;
        p3->coeff=p2->coeff;
        p3->power=p2->power;
        p2=p2->next;
    }
    p3->next=NULL;
    //PrintPolyn1(p->next);  //分析行
    return p->next;  //直接返回一个指向第一个值的指针
}
//减法
Polynomial SubPolyn(Polynomial p1,Polynomial p2)
{
    Polynomial p=p2,q=NULL;
    while (p)
    {
        p->coeff=-(p->coeff);  //变负
        p=p->next;
    }
    q=AddPolyn(p1, p2);
    //PrintPolyn1(p);   //分析行
    return q;  //直接返回一个指向第一个值的指针
}
//乘法
Polynomial MulPolyn(Polynomial p1,Polynomial p2)
{
    Polynomial p3=(Polynomial)malloc(sizeof(Polyn));  //结果域
    Polynomial p4=(Polynomial)malloc(sizeof(Polyn));  //辅助域
    Polynomial p=p1;   //保存头结点
    Polynomial pn=p4;  //保存头结点
    int i=0;
    while(p2)
    {
        pn=p4;  //p4重来
        p1=p;  //p1重来
        while(p1)
        {
            if(i==0)
                pn->next=(Polynomial)malloc(sizeof(Polyn));  //运行一趟
            //printf("(%d %d)\n",pn->coeff,pn->power);  //分析行
            pn=pn->next;
            pn->coeff=p1->coeff*p2->coeff;  //系数
            pn->power=p1->power+p2->power;  //幂次
            p1=p1->next;
            //printf("[%d %d]\n",pn->coeff,pn->power);  //分析行
        }
        pn->next=NULL;
        //printf("/");
        //PrintPolyn1(pn);
        //printf("//");
        if(i==0)
            p3=copyPolyn(p4->next);  //拷贝，p3变为指向第一个值的指针，运行一趟
        else
        {
            //PrintPolyn1(pn);  //分析行
            p3=AddPolyn(p3, p4->next);
        }
        //printf("///");
        p2=p2->next;  //p2向后移一位
        i++;
    }
    return p3;   //直接返回一个指向第一个值的指针
}

int main()
{
    printf("按升幂输入多项式A(x),B(x)的系数\n");
    //Polynomial p1=InitPolyn();  //p1指向第一个值的指针
    //Polynomial p2=InitPolyn();  //p2指向第一个值的指针
    
    Polynomial p1=InitPolyn1();  //p1指向第一个值的指针，简化输入
    Polynomial p2=InitPolyn2();  //p2指向第一个值的指针，简化输入
    Polynomial p3 = NULL;  //辅助结点
    
    printf("A(x)=");
    PrintPolyn1(p1);  //打印从指向第一个值的指针打印
    
    printf("B(x)=");
    PrintPolyn1(p2);

    printf("1.多项式相加\n");
    printf("C(x)=");
    p3=AddPolyn(p1,p2);
    PrintPolyn1(p3);
    
    printf("2.多项式相减\n");
    printf("D(x)=");
    p3=copyPolyn(p2);  //拷贝一份，防止被覆盖掉。拷贝从指向第一个值的指针开始拷贝
    //PrintPolyn1(p3);    //分析行
    p3=SubPolyn(p1,p3);
    PrintPolyn1(p3);
    
    printf("3.多项式相乘\n");
    printf("E(x)=");
    p3=MulPolyn(p1,p2);
    PrintPolyn1(p3);
    
    return 0;
}
/*
数据1:
4
1 0
-1 1
1 2
2 3
 
3
-1 0
1 1
-1 3
数据2：
4
7 0
3 1
9 8
5 17
 
3
8 1
22 7
-9 8

  以下是输出：

 按升幂输入多项式A(x),B(x)的系数
 输入多项式的项数：4
 输入多项式的系数和对应幂次：
 1 0
 -1 1
 1 2
 2 3
 输入多项式的项数：3
 输入多项式的系数和对应幂次：
 -1 0
 1 1
 -1 3
 A(x)=1 -x +x^2 +2x^3
 B(x)=-1 +x -x^3
 1.多项式相加
 C(x)=x^2 +x^3
 2.多项式相减
 D(x)=2 -2x +x^2 +3x^3
 3.多项式相乘
 E(x)=-1 +2x -2x^2 -2x^3 +3x^4 -x^5 -2x^6
 
 按升幂输入多项式A(x),B(x)的系数
 输入多项式的项数：4
 输入多项式的系数和对应幂次：
 7 0
 3 1
 9 8
 5 17
 输入多项式的项数：3
 输入多项式的系数和对应幂次：
 8 1
 22 7
 -9 8
 A(x)=7 +3x +9x^8 +5x^17
 B(x)=8x +22x^7 -9x^8
 1.多项式相加
 C(x)=7 +11x +22x^7 +5x^17
 2.多项式相减
 D(x)=7 -5x -22x^7 +18x^8 +5x^17
 3.多项式相乘
 E(x)=56x +24x^2 +154x^7 +3x^8 +45x^9 +198x^15 -81x^16 +40x^18 +110x^24 -45x^25
 
*/
