//
//  main.c
//  �����Ѵ洢�ṹ����̬����׼
//
//  Created by ���� on 2021/11/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxsize 100
#define SMAX 100

char store[SMAX+1];//�ѿռ�
int free1;//������ָ��

typedef struct
{//�������ȵ�������
    char name[maxsize];//����
    int length;//����
    char * stradr;//��ʼ��ַ
}lnode;

typedef struct
{//ĩβָ���������
    char name[maxsize];//����
    char * stradr,* enadr;//��ʼ��ַ��ĩβ��ַ
}enode;

typedef struct
{
    int length;//����
    int stradr;//��ʼ��ַ
}hstring,*phstring;

phstring InitString(void)
{//���� �ַ��� �ռ�
    phstring H=(phstring)malloc(sizeof(hstring));
    if(NULL==H)
    {
        printf("Memory allocate is error!");
        system("pause");
        exit(0);
    }
    else
    {
        H->stradr = 0;
        H->length = 0;
        return H;
    }
}

int strassign(phstring s1,char *s2)
{//��һ���ַ�����s2�е��ַ��������stroe�У�free1��������ָ�룬������������1
    int i=0;
    int len;
    len=(int)(strlen(s2));
    if(len<0||free1+len > SMAX+1)
        return 0;
    else
    {
        for(i=0;i<len;i++)
            store[free1+i]=s2[i];
        s1->stradr=free1;
        s1->length=len;
        free1=free1+len;    //�޸�������ָ��
        printf("s��Ϊ��");
        for(i=0;i<len;i++)  //���
            printf("%c",store[s1->stradr+i]);
        printf("\n");
        return 1;
    }
}

int strcopy(phstring s1,phstring s2)
{//�����㽫��store�е�s2���Ƶ�һ���´�s1��
    int i=0;
    if(free1+s2->length > SMAX+1)
        return 0;
    else
    {
        for(i=0;i<s2->length;i++)
            store[free1+i]=store[s2->stradr+i];
        s1->length=s2->length;
        s1->stradr=free1;
        free1=free1+s2->length;
        printf("�������´�Ϊ��");
        for(i=0;i<s1->length;i++)  //���
            printf("%c",store[s1->stradr+i]);
        printf("\n");
        return 1;
    }
}

int main(int argc, const char * argv[])
{
    phstring s1=InitString(); //���ռ��ʼ��
    phstring s2=InitString();
    
    strassign(s1, "love ");  //������
    strassign(s2, "you ");
    strcopy(s2, s1);  //����������s2������s1
    
    printf("store��ȫ���Ĵ�Ϊ��");
    for(int i=0;i<free1;i++)
        printf("%c",store[i]);
    printf("\n");
    return 0;
}
/*
 s��Ϊ��love
 s��Ϊ��you
 �������´�Ϊ��love
 store��ȫ���Ĵ�Ϊ��love you love 
 */