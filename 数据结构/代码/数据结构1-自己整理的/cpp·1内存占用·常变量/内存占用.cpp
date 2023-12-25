#include <iostream>
using namespace std;
class A
{
private:
    int a;
public:
    A(int a)
    {
        this->a=a;
        cout<<"A commonly constructor is called\n";
    }
    ~A(){cout<<"A destructor is called\n";}
};//4

class B:virtual public A
{
private:
    int b;
public:
    B(int a,int b):A(a)
    {
        this->b=b;
        cout<<"B commonly constructor is called\n";
    }
    ~B(){cout<<"B destructor is called\n";}
};//4+4+8=16

class C:public B
{
private:
    int c;
public:
    C(int a,int b,int c):B(a,b),A(a)//ע��˴�
    {
        this->c=c;
        cout<<"C commonly constructor is called\n";
    }
    ~C(){cout<<"C destructor is called\n";}
};//4+16

class E:virtual public A
{
private:
    int e;
public:
    E(int a,int e):A(a)
    {
        this->e=e;
        cout<<"E commonly constructor is called\n";
    }
    ~E(){cout<<"E destructor is called\n";}
};

class D:public C,public E
{
private:
    int d;
public:
    D(int a,int b,int c,int d,int e):C(a,b,c),E(a,e),A(a)//ע��˴�
    {
        this->d=d;
        cout<<"D commonly constructor is called\n";
    }
    ~D(){cout<<"D destructor is called\n";}
};



class X
{
public:
    int a;
};//sizeof(X)=4

class W:public X
{
public:
    int d;
};//sizeof(W)=4+4=8
 
class Y :virtual public X
{
public:
    int b;
};//sizeof(Y)=4(X����)+8(���ָ��)+4(�Լ�����)=16
class P :virtual public X
{
public:
    int p;
};//sizeof(P)=4(X����)+8(���ָ��)+4(�Լ�����)=16

class Z :virtual public Y
{
public:
    int c;
};//sizeof(Z)= 16(Y����)+8(���ָ��)+4(�Լ�����)+4(slign) = 32,��������Ϊֱ�Ӽ̳У���ôsizeof(Z)=24

class Q :public P,public Y
{
public:
    int q;
};//sizeof(Q)= 16(P����)+16(Y����)+8(���ָ��)+4(�Լ�����)-4(A�ظ�) = 40

class R :public P,public Z
{
public:
    int q;
};//sizeof(R)= 16(P����)+32(Z����)+8(���ָ��)+4(�Լ�����)-4(A�ظ�) = 56

int main()
{
    cout<<"A:"<<sizeof(A)<<endl;
    cout<<"B:"<<sizeof(B)<<endl;
    cout<<"E:"<<sizeof(E)<<endl;
    cout<<"C:"<<sizeof(C)<<endl;
    cout<<"D:"<<sizeof(D)<<endl;
    
    cout<<"X:"<<sizeof(X)<<endl;
    cout<<"W:"<<sizeof(W)<<endl;
    cout<<"Y:"<<sizeof(Y)<<endl;
    cout<<"P:"<<sizeof(P)<<endl;
    cout<<"Z:"<<sizeof(Z)<<endl;
    cout<<"Q:"<<sizeof(Q)<<endl;
    cout<<"R:"<<sizeof(R)<<endl;
    
    cout<<"ע��A�Ĺ��캯�������˼���" <<endl;
    D d1(1,2,3,4,5);
    
    return 0;
}

/*
A:4
B:16
E:16
C:24
D:40
X:4
W:8
Y:16
P:16
Z:32
Q:40
R:56
ע��A�Ĺ��캯�������˼���
A commonly constructor is called
B commonly constructor is called
C commonly constructor is called
E commonly constructor is called
D commonly constructor is called
D destructor is called
E destructor is called
C destructor is called
B destructor is called
A destructor is called




 ��̳У�(�����ָ����64λ������Ϊ8 bytes)
 class B �� class E �ڲ�����һ�������ָ�룬ָ����Ե�virtual base class A subobject��64λ������ָ��Ϊ8 bytes����class AΪ�գ�sizeofΪ 1 btye����������empty virtual base class�����Ż����̳�ʱ���ʡ class A �е� 1 byte
 class A ���� int Ϊ 4 byte
 class B �� class E�ڲ��̳��� class A �������ָ�룬��СΪ 4(B) + 8(A��) +4(A)= 16
 class C �ڲ��̳��� class B ����СΪ 4(C) + 8(A��) + 4(B) + 4(A) = 24
 class D �ڲ��ֱ�̳��˵� class C �� class E �������ָ�룬��С���� 4(C) + 4(E) + 8(A��) + 8(A��) + 4(B) + 4(A) = 40
 
 �ڴ���룺
 ʵ�ʵļ����ϵͳ�Ի��������������ڴ��д�ŵ�λ�������ƣ����ǻ�Ҫ����Щ���ݵ��׵�ַ��ֵ��ĳ����k��ͨ����Ϊ4��8���ı���
 ����alignment���ڴ���룩����64λ�Ļ����ϣ�ͨ��alignmentΪ8 bytes����ʹbus�ġ����������ﵽ���Ч�ʣ��ڴ�ȡַ���㣩
 ����char��int�Ľṹ��ʱ��sizeofӦΪ5 type�����ڴ���뵽8 type
 64λ�ڴ������8�ı���
 32λ�ڴ������4�ı���
 
 
 �������麯����ʱ����һ��ָ���麯����ָ�루VPTR/vpointer��,64λ�� 8 byte
 ÿ������һ���������麯�������Ӱ������麯����������һ����ʱ������ഴ��һ���麯����VTABLE��������������麯���ĵ�ַ
 ��м̵�����������漰���麯������������ͬʱ����һ����������̳��¶�Ӧ�����vfPtrָ��ָ���麯����vfTable��һ��vbPtrָ��ָ�������vbTable����������ռ�Ŀռ��СΪ��8����8���Զ�̳�ʱ����ĸ�����
 
 �麯����ʵ��Ҫ�����Я���������Ϣ����Щ��Ϣ����������ʱȷ���ö���Ӧ�õ�����һ���麯������������£���һ��Ϣ����һ�ֱ���Ϊ vptr��virtual table pointer���麯����ָ�룩��ָ�����ʽ��vptrָ��һ������Ϊ vtbl��virtual table���麯�����ĺ���ָ�����飬ÿһ�������麯�����඼������vtbl��
 ��һ������������麯����ʵ�ʵı����ú���ͨ������Ĳ���ȷ�����ҵ������vptrָ���vtbl��Ȼ����vtbl��Ѱ�Һ��ʵĺ���ָ�롣
      ���⺯���ĵ�ַ����ȡ���ڶ�����ڴ��ַ������ȡ������������(�������Ժ������õĺϷ��Լ��ȡ������������)������ඨ�����麯�������༰���������Ҫ����һ�����⺯������vtable��������Ķ����ַ�ռ��д洢һ����������ڣ�ռ4���ֽڣ������ڵ�ַ���ڹ������ʱ�ɱ�����д��ġ����ԣ����ڶ�����ڴ�ռ�����������ڣ��������ܹ����������ҵ�ǡ�����麯������������ĵ�ַ�������������;����ˡ��ʶ���һ������Ķ���ָ�룬�������⺯���������������������ָ�룬��ô���͵��ø����еĺ����������������������ָ�룬���͵��������еĺ���(ȡ���ڶ�����ڴ��ַ)��

 ÿ������һ���������麯�������Ӱ������麯����������һ����ʱ���������ͻ�Ϊ����ഴ��һ���麯����VTABLE��������������麯���ĵ�ַ�����԰�VTABLE����ؿ���һ������ָ�����飬��������ÿ��Ԫ�ش�ŵľ����麯���ĵ�ַ��
 ��ÿ�������麯�������У����������ܵ�����һָ�룬��Ϊvpointer����дΪV P T R����ָ����������VTABLE��
 ����������������ʱ�����ԱVPTR����ʼ��ָ����������VTABLE�����Կ�����ΪVTABLE�Ǹ�������ж����еģ��ڶ������ʱ����ʼ������VPTR����ÿ��������ж���һ�ݵģ����ڸ�����󱻹���ʱ����ʼ����
       ͨ������ָ�����麯������ʱ��Ҳ��������̬����ʱ������������̬�ز���ȡ�����VPTR������VTABLE���в��Һ�����ַ�Ĵ��룬�������ܵ�����ȷ�ĺ���ʹ����������Ϊÿ��������VTABLE����ʼ��VPTR��Ϊ�麯�����ò�����룬������Щ�����Զ������ģ��������ǲ��ص�����Щ��

 1���򵥼̳У�

 �ܽ�һ��VPTR �� VTABLE �������Ĺ�ϵ:
     ÿһ�������麯�����඼��һ���麯����VTABLE�����水�������������麯����˳�������麯���ĵ�ַ������麯����VTABLE�����������ж��������еģ�Ҳ����˵�����û������˶��ٸ�����󣬵������VTABLE�麯����ֻ��һ����
     ��ÿ�������麯������Ķ������涼��һ��VPTR�麯��ָ�룬���ָ��ָ��VTABLE���׵�ַ��ÿ����Ķ�������ôһ��ָ�롣

 2����̳У�
      ����ǱȽϲ������ģ�������̳У������������Լ����麯��������������Ҫ��һ����ָ�룬ָ���Լ���������⣬��������̳и���ʱ������Ҫͨ������һ����ָ����ָ���࣬����п��ܻ���������ָ�롣

 ����һ������̳��У�����һ��ָ��ָ����̳еĻ��ࣻ�ڶ������ڻ��������麯���������Ҫָ��ָ�����麯���������������������Լ�����Ҳ���Լ����麯������Ϊ��ȡ������̳У�������Լ����麯������ŵ�������麯����ĺ��棬�����������һ��ֻ����Լ����麯�����麯��������������һ��ָ�룩
 
 
 ����һ�������Ĵ�Сʱ�Ĺ��ɣ�
 1�����ࡢ��һ�̳еĿ��ࡢ���ؼ̳еĿ�����ռ�ռ��СΪ��1���ֽڣ���ͬ����
 2��һ�����У��麯��������Ա������������̬��Ǿ�̬���;�̬���ݳ�Ա���ǲ�ռ�������Ĵ洢�ռ�ģ�
 3�����һ������Ĵ�С�����зǾ�̬��Ա��С���ܺͣ�
 4���������������麯����������1�����Ƕ��������ô��ʵ��������ʱ�����������Զ��ڶ����ﰲ��һ��ָ��vPtrָ���麯����VTable��
 5����м̵�����������漰���麯������������ͬʱ����һ����������̳��¶�Ӧ�����vfPtrָ��ָ���麯����vfTable��һ��vbPtrָ��ָ�������vbTable����������ռ�Ŀռ��СΪ��8����8���Զ�̳�ʱ����ĸ�������
 6���ڿ�������������ռ�ռ�Ĵ�Сʱ����Ҫע��������µġ����롱padding��Ӱ�죬������������������ֽڲ��룻
 7�������Ĵ�С=���Ǿ�̬���ݳ�Ա����������ķǾ�̬���ݳ�Ա�������������еĳ�Ա���������ܺ�+ vfptrָ��(��̳��¿��ܲ�ֹһ��)+vbptrָ��(��̳��¿��ܲ�ֹһ��)+�������������ӵ��ֽڡ�
 
 E��ǰ��C�ں�
 A commonly constructor is called <-����๹�캯��
 E commonly constructor is called <-���๹�캯��
 B commonly constructor is called <-���๹�캯��
 C commonly constructor is called <-���๹�캯��
 D commonly constructor is called <-�ö�������Ĺ��캯��
 D destructor is called
 C destructor is called
 B destructor is called
 E destructor is called
 A destructor is called
 
 C��ǰ��E�ں�
 A commonly constructor is called <-����๹�캯��
 B commonly constructor is called <-���๹�캯��
 C commonly constructor is called <-���๹�캯��
 E commonly constructor is called <-���๹�캯��
 D commonly constructor is called <-�ö�������Ĺ��캯��
 D destructor is called
 E destructor is called
 C destructor is called
 B destructor is called
 A destructor is called

 */
