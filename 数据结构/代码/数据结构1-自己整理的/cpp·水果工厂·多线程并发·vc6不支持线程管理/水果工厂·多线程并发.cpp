#include <iostream>
#include <thread>  //thread管理线程
#include <unistd.h>  //sleep()函数
#include <mutex>  //进程锁
using namespace std;

//多线程竞争
mutex apple_mu;  //线程互斥对象
mutex orange_mu;
int people_num = 20;  //人数
int num=0;

//水果类
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
Fruit::Fruit(){cout<<"园丁上岗"<<endl;}
Fruit::~Fruit(){cout<<"园丁打包回家"<<endl;}

//工厂类
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

//橘子类
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
Orange::Orange(){cout<<"园丁开始种植 orange"<<endl;}
Orange::~Orange(){cout<<"果树 铲除完毕"<<endl;}

void Orange::grow(){cout<<"橘子 生长中……"<<endl;}
void Orange::bear(){cout<<"橘子 成熟了……"<<endl;}
void Orange::wxpay()
{
    while (num<=people_num)
    {
        orange_mu.lock();     //同步数据锁
        cout<<"橘子：微信到账"<<num<<endl;
        num++;
        orange_mu.unlock();  //解除锁定
    }
}
void Orange::zfbpay()
{
    while (num<=people_num)
    {
        orange_mu.lock();     //同步数据锁
        cout<<"橘子：支付宝到账"<<num<<endl;
        num++;
        orange_mu.unlock();  //解除锁定
    }
}
void Orange::ylpay()
{
    while (num<=people_num)
    {
        orange_mu.lock();     //同步数据锁
        cout<<"橘子：银联到账"<<num<<endl;
        num++;
        orange_mu.unlock();  //解除锁定
    }
}
void Orange::paypal()
{
    while (num<people_num)
    {
        orange_mu.lock();     //同步数据锁
        cout<<"橘子：PayPal到账"<<num<<endl;
        num++;
        orange_mu.unlock();  //解除锁定
    }
}
//橘子工厂
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
OrangeFactory::OrangeFactory(){cout<<"<>  橘子工厂建造完毕  <>"<<endl;}
OrangeFactory::~OrangeFactory(){cout<<"<>  橘子工厂拆除完毕  <>"<<endl;}
Factory* OrangeFactory::OrangeFactory_thread()
{
    Factory *result;
    thread *t1;
    t1=new thread([&] {result=OrangeFactory::GetInstance();}); //苹果工厂单例线程
    (*t1).detach();
    this_thread::sleep_for(chrono::milliseconds(10));
    return result;
}
Fruit* OrangeFactory::createFruit()
{
    cout<<"orange 工厂收到橘子订单,组织园丁中"<<endl;
    Fruit *some =Orange::GetInstance();  //造橘子单例
    return some;
}
OrangeFactory* OrangeFactory::GetInstance()
{
    if(0==instance_OrangeFactory)
        instance_OrangeFactory=new OrangeFactory;  //造橘子工厂
    return instance_OrangeFactory;
}

//苹果类
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
Apple::Apple(){cout<<"园丁开始种植 apple"<<endl;}
Apple::~Apple(){cout<<"果树 铲除完毕"<<endl;}

void Apple::grow(){cout<<"苹果 成长中……"<<endl;}
void Apple::bear(){cout<<"苹果 成熟了……"<<endl;}
void Apple::wxpay()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //同步数据锁
        cout<<"苹果：微信到账"<<num<<endl;
        num++;
        apple_mu.unlock();   //解除锁定
    }
}
void Apple::zfbpay()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //同步数据锁
        cout<<"苹果：支付宝到账"<<num<<endl;
        num++;
        apple_mu.unlock();   //解除锁定
    }
}
void Apple::ylpay()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //同步数据锁
        cout<<"苹果：银联到账"<<num<<endl;
        num++;
        apple_mu.unlock();  //解除锁定
    }
}
void Apple::paypal()
{
    while (num<=people_num)
    {
        apple_mu.lock();     //同步数据锁
        cout<<"苹果：PayPal到账"<<num<<endl;
        num++;
        apple_mu.unlock();   //解除锁定
    }
}
//苹果工厂
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
AppleFactory::AppleFactory(){cout<<"<>  苹果工厂建造完毕  <>"<<endl;}
AppleFactory::~AppleFactory(){cout<<"<>  苹果工厂拆除完毕  <>"<<endl;}
Factory* AppleFactory::AppleFactory_thread()
{
    Factory *result;
    thread *t2;
    t2=new thread([&] {result=AppleFactory::GetInstance();}); //苹果工厂单例线程
    (*t2).detach();
    this_thread::sleep_for(chrono::milliseconds(10));//毫秒
    //从当前时间开始阻塞当前线程直到rel_time（一段时间）这段时间过去，其他线程依旧指向。
    return result;
}

Fruit* AppleFactory::createFruit()
{
    cout<<"apple 工厂收到苹果订单,组织园丁中"<<endl;
    Fruit *some =Apple::GetInstance();  //造苹果单例
    return some;
}
AppleFactory* AppleFactory::GetInstance()
{
    if(instance_AppleFactory==0)
        instance_AppleFactory=new AppleFactory;  //造苹果工厂
    return instance_AppleFactory;
}
//选择水果
void shop_show(void)
{
    cout<<endl;
    cout<<"[--------SHOP--------]"<<endl;
    cout<<"|  a.苹果      b.橘子  |"<<endl;
    cout<<"|  c.桃子      d.梨子  |"<<endl;
    cout<<endl;
}
//支付方式
void pay_show(void)
{
    cout<<endl;
    cout<<"[-----------支付方式-----------]"<<endl;
    cout<<"|    1.微信         2.支付宝    |"<<endl;
    cout<<"|    3.银联         4.PayPal   |"<<endl;
    cout<<endl;
}
Factory * shop_choose(string name)  //选择水果
{
    if(name == "a")
    {
        cout<<">>>>商店正在向工厂派送 apple 订单>>>>"<<endl;
        Factory *some=AppleFactory::AppleFactory_thread();  //开苹果工厂线程
        return some;
    }
    else if(name == "b")
    {
        cout<<">>>>商店正在向工厂派送 orange 订单>>>>"<<endl;
        Factory *some=OrangeFactory::OrangeFactory_thread();  //开橘子工厂线程
        return some;
    }
    else
    {
        cout<<"不会生产，谢谢，不接受建议"<<endl;
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
void pay_way(Fruit *pFruit)  //支付线程
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

    cout<<"\n欢迎光临！"<<endl;
    char a;
    do{
        shop_show();     //选择水果
        cout<<"你选择的水果是:";
        string choose;
        cin>>choose;
        
        cout<<"有多少人买水果:";  //输线程数
        cin>>people_num;
        
        pFactory = shop_choose(choose);
        pFruit = pFactory->createFruit();
        pFruit->grow();
        pFruit->bear();

        pay_show();
        pay_way(pFruit);
        
        cout<<"\n若继续买请输入任意字符……   不买按 # "<<endl;
        cin>>a;
        num=0;

    }while(a!='#');
    
    cout<<endl;
    delete pFruit;
    delete pFactory;
    
    cout<<"\n欢迎下次光临！不送"<<endl;
    return 0;
}
//如果用vs2019或者vs code应该可以运行，vc6是c++98版本，“线程管理”是c++11版本的新功能，vc6不支持

/*
输出：
 
 欢迎光临！

 [--------SHOP--------]
 |  a.苹果      b.橘子  |
 |  c.桃子      d.梨子  |

 你选择的水果是:a
 有多少人买水果:10
 >>>>商店正在向工厂派送 apple 订单>>>>
 <>  苹果工厂建造完毕  <>
 apple 工厂收到苹果订单,组织园丁中
 园丁上岗
 园丁开始种植 apple
 苹果 成长中……
 苹果 成熟了……

 [-----------支付方式-----------]
 |    1.微信         2.支付宝    |
 |    3.银联         4.PayPal   |

 苹果：微信到账0
 苹果：银联到账1
 苹果：银联到账2
 苹果：银联到账3
 苹果：银联到账4
 苹果：银联到账5
 苹果：银联到账6
 苹果：银联到账7
 苹果：银联到账8
 苹果：银联到账9
 苹果：银联到账10
 苹果：支付宝到账11
 


 */



/*
 在类中使用子线程的一个问题
 　　当我们再类中使用子线程我们会发现，我们不能把初始函数设置为类的成员函数，必须要把成员函数设置成static类型的才可以，但是这有设计到一个问题，就是static的类成员函数不能调用非static的变量成员
 下面是一个两全其美的方法：
 thread sendtask(bind(&client::sendata, this));//其中client是类的名字
 
 //连接线程 —— int pthread_join(pthread_t thread, void **retval);
 调用pthread_join()会使得当前线程阻塞等待
 当目标线程退出函数会立即返回，然后线程资源回收
 目标函数必须是joinable的（线程创建后默认就是joinable）
 如果retval不是空指针，那么会在retval返回目标线程退出状态
 如果当前线程在等待过程被杀死，那么目标线程还是继续joinable
 请勿多个线程同时join一个目标线程

 //分离线程 —— int pthread_detach(pthread_t thread);
 pthread_detach将一条线程由joinable转换成detached
 分离线程的好处是线程退出后，省略了join的步骤，自己回收资源
 已经处于detached的线程切勿再次detached
 
 //join和detach的区别：
 join()的作用前面已经提到，主线程等待子线程结束方可执行下一步（串行）
 detach()是的子线程放飞自我，独立于主线程并发执行，主线程后续代码段无需等待
 
 //成员函数
 get_id()每个线程具有唯一的线程Id，可以用get_id()获取，同时其值还能指示所标识的线程的状态
 joinable：检查线程是否可被join。检查thread对象是否标识一个活动(active)的可行性线程。缺省构造的thread对象、已经完成join的thread对象、已经detach的thread对象都不是joinable
 join：调用该函数会阻塞当前线程。阻塞调用者(caller)所在的线程直至被join的std::thread对象标识的线程执行结束。
 detach：将当前线程对象所代表的执行实例与该线程对象分离，使得线程的执行可以单独进行。一旦线程执行完毕，它所分配的资源将会被释放。
 native_handle：该函数返回与std::thread具体实现相关的线程句柄。native_handle_type是连接thread类和操作系统SDK API之间的桥梁，如在Linux g++(libstdc++)里，native_handle_type其实就是pthread里面的pthread_t类型，当thread类的功能不能满足我们的要求的时候(比如改变某个线程的优先级)，可以通过thread类实例的native_handle()返回值作为参数来调用相关的pthread函数达到目录。
 swap：交换两个线程对象所代表的底层句柄。
 operator=：moves the thread object
 hardware_concurrency：静态成员函数，返回当前计算机最大的硬件并发线程数目。基本上可以视为处理器的核心数目。
 yield()函数可以用来将调用者线程跳出运行状态，重新交给操作系统进行调度，即当前线程放弃执行，操作系统调度另一线程继续执行
 sleep_until()函数是将线程休眠至某个指定的时刻(time point),该线程才被重新唤醒
 sleep_for()函数是将线程休眠某个指定的时间片(time span)，该线程才被重新唤醒，不过由于线程调度等原因，实际休眠实际可能比sleep_duration所表示的时间片更长
 
 
 //#include <mutex>互斥锁
 mutex：用来保证线程同步的，防止不同的线程同时操作同一个共享数据
 lock_guard：使用lock_guard则相对安全，它是基于作用域的，能够自解锁，当该对象创建时，它会像m.lock()一样获得互斥锁，当生命周期结束时，它会自动析构(unlock)，不会因为某个线程异常退出而影响其他线程
 
 //得到线程名称
 使用getName就可以直接得到线程的名称
 
 //注意
 线程只能被move而不能被复制,线程可以执行一切可以被调用的结构（包括类等）
 每个任务可以用多少个线程高效完成操作，和cpu的核心数有关，过多反而会导致效率低；
 
 //优点
 可以有返回值，还可以抛异常
 
 //线程生命周期的五种状态
 新建(就是刚刚new出来的时候)
 就绪(就是调用start的时候)
 运行
 堵塞
 死亡
 
 控制线程的常见的方法：
 1.join就是将线程加入到另一个线程中去，这样会造成不是并发的执行。
 2.t.setDaemon(true)表示将该线程申明为后台线程，当前台线程执行完死亡后，后台的线程也不执行了。
 3.sleep方法表示当前的线程睡一会儿，cpu爱执行谁执行谁
 4.yield移植性不好，不建议使用。表示礼让给别人执行，但是别人优先级比自己低的话，还是会执行自己。

 //sleep与yield的区别;
 1.sleep礼让很干脆，但是yield是一个伪君子，还要看别人的优先级。
 2.sleep之后，仅仅处于堵塞的状态，而yield处于就绪的状态。
 3.sleep抛异常，yield不抛异常
 4.sleep的移植性更好，建议使用。

 //线程优先级的问题
 默认的情况下都是5，但是主线程改变优先级之后，其他的与他保持一致。除非其它的线程重新设置优先级。
 max 10 norm5 min1
 
 //什么时候分离线程会存在陷阱？
 一个分离线程使用一个共享资源
 分离线程的生命周期比所使用的资源的生命周期长
 那么就有可能造成未知的错误
 

 例如：子线程使用一个全局对象(object)，子线程与程序一并退出。
 由于程序退出的顺序是:
 1.对象析构
 2.子线程退出
 3.主线程退出
 因此，程序退出过程中，全局对象会调用自己的析构函数，此时，对象生命周期结束，对象被销毁。但是，子线程还没马上死亡，子线程仍然有可能继续调用已经析构的对象。期望的结果是安全退出程序，结果却造成了未知的错误。

 方法论
 1.不要使用分离线程
 2.分离线程不要使用共享资源
 3.主线程退出前主动销毁子线程（主线程是主动的）
 4.使用条件变量，主线程等待子线程退出（主线程是被动的）
 5.使用 void quick_exit (int status) 函数，直接退出，不调用析构函数
 
 既使用quick_exit()，又需要析构,使用 int at_quick_exit( void (*func)(void) ) 函数，注册退出函数。
 PS
 quick_exit()系列函数包含在<stdlib.h>中，但Windows不一定（具体和编译器、编译器版本都有关）。
 
 
 < thread > :包含std::thread类以及std::this_thread命名空间。管理线程的函数和类在 中声明.
 < atomic > :包含std::atomic和std::atomic_flag类，以及一套C风格的原子类型和与C兼容的原子操作的函数。
 < mutex > :包含了与互斥量相关的类以及其他类型和函数
 < future > :包含两个Provider类（std::promise和std::package_task）和两个Future类（std::future和std::shared_future）以及相关的类型和函数。
 < condition_variable > :包含与条件变量相关的类，包括std::condition_variable和std::condition_variable_any。
 
 
 如果是通过引用传递参数；
 calss factor
 {
    void function(string& str)
    {
        cout<<"hello"+str<<endl;
    }
 }
 相应的调用部分应该是：
 thread t((function()),std::ref(s));
 如果调用的时候是：
 thread t((function()),s);
 尽管被调用的方法是引用传递值的，但是并不会影响值传递之实；
 引用就是别名的概念，可以减少不必要的复制；

 引用还可以写成
 thread t((function()),move(s));
 但是线程只能写成move
 如：
 thread t2=move（t）；

 
 */