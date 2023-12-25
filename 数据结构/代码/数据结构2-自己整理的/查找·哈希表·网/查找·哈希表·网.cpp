//
//  main.c
//  ���ҡ���ϣ����

#include <stdio.h>

#include <stdio.h>
#define MaxSize 100      //��������ϣ����
#define NULLKEY -1       //����չؼ���ֵ
#define DELKEY -2        //���屻ɾ�ؼ���ֵ
typedef int KeyType;     //�ؼ�������
typedef char *InfoType;  //������������
typedef struct{
    KeyType key;        //�ؼ�����
    InfoType data;      //����������
    int count;          //̽�������
}HashTable[MaxSize];    //��ϣ������

//���ؼ���k���뵽��ϣ����
int InsertHT(HashTable ha,int n,KeyType k,int p)
{
    int i,adr;
    adr = k%p;
    if (ha[adr].key==NULLKEY || ha[adr].key==DELKEY)  //x[j]����ֱ�ӷ��ڹ�ϣ����
    {
        ha[adr].key=k;
        ha[adr].count=1;
    }
    else      //������ͻʱ,��������̽�鷨�����ͻ
    {
        i=1;  //i��¼x[j]������ͻ�Ĵ���
        do
        {
            adr = (adr+1)%p;
            i++;
        } while (ha[adr].key!=NULLKEY && ha[adr].key!=DELKEY);
        ha[adr].key=k;
        ha[adr].count=i;
    }
    n++;
    return n;
}

//������ϣ��
void CreateHT(HashTable ha,KeyType x[],int n,int m,int p){
    int i,n1=0;
    for (i=0;i<m;i++)  //��ϣ���ó�ֵ
    {
        ha[i].key=NULLKEY;
        ha[i].count=0;
    }
    for(i=0;i<n;i++)
        InsertHT(ha,n1,x[i],p);
}

//�ڹ�ϣ���в��ҹؼ���k
int SearchHT(HashTable ha,int p,KeyType k){
    int i=0,adr;
    adr = k%p;
    while (ha[adr].key!=NULLKEY && ha[adr].key!=k)
    {
        i++;             //��������̽�鷨����һ����ַ
        adr = (adr+1)%p;
    }
    if(ha[adr].key==k)  //���ҳɹ�
    {
        printf("  ha[%d].key=%d\n",adr,k);
        return adr;  //����k����λ��
    }
    else                //����ʧ��
    {
        printf("  δ�ҵ�%d\n",k);
        return -1;
    }
}

//ɾ����ϣ���йؼ���k
int DeleteHT(HashTable ha,int p,int k,int n)
{
    int adr;
    adr = SearchHT(ha,p,k);
    if (adr!=-1)   //�ڹ�ϣ�����ҵ��ؼ���
    {
        ha[adr].key=DELKEY;
        n--;       //��ϣ���ȼ�1
        return n;
    }
    else            //�ڹ�ϣ����δ�ҵ��ùؼ���
        return n;
}

//�����ϣ��
void DispHT(HashTable ha,int n,int m)
{
    float avg=0;
    int i;
    printf(" ��ϣ���ַ:\t");
    for(i=0;i<m;i++)
        printf(" %3d",i);
    printf("\n");
    printf(" ��ϣ��ؼ���:\t");
    for(i=0;i<m;i++)
    {
        if(ha[i].key==NULLKEY || ha[i].key==DELKEY)
            printf("    "); //���4���ո�
        else
            printf(" %3d",ha[i].key);
    }
    printf(" \n");
    printf(" ��������:\t");
    for(i=0;i<m;i++)
    {
        if(ha[i].key==NULLKEY || ha[i].key==DELKEY)
            printf("    "); //���4���ո�
        else
            printf(" %3d",ha[i].count);
    }
    printf("\n");
    for(i=0;i<m;i++)
        if(ha[i].key!=NULLKEY && ha[i].key!=DELKEY)
            avg=avg+ha[i].count;
    avg=avg/n;
    printf(" ƽ����������ASL(%d)=%.3g\n",n,avg);

}

//���ҳɹ�ʱ��ƽ�����ҳ���
void CompASL(HashTable ha,int m)
{
    int i;
    int s=0,n=0;
    for (i=0;i<m;i++)
    {
        if(ha[i].key!=DELKEY && ha[i].key!=NULLKEY)
        {
            s=s+ha[i].count;
            n++;
        }
    }
    printf(" ���ҳɹ���ASL=%.3g\n",s*1.0/n);
}
int main()
{
    int x[]={16,74,60,43,54,90,46,31,29,88,77};
    int n=11;  //Ԫ�ظ���
    int m=13,p=13,i;
    HashTable ha;
    
    int k=29;  //�ؼ���k
    printf("������ϣ��:\n");
    CreateHT(ha,x,n,m,p);  //������ϣ��
    DispHT(ha,n,m);        //�����ϣ��
    
    i=SearchHT(ha,p,k);    //���ҹؼ���
    
    printf("\nɾ���ؼ���%d\n",k);
    n=DeleteHT(ha,p,k,n);  //ɾ���ؼ���
    DispHT(ha,n,m);
    
    i=SearchHT(ha,p,k);    //���ҹؼ���
    
    printf("\n����ؼ���%d\n",k);
    n=InsertHT(ha,n,k,p);  //����ؼ���
    DispHT(ha,n,m);
    
    printf("\n");
}
/*
 ������ϣ��:
  ��ϣ���ַ:       0   1   2   3   4   5   6   7   8   9  10  11  12
  ��ϣ��ؼ���:      77      54  16  43  31  29  46  60  74  88      90
  ��������:       2       1   1   1   1   4   1   1   1   1       1
  ƽ����������ASL(11)=1.36
   ha[6].key=29

 ɾ���ؼ���29
   ha[6].key=29
  ��ϣ���ַ:       0   1   2   3   4   5   6   7   8   9  10  11  12
  ��ϣ��ؼ���:      77      54  16  43  31      46  60  74  88      90
  ��������:       2       1   1   1   1       1   1   1   1       1
  ƽ����������ASL(10)=1.1
   δ�ҵ�29

 ����ؼ���29
  ��ϣ���ַ:       0   1   2   3   4   5   6   7   8   9  10  11  12
  ��ϣ��ؼ���:      77      54  16  43  31  29  46  60  74  88      90
  ��������:       2       1   1   1   1   4   1   1   1   1       1
  ƽ����������ASL(11)=1.36
 */
