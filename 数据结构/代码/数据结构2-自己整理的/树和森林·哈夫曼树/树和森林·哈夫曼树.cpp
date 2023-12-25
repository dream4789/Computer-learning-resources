//
//  main.c
//  ����ɭ�֡���������
//

#include <stdio.h>

#include <stdlib.h>
#define N 20

typedef int DataType;

typedef struct{//��������������Ͷ���
    char ch;
    DataType weight;
    int lchild,rchild,parent;
}Htnode;

//Htnode huffTree[];//���þ�̬����洢��������

typedef struct{//Ҷ��������
    char *code;
    char leaf;
    int length;
}CodeType;

//CodeType cd[];//һά����洢����

void selectsort(Htnode huftree[],int n,int *s1,int *s2)
{
    int i,min1,min2;//������С��
    min1=huftree[0].weight;
    min2=huftree[0].weight;
    *s1=0;
    for(i=1;i<=n;i++)
    {
        if(huftree[i].parent==-1&&huftree[i].weight<min1)
        {//����ڵ�δ��������,����С����Сֵ,�������Сֵ*/
            min1=huftree[i].weight;
            *s1=i;
        }
        else//Ϊ�±�����һ����Сֵ����ֵ*/
        {
            min2=huftree[i].weight;
            *s2=i;
        }
    }/*end for*/
    for(i=1;i<=n;i++)
    {
        if(huftree[i].parent==-1&&huftree[i].weight<min2&&huftree[i].weight>= min1&&*s1!=i)
        /*����ڵ�δ��������,����С����Сֵ,���Ҵ��ڵ�һ����Сֵ,*/
        /*�����������е��±겻���ڵ�һ����Сֵ,�������Сֵ*/
        {
            min2 = huftree[i].weight;
            *s2 = i;
        }
    }/*end for*/
}

void Hufcoding(Htnode huftree[],CodeType cd[],int w[],int n)
{//������������ھ�̬����huftree��,w��Ž��Ȩ��,n��Ҷ�Ӹ���,���ı������cd[]
    int i,k,s1,s2,m,f,c,sum;
    char temp[N];   //�ݴ�Ҷ�ӱ����ַ����������Ҫת��
    m=2*n-1;     //������������Ľ������
    for(i=1;i<=n;i++)  //��ʼ��ÿ��Ҷ�ӽ���Գ�һ ����
    {
        huftree[i].weight=w[i-1];
        huftree[i].lchild=huftree[i].rchild=huftree[i].parent=-1;
        //huftree[i].ch=getch();
    }
    for(i=n+1;i<=m;i++)  //��ʼ����Ҷ�ӽ��
    {
        huftree[i].weight=-1;
        huftree[i].lchild=huftree[i].rchild=huftree[i].parent=-1;
    }
    for(i=1;i<=n-1;i++)  //����n-1����Ҷ�ӽ���ѭ��
    {
        selectsort(huftree,n+i-1,&s1,&s2);
        //������ huftree[1..n+i-1]����˫�׵Ľ��Ȩֵ��������s1,s2������˫����Ȩ����С����������±�
        sum=huftree[s1].weight+huftree[s2].weight;//���,���츸�ڵ�
        huftree[n+i].weight=sum;
        huftree[s1].parent=huftree[s2].parent=n+i;//��С�������ڵ�ĸ��ڵ��������±�
        huftree[n+i].lchild=s1;//���ڵ�������±�
        huftree[n+i].rchild=s2;//���ڵ���Һ����±�
    }
    for(i=1;i<=n;i++)     //��ʼ��ÿ��Ҷ�ӽ��ı���
    {
        c=0;
        for (k=i,f=huftree[i].parent;f!=-1;k=f,f=huftree[f].parent)
        {
            if (huftree[f].lchild==k)
            {
                temp[c]='0' ;
                c++;
            }
            else
            {
                temp[c]='1';
                c++;
            }    //���֦��0�ҷ�֦��1
        }
        cd[i].code=(char *)malloc(c+1);  //�����洢����Ŀռ�
        cd[i].code[c]='\0';
        c--;
        k=0;
        while (c>=0)
            cd[i].code[k++]=temp[c--]; //��tempת�õ�cd��
        cd[i].leaf=huftree[i].ch;
        cd[i].length=k;
    }
}

/*����:����������и����ڵ�ı���*/
/*�������:��huftree[],�ڵ����n,��������cd[]*/
void HuftreeCode(Htnode huftree[], CodeType cd[], int n)
{
    int i,c,f,k;
    char temp[N];/*�ݴ�Ҷ�ӱ����ַ���,�����Ҫת��*/
    for(i=1;i<=n;i++)/*��ʼ��ÿ��Ҷ�ӽ��ı���*/
    {
        c = 0;
        for(k=i,f=huftree[i].parent;f!=-1;k=f,f=huftree[f].parent)
            if(huftree[f].lchild == k)/*���֧��0*/
                temp[c++]='0';
            else
                temp[c++]='1';/*�ҷ�֧��1*/
        cd[i].code=(char *)malloc(c+1); /*�����洢����Ŀռ�*/
        cd[i].code[c--]='\0';
        k = 0;
        while(c>=0)
            cd[i].code[k++]=temp[c--];//��tempת�õ�cd��*/
        //cd[i].leaf=huftree[i].ch;
        cd[i].length=k;
    }
}

int main()
{
    Htnode huftree[2*N];   //������������
    CodeType cd[N];    //�ڵ�ı�������
    int w[N],n,i,temp,sum=0;  //�ڵ����ʱ��ż��ڵ�ĸ���
    printf("�����Ȩ�ڵ�ĸ���:");  //�����Ȩ�ڵ�ĸ���
    scanf("%d",&n);
    if(n < N)
    {
        A:printf("�����Ȩֵ����:\n");   //�����Ȩֵ����
        for(i = 1; i <= n; i++)
        {
            scanf("%d",&temp);
            w[i-1] = temp;
        }
        Hufcoding(huftree,cd,w,n);  //������������
        printf("HuftreeCodeÿ���ڵ�ı���:\n");  //��ӡÿ���ڵ�ı���
        HuftreeCode(huftree, cd, n);
        for(i = 1; i <= n; i++)
        {
            printf("%d �� HuftreeCode �ڵ�ı���:",huftree[i].weight);
            puts(cd[i].code);
        }
        printf("Huftree ��Ȩ·������:\n");   //��ӡWPL(��Ȩ·������)
        for(i = 1; i <= n; i++)
        {
            printf("%d * %d + ",huftree[i].weight,cd[i].length);
            sum += huftree[i].weight * cd[i].length;
        }
        printf("0 = %d\n",sum);
    }
    else
    {
        printf("�������\n");
        goto A;
    }
}

/*
 �����Ȩ�ڵ�ĸ���:5
 �����Ȩֵ����:
 1
 2
 3
 4
 5
 HuftreeCodeÿ���ڵ�ı���:
 1 �� HuftreeCode �ڵ�ı���:010
 2 �� HuftreeCode �ڵ�ı���:011
 3 �� HuftreeCode �ڵ�ı���:00
 4 �� HuftreeCode �ڵ�ı���:10
 5 �� HuftreeCode �ڵ�ı���:11
 Huftree ��Ȩ·������:
 1 * 3 + 2 * 3 + 3 * 2 + 4 * 2 + 5 * 2 + 0 = 33
 */
