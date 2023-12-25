//
//  main.c
//  �����������������
//

#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct lnode
{   int tag;                //�ڵ����ͱ�ʶ
    union
    {
        ElemType data;
        struct lnode *sublist;
    }val;
    struct lnode *link;     //ָ����һ��Ԫ��
} GLNode;
GLNode *CreateGL(char *s)           //���������ű�ʾ����ʾs�Ĺ������ʽ�洢�ṹ
{   GLNode *g;
    char ch=*s++;                   //ȡһ���ַ�
    if (ch!='\0')                   //��δ�����ж�
    {   g=(GLNode *)malloc(sizeof(GLNode));//����һ���½ڵ�
        if (ch=='(')                //��ǰ�ַ�Ϊ������ʱ
        {   g->tag=1;               //�½ڵ���Ϊ��ͷ�ڵ�
            g->val.sublist=CreateGL(s);  //�ݹ鹹���ӱ�������ͷ�ڵ�
        }
        else if (ch==')')
            g=NULL;                   //����')'�ַ�,g��Ϊ��
        else if (ch=='#')             //����'#'�ַ�����ʾ�ձ�
            g->val.sublist=NULL;
        else                          //Ϊԭ���ַ�
        {   g->tag=0;                 //�½ڵ���Ϊԭ�ӽڵ�
            g->val.data=ch;
        }
    }
    else                              //������,g��Ϊ��
        g=NULL;
    ch=*s++;                          //ȡ��һ���ַ�
    if (g!=NULL)                      //��δ���������������ֵݽڵ�
    {
        if (ch==',')                  //��ǰ�ַ�Ϊ','
            g->link=CreateGL(s);      //�ݹ鹹���ֵݽڵ�
        else                          //û���ֵ���,���ֵ�ָ����ΪNULL
            g->link=NULL;
    }
    return g;                         //���ع����g
}
int GLLength(GLNode *g)               //������g�ĳ���
{
    int n=0;
    g=g->val.sublist;                 //gָ������ĵ�һ��Ԫ��
    while (g!=NULL)
    {
        n++;
        g=g->link;
    }
    return n;
}
int GLDepth(GLNode *g)                  //������g�����
{
    int max=0,dep;
    if (g->tag==0)
        return 0;
    g=g->val.sublist;                   //gָ���һ��Ԫ��
    if  (g==NULL)                       //Ϊ�ձ�ʱ����1
        return 1;
    while (g!=NULL)                     //�������е�ÿһ��Ԫ��
    {
        if (g->tag==1)                  //Ԫ��Ϊ�ӱ�����
        {
            dep=GLDepth(g);             //�ݹ��������ӱ�����
            if (dep>max) max=dep;       //maxΪͬһ����������ӱ�����ȵ����ֵ
        }
        g=g->link;                      //ʹgָ����һ��Ԫ��
    }
    return(max+1);                      //���ر�����
}
void DispGL(GLNode *g)                  //��������g
{   if (g!=NULL)                        //��Ϊ���ж�
    {                                   //�����g��Ԫ��
        if (g->tag==0)                  //g��Ԫ��Ϊԭ��ʱ
            printf("%c", g->val.data);  //���ԭ��ֵ
        else                            //g��Ԫ��Ϊ�ӱ�ʱ
        {   printf("(");                //���'('
            if (g->val.sublist==NULL)   //Ϊ�ձ�ʱ
                printf("#");
            else                        //Ϊ�ǿ��ӱ�ʱ
                DispGL(g->val.sublist); //�ݹ�����ӱ�
            printf(")");                //���')'
        }
        if (g->link!=NULL)
        {   printf(",");
            DispGL(g->link);            //�ݹ����g���ֵ�
        }
    }
}
ElemType maxatom(GLNode *g)             //������g�����ԭ��
{
    ElemType max1,max2;
    if (g!=NULL)
    {
        if (g->tag==0)
        {
            max1=maxatom(g->link);
            return(g->val.data>max1?g->val.data:max1);
        }
        else
        {
            max1=maxatom(g->val.sublist);
            max2=maxatom(g->link);
            return(max1>max2?max1:max2);
        }
    }
    else
        return 0;
}
int main()
{
    GLNode *g;
    char *str="(b,(b,a,(#),d),((a,b),c,((#))))";
    g=CreateGL(str);
    printf("�����g:");DispGL(g);
    printf("\n");
    printf("�����g�ĳ���:%d\n",GLLength(g));
    printf("�����g�����:%d\n",GLDepth(g));
    printf("�����g�����ԭ��:%c\n",maxatom(g));
}
/*
�����g:(b,(b,a,((#)),d),((a,b),c,(((#)))))
�����g�ĳ���:3
�����g�����:4
�����g�����ԭ��:d
 */