#include<iostream>
#define maxtemr 100
using namespace std;

class SparseMatrix; //��ǰ����

class MatrixTerm//����Ԫ����
{
public:
    int row;//��
    int col;//��
    int value;//ֵ
    friend SparseMatrix;
};

class SparseMatrix
{
private:
    int Rows;//����
    int Cols;//����
    int Terms;//���������
    MatrixTerm smArray[maxtemr];//maxterm�ǳ�����maxterm<<Rows*Cols
    int cpot[20];
public:
    void InitMatrix(int count);  //��������
    SparseMatrix Transpose1();   //����ת���㷨1
    SparseMatrix Transpose2();   //����ת���㷨2
    bool Multiply(SparseMatrix b,SparseMatrix &q);//�������
    bool Add(SparseMatrix b,SparseMatrix &c);     //�������
    void print();   //��ӡ��Ԫ��
    void print1();  //��ӡ����
};
int arry[6][6] = {
    {1, 0, 0, 0, 0, 0},
    {0, 2, 0, 4, 0, 0},
    {3, 0, 0, 0, 0, 4},
    {0, 0, 0, 3, 0, 3},
    {0, 4, 0, 0, 2, 0},
    {0, 0, 4, 0, 0, 1}
};
int arry1[6][6] = {
    {0, 5, 0, 0, 2, 0},
    {2, 0, 4, 0, 0, 2},
    {0, 0, 0, 0, 0, 3},
    {0, 0, 0, 2, 3, 0},
    {0, 0, 2, 0, 0, 0},
    {0, 2, 0, 4, 0, 0}
};
int arry2[6][6] = {
    {0, 2, 0, 2, 0, 3},
    {1, 0, 4, 0, 0, 1},
    {0, 4, 0, 0, 0, 0},
    {0, 0, 2, 0, 4, 0},
    {3, 0, 0, 0, 1, 0},
    {0, 0, 0, 2, 0, 0}
};
void SparseMatrix::InitMatrix(int count)
{
    Terms=0;
    int r,c,s=0,val,m;
    //cout<<"����Ҫ�����ľ����������������";
    //cin>>r>>c;
    r=6;  //��ʱ��������
    c=6;  //��ʱ��������
    Rows=r;
    Cols=c;
    //cout<<"����������и�Ԫ�ص�ֵ��������"<<r*c<<"������"<<endl;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            //cin>>val;
            if(count==0) //��ʱ��������
                val=arry[i][j];
            else if(count==1)
                val=arry1[i][j];
            else
                val=arry2[i][j];
            
            if(val!=0)
            {
                smArray[s].row=i;
                smArray[s].col=j;
                smArray[s].value=val;
                s++;
            }
        }
    }
    
    Terms=s;
    int *num=new int[r];
 
    for(m=0;m<Rows;m++)
        num[m]=0;
 
    for(m=0;m<Terms;m++)
        ++num[smArray[m].row];
    
    cpot[0]=0;
 
    for(m=1;m<Rows;m++)
        cpot[m]=cpot[m-1]+num[m-1];
    
}
 
SparseMatrix SparseMatrix::Transpose1()
{
    SparseMatrix b;
    b.Rows=Cols;
    b.Cols=Rows;
    b.Terms=Terms;
    if(b.Terms)
    {
        int currentB=0;
        for(int c=0;c<Cols;c++)
            for(int i=0;i<Terms;i++)
                if(smArray[i].col==c)//�ҵ�c���е�Ԫ��
                {
                    b.smArray[currentB].row=c;
                    b.smArray[currentB].col=smArray[i].row;
                    b.smArray[currentB].value=smArray[i].value;
                    currentB++;
                }
    }
    return b;
}
 
SparseMatrix SparseMatrix::Transpose2()
{
    SparseMatrix b;
    b.Rows=Cols;
    b.Cols=Rows;
    b.Terms=Terms;
    
    int *num;
    int *cpot;
    int c;
    num=new int[Cols];
    cpot=new int[Cols];
 
    if(b.Terms)
    {
        for(c=0;c<Cols;c++)
            num[c]=0;
    
        for(c=0;c<b.Terms;c++)
            ++num[smArray[c].col];
        cpot[0]=0;
        
        for(c=1;c<Cols;c++)
            cpot[c]=cpot[c-1]+num[c-1];
        
        for(int p=0;p<b.Terms;p++)
        {
            int j=smArray[p].col;
            int q=cpot[j];
            b.smArray[q].row=smArray[p].col;
            b.smArray[q].col=smArray[p].row;
            b.smArray[q].value=smArray[p].value;
            ++cpot[j];
        }
    }
    return b;
}
 
 
bool SparseMatrix::Multiply(SparseMatrix b,SparseMatrix &q)
{
    /*
    ������������ĳ˻�����C��װ
    ������ڶ���ת�õ��㷨һ������������ÿ����������һ�����飬������¼ÿһ�е�һ������ֵ��
    �ھ���smArray[]�е�λ�ã�����������cpot[],�������ṹ��ϡ�����������߼�����˳���
    ����������£�
    1.    ���ھ���a��Q��������Ȳ���C��������Ϊ������д洢��������a�������е�ɨ�衣
    2.    ʹQ�Ĵ����߼������ŵ��������Ԫ����Q.terms+1���Ա�ʾ���е��׸�Ԫ�ص���š�
    3.    �������ҵ�a�ķ���Ԫ������������ֵΪb���кţ���b�����е�ɨ�裬�����ڣ�
          �����μ������ǣ�������ֵ�ۼӵ�һ����b�������Ӧ����Ԫ����ֵΪ��ŵ���ʱ����q_sum[q_col]�С�
    4.    ��a�ĵ�ǰ�����ɨ��󣬽�q_sum[q_col]��Ϊ0��ֵ��ѹ�뵽Q�������Ԫ�飬�ۼ�Q.Terms
    */
    
    int t1,t2,q_col;
    int *q_sum;//���ڴ�Ž������ʱ����
    
    if(this->Cols!=b.Rows)
        return false;
    
    q.Rows=this->Rows;
    q.Cols=b.Cols;
    q.Terms=0;
    q_sum=new int[b.Cols];
    if(this->Terms*b.Terms!=0)
    {
        for(int a_row=0;a_row<this->Rows;a_row++)//��a��ÿһ��Ϊ��׼����������
        {
            for(int i=0;i<b.Cols;i++)
                q_sum[i]=0;
            
            q.cpot[a_row]=q.Terms;
            
            if(a_row<this->Rows-1)
                t1=this->cpot[a_row+1];
            else
                t1=this->Terms;
            
            for(int p=this->cpot[a_row];p<t1;p++)
            {
                int b_row=this->smArray[p].col;
                
                if(b_row<b.Rows-1)
                    t2=b.cpot[b_row+1];
                else
                    t2=b.Terms;
                
                for(int q=b.cpot[b_row];q<t2;q++)
                {
                    q_col=b.smArray[q].col;
                    q_sum[q_col]+=this->smArray[p].value*b.smArray[q].value;
                }
            }
            
            for(q_col=0;q_col<q.Cols;q_col++)
                if(q_sum[q_col])
                {
                    q.smArray[q.Terms].row=a_row;
                    q.smArray[q.Terms].col=q_col;
                    q.smArray[q.Terms].value=q_sum[q_col];
                    ++q.Terms;
                }
        }
    }
    return true;
}
 
bool SparseMatrix::Add(SparseMatrix b,SparseMatrix &c)
{
    /*
    ��������������ģ�һ��ɨ����������a,b��smArray[]�е�ÿ�����ݣ�
    �Ƚ��������ݣ�����к���ͬ����Ƚ��кţ����кŲ�������к�С�Ĵ������c
    ��smArray[]�У����к���ȣ�����㣬��������㣬�ٴ���c�У�
    ���a�ĵ�ǰ���к�С��b�ĵ�ǰ���кţ���ô�ͽ�a�������c����֮����b
    */
    if(this->Rows!=b.Rows||this->Cols!=b.Cols)
        return false;
    int sum=0;
    int p=0;//ָ��a�ĵ�ǰ��
    int t=0;//ָ��b�ĵ�ǰ��
    int k=0;//ָ��c�ĵ�ǰ��
    while( p<this->Terms && t<b.Terms)
    {
        if(this->smArray[p].row==b.smArray[t].row)
        {
            if(this->smArray[p].col==b.smArray[t].col)
            {
                sum=this->smArray[p].value+b.smArray[t].value;
                if(sum)
                {
                    c.smArray[k].row=b.smArray[t].row;
                    c.smArray[k].col=b.smArray[t].col;
                    c.smArray[k].value=sum;
                    k++;p++;t++;
                }
            }
            else if(this->smArray[p].col<b.smArray[t].col)
            {
                c.smArray[k].row=this->smArray[p].row;
                c.smArray[k].col=this->smArray[p].col;
                c.smArray[k].value=this->smArray[p].value;
                k++;p++;
            }
            else
            {
                c.smArray[k].row=b.smArray[t].row;
                c.smArray[k].col=b.smArray[t].col;
                c.smArray[k].value=b.smArray[t].value;
                k++;t++;
            }
        }
        else if(this->smArray[p].row<b.smArray[t].row)
        {
            c.smArray[k].row=this->smArray[p].row;
            c.smArray[k].col=this->smArray[p].col;
            c.smArray[k].value=this->smArray[p].value;
            k++;p++;
        }
        else
        {
            c.smArray[k].row=b.smArray[t].row;
            c.smArray[k].col=b.smArray[t].col;
            c.smArray[k].value=b.smArray[t].value;
            k++;t++;
        }
    }
    while(p<this->Terms)
    {
        c.smArray[k].row=this->smArray[p].row;
        c.smArray[k].col=this->smArray[p].col;
        c.smArray[k].value=this->smArray[p].value;
        k++;p++;
    }
    while(t<b.Terms)
    {
        c.smArray[k].row=b.smArray[t].row;
        c.smArray[k].col=b.smArray[t].col;
        c.smArray[k].value=b.smArray[t].value;
        k++;t++;
    }
    c.Rows=b.Rows;
    c.Cols=b.Cols;
    c.Terms=k;
    return true;
}
 
void SparseMatrix::print()//�����Ԫ��
{
    int p=Terms;
    for(int i=0;i<p;i++)
        cout<<"smArray["<<smArray[i].row<<"]["<<smArray[i].col<<"]= "<<smArray[i].value<<endl;
    cout<<endl;
}
void SparseMatrix::print1()//�������
{
    int m=0;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(smArray[m].row==i&&smArray[m].col==j)
            {
                cout<<smArray[m].value<<" ";
                m++;
            }
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    SparseMatrix M,Z,T,Y,K,L;
    
    cout<<"���� M Ϊ��"<<endl;
    M.InitMatrix(0);
    M.print();
    M.print1();
    
    cout<<"���� M ��ת��Ϊ: "<<endl;
    K=M.Transpose2();
    //Z=M.Transpose1();
    K.print();
    K.print1();
    
    cout<<"���� Z Ϊ��"<<endl;
    Z.InitMatrix(1);
    Z.print();
    Z.print1();
    if(M.Multiply(T,Y))
    {
        cout<<"���� T ����� M ���Ϊ��"<<endl;
        Y.print();
        Y.print1();
    }
    
    cout<<"���� T Ϊ��"<<endl;
    T.InitMatrix(2);
    T.print();
    T.print1();
    if(M.Add(T,L))
    {
        cout<<"���� M �;��� T ���Ϊ��"<<endl;
        L.print();
        L.print1();
    }
    return 0;
}
/*
 //���ֻչʾ����������㡰���С��󣬳������п��ڿ����һ�����������ԡ����ҵ������֡�,���ڡ���Ļ����߶ȡ�Ϊ1000�Ϳ�����

 Ϊ�˼�������˲��٣����˺þã���ʵ�����Ҳ���ᣬ��ģ���ģ���ģ�
 �������Ϊ�������ö�����Ҷ���׼�����ˣ�׼��ƽ��

 ���� M Ϊ��
 smArray[0][0]= 1
 smArray[1][1]= 2
 smArray[1][3]= 4
 smArray[2][0]= 3
 smArray[2][5]= 4
 smArray[3][3]= 3
 smArray[3][5]= 3
 smArray[4][1]= 4
 smArray[4][4]= 2
 smArray[5][2]= 4
 smArray[5][5]= 1

 1 0 0 0 0 0
 0 2 0 4 0 0
 3 0 0 0 0 4
 0 0 0 3 0 3
 0 4 0 0 2 0
 0 0 4 0 0 1

 ���� M ��ת��Ϊ:
 smArray[0][0]= 1
 smArray[0][2]= 3
 smArray[1][1]= 2
 smArray[1][4]= 4
 smArray[2][5]= 4
 smArray[3][1]= 4
 smArray[3][3]= 3
 smArray[4][4]= 2
 smArray[5][2]= 4
 smArray[5][3]= 3
 smArray[5][5]= 1

 1 0 3 0 0 0
 0 2 0 0 4 0
 0 0 0 0 0 4
 0 4 0 3 0 0
 0 0 0 0 2 0
 0 0 4 3 0 1

 ���� Z Ϊ��
 smArray[0][1]= 5
 smArray[0][4]= 2
 smArray[1][0]= 2
 smArray[1][2]= 4
 smArray[1][5]= 2
 smArray[2][5]= 3
 smArray[3][3]= 2
 smArray[3][4]= 3
 smArray[4][2]= 2
 smArray[5][1]= 2
 smArray[5][3]= 4

 0 5 0 0 2 0
 2 0 4 0 0 2
 0 0 0 0 0 3
 0 0 0 2 3 0
 0 0 2 0 0 0
 0 2 0 4 0 0

 ���� T Ϊ��
 smArray[0][1]= 2
 smArray[0][3]= 2
 smArray[0][5]= 3
 smArray[1][0]= 1
 smArray[1][2]= 4
 smArray[1][5]= 1
 smArray[2][1]= 4
 smArray[3][2]= 2
 smArray[3][4]= 4
 smArray[4][0]= 3
 smArray[4][4]= 1
 smArray[5][3]= 2

 0 2 0 2 0 3
 1 0 4 0 0 1
 0 4 0 0 0 0
 0 0 2 0 4 0
 3 0 0 0 1 0
 0 0 0 2 0 0

 ���� M �;��� T ���Ϊ��
 smArray[0][0]= 1
 smArray[0][1]= 2
 smArray[0][3]= 2
 smArray[0][5]= 3
 smArray[1][0]= 1
 smArray[1][1]= 2
 smArray[1][2]= 4
 smArray[1][3]= 4
 smArray[1][5]= 1
 smArray[2][0]= 3
 smArray[2][1]= 4
 smArray[2][5]= 4
 smArray[3][2]= 2
 smArray[3][3]= 3
 smArray[3][4]= 4
 smArray[3][5]= 3
 smArray[4][0]= 3
 smArray[4][1]= 4
 smArray[4][4]= 3
 smArray[5][2]= 4
 smArray[5][3]= 2
 smArray[5][5]= 1

 1 2 0 2 0 3
 1 2 4 4 0 1
 3 4 0 0 0 4
 0 0 2 3 4 3
 3 4 0 0 3 0
 0 0 4 2 0 1
 */