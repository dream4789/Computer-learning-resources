package ch10;
public class Example10_06 
{     
	public static void main(String[] args)
	{
		Wash wash = new Wash();
          wash.setName("Sawyer");
          wash.start();
          Thread.currentThread().setName("Billy");
          try
		{//主线程在运行，执行下面语句后，主线程让出CPU给sub
			Thread.sleep(100);
            wash.join();//直到wash执行完后，主线程才能继续执行
		}
		catch(InterruptedException e)
		{}
		System.out.println(Thread.currentThread().getName()+"吃了个苹果。");
	}
}

class Pick extends Thread
{
	public void run()
	{
		
try
		{
			sleep(3000);//模拟子线程运行
		}
		catch(InterruptedException e)
		{
			System.out.println("interrupted!");
		}
		System.out.println(this.getName()+"摘了个苹果");
	}
} 
class Wash extends Thread
{   Pick pick;                                  
    Wash(){
       pick = new Pick();
       pick.setName("Tom");
}
	public void run()
	{                                            
		try
		{
			pick.start();
			sleep(3000);
			pick.join();
		}
		catch(InterruptedException e)
		{
			System.out.println("interrupted!");
		}
         System.out.println(this.getName()+"洗了个苹果");
	}
}
