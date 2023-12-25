package ch10;
public class Example10_13 
{ 
	public static void main(String[] args) 
	{ 
		ThreadB b = new ThreadB(); 
		
		//启动计算线程 
		 b.start(); 
		 
		//线程main拥有b对象上的锁。
		synchronized(b)
		{ 
			try 
			{
				String name=Thread.currentThread().getName();
				System.out.println(name+"等待对象b完成计算……");
				//当前线程main等待
				b.wait();
				System.out.println("对象b计算完成，结果="+b.total);
				System.out.println(name+"继续运行！");
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}
}
class ThreadB extends Thread
{ 
	int total=0; 
	public void run()
	{ 
		synchronized (this) 
		{ 
			for (int i = 0; i < 101; i++) 
				total += i; 

			//计算完成了，唤醒在此对象监视器上等待的单个线程。 
			notify(); 
		} 
	}
}
