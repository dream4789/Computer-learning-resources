//
//  main.c
//  BF��KMP��nextֵ������
//

#include <stdio.h>
#include <string.h>

int strindex_BF(char *s,char *t)
{//�Ӵ�s�ĵ�1���ַ���ʼ���״��봮t��ȵ��Ӵ�    //��ģʽƥ��
    int i=0,j=0;
    int count=0;
    int ls=(int)strlen(s),lt=(int)strlen(t);
    while(i<ls&&j<lt)
    {
        if(s[i]==t[j])
        {
            //printf("[%c %c]",s[i],t[j]);   //������
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
            //printf("<%d|%c>",i,s[i]);   //������
        }
        count++;
    }
    printf("BF�ıȽϴ���Ϊ��%d       ",count+1);//���һλƥ��ɹ�ҲҪ����
    if(j>=lt)
        return i-lt;
    else
        return -1;
}

/*
int strindex_BF(char *s,char *t)
{//�Ӵ�s�ĵ�1���ַ���ʼ���״��봮t��ȵ��Ӵ�    //��ģʽƥ��
    int i=1,j=1;
    while(i<=s[0]&&j<=t[0])
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+2;
            j=1;
        }
    if(j>t[0])
        return i-t[0];
    else
        return -1;
}
*/
void web_getnext1(char *t,int next[])
{//��һ�ڶ�λΪ-1��0��֮�������ͬ�Ӵ�����ͬλ����1
    int j=0,k=-1;
    next[0]=-1;
    int lt=(int)strlen(t);
    while(j<lt-1)
    {
        if(k ==-1||t[j]==t[k])
        {
            j++;
            k++;
            /*
            if(t[j]==t[k])//�������ַ���ͬʱ��������
                next[j] = next[k];
            else
                */
            next[j] = k;
        }
        else
            k = next[k];
    }
    printf("next(-1,0��ʼ)ֵΪ��");
    for(int i=0;i<lt;i++)   //������
        printf("%d ",next[i]);
}
int web_KMP(char *s,char *t)
{//�Ӵ�s�ĵ�1���ַ���ʼ���״��봮t��ȵ��Ӵ�
    int next[10],i=0,j=0;
    int count=0;
    web_getnext1(t,next);
    int ls=(int)strlen(s),lt=(int)strlen(t);
    while(i<ls&&j<lt)
    {
        if(j==-1 || s[i]==t[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];               //j����
        count++;
    }
    printf("  WEB_KMP�ıȽϴ���Ϊ��%d  ",count);
    if(j>=lt)
        return (i-lt);         //ƥ��ɹ��������Ӵ���λ��
    else
        return (-1);                  //û�ҵ�
}

void getnext(char *t,int next[])
{//��ģʽt��nextֵ������next�����У��ַ������ȱ�����t[0]
    //��һ�ڶ�λΪ-1��0��֮�������ͬ�Ӵ�����ͬλ����1
    int i=0,j=-1;
    int lt=(int)strlen(t);
    next[0]=-1;
    while(i<lt-1)
        if(j==-1||t[i]==t[j])
        {
            ++i;
            ++j;
            next[i]=j;//����
        }
        else
            j=next[j];
    printf("next(-1,0��ʼ)ֵΪ��");
    for(i=0;i<lt;i++)   //������
        printf("%d ",next[i]);
}

int strindex_KMP(char *s,char *t,int pos,int *next)
{//�Ӵ�s�ĵ�pos���ַ���ʼ���״��봮t��ȵ��Ӵ�    //KPMģʽƥ�䣬��ƥ����Ӵ���ƽ��
    int i=pos-1,j=0;
    //char next[10];
    int ls=(int)strlen(s),lt=(int)strlen(t);
    while(i<ls&&j<lt)
        if(j==-1||s[i]==t[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];//����
    if(j>=lt)
        return i-j;//ƥ��ɹ������ش洢λ��
    else
        return -1;
}

/*
int strindex_KMP(char *s,char *t,int pos)
{//�Ӵ�s�ĵ�pos���ַ���ʼ���״��봮t��ȵ��Ӵ�    //KPMģʽƥ�䣬��ƥ����Ӵ���ƽ��
    int i=pos,j=1;
    char next[10];
    while(i<=s[0]&&j<=t[0])
        if(j==0||s[i]==t[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];//����
    if(j>t[0])
        return i-t[0];//ƥ��ɹ������ش洢λ��
    else
        return -1;
}
*/

void getnext_rec(char *t,int next[],int l)
{//�ݹ��㷨��nextֵ��tΪģʽ����lΪģʽ������=t[0]
    if(l==1)//l=1���ݹ����
    {
        next[1]=0;//�ݹ���next[l-1],Ϊnext[l]��׼��
        return;
    }
    getnext_rec(t,next,l-1);
    int k=next[l-1];
    while(1)//ֱ��next[l]�������
    {
        if(t[k]==t[l-1])
        {
            next[l]=k+1;
            return;
        }
        k=next[k];//����
        if(k==0)//�����������ȵ�ǰ׺�ͺ�׺�Ӵ���next[1]=1
        {
            next[l]=1;
            return;
        }
    }
}


int main() {
    char s[]={"001000100001010"};
    char s1[]="00101";
    
    int BF,KMP,WEB_KMP;
    BF=strindex_BF(s,s1);
    printf("BFƥ�䣺��%dλ \n",BF+1);
    WEB_KMP=web_KMP(s,s1);
    printf("WEB_KMPƥ�䣺��%dλ\n",WEB_KMP+1);
    
    int next[10];
    getnext(s1, next);
    KMP=strindex_KMP(s, s1, 2, next);
    printf("  KMPƥ�䣺��%dλ\n",KMP+1);

    return 0;
}
/*
 BF�ıȽϴ���Ϊ��31       BFƥ�䣺��10λ
 next(-1,0��ʼ)ֵΪ��-1 0 1 0 1   WEB_KMP�ıȽϴ���Ϊ��19  WEB_KMPƥ�䣺��10λ
 next(-1,0��ʼ)ֵΪ��-1 0 1 0 1   KMPƥ�䣺��10λ
 */
