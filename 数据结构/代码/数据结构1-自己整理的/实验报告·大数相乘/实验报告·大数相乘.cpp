#include <stdio.h>
#include <string.h>
#define MaxSize 100

void mult_largenum(char A[], char B[])
{
    int i,j,num;
    int x=0;
    int m=(int)strlen(A);//��int��Ϊ����ǿ��ת����strlen(A)��Ϊ char�� ǿ��תΪ int��
    int n=(int)strlen(B);
    //char result[m+n+1];//��vc6�ϲ�������д
	char result[MaxSize]; //ֱ�Ӹ���������
    for(i=0;i<m+n;i++)  //��ʼ��
        result[i]='0';
    
    for(i=m-1;i>=0;i--)
    {
        for(j=n-1;j>=0;j--)
        {
            num=(A[j]-48)*(B[i]-48);
            if(num<10)  //��ͬλ����� <10 ��
            {
                result[x]=result[x]+num;
                if(result[x]-48>9)  //��λ�ﵽ 10����һλ�� 1
                {
                    result[x+1]++;  //��һλ ��λ
                    result[x]=result[x]-10;  //���� ��λ
                }
            }
            else    //��ͬλ����� >10 ��
            {
                result[x]=num%10+result[x];
                if(result[x]-48>9)  //��λ�ﵽ 10����һλ�� 1
                {
                    result[x+1]++;  //��һλ ��λ
                    result[x]=result[x]-10;  //���� ��λ
                }
                result[x+1]=num/10+result[x+1];
                if(result[x+1]-48>9)  //��λ�ﵽ 10����һλ�� 1
                {
                    result[x+2]++;  //��һλ ��λ
                    result[x+1]=result[x+1]-10;   //���� ��λ
                }
            }
            x++;
        }
        x=x-n+1;  //���ص� ��һ����λ�� �� ��һλ
    }
    printf("���ս��Ϊ��\n");
    for(i=m+n-1;i>=0;i--)
        printf("%c",result[i]);
    printf("\n");
}

int main()
{
    char A[MaxSize]="999999999999999999999999999";
    char B[MaxSize]="999999999999999999999999999";
    /*
    printf("�����һ��������");
    scanf("%s",A);
    printf("����ڶ���������");
    scanf("%s",B);
    */
    mult_largenum(A, B);
	return 0;
}
/*
 �����
 ���ս��Ϊ��
 999999999999999999999999998000000000000000000000000001

A��B��λ�����Ҫһ��
��Ȼ�����"��������"����Ϊvc���Զ���δ�ú����ľֲ������ռ䰴�ֽ�ȫ����ʼ��ΪCC
��������ַ�����ռ䲻�������Ծ�ռ�����ǲ��ֲ������Լ��Ŀռ�
��Ϊ���char*��Ҫ�������ַ���ֹͣ�ģ����Ա����Щ�������������
����˵�����û���ַ���������־'\0'
/*/

