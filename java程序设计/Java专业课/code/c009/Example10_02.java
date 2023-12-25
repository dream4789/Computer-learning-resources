package ch10;
class ImpRunnable implements Runnable//实现Runnable接口 
{ 
	private String name;
	public ImpRunnable(String name)
	{
		this.name = name; 
	} 
	public void run()//接口的方法，子类必须定义
	{ 
		for (int i = 0; i < 5; i++) 
		{ 
			for (long k = 0; k < 100000000; k++);//延时
			System.out.println(name + ": " + i); 
		} 
	} 
}
public class Example10_02 
{ 
	public static void main(String[] args) 
	{ 
		ImpRunnable ds1 = new ImpRunnable("A");
		ImpRunnable ds2 = new ImpRunnable("B");
		
		Thread t1 = new Thread(ds1);//ds1为t1提供线程体
		Thread t2 = new Thread(ds2);//ds2为t2提供线程体
		
		t1.start();//线程启动
		t2.start();
	} 
}
