#include <iostream>
#include <thread>  //thread�����߳�
#include <unistd.h>  //sleep()����
#include <mutex>  //������
using namespace std;

//���߳̾���
mutex apple_mu;  //�̻߳������
mutex orange_mu;
int people_num = 20;  //����
int num=0;

//ˮ����
class Fruit
{
public:
    Fruit();
    virtual ~Fruit();
    virtual void grow(){};
    virtual void bear(){};
    virtual void wxpay(){};
    virtual void zfbpay(){};
    virtual void ylpay(){};
    virtual void paypal(){};
protected:
};
Fruit::Fruit(){cout<<"԰���ϸ�"<<endl;}
Fruit::~Fruit(){cout<<"԰������ؼ�"<<endl;}

//������
class Factory
{
public:
    Factory();
    virtual ~Factory();
    virtual Fruit* createFruit()=0;
protected:
};
Factory::Factory(){}
Factory::~Factory(){}

//������
class Orange:public Fruit
{
public:
    static Orange* GetInstance();
    ~Orange();
    virtual void grow();
    virtual void bear();
    virtual void wxpay();
    virtual void zfbpay();
    virtual void ylpay();
    virtual void paypal();
private:
    Orange();
    static Orange* instance_Orange;
};
Orange* Orange::instance_Orange=0;
Orange* Orange::GetInstance()
{
    if(instance_Orange==0)
        instance_Orange=new Orange();
    return instance_Orange;
}
Orange::Orange(){cout<<"԰����ʼ��ֲ orange"<<endl;}
Orange::~Orange(){cout<<"���� �������"<<endl;}

void Orange::grow(){cout<<"���� �����С���"<<endl;}
void Orange::bear(){cout<<"���� �����ˡ���"<<endl;}
void Orange::wxpay()
{
    while (num<=people_num)
    {
        orange_mu.lock();     //ͬ��������
        cout<<"���ӣ�΢�ŵ���"<<num<<endl;
        num++;
        orange_mu.unlock();  //�������
    }
}
void Orange::zfbpay()
{
    while (num<=people_num)
    {
        orange_mu.lock();     //ͬ��������
        cout<<"���ӣ�֧��������"<<num<<endl;
        num++;
        orange_mu.unlock();  //�������
    }
}
void Orange::ylpay()
{
    while (num<=people_num)
    {
        orange_mu.lock();     //ͬ��������
        cout<<"���ӣ���������"<<num<<endl;
        num++;
        orange_mu.unlock();  //�������
    }
}
void Orange::paypal()
{
    while (num<people_num)
    {
        orange_mu.lock();     //ͬ��������
        cout<<"���ӣ�PayPal����"<<num<<endl;
        num++;
        orange_mu.unlock();  //�������
    }
}
//���ӹ���
class OrangeFactory:public Factory
{
public:
    ~OrangeFactory();
    Fruit* createFruit();
    static OrangeFactory* GetInstance();
    static Factory* OrangeFactory_thread();
private:
    OrangeFactory();
    static OrangeFactory* instance_OrangeFactory;
};
OrangeFactory* OrangeFactory::instance_OrangeFactory = 0;
OrangeFactory::OrangeFactory(){cout<<"<>  ���ӹ����������  <>"<<endl;}
OrangeFactory::~OrangeFactory(){cout<<"<>  ���ӹ���������  <>"<<endl;}
Factory* OrangeFactory::OrangeFactory_thread()
{
    Factory *result;
    thread *t1;
    t1=new thread([&] {result=OrangeFactory::GetInstance();}); //ƻ�����������߳�
    (*t1).detach();
    this_thread::sleep_for(chrono::milliseconds(10));
    return result;
}
Fruit* OrangeFactory::createFruit()
{
    cout<<"orange �����յ����Ӷ���,��֯԰����"<<endl;
    Fruit *some =Orange::GetInstance();  //�����ӵ���
    return some;
}
OrangeFactory* OrangeFactory::GetInstance()
{
    if(0==instance_OrangeFactory)
        instance_OrangeFactory=new OrangeFactory;  //�����ӹ���
    return instance_OrangeFactory;
}

//ƻ����
class Apple:public Fruit
{
public:
    static Apple* GetInstance();
    ~Apple();
    virtual void grow();
    virtual void bear();
    virtual void wxpay();
    virtual void zfbpay();
    virtual void ylpay();
    virtual void paypal();
private:
    Apple();
    static Apple* instance_Apple;
};
Apple* Apple::instance_Apple=0;
Apple* Apple::GetInstance()
{
    if(instance_Apple==0)
        instance_Apple=new Apple();
    return instance_Apple;
}
Apple::Apple(){cout<<"԰����ʼ��ֲ apple"<<endl;}
Apple::~Apple(){cout<<"���� �������"<<endl;}

void Apple::grow(){cout<<"ƻ�� �ɳ��С���"<<endl;}
void Apple::bear(){cout<<"ƻ�� �����ˡ���"<<endl;}
void Apple::wxpay()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //ͬ��������
        cout<<"ƻ����΢�ŵ���"<<num<<endl;
        num++;
        apple_mu.unlock();   //�������
    }
}
void Apple::zfbpay()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //ͬ��������
        cout<<"ƻ����֧��������"<<num<<endl;
        num++;
        apple_mu.unlock();   //�������
    }
}
void Apple::ylpay()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //ͬ��������
        cout<<"ƻ������������"<<num<<endl;
        num++;
        apple_mu.unlock();  //�������
    }
}
void Apple::paypal()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //ͬ��������
        cout<<"ƻ����PayPal����"<<num<<endl;
        num++;
        apple_mu.unlock();   //�������
    }
}
//ƻ������
class AppleFactory:public Factory
{
public:
    ~AppleFactory();
    Fruit* createFruit();
    static AppleFactory* GetInstance();
    static Factory* AppleFactory_thread();
private:
    AppleFactory();
    static AppleFactory* instance_AppleFactory;
};
AppleFactory* AppleFactory::instance_AppleFactory=0;
AppleFactory::AppleFactory(){cout<<"<>  ƻ�������������  <>"<<endl;}
AppleFactory::~AppleFactory(){cout<<"<>  ƻ������������  <>"<<endl;}
Factory* AppleFactory::AppleFactory_thread()
{
    Factory *result;
    thread *t2;
    t2=new thread([&] {result=AppleFactory::GetInstance();}); //ƻ�����������߳�
    (*t2).detach();
    this_thread::sleep_for(chrono::milliseconds(10));//����
    //�ӵ�ǰʱ�俪ʼ������ǰ�߳�ֱ��rel_time��һ��ʱ�䣩���ʱ���ȥ�������߳�����ָ��
    return result;
}

Fruit* AppleFactory::createFruit()
{
    cout<<"apple �����յ�ƻ������,��֯԰����"<<endl;
    Fruit *some =Apple::GetInstance();  //��ƻ������
    return some;
}
AppleFactory* AppleFactory::GetInstance()
{
    if(instance_AppleFactory==0)
        instance_AppleFactory=new AppleFactory;  //��ƻ������
    return instance_AppleFactory;
}
//ѡ��ˮ��
void shop_show(void)
{
    cout<<endl;
    cout<<"[--------SHOP--------]"<<endl;
    cout<<"|  a.ƻ��      b.����  |"<<endl;
    cout<<"|  c.����      d.����  |"<<endl;
    cout<<endl;
}
//֧����ʽ
void pay_show(void)
{
    cout<<endl;
    cout<<"[-----------֧����ʽ-----------]"<<endl;
    cout<<"|    1.΢��         2.֧����    |"<<endl;
    cout<<"|    3.����         4.PayPal   |"<<endl;
    cout<<endl;
}
Factory * shop_choose(string name)  //ѡ��ˮ��
{
    if(name == "a")
    {
        cout<<">>>>�̵������򹤳����� apple ����>>>>"<<endl;
        Factory *some=AppleFactory::AppleFactory_thread();  //��ƻ�������߳�
        return some;
    }
    else if(name == "b")
    {
        cout<<">>>>�̵������򹤳����� orange ����>>>>"<<endl;
        Factory *some=OrangeFactory::OrangeFactory_thread();  //�����ӹ����߳�
        return some;
    }
    else
    {
        cout<<"����������лл�������ܽ���"<<endl;
        exit(0);
    }
}
void wx_pay(Fruit *pFruit)
{
    pFruit->wxpay();
}
void zfb_pay(Fruit *pFruit)
{
    pFruit->zfbpay();
}
void yl_pay(Fruit *pFruit)
{
    pFruit->ylpay();
}
void PayPal_pay(Fruit *pFruit)
{
    pFruit->paypal();
}
void pay_way(Fruit *pFruit)  //֧���߳�
{
    thread task1(wx_pay, pFruit);
    thread task2(zfb_pay, pFruit);
    thread task3(yl_pay, pFruit);
    thread task4(PayPal_pay, pFruit);
    task1.join();
    task2.join();
    task3.join();
    task4.join();
}
int main()
{
    Factory *pFactory;
    Fruit *pFruit;

    cout<<"\n��ӭ���٣�"<<endl;
    char a;
    do{
        shop_show();     //ѡ��ˮ��
        cout<<"��ѡ���ˮ����:";
        string choose;
        cin>>choose;
        
        cout<<"�ж�������ˮ��:";  //���߳���
        cin>>people_num;
        
        pFactory = shop_choose(choose);
        pFruit = pFactory->createFruit();
        pFruit->grow();
        pFruit->bear();

        pay_show();
        pay_way(pFruit);
        
        cout<<"\n�������������������ַ�����   ���� # "<<endl;
        cin>>a;
        num=0;

    }while(a!='#');
    
    cout<<endl;
    delete pFruit;
    delete pFactory;
    
    cout<<"\n��ӭ�´ι��٣�����"<<endl;
    return 0;
}
//�����vs2019����vs codeӦ�ÿ������У�vc6��c++98�汾�����̹߳�����c++11�汾���¹��ܣ�vc6��֧��

/*
�����
 
 ��ӭ���٣�

 [--------SHOP--------]
 |  a.ƻ��      b.����  |
 |  c.����      d.����  |

 ��ѡ���ˮ����:a
 �ж�������ˮ��:10
 >>>>�̵������򹤳����� apple ����>>>>
 <>  ƻ�������������  <>
 apple �����յ�ƻ������,��֯԰����
 ԰���ϸ�
 ԰����ʼ��ֲ apple
 ƻ�� �ɳ��С���
 ƻ�� �����ˡ���

 [-----------֧����ʽ-----------]
 |    1.΢��         2.֧����    |
 |    3.����         4.PayPal   |

 ƻ����΢�ŵ���0
 ƻ������������1
 ƻ������������2
 ƻ������������3
 ƻ������������4
 ƻ������������5
 ƻ������������6
 ƻ������������7
 ƻ������������8
 ƻ������������9
 ƻ������������10
 ƻ����֧��������11
 


 */



/*
 ������ʹ�����̵߳�һ������
 ����������������ʹ�����߳����ǻᷢ�֣����ǲ��ܰѳ�ʼ��������Ϊ��ĳ�Ա����������Ҫ�ѳ�Ա�������ó�static���͵Ĳſ��ԣ�����������Ƶ�һ�����⣬����static�����Ա�������ܵ��÷�static�ı�����Ա
 ������һ����ȫ�����ķ�����
 thread sendtask(bind(&client::sendata, this));//����client���������
 
 //�����߳� ���� int pthread_join(pthread_t thread, void **retval);
 ����pthread_join()��ʹ�õ�ǰ�߳������ȴ�
 ��Ŀ���߳��˳��������������أ�Ȼ���߳���Դ����
 Ŀ�꺯��������joinable�ģ��̴߳�����Ĭ�Ͼ���joinable��
 ���retval���ǿ�ָ�룬��ô����retval����Ŀ���߳��˳�״̬
 �����ǰ�߳��ڵȴ����̱�ɱ������ôĿ���̻߳��Ǽ���joinable
 �������߳�ͬʱjoinһ��Ŀ���߳�

 //�����߳� ���� int pthread_detach(pthread_t thread);
 pthread_detach��һ���߳���joinableת����detached
 �����̵߳ĺô����߳��˳���ʡ����join�Ĳ��裬�Լ�������Դ
 �Ѿ�����detached���߳������ٴ�detached
 
 //join��detach������
 join()������ǰ���Ѿ��ᵽ�����̵߳ȴ����߳̽�������ִ����һ�������У�
 detach()�ǵ����̷߳ŷ����ң����������̲߳���ִ�У����̺߳������������ȴ�
 
 //��Ա����
 get_id()ÿ���߳̾���Ψһ���߳�Id��������get_id()��ȡ��ͬʱ��ֵ����ָʾ����ʶ���̵߳�״̬
 joinable������߳��Ƿ�ɱ�join�����thread�����Ƿ��ʶһ���(active)�Ŀ������̡߳�ȱʡ�����thread�����Ѿ����join��thread�����Ѿ�detach��thread���󶼲���joinable
 join�����øú�����������ǰ�̡߳�����������(caller)���ڵ��߳�ֱ����join��std::thread�����ʶ���߳�ִ�н�����
 detach������ǰ�̶߳����������ִ��ʵ������̶߳�����룬ʹ���̵߳�ִ�п��Ե������С�һ���߳�ִ����ϣ������������Դ���ᱻ�ͷš�
 native_handle���ú���������std::thread����ʵ����ص��߳̾����native_handle_type������thread��Ͳ���ϵͳSDK API֮�������������Linux g++(libstdc++)�native_handle_type��ʵ����pthread�����pthread_t���ͣ���thread��Ĺ��ܲ����������ǵ�Ҫ���ʱ��(����ı�ĳ���̵߳����ȼ�)������ͨ��thread��ʵ����native_handle()����ֵ��Ϊ������������ص�pthread�����ﵽĿ¼��
 swap�����������̶߳���������ĵײ�����
 operator=��moves the thread object
 hardware_concurrency����̬��Ա���������ص�ǰ���������Ӳ�������߳���Ŀ�������Ͽ�����Ϊ�������ĺ�����Ŀ��
 yield()���������������������߳���������״̬�����½�������ϵͳ���е��ȣ�����ǰ�̷߳���ִ�У�����ϵͳ������һ�̼߳���ִ��
 sleep_until()�����ǽ��߳�������ĳ��ָ����ʱ��(time point),���̲߳ű����»���
 sleep_for()�����ǽ��߳�����ĳ��ָ����ʱ��Ƭ(time span)�����̲߳ű����»��ѣ����������̵߳��ȵ�ԭ��ʵ������ʵ�ʿ��ܱ�sleep_duration����ʾ��ʱ��Ƭ����
 
 
 //#include <mutex>������
 mutex��������֤�߳�ͬ���ģ���ֹ��ͬ���߳�ͬʱ����ͬһ����������
 lock_guard��ʹ��lock_guard����԰�ȫ�����ǻ���������ģ��ܹ��Խ��������ö��󴴽�ʱ��������m.lock()һ����û����������������ڽ���ʱ�������Զ�����(unlock)��������Ϊĳ���߳��쳣�˳���Ӱ�������߳�
 
 //�õ��߳�����
 ʹ��getName�Ϳ���ֱ�ӵõ��̵߳�����
 
 //ע��
 �߳�ֻ�ܱ�move�����ܱ�����,�߳̿���ִ��һ�п��Ա����õĽṹ��������ȣ�
 ÿ����������ö��ٸ��̸߳�Ч��ɲ�������cpu�ĺ������йأ����෴���ᵼ��Ч�ʵͣ�
 
 //�ŵ�
 �����з���ֵ�����������쳣
 
 //�߳��������ڵ�����״̬
 �½�(���Ǹո�new������ʱ��)
 ����(���ǵ���start��ʱ��)
 ����
 ����
 ����
 
 �����̵߳ĳ����ķ�����
 1.join���ǽ��̼߳��뵽��һ���߳���ȥ����������ɲ��ǲ�����ִ�С�
 2.t.setDaemon(true)��ʾ�����߳�����Ϊ��̨�̣߳���ǰ̨�߳�ִ���������󣬺�̨���߳�Ҳ��ִ���ˡ�
 3.sleep������ʾ��ǰ���߳�˯һ�����cpu��ִ��˭ִ��˭
 4.yield��ֲ�Բ��ã�������ʹ�á���ʾ���ø�����ִ�У����Ǳ������ȼ����Լ��͵Ļ������ǻ�ִ���Լ���

 //sleep��yield������;
 1.sleep���úܸɴ࣬����yield��һ��α���ӣ���Ҫ�����˵����ȼ���
 2.sleep֮�󣬽������ڶ�����״̬����yield���ھ�����״̬��
 3.sleep���쳣��yield�����쳣
 4.sleep����ֲ�Ը��ã�����ʹ�á�

 //�߳����ȼ�������
 Ĭ�ϵ�����¶���5���������̸߳ı����ȼ�֮����������������һ�¡������������߳������������ȼ���
 max 10 norm5 min1
 
 //ʲôʱ������̻߳�������壿
 һ�������߳�ʹ��һ��������Դ
 �����̵߳��������ڱ���ʹ�õ���Դ���������ڳ�
 ��ô���п������δ֪�Ĵ���
 

 ���磺���߳�ʹ��һ��ȫ�ֶ���(object)�����߳������һ���˳���
 ���ڳ����˳���˳����:
 1.��������
 2.���߳��˳�
 3.���߳��˳�
 ��ˣ������˳������У�ȫ�ֶ��������Լ���������������ʱ�������������ڽ������������١����ǣ����̻߳�û�������������߳���Ȼ�п��ܼ��������Ѿ������Ķ��������Ľ���ǰ�ȫ�˳����򣬽��ȴ�����δ֪�Ĵ���

 ������
 1.��Ҫʹ�÷����߳�
 2.�����̲߳�Ҫʹ�ù�����Դ
 3.���߳��˳�ǰ�����������̣߳����߳��������ģ�
 4.ʹ���������������̵߳ȴ����߳��˳������߳��Ǳ����ģ�
 5.ʹ�� void quick_exit (int status) ������ֱ���˳�����������������
 
 ��ʹ��quick_exit()������Ҫ����,ʹ�� int at_quick_exit( void (*func)(void) ) ������ע���˳�������
 PS
 quick_exit()ϵ�к���������<stdlib.h>�У���Windows��һ��������ͱ��������������汾���йأ���
 
 
 < thread > :����std::thread���Լ�std::this_thread�����ռ䡣�����̵߳ĺ��������� ������.
 < atomic > :����std::atomic��std::atomic_flag�࣬�Լ�һ��C����ԭ�����ͺ���C���ݵ�ԭ�Ӳ����ĺ�����
 < mutex > :�������뻥������ص����Լ��������ͺͺ���
 < future > :��������Provider�ࣨstd::promise��std::package_task��������Future�ࣨstd::future��std::shared_future���Լ���ص����ͺͺ�����
 < condition_variable > :����������������ص��࣬����std::condition_variable��std::condition_variable_any��
 
 
 �����ͨ�����ô��ݲ�����
 calss factor
 {
    void function(string& str)
    {
        cout<<"hello"+str<<endl;
    }
 }
 ��Ӧ�ĵ��ò���Ӧ���ǣ�
 thread t((function()),std::ref(s));
 ������õ�ʱ���ǣ�
 thread t((function()),s);
 ���ܱ����õķ��������ô���ֵ�ģ����ǲ�����Ӱ��ֵ����֮ʵ��
 ���þ��Ǳ����ĸ�����Լ��ٲ���Ҫ�ĸ��ƣ�

 ���û�����д��
 thread t((function()),move(s));
 �����߳�ֻ��д��move
 �磺
 thread t2=move��t����

 
 */