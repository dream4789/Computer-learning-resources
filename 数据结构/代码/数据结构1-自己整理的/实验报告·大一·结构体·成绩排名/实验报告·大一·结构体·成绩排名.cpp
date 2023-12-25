#include <stdio.h>
#define num 5
struct student
{
    int number;
    char name[10];
    int math,Chinese,English;
    float average;
}stu[num];

void singlemax(struct student stu[])
{
    int i,m,c,e,j=0,k=0,l=0;
    m=stu[0].math;
    c=stu[0].Chinese;
    e=stu[0].English;
    for(i=0;i<num;i++)
    {
        if(m<stu[i].math)
        {
            j=i;
            m=stu[i].math;
        }
        if(e<stu[i].English)
        {
            k=i;
            e=stu[i].English;
        }
        if(c<stu[i].Chinese)
        {
            l=i;
            c=stu[i].Chinese;
        }
    }
    printf("\n数学成绩最高:%s  学号:%d  数学成绩:%d\n",stu[j].name,stu[j].number,stu[j].math);
    printf("语文成绩最高:%s  学号:%d  语文成绩:%d\n",stu[k].name,stu[k].number,stu[k].English);
    printf("英语成绩最高:%s  学号:%d  英语成绩:%d\n",stu[l].name,stu[l].number,stu[l].Chinese);
}

void allmax(struct student stu[])
{
    int i,t=0;
    float a;
    a=stu[0].average;
    for(i=0;i<num;i++)
    {
        if(a<stu[i].average)
        {
            t=i;
            a=stu[i].average;
        }
    }
    printf("\n平均成绩最高:%s  学号:%d  平均成绩:%.2lf\n\n",stu[t].name,stu[t].number,stu[t].average);
}

void sort(struct student stu[])
{
    struct student t;
    int i,j;
	float a;
    a=stu[0].average;
    for(i=0;i<num-1;i++)
    {
        for(j=i+1;j<num;j++)
        {
            if(stu[i].average<stu[j].average)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
    }
    printf("%-8s%-6s%-6s%-9s%-9s%-9s\n","number","name","math","Chinese","English","average");
    for(i=0;i<num;i++)
        printf("%-8d%-6s%-6d%-9d%-9d%-9.2lf\n",stu[i].number,stu[i].name,stu[i].math,stu[i].Chinese,stu[i].English,stu[i].average);
}

int main()
{
    int i,j;
    for(i=0,j=1;i<num;i++,j++)
    {
        printf("输入第 %d 位学生学号：",j);
        scanf("%d",&stu[i].number);
        printf("输入第 %d 位学生姓名：",j);
        getchar();
        gets(stu[i].name);
        printf("输入第 %d 位学生 数学 语文 英语 的成绩：",j);
        scanf("%d %d %d",&stu[i].math,&stu[i].Chinese,&stu[i].English);
        stu[i].average=(stu[i].math+stu[i].Chinese+stu[i].English)/3.0;
    }
    singlemax(stu);
    allmax(stu);
    sort(stu);
	return 0;
}
/*
 输入第 1 位学生学号：1001
 输入第 1 位学生姓名：banban
 输入第 1 位学生 数学 语文 英语 的成绩：120 121 122
 输入第 2 位学生学号：1002
 输入第 2 位学生姓名：huahua
 输入第 2 位学生 数学 语文 英语 的成绩：112 132 110
 输入第 3 位学生学号：1003
 输入第 3 位学生姓名：yueyue
 输入第 3 位学生 数学 语文 英语 的成绩：132 113 127
 输入第 4 位学生学号：1004
 输入第 4 位学生姓名：caicai
 输入第 4 位学生 数学 语文 英语 的成绩：131 125 132
 输入第 5 位学生学号：1005
 输入第 5 位学生姓名：mei
 输入第 5 位学生 数学 语文 英语 的成绩：142 137 141

 数学成绩最高:mei  学号:1005  数学成绩:142
 语文成绩最高:mei  学号:1005  语文成绩:141
 英语成绩最高:mei  学号:1005  英语成绩:137

 平均成绩最高:mei  学号:1005  平均成绩:140.00

 number  name  math  Chinese  English  average
 1005    mei   142   137      141      140.00
 1004    caicai131   125      132      129.33
 1003    yueyue132   113      127      124.00
 1001    banban120   121      122      121.00
 1002    huahua112   132      110      118.00
 */