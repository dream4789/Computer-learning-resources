//
//  main.cpp
//  cpp���쳣�������ص���
//
//  Created by ���� on 2021/11/30.
//

#include <iostream>
#include <exception>  //�쳣��������Ϊһ�����࣬�쳣��
//#include <stdexcept>  //�쳣����,�Թ������exception����������
//���е��쳣�඼��һ��what()����������const char* ���ͣ�C����ַ�������ֵ�������쳣��Ϣ
//#include <cstdlib>  //abort()�Ŀ⺯��
//#include <assert.h>  //����

#define throw(...)  //c++98�汾��֧��

using namespace std;

class terminata {};
class MyType {};  //���࣬����Ĵ�С��sizeof����1
//����һ�����࣬�����κ�����Ļ������������Զ�Ϊ������һ��Ĭ�Ϲ��졢һ������Ĭ�Ϲ��졢һ��Ĭ�Ͽ�����ֵ��������һ��Ĭ������

class MyException:public exception  //�̳�excpetion
{
public:
    const char* what() const noexcept throw()  //�����׳�
    {
        return "ִ��";
    }
    //���һ������throw()�ĺ����ڲ�������throw������ڲ�ֱ��throw something���������ᷢ�ֲ�ָ����������ڲ�������һ������throw something�ĺ������������޷����֣�����ʱһ������ڲ��ĺ���throw�������abort
    // const noexcept �� throw() �ȼۣ��ɴ���
    //�ڴ�exception�����������������¶���һ����Ϊwhat()�������Ա����
};

struct X
{
    ~X() {};
};
void check_noexcept(void)
{
    X x;
    //int n;
    static_assert(noexcept(x.~X()), "Ouch!");  //�������������Ƿ���noexcept
    //��̬���ԣ�static_assert(�������ʽ��"��ʾ�ַ���")
    //static_assert(n>0, "value must > 0");//�������ʽ�в���ʹ�ñ���
}

void f() throw(double,int,const char *,MyType,MyException)//��Ҫ�ڿ�ͷ�� #define throw(...)
{
    int n;
    cout<<"Please input n:";
    cin>>n;
    if (1==n) throw MyException();  //����MyException()ȱʡ����
    if (2==n) throw MyType();  //����MyType()ȱʡ����
    if (3==n) throw "Hello";  //�� Hello ����һ���׳���e()����δ����������һ���׳����׵�main()
    if (4==n) throw 123;
    if (5==n) throw 123.45;  //�� 123.45 ����һ���׳����׵�e()����
    if (6==n) throw terminata();
    if (7==n) check_noexcept();
    cout<<"-----------end of f()----------"<<endl;
}
void e()
{
    try {
        f();
    }
    //������5
    catch(double e) {cout<<"double:"<<e<<endl;}// throw;}
    catch(terminata e) {throw terminata();}  //������mian�� terminata()
    cout<<"-----------end of e()----------"<<endl;
}


void terminator()  //��ϵͳ Ĭ��terminata() �޸�Ϊ terminator() ���洦��
{
    cout <<"����mian�����״���"<<endl;
    exit(0);
}
void (*old_terminate)() = set_terminate(terminator);  //������ terminata()


int main()
{
    try {
        e();
    }
    //������1��3,û�в���5
    catch(MyException e) {cout<<"MyException:"<<e.what()<<endl;}
    catch(const char *e) {cout<<"const char *:"<<e<<endl;}
    //catch(...) {cout<<"δ֪�쳣"<<endl;}   //���Բ����κδ�e()���׵���ʽ�������ã���mian��δ��׽�����׸�����ϵͳ����Ĭ��terminata()����Ĭ�Ϸ������棩
    cout<<"-----------end of mian()----------"<<endl;
    return 1;
}

//vs2019��vs codeӦ�ÿ������У�c++98���ƺܶ�

/*
���н����

Please input n:1
MyException:ִ��
-----------end of mian()----------

Please input n:2
����mian�����״���

Please input n:3
const char *:Hello
-----------end of mian()----------

Please input n:4
����mian�����״���

Please input n:5
double:123.45
-----------end of e()----------
-----------end of mian()----------

Please input n:6
����mian�����״���

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
 
 f() throw(type)  ���׳�ĳ���쳣
 f() throw()      �����׳�
 f() throw(...)   �������κ����͵��쳣
 
 
 noexcept��
 void swap(Type& x, Type& y) noexcept(noexcept(x.swap(y)))  //��ʾ�����޶���swap�������Բ������쳣
 {
     x.swap(y);
 }
 ����ʾ���������x.swap(y)�������쳣����ô����swap(Type& x, Type& y)һ���������쳣��

 ����ʹ��noexcept��
 �ƶ����캯����move constructor��
 �ƶ����亯����move assignment��
 ����������destructor��������������Ĭ�ϼ��Ϲؼ���noexcept��
 Ҷ�Ӻ�����Leaf Function����Ҷ�Ӻ�����ָ�ں����ڲ�������ջ�ռ䣬Ҳ����������������Ҳ���洢����ʧ�ԼĴ�����Ҳ�������쳣��
 
 
 abort();
 abort������ʱ������ֱ���˳����κζ���������������������
 
 
 throw                  �׳��쳣
 try catch              �����쳣
 exception e  e.what(); ���쳣��Ϣ�׳���
 
 
 C++�д����쳣�Ĺ��̣�
 ��ִ�г������쳣�����Բ��ڱ������д��������׳�һ��������Ϣ���������ݸ���һ���ĺ������������һ��������ˣ��ٴ�������һ����������һ������������ϴ���ֱ�����һ�����޷�����Ļ�������ϵͳ���Զ�����ϵͳ����terminate()�����������ú���abort()����ֹ����
 
 
 <stdexcept>ͷ�ļ����漸���������
 exception ���������
 runtime_error ����ʱ���󣺽�������ʱ���ܼ�⵽�ô���
 range_error ����ʱ�������ɵĽ���������������ֵ��Χ
 overflow_error ����ʱ���󣺼�������
 underflow_error ����ʱ���� ����������
 logic_error �߼����󣺿�������ǰ��⵽������
 domain_error �߼����󣺲����Ľ��ֵ������
 invalid_argument �߼����󣺲����ʵĲ���
 length_error �߼�������ͼ���� һ��������������󳤶ȵĶ���
 out_of_range �߼�����ʹ��һ��������Ч��Χ��ֵ
 
 */
