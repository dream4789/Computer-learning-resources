#include<iostream>
#define maxtemr 100
using namespace std;

class SparseMatrix; //向前声明

class MatrixTerm//矩阵元素类
{
public:
    int row;//行
    int col;//列
    int value;//值
    friend SparseMatrix;
};

class SparseMatrix
{
private:
    int Rows;//行数
    int Cols;//列数
    int Terms;//非零项个数
    MatrixTerm smArray[maxtemr];//maxterm是常数，maxterm<<Rows*Cols
    int cpot[20];
public:
    void InitMatrix(int count);  //建立矩阵
    SparseMatrix Transpose1();   //矩阵转置算法1
    SparseMatrix Transpose2();   //矩阵转置算法2
    bool Multiply(SparseMatrix b,SparseMatrix &q);//矩阵相乘
    bool Add(SparseMatrix b,SparseMatrix &c);     //矩阵相加
    void print();   //打印三元表
    void print1();  //打印矩阵
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
    //cout<<"输入要创建的矩阵的行数和列数：";
    //cin>>r>>c;
    r=6;  //临时，简化输入
    c=6;  //临时，简化输入
    Rows=r;
    Cols=c;
    //cout<<"请输入矩阵中各元素的值，请输入"<<r*c<<"个整数"<<endl;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            //cin>>val;
            if(count==0) //临时，简化输入
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
                if(smArray[i].col==c)//找到c列中的元素
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
    返回两个矩阵的乘积，用C来装
    采用与第二种转置的算法一样的做法，给每个矩阵增加一个数组，用来记录每一行第一个非零值在
    在矩阵smArray[]中的位置，这个数组就是cpot[],有这样结构的稀疏矩阵叫做行逻辑连接顺序表
    计算过程如下：
    1.    由于矩阵a和Q的行数相等并且C语言以行为主序进行存储，所以以a进行逐行的扫描。
    2.    使Q的此行逻辑表的序号等于其非零元个数Q.terms+1，以表示其行的首个元素的序号。
    3.    从行中找到a的非零元，并以它的列值为b的行号，对b进行行的扫描，若存在，
          则依次计算它们，并把其值累加到一个以b中这个对应非零元的列值为序号的临时数组q_sum[q_col]中。
    4.    在a的当前行完成扫描后，将q_sum[q_col]不为0的值，压入到Q矩阵的三元组，累加Q.Terms
    */
    
    int t1,t2,q_col;
    int *q_sum;//用于存放结果的临时数组
    
    if(this->Cols!=b.Rows)
        return false;
    
    q.Rows=this->Rows;
    q.Cols=b.Cols;
    q.Terms=0;
    q_sum=new int[b.Cols];
    if(this->Terms*b.Terms!=0)
    {
        for(int a_row=0;a_row<this->Rows;a_row++)//以a的每一行为标准，进行运算
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
    计算过程是这样的，一次扫描两个矩阵a,b的smArray[]中的每个数据，
    比较两个数据，如果行号相同，则比较列号，若列号不想等则将列号小的存入矩阵c
    的smArray[]中，若列号相等，则计算，计算完非零，再存入c中；
    如果a的当前项行号小于b的当前项行号，那么就将a的项存入c，反之，存b
    */
    if(this->Rows!=b.Rows||this->Cols!=b.Cols)
        return false;
    int sum=0;
    int p=0;//指向a的当前项
    int t=0;//指向b的当前项
    int k=0;//指向c的当前项
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
 
void SparseMatrix::print()//输出三元表
{
    int p=Terms;
    for(int i=0;i<p;i++)
        cout<<"smArray["<<smArray[i].row<<"]["<<smArray[i].col<<"]= "<<smArray[i].value<<endl;
    cout<<endl;
}
void SparseMatrix::print1()//输出矩阵
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
    
    cout<<"矩阵 M 为："<<endl;
    M.InitMatrix(0);
    M.print();
    M.print1();
    
    cout<<"矩阵 M 的转置为: "<<endl;
    K=M.Transpose2();
    //Z=M.Transpose1();
    K.print();
    K.print1();
    
    cout<<"矩阵 Z 为："<<endl;
    Z.InitMatrix(1);
    Z.print();
    Z.print1();
    if(M.Multiply(T,Y))
    {
        cout<<"矩阵 T 与矩阵 M 相乘为："<<endl;
        Y.print();
        Y.print1();
    }
    
    cout<<"矩阵 T 为："<<endl;
    T.InitMatrix(2);
    T.print();
    T.print1();
    if(M.Add(T,L))
    {
        cout<<"矩阵 M 和矩阵 T 相加为："<<endl;
        L.print();
        L.print1();
    }
    return 0;
}
/*
 //如果只展示部分输出，点“运行”后，出现运行框，在框上右击，点击“属性”，找到“布局“,调节”屏幕缓冲高度”为1000就可以了

 为了简化输入改了不少，想了好久，其实这个我也不会，真的，真的，真的！
 如果不是为你整理，好多代码我都不准备看了，准备平躺

 矩阵 M 为：
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

 矩阵 M 的转置为:
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

 矩阵 Z 为：
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

 矩阵 T 为：
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

 矩阵 M 和矩阵 T 相加为：
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