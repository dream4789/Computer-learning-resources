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
    printf("\n��ѧ�ɼ����:%s  ѧ��:%d  ��ѧ�ɼ�:%d\n",stu[j].name,stu[j].number,stu[j].math);
    printf("���ĳɼ����:%s  ѧ��:%d  ���ĳɼ�:%d\n",stu[k].name,stu[k].number,stu[k].English);
    printf("Ӣ��ɼ����:%s  ѧ��:%d  Ӣ��ɼ�:%d\n",stu[l].name,stu[l].number,stu[l].Chinese);
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
    printf("\nƽ���ɼ����:%s  ѧ��:%d  ƽ���ɼ�:%.2lf\n\n",stu[t].name,stu[t].number,stu[t].average);
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
        printf("����� %d λѧ��ѧ�ţ�",j);
        scanf("%d",&stu[i].number);
        printf("����� %d λѧ��������",j);
        getchar();
        gets(stu[i].name);
        printf("����� %d λѧ�� ��ѧ ���� Ӣ�� �ĳɼ���",j);
        scanf("%d %d %d",&stu[i].math,&stu[i].Chinese,&stu[i].English);
        stu[i].average=(stu[i].math+stu[i].Chinese+stu[i].English)/3.0;
    }
    singlemax(stu);
    allmax(stu);
    sort(stu);
	return 0;
}
/*
 ����� 1 λѧ��ѧ�ţ�1001
 ����� 1 λѧ��������banban
 ����� 1 λѧ�� ��ѧ ���� Ӣ�� �ĳɼ���120 121 122
 ����� 2 λѧ��ѧ�ţ�1002
 ����� 2 λѧ��������huahua
 ����� 2 λѧ�� ��ѧ ���� Ӣ�� �ĳɼ���112 132 110
 ����� 3 λѧ��ѧ�ţ�1003
 ����� 3 λѧ��������yueyue
 ����� 3 λѧ�� ��ѧ ���� Ӣ�� �ĳɼ���132 113 127
 ����� 4 λѧ��ѧ�ţ�1004
 ����� 4 λѧ��������caicai
 ����� 4 λѧ�� ��ѧ ���� Ӣ�� �ĳɼ���131 125 132
 ����� 5 λѧ��ѧ�ţ�1005
 ����� 5 λѧ��������mei
 ����� 5 λѧ�� ��ѧ ���� Ӣ�� �ĳɼ���142 137 141

 ��ѧ�ɼ����:mei  ѧ��:1005  ��ѧ�ɼ�:142
 ���ĳɼ����:mei  ѧ��:1005  ���ĳɼ�:141
 Ӣ��ɼ����:mei  ѧ��:1005  Ӣ��ɼ�:137

 ƽ���ɼ����:mei  ѧ��:1005  ƽ���ɼ�:140.00

 number  name  math  Chinese  English  average
 1005    mei   142   137      141      140.00
 1004    caicai131   125      132      129.33
 1003    yueyue132   113      127      124.00
 1001    banban120   121      122      121.00
 1002    huahua112   132      110      118.00
 */