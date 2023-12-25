//
//  main.cpp
//  cpp·异常处理·二重调用
//
//  Created by 徐龙 on 2021/11/30.
//

#include <iostream>
#include <exception>  //异常处理，可作为一个基类，异常类
//#include <stdexcept>  //异常捕获,以公有类从exception派生而来的
//所有的异常类都有一个what()方法，返回const char* 类型（C风格字符串）的值，描述异常信息
//#include <cstdlib>  //abort()的库函数
//#include <assert.h>  //断言

#define throw(...)  //c++98版本不支持

using namespace std;

class terminata {};
class MyType {};  //空类，空类的大小（sizeof）是1
//声明一个空类，不做任何事情的话，编译器会自动为你生成一个默认构造、一个拷贝默认构造、一个默认拷贝赋值操作符，一个默认析构

class MyException:public exception  //继承excpetion
{
public:
    const char* what() const noexcept throw()  //不会抛出
    {
        return "执行";
    }
    //如果一个标明throw()的函数内部发生了throw：如果内部直接throw something，编译器会发现并指出；如果是内部调用了一个可能throw something的函数，编译器无法发现，运行时一旦这个内部的函数throw，程序会abort
    // const noexcept 与 throw() 等价，可代替
    //在从exception派生而来的类中重新定义一个名为what()的虚拟成员函数
};

struct X
{
    ~X() {};
};
void check_noexcept(void)
{
    X x;
    //int n;
    static_assert(noexcept(x.~X()), "Ouch!");  //测试析构函数是否含有noexcept
    //静态断言，static_assert(常量表达式，"提示字符串")
    //static_assert(n>0, "value must > 0");//常量表达式中不可使用变量
}

void f() throw(double,int,const char *,MyType,MyException)//需要在开头加 #define throw(...)
{
    int n;
    cout<<"Please input n:";
    cin>>n;
    if (1==n) throw MyException();  //调用MyException()缺省函数
    if (2==n) throw MyType();  //调用MyType()缺省函数
    if (3==n) throw "Hello";  //将 Hello 往上一级抛出，e()函数未捕获；再向上一级抛出，抛到main()
    if (4==n) throw 123;
    if (5==n) throw 123.45;  //将 123.45 往上一级抛出，抛到e()函数
    if (6==n) throw terminata();
    if (7==n) check_noexcept();
    cout<<"-----------end of f()----------"<<endl;
}
void e()
{
    try {
        f();
    }
    //捕获了5
    catch(double e) {cout<<"double:"<<e<<endl;}// throw;}
    catch(terminata e) {throw terminata();}  //继续向mian抛 terminata()
    cout<<"-----------end of e()----------"<<endl;
}


void terminator()  //将系统 默认terminata() 修改为 terminator() 代替处理
{
    cout <<"来自mian的上抛处理"<<endl;
    exit(0);
}
void (*old_terminate)() = set_terminate(terminator);  //重命名 terminata()


int main()
{
    try {
        e();
    }
    //捕获了1，3,没有捕获5
    catch(MyException e) {cout<<"MyException:"<<e.what()<<endl;}
    catch(const char *e) {cout<<"const char *:"<<e<<endl;}
    //catch(...) {cout<<"未知异常"<<endl;}   //可以捕获任何从e()上抛的形式，若禁用，则mian将未捕捉的上抛给操作系统，由默认terminata()处理（默认发出警告）
    cout<<"-----------end of mian()----------"<<endl;
    return 1;
}

//vs2019或vs code应该可以运行，c++98限制很多

/*
运行结果：

Please input n:1
MyException:执行
-----------end of mian()----------

Please input n:2
来自mian的上抛处理

Please input n:3
const char *:Hello
-----------end of mian()----------

Please input n:4
来自mian的上抛处理

Please input n:5
double:123.45
-----------end of e()----------
-----------end of mian()----------

Please input n:6
来自mian的上抛处理

Please input n:7
-----------end of f()----------
-----------end of e()----------
-----------end of mian()----------

 Please input n:8
-----------end of f()----------
-----------end of e()----------
-----------end of mian()----------
*/

/*
 
 f() throw(type)  会抛出某种异常
 f() throw()      不会抛出
 f() throw(...)   可能是任何类型的异常
 
 
 noexcept：
 void swap(Type& x, Type& y) noexcept(noexcept(x.swap(y)))  //表示其所限定的swap函数绝对不发生异常
 {
     x.swap(y);
 }
 它表示，如果操作x.swap(y)不发生异常，那么函数swap(Type& x, Type& y)一定不发生异常。

 鼓励使用noexcept：
 移动构造函数（move constructor）
 移动分配函数（move assignment）
 析构函数（destructor），析构函数是默认加上关键字noexcept的
 叶子函数（Leaf Function）。叶子函数是指在函数内部不分配栈空间，也不调用其它函数，也不存储非易失性寄存器，也不处理异常。
 
 
 abort();
 abort被调用时，程序将直接退出，任何对象的析构函数都不会调用
 
 
 throw                  抛出异常
 try catch              捕获异常
 exception e  e.what(); 将异常信息抛出来
 
 
 C++中处理异常的过程：
 在执行程序发生异常，可以不在本函数中处理，而是抛出一个错误信息，把它传递给上一级的函数来解决，上一级解决不了，再传给其上一级，由其上一级处理。如此逐级上传，直到最高一级还无法处理的话，运行系统会自动调用系统函数terminate()，再由它调用函数abort()，终止程序
 
 
 <stdexcept>头文件里面几个类的作用
 exception 最常见的问题
 runtime_error 运行时错误：仅在运行时才能检测到得错误
 range_error 运行时错误：生成的结果超出了有意义的值域范围
 overflow_error 运行时错误：计算上溢
 underflow_error 运行时错误 ：计算下溢
 logic_error 逻辑错误：可在运行前检测到得问题
 domain_error 逻辑错误：参数的结果值不存在
 invalid_argument 逻辑错误：不合适的参数
 length_error 逻辑错误：试图生成 一个超出改类型最大长度的对象
 out_of_range 逻辑错误：使用一个超出有效范围的值
 
 */
