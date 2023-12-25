#include <stdio.h>
#include <stdlib.h>
typedef struct Polyn
{
    int coeff;   //ϵ��
    int power;   //�ݴ�
    struct Polyn *next;
}Polyn,*Polynomial;

Polynomial InitPolyn(void)
{
    int num;
    Polynomial p=(Polynomial)malloc(sizeof(Polyn));
    Polynomial q=p;  //����ͷ���
    printf("�������ʽ��������");
    scanf("%d",&num);
    printf("�������ʽ��ϵ���Ͷ�Ӧ�ݴΣ�\n");
    for(int i=0;i<num;i++)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        scanf("%d %d",&p->coeff,&p->power);
    }
    p->next=NULL;
    return q->next;  //ֱ�ӷ���һ��ָ���һ��ֵ��ָ��
}

Polynomial InitPolyn1(void)
{
    //int a[4]={7,3,9,5};   //������1
    //int b[4]={0,1,8,17}; //������2
    int a[4]={1,-1,1,2};
    int b[4]={0,1,2,3};
    Polynomial p=(Polynomial)malloc(sizeof(Polyn));
    Polynomial q=p;  //����ͷ���
    for(int i=0;i<4;i++)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        p->coeff=a[i];
        p->power=b[i];
    }
    p->next=NULL;
    return q->next;  //ֱ�ӷ���һ��ָ���һ��ֵ��ָ��
}
Polynomial InitPolyn2(void)
{
    //int a[3]={8,22,-9};  //������1
    //int b[3]={1,7,8};
    int a[3]={-1,1,-1}; //������2
    int b[3]={0,1,3};
    Polynomial p=(Polynomial)malloc(sizeof(Polyn));
    Polynomial q=p;  //����ͷ���
    for(int i=0;i<3;i++)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        p->coeff=a[i];
        p->power=b[i];
    }
    p->next=NULL;
    return q->next;  //ֱ�ӷ���һ��ָ���һ��ֵ��ָ��
}

void PrintPolyn1(Polynomial p)
{//���1���ĸ���������2������������һЩ
    int count=0;  //�ж��Ƿ�Ϊ��һ��
    while (p)
    {
        if(p->power==0)
        {  //�ݴ�Ϊ0
            printf("%d ",p->coeff);  //����ݵ�һ��
            count++;
            p=p->next;
        }
        if(p->power==1)
        {  //�ݴ�Ϊ1
            if(p->coeff == 1)
            {
                if(count==0)
                {
                    printf("x ");  //һ���ݵ�һ��
                    count++;
                }
                else
                    printf("+x ");
            }
            else if (p->coeff == -1)
                printf("-x ");
            else
            {
                if(count==0)
                {
                    printf("%dx ",p->coeff);  //һ���ݵ�һ��
                    count++;
                }
                else
                    printf("%+dx ",p->coeff);
            }
            p = p->next;
        }
        else
        {  //�����ݴ�
            if(p->coeff == 1)
            {
                if(count==0)
                {
                    printf("x^%d ",p->power);  //�ߴ��ݵ�һ��
                    count++;
                }
                else
                    printf("+x^%d ",p->power);
            }
            else if (p->coeff == -1)
                printf("-x^%d ",p->power);
            else
            {
                if(count==0)
                {
                    printf("%dx^%d ",p->coeff,p->power);  //�ߴ��ݵ�һ��
                    count++;
                }else
                    printf("%+dx^%d ",p->coeff,p->power);
            }
            p = p->next;
        }
    }
    printf("\n");
}
Polynomial copyPolyn(Polynomial p2)
{
    Polynomial p1=(Polynomial)malloc(sizeof(Polyn));
    Polynomial p=p1;
    while (p2)
    {
        p->next=(Polynomial)malloc(sizeof(Polyn));
        p=p->next;
        p->coeff=p2->coeff;
        p->power=p2->power;
        p2=p2->next;
    }
    p->next=NULL;
    //PrintPolyn1(p1->next);   //������
    return p1->next;  //ֱ�ӷ���һ��ָ���һ��ֵ��ָ��
}

void PrintPolyn2(Polynomial p)
{//�����1һ����ֻ�ǻ���һЩ
    int count=0;  //�ж��Ƿ�Ϊ��һ��
    while (p)
    {
        if(p->power==0)  //�ݴ�Ϊ0
        {
            printf("%d ",p->coeff);  //����� ��һ��
            count++;
            p=p->next;
        }
        if(p->power==1)  //�ݴ�Ϊ1
        {
            if(p->coeff == 1)
            {
                if(count==0) {printf("x ");count++;}  //һ���� ��һ��
                else          printf("+x ");
            }
            else if (p->coeff == -1) printf("-x ");
            else
            {
                if(count==0) {printf("%dx ",p->coeff);count++;}  //һ���� ��һ��
                else          printf("%+dx ",p->coeff);
            }
            p = p->next;
        }
        else            //�����ݴ�
        {
            if(p->coeff == 1)
            {
                if(count==0) {printf("x^%d ",p->power);count++;}  //�ߴ��� ��һ��
                else          printf("+x^%d ",p->power);
            }
            else if (p->coeff == -1) printf("-x^%d ",p->power);
            else
            {
                if(count==0) {printf("%dx^%d ",p->coeff,p->power);count++;}  //�ߴ��� ��һ��
                else          printf("%+dx^%d ",p->coeff,p->power);
            }
            p = p->next;
        }
    }
    printf("\n");
}
//�ӷ�
Polynomial AddPolyn(Polynomial p1,Polynomial p2)
{
    Polynomial p3=(Polynomial)malloc(sizeof(Polyn));
    Polynomial p=p3;  //����ͷ���
    while (p1 && p2)
    {
        if(p1->power < p2->power)
        {
            p3->next=(Polynomial)malloc(sizeof(Polyn));
            p3=p3->next;
            p3->coeff=p1->coeff;
            p3->power=p1->power;
            p1=p1->next;
        }
        else if(p1->power > p2->power)
        {
            p3->next=(Polynomial)malloc(sizeof(Polyn));
            p3=p3->next;
            p3->coeff=p2->coeff;
            p3->power=p2->power;
            p2=p2->next;
        }
        else
        {
            if(p1->coeff+p2->coeff!=0)
            {
                p3->next=(Polynomial)malloc(sizeof(Polyn));
                p3=p3->next;
                p3->coeff=p1->coeff+p2->coeff;
                p3->power=p1->power;
            }
            p1=p1->next;
            p2=p2->next;
        }
    }
    while(p1)
    {
        p3->next=(Polynomial)malloc(sizeof(Polyn));
        p3=p3->next;
        p3->coeff=p1->coeff;
        p3->power=p1->power;
        p1=p1->next;
    }
    while(p2)
    {
        p3->next=(Polynomial)malloc(sizeof(Polyn));
        p3=p3->next;
        p3->coeff=p2->coeff;
        p3->power=p2->power;
        p2=p2->next;
    }
    p3->next=NULL;
    //PrintPolyn1(p->next);  //������
    return p->next;  //ֱ�ӷ���һ��ָ���һ��ֵ��ָ��
}
//����
Polynomial SubPolyn(Polynomial p1,Polynomial p2)
{
    Polynomial p=p2,q=NULL;
    while (p)
    {
        p->coeff=-(p->coeff);  //�为
        p=p->next;
    }
    q=AddPolyn(p1, p2);
    //PrintPolyn1(p);   //������
    return q;  //ֱ�ӷ���һ��ָ���һ��ֵ��ָ��
}
//�˷�
Polynomial MulPolyn(Polynomial p1,Polynomial p2)
{
    Polynomial p3=(Polynomial)malloc(sizeof(Polyn));  //�����
    Polynomial p4=(Polynomial)malloc(sizeof(Polyn));  //������
    Polynomial p=p1;   //����ͷ���
    Polynomial pn=p4;  //����ͷ���
    int i=0;
    while(p2)
    {
        pn=p4;  //p4����
        p1=p;  //p1����
        while(p1)
        {
            if(i==0)
                pn->next=(Polynomial)malloc(sizeof(Polyn));  //����һ��
            //printf("(%d %d)\n",pn->coeff,pn->power);  //������
            pn=pn->next;
            pn->coeff=p1->coeff*p2->coeff;  //ϵ��
            pn->power=p1->power+p2->power;  //�ݴ�
            p1=p1->next;
            //printf("[%d %d]\n",pn->coeff,pn->power);  //������
        }
        pn->next=NULL;
        //printf("/");
        //PrintPolyn1(pn);
        //printf("//");
        if(i==0)
            p3=copyPolyn(p4->next);  //������p3��Ϊָ���һ��ֵ��ָ�룬����һ��
        else
        {
            //PrintPolyn1(pn);  //������
            p3=AddPolyn(p3, p4->next);
        }
        //printf("///");
        p2=p2->next;  //p2�����һλ
        i++;
    }
    return p3;   //ֱ�ӷ���һ��ָ���һ��ֵ��ָ��
}

int main()
{
    printf("�������������ʽA(x),B(x)��ϵ��\n");
    //Polynomial p1=InitPolyn();  //p1ָ���һ��ֵ��ָ��
    //Polynomial p2=InitPolyn();  //p2ָ���һ��ֵ��ָ��
    
    Polynomial p1=InitPolyn1();  //p1ָ���һ��ֵ��ָ�룬������
    Polynomial p2=InitPolyn2();  //p2ָ���һ��ֵ��ָ�룬������
    Polynomial p3 = NULL;  //�������
    
    printf("A(x)=");
    PrintPolyn1(p1);  //��ӡ��ָ���һ��ֵ��ָ���ӡ
    
    printf("B(x)=");
    PrintPolyn1(p2);

    printf("1.����ʽ���\n");
    printf("C(x)=");
    p3=AddPolyn(p1,p2);
    PrintPolyn1(p3);
    
    printf("2.����ʽ���\n");
    printf("D(x)=");
    p3=copyPolyn(p2);  //����һ�ݣ���ֹ�����ǵ���������ָ���һ��ֵ��ָ�뿪ʼ����
    //PrintPolyn1(p3);    //������
    p3=SubPolyn(p1,p3);
    PrintPolyn1(p3);
    
    printf("3.����ʽ���\n");
    printf("E(x)=");
    p3=MulPolyn(p1,p2);
    PrintPolyn1(p3);
    
    return 0;
}
/*
����1:
4
1 0
-1 1
1 2
2 3
 
3
-1 0
1 1
-1 3
����2��
4
7 0
3 1
9 8
5 17
 
3
8 1
22 7
-9 8

  �����������

 �������������ʽA(x),B(x)��ϵ��
 �������ʽ��������4
 �������ʽ��ϵ���Ͷ�Ӧ�ݴΣ�
 1 0
 -1 1
 1 2
 2 3
 �������ʽ��������3
 �������ʽ��ϵ���Ͷ�Ӧ�ݴΣ�
 -1 0
 1 1
 -1 3
 A(x)=1 -x +x^2 +2x^3
 B(x)=-1 +x -x^3
 1.����ʽ���
 C(x)=x^2 +x^3
 2.����ʽ���
 D(x)=2 -2x +x^2 +3x^3
 3.����ʽ���
 E(x)=-1 +2x -2x^2 -2x^3 +3x^4 -x^5 -2x^6
 
 �������������ʽA(x),B(x)��ϵ��
 �������ʽ��������4
 �������ʽ��ϵ���Ͷ�Ӧ�ݴΣ�
 7 0
 3 1
 9 8
 5 17
 �������ʽ��������3
 �������ʽ��ϵ���Ͷ�Ӧ�ݴΣ�
 8 1
 22 7
 -9 8
 A(x)=7 +3x +9x^8 +5x^17
 B(x)=8x +22x^7 -9x^8
 1.����ʽ���
 C(x)=7 +11x +22x^7 +5x^17
 2.����ʽ���
 D(x)=7 -5x -22x^7 +18x^8 +5x^17
 3.����ʽ���
 E(x)=56x +24x^2 +154x^7 +3x^8 +45x^9 +198x^15 -81x^16 +40x^18 +110x^24 -45x^25
 
*/
