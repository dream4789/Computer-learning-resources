//
//  main.c
//  ����˳��洢����׼
//

#include <stdio.h>

#define maxsize 256
char s[maxsize];

typedef struct
{
    char data[maxsize];
    int length;
}seqstring;

int strlength(char *s)
{//�󴮳�
    int i=0;
    while(s[i]!='\0')
        i++;
    return i;
}

int strconcat(char *s1,char *s2,char *s)
{//�´�������ָ��s��,������
    int i=0,j,len1,len2;
    len1=strlength(s1);
    len2=strlength(s2);
    if(len1+len2>maxsize-1)
        return 0;
    j=0;
    while(s1[j]!='\0')
    {
        s[i]=s1[j];
        i++;
        j++;
    }
    j=0;
    while(s2[j]!='\0')
    {
        s[i]=s2[j];
        i++;
        j++;
    }
    s[i]='\0';
    return 1;
}

int strsub(char *t,char *s,int i,int len)
{//���Ӵ�����t���ش�s�е�i���ַ���ʼ�ĳ���Ϊlen���Ӵ���1��i�ܴ���
    int slen,j;
    slen=strlength(s);
    if(i<1||i>slen||len>slen-i+1)
    {
        printf("��������");
        return 0;
    }
    for(j=0;j<len;j++)
        t[j]=s[i+j-1];
    t[j]='\0';
    return 1;
}

int Strcmp(char *s1,char *s2)
{//���Ƚ�
    int i=0;
    while(s1[i]==s2[i]&&s1[i]!='\0')
        i++;
    return  s1[i]==s2[i];
}

int main(int argc, const char * argv[])
{
    char s1[10]="12345";
    char s2[10]="6789";
    char s[20],t[10];
    
    int l=strlength(s1);    //�󴮳�
    printf("s1����Ϊ��%d\n",l);
    
    strconcat(s1, s2, s);  //������
    printf("�����ӣ�%s\n",s);
    
    strsub(t, s1, 1, 3);   //���Ӵ�
    printf("���Ӵ���%s\n",t);
    
    int c=Strcmp(s1, s2);  //���Ƚ�
    printf("���Ƚϣ�%d(���Ϊ1������Ϊ0)\n",c);  //���Ϊ1������Ϊ0
    
    return 0;
}
/*
 s1����Ϊ��5
 �����ӣ�123456789
 ���Ӵ���123
 ���Ƚϣ�0(���Ϊ1������Ϊ0)
 */
