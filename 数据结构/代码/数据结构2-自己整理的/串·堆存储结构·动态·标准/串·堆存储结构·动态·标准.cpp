//
//  main.c
//  �����Ѵ洢�ṹ����̬����׼
//

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *p;
    int length;
}hstring,*phstring;

phstring InitString(void)
{//���� �ַ��� �ռ�
    phstring H=(phstring)malloc(sizeof(hstring));
    if(NULL==H)
    {
        printf("�ڴ濪��ʧ��!");
        exit(0);
    }
    else
    {
        H->p=NULL;
        H->length=0;
        return H;
    }
}

int strassign(phstring s1,char *s2)
{//��������ֵ����һ���ַ���������ֵ��ֵ��һ���ַ�������
    int i;
    char *pc;
    if(s1->p)
        free(s1->p);
    for(i=0,pc=s2;*pc!='\0';i++,pc++);//��s2����
    //printf("%d",i);
    if(i==0)
    {
        s1->p=NULL;
        s1->length=0;
        return 0;
    }
    if(!(s1->p=(char *)malloc((i+1) * sizeof(char))))
    {// +1 Ϊ������ַ���������ʶ����Ҫ������һ���ֽ��ڴ棻
        printf("�ѿռ䲻�㣬��ֵʧ�ܣ�\n");
        return 0;
    }
    for(int j=0;j<i;j++)
        s1->p[j]=s2[j];
    s1->p[i]='\0';  //�ַ���������ʶ��
    s1->length=i;
    printf("�ַ�������Ϊ��%d\n",s1->length);
    return 1;//��ֵ�ɹ�
}

int strcopy(phstring s1,hstring s2)
{//s2Ҳ��������Ϊ phstring s2 ������ . ȫ��Ϊ ->
//��ֵһ����,��һ���ַ�����ֵ��ֵ��һ���ַ�������,��s2��ֵ��s1
    if(s2.length<=0)
        return 0;
    if(!(s1->p=(char *)malloc((s2.length+1) * sizeof(char))))
    {
        printf("�ѿռ䲻��,��ֵʧ��!\n");
        return 0;
    }
    for(int i=0;i<s2.length;i++)
        s1->p[i]=s2.p[i];
    s1->length=s2.length;
    s1->p[s2.length]='\0';
    //for(int i=0;i<7;i++)      //��� s1  ����һ
        //printf("%c",s1->p[i]);
    printf("��ֵ��s3�������%s\n",s1->p);   //��� s1  ������
    return 1;//��ֵ�ɹ�
}
                      
int substring(phstring sub, phstring s, int pos, int len)
{//���Ӵ�,��sub���ش�s�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�;����,1��pos��strlength(s)��0��len��strlength(s)-pos+1
    int i;
    if(pos<1||pos>s->length||len<0||len>s->length-pos+1)
        return 0;
    if(sub->p)//�ͷžɿռ�
        free(sub->p);
    if(!len)
    {
        sub->p=0;
        sub->length=0;//���Ӵ�
    }
    else//�����Ӵ�
    {
        sub->p=(char *)malloc((len+1) * sizeof(char));
        for(i=0;i<len;i++)
            sub->p[i]=s->p[pos+i-1];
        sub->p[len]='\0';
        sub->length=len;
    }
    printf("��s1��%dλ����%d���Ӵ�sub��%s\n",pos,len,sub->p);  //����Ӵ�
    return 1;
}


int strcontact(phstring t,phstring s1,phstring s2)
//int strcontact(hstring *t,hstring s1,hstring s2)
{//������,t �������ַ��� s1 �� s2 ���Ӷ��ɵ��´�
	int i;
    if(t->p)
        free(t->p);//�ͷžɿռ�
    if(!(t->p=(char*)malloc((s1->length+s2->length+1)*sizeof(char))))
        printf("�ѿռ䲻��,������ʧ��!\n");
    for(i=0;i<s1->length;i++)
        t->p[i]=s1->p[i];
    t->length=s1->length+s2->length;
    for(i=s1->length;i<t->length;i++)
        t->p[i]=s2->p[i-s1->length];
    t->p[t->length]='\0';
    printf("��s1��s2���ӵĴ�tΪ��%s\n",t->p);  //��� t
    return 1;
}

int strinsert(phstring s,int pos,phstring t)
{//��Ŀ�괮��ָ��λ��ǰ�����ַ���,1��pos��strlength(s)+1,�ڴ�s�ĵ�pos�ַ�ǰ���봮t
    int i;
    if(pos<1||pos>s->length+1)
        return 0;
    if(t->length==0)//t�ǿմ�
        return 1;
    if(!(s->p=(char *)realloc(s->p,(s->length+t->length+1)*sizeof(char))))
    {         //realloc���·��� s->p ���ڴ�
        printf("�ѿռ䲻��,����ʧ��!\n");
        return 0;
    }
    for(i=s->length-1;i>=pos-1;i--)//�ó����˵�λ��
        s->p[i+t->length]=s->p[i];
    for(i=pos-1;i<=pos+t->length-2;i++)
        s->p[i]=t->p[i-pos+1];
    s->length=s->length+t->length;
    s->p[s->length]='\0';
    printf("�ڴ�s2�ĵ�%d�ַ�ǰ���봮s3��%s\n",pos,s->p);  //��� t
    return 1;
}

int initstring(hstring *s)
{//�ÿմ�
    s->p=0;//ָ���ÿ�
    s->length=0;
    return 1;
}

int destorystring(phstring s)
{//���ٴ�
    if(s->length)
    {
        free(s->p);
        s->p=0;//ָ������
        s->length=0;
    }
    return 1;
}


int main(int argc, const char * argv[]) 
{
    phstring s1=InitString();
    phstring s2=InitString();
    phstring s3=InitString();
    phstring sub=InitString();
    phstring t=InitString();
    
    strassign(s1,"abcdefg");// �� �����ַ��� ��ֵ�� s1
    strassign(s2,"12345678");// �� �����ַ��� ��ֵ�� s2
    strcopy(s3, *s1);  //��s1 ��ֵ�� s3
    substring(sub, s1, 2, 4);  //�� s1�� 2λ���� 4���Ӵ�sub
    strcontact(t, s1, s2);  //�� s1�� s2���ӣ��� t
    strinsert(s2, 3, sub);   //�ڴ� s2�ĵ� 3�ַ�ǰ���봮 sub
    
    destorystring(s1);
    destorystring(s2);
    destorystring(s3);
    destorystring(sub);
    destorystring(t);
}
/*
 �ַ�������Ϊ��7
 �ַ�������Ϊ��8
 ��ֵ��s3�������abcdefg
 ��s1��2λ����4���Ӵ�sub��bcde
 ��s1��s2���ӵĴ�tΪ��abcdefg12345678
 �ڴ�s2�ĵ�3�ַ�ǰ���봮s3��12bcde345678
 */
