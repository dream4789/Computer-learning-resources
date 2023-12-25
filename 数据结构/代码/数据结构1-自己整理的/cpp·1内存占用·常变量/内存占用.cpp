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
    C(int a,int b,int c):B(a,b),A(a)//注意此处
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
    D(int a,int b,int c,int d,int e):C(a,b,c),E(a,e),A(a)//注意此处
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
};//sizeof(Y)=4(X副本)+8(虚表指针)+4(自己变量)=16
class P :virtual public X
{
public:
    int p;
};//sizeof(P)=4(X副本)+8(虚表指针)+4(自己变量)=16

class Z :virtual public Y
{
public:
    int c;
};//sizeof(Z)= 16(Y副本)+8(虚表指针)+4(自己变量)+4(slign) = 32,如果这里改为直接继承，那么sizeof(Z)=24

class Q :public P,public Y
{
public:
    int q;
};//sizeof(Q)= 16(P副本)+16(Y副本)+8(虚表指针)+4(自己变量)-4(A重复) = 40

class R :public P,public Z
{
public:
    int q;
};//sizeof(R)= 16(P副本)+32(Z副本)+8(虚表指针)+4(自己变量)-4(A重复) = 56

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
    
    cout<<"注意A的构造函数调用了几次" <<endl;
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
注意A的构造函数调用了几次
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




 虚继承：(虚基类指针在64位机器上为8 bytes)
 class B 和 class E 内部存在一个虚基类指针，指向各自的virtual base class A subobject，64位机器中指针为8 bytes。若class A为空，sizeof为 1 btye，编译器对empty virtual base class做了优化，继承时会节省 class A 中的 1 byte
 class A 中有 int 为 4 byte
 class B 和 class E内部继承了 class A 的虚基类指针，大小为 4(B) + 8(A虚) +4(A)= 16
 class C 内部继承了 class B ，大小为 4(C) + 8(A虚) + 4(B) + 4(A) = 24
 class D 内部分别继承了的 class C 和 class E 的虚基类指针，大小就是 4(C) + 4(E) + 8(A虚) + 8(A虚) + 4(B) + 4(A) = 40
 
 内存对齐：
 实际的计算机系统对基本类型数据在内存中存放的位置有限制，它们会要求这些数据的首地址的值是某个数k（通常它为4或8）的倍数
 存在alignment（内存对齐），在64位的机器上，通常alignment为8 bytes，以使bus的“运输量”达到最高效率（内存取址方便）
 当有char和int的结构体时，sizeof应为5 type，但内存对齐到8 type
 64位内存对齐是8的倍数
 32位内存对齐是4的倍数
 
 
 类中有虚函数的时候有一个指向虚函数的指针（VPTR/vpointer）,64位中 8 byte
 每当创建一个包含有虚函数的类或从包含有虚函数的类派生一个类时，这个类创建一个虚函数表（VTABLE）保存该类所有虚函数的地址
 虚承继的情况：由于涉及到虚函数表和虚基表，会同时增加一个（多重虚继承下对应多个）vfPtr指针指向虚函数表vfTable和一个vbPtr指针指向虚基表vbTable，这两者所占的空间大小为：8（或8乘以多继承时父类的个数）
 
 虚函数的实现要求对象携带额外的信息，这些信息用于在运行时确定该对象应该调用哪一个虚函数。典型情况下，这一信息具有一种被称为 vptr（virtual table pointer，虚函数表指针）的指针的形式。vptr指向一个被称为 vtbl（virtual table，虚函数表）的函数指针数组，每一个包含虚函数的类都关联到vtbl。
 当一个对象调用了虚函数，实际的被调用函数通过下面的步骤确定：找到对象的vptr指向的vtbl，然后在vtbl中寻找合适的函数指针。
      虚拟函数的地址翻译取决于对象的内存地址，而不取决于数据类型(编译器对函数调用的合法性检查取决于数据类型)。如果类定义了虚函数，该类及其派生类就要生成一张虚拟函数表，即vtable。而在类的对象地址空间中存储一个该虚表的入口，占4个字节，这个入口地址是在构造对象时由编译器写入的。所以，由于对象的内存空间包含了虚表入口，编译器能够由这个入口找到恰当的虚函数，这个函数的地址不再由数据类型决定了。故对于一个父类的对象指针，调用虚拟函数，如果给他赋父类对象的指针，那么他就调用父类中的函数，如果给他赋子类对象的指针，他就调用子类中的函数(取决于对象的内存地址)。

 每当创建一个包含有虚函数的类或从包含有虚函数的类派生一个类时，编译器就会为这个类创建一个虚函数表（VTABLE）保存该类所有虚函数的地址，可以把VTABLE形象地看成一个函数指针数组，这个数组的每个元素存放的就是虚函数的地址。
 在每个带有虚函数的类中，编译器秘密地置入一指针，称为vpointer（缩写为V P T R），指向这个对象的VTABLE。
 当构造该派生类对象时，其成员VPTR被初始化指向该派生类的VTABLE。所以可以认为VTABLE是该类的所有对象共有的，在定义该类时被初始化；而VPTR则是每个类对象都有独立一份的，且在该类对象被构造时被初始化。
       通过基类指针做虚函数调用时（也就是做多态调用时），编译器静态地插入取得这个VPTR，并在VTABLE表中查找函数地址的代码，这样就能调用正确的函数使晚捆绑发生。为每个类设置VTABLE、初始化VPTR、为虚函数调用插入代码，所有这些都是自动发生的，所以我们不必担心这些。

 1）简单继承：

 总结一下VPTR 和 VTABLE 和类对象的关系:
     每一个具有虚函数的类都有一个虚函数表VTABLE，里面按在类中声明的虚函数的顺序存放着虚函数的地址，这个虚函数表VTABLE是这个类的所有对象所共有的，也就是说无论用户声明了多少个类对象，但是这个VTABLE虚函数表只有一个。
     在每个具有虚函数的类的对象里面都有一个VPTR虚函数指针，这个指针指向VTABLE的首地址，每个类的对象都有这么一种指针。

 2）虚继承：
      这个是比较不好理解的，对于虚继承，若派生类有自己的虚函数，则它本身需要有一个虚指针，指向自己的虚表。另外，派生类虚继承父类时，首先要通过加入一个虚指针来指向父类，因此有可能会有两个虚指针。

 （第一，在虚继承中，引入一个指针指向虚继承的基类；第二由于在基类中有虚函数，因此需要指针指向其虚函数表；第三，由于派生类自己本身也有自己的虚函数，因为采取的是虚继承，因此它自己的虚函数不会放到基类的虚函数表的后面，而是另外分配一个只存放自己的虚函数的虚函数表，于是又引入一个指针）
 
 
 计算一个类对象的大小时的规律：
 1、空类、单一继承的空类、多重继承的空类所占空间大小为：1（字节，下同）；
 2、一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间的；
 3、因此一个对象的大小≥所有非静态成员大小的总和；
 4、当类中声明了虚函数（不管是1个还是多个），那么在实例化对象时，编译器会自动在对象里安插一个指针vPtr指向虚函数表VTable；
 5、虚承继的情况：由于涉及到虚函数表和虚基表，会同时增加一个（多重虚继承下对应多个）vfPtr指针指向虚函数表vfTable和一个vbPtr指针指向虚基表vbTable，这两者所占的空间大小为：8（或8乘以多继承时父类的个数）；
 6、在考虑以上内容所占空间的大小时，还要注意编译器下的“补齐”padding的影响，即编译器会插入多余的字节补齐；
 7、类对象的大小=各非静态数据成员（包括父类的非静态数据成员但都不包括所有的成员函数）的总和+ vfptr指针(多继承下可能不止一个)+vbptr指针(多继承下可能不止一个)+编译器额外增加的字节。
 
 E在前，C在后
 A commonly constructor is called <-虚基类构造函数
 E commonly constructor is called <-基类构造函数
 B commonly constructor is called <-基类构造函数
 C commonly constructor is called <-基类构造函数
 D commonly constructor is called <-该对象自身的构造函数
 D destructor is called
 C destructor is called
 B destructor is called
 E destructor is called
 A destructor is called
 
 C在前，E在后
 A commonly constructor is called <-虚基类构造函数
 B commonly constructor is called <-基类构造函数
 C commonly constructor is called <-基类构造函数
 E commonly constructor is called <-基类构造函数
 D commonly constructor is called <-该对象自身的构造函数
 D destructor is called
 E destructor is called
 C destructor is called
 B destructor is called
 A destructor is called

 */
