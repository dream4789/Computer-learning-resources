package ch10;
public class Example10_05
{ 
	public static void main(String[] args) 
	{   //注意，两个线程对象的创建方式不同
		Thread t1 = new MyThread1();
		Thread t2 = new Thread(new MyRunnable1()); 
		t2.start(); 
		t1.start(); 
     } 
}
class MyThread1 extends Thread//线程类的子类
{ 
	public void run() 
	{ 
		for (int i = 1; i <= 10; i++) 
			System.out.println("线程1第" + i + "次执行！"); 
	} 
}

class MyRunnable1 implements Runnable//实现接口
{ 
	public void run() 
	{ 
		for (int i = 1; i <= 10; i++) 
		{ 
			System.out.println("线程2第" + i + "次执行！"); 
			Thread.yield();//让步                    
		} 
		for (int i = 1; i <= 10000; i++);//延时
	} 
}
