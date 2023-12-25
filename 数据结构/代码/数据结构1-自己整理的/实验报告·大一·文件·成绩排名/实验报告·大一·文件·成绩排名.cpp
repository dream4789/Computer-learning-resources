#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct student {
    int num;
    int math;
    int English;
    int Chinese;
    double average;
    char name[20];
}Stu;

FILE *fp1,*fp2;
Stu stu[N];

void input(void)
{
    Stu stu[N];
    int i;
    printf("请依次输入10个同学的信息：学号 姓名 数学 英语 语文 成绩:\n");
    for(i=0;i<N;i++)
    {
        scanf("%d %s %d %d %d", &stu[i].num,stu[i].name,&stu[i].math,&stu[i].English,&stu[i].Chinese);
        stu[i].average=(stu[i].math+stu[i].English+stu[i].Chinese)/3.0;
    }
    if((fp1=fopen("stud.txt","w"))==NULL)
    {
        printf("文件打开失败!\n");
        exit(0);
    }
    for(i=0;i<N;i++)
        if(fwrite(&stu[i],sizeof(struct student),1,fp1)!=1)
            printf("信息写入失败!\n");
    fprintf(fp1,"%-8s%-6s%-6s%-9s%-9s%-9s\n","number","name","math","English","Chinese","average");
    for(i=0;i<N;i++)
        fprintf(fp1,"%-8d%-6s%-6d%-9d%-9d%-9.2lf\n",stu[i].num,stu[i].name,stu[i].math,stu[i].English,stu[i].Chinese,stu[i].average);
    fclose(fp1);
}

void output(void)
{
    int i;
    if((fp1=fopen("stud.txt","r"))==NULL)
    {
        printf("文件打开失败\n");
        exit(0);
    }
    for(i=0;i<N;i++)
        if(fread(&stu[i],sizeof(struct student),1,fp1)!=1)
        {
            if(feof(fp1))break;
                printf("FILE read error!\n");
        }
    fprintf(fp1,"排序前\n%-8s%-6s%-6s%-9s%-9s%-9s\n","number","name","math","English","Chinese","average");
    for(i=0;i<N;i++)
        fprintf(fp1,"%-8d%-6s%-6d%-9d%-9d%-9.2lf\n",stu[i].num,stu[i].name,stu[i].math,stu[i].English,stu[i].Chinese,stu[i].average);
    fclose(fp1);
    
    printf("排序前\n%-8s%-6s%-6s%-9s%-9s%-9s\n","number","name","math","English","Chinese","average");
    for(i=0;i<N;i++)
        printf("%-8d%-6s%-6d%-9d%-9d%-9.2lf\n",stu[i].num,stu[i].name,stu[i].math,stu[i].English,stu[i].Chinese,stu[i].average);
    printf("\n");
}

void sort(void)
{
    struct student t;
    int i,a,j;
    if((fp1=fopen("stud.txt","r")) == NULL)
    {
        printf("文件打开失败\n");
        exit(0);
    }
    for(i=0;i<N;i++)
    {
        if(fread(&stu[i],sizeof(struct student),1,fp1)!=1)
        {
             if(feof(fp1))break;
                 printf("信息写入失败!\n");
        }
    }
    fclose(fp1);
    a=stu[0].average;
    for(i=0;i<N;i++)
    {
        for(j=i+1;j<N;j++)
        {
            if(stu[i].average<stu[j].average)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
    }
    if ((fp2=fopen("studsort.txt","w"))==NULL)
    {
        printf("文件打开失败\n");
        exit(0);
    }
    fprintf(fp2,"排序后\n%-8s%-6s%-6s%-9s%-9s%-9s\n","number","name","math","English","Chinese","average");
    for(i=0;i<N;i++)
        fprintf(fp2,"%-8d%-6s%-6d%-9d%-9d%-9.2lf\n",stu[i].num,stu[i].name,stu[i].math,stu[i].English,stu[i].Chinese,stu[i].average);
    fclose(fp2);
    
    printf("排序后\n%-8s%-6s%-6s%-9s%-9s%-9s\n","number","name","math","English","Chinese","average");
    for(i=0;i<N;i++)
        printf("%-8d%-6s%-6d%-9d%-9d%-9.2lf\n",stu[i].num,stu[i].name,stu[i].math,stu[i].English,stu[i].Chinese,stu[i].average);
    printf("\n");
}

int main()
{
    input();
    output();
    sort();
    
    return 0;
}

/*
101 a 89 95 92
102 b 96 87 78
103 c 70 98 93
104 d 79 86 78
105 e 93 90 78
106 f 80 90 79
107 g 88 75 83
108 h 81 91 73
109 i 92 79 87
110 j 91 82 80
 
 请依次输入10个同学的信息：学号 姓名 数学 英语 语文 成绩:
 101 a 89 95 92
 102 b 96 87 78
 103 c 70 98 93
 104 d 79 86 78
 105 e 93 90 78
 106 f 80 90 79
 107 g 88 75 83
 108 h 81 91 73
 109 i 92 79 87
 110 j 91 82 80
 排序前
 number  name  math  English  Chinese  average
 101     a     89    95       92       92.00
 102     b     96    87       78       87.00
 103     c     70    98       93       87.00
 104     d     79    86       78       81.00
 105     e     93    90       78       87.00
 106     f     80    90       79       83.00
 107     g     88    75       83       82.00
 108     h     81    91       73       81.67
 109     i     92    79       87       86.00
 110     j     91    82       80       84.33

 排序后
 number  name  math  English  Chinese  average
 101     a     89    95       92       92.00
 102     b     96    87       78       87.00
 103     c     70    98       93       87.00
 105     e     93    90       78       87.00
 109     i     92    79       87       86.00
 110     j     91    82       80       84.33
 106     f     80    90       79       83.00
 107     g     88    75       83       82.00
 108     h     81    91       73       81.67
 104     d     79    86       78       81.00
 */