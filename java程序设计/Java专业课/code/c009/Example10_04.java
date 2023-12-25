package ch10;
import java.io.*;
public class Example10_04
{
	public static void main(String[] args) throws IOException  
	{
		MyThread thread = new MyThread();
		thread.setName("测试线程");
		thread.start();
		try 
		{   //main线程
			System.out.println(Thread.currentThread().getName()+"进入睡眠");
			Thread.currentThread().sleep(2000);//睡眠2秒
			System.out.println(Thread.currentThread().getName()+"睡眠完毕");
		}
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
		thread.interrupt();//测试线程应该休眠10秒，但被中断
	}
}
class MyThread extends Thread
{
	@Override
	public void run() 
	{
		try 
		{   //测试线程
			System.out.println(Thread.currentThread().getName()+"进入睡眠");
			Thread.currentThread().sleep(10000);//休眠10秒，但被提前中断
			System.out.println(Thread.currentThread().getName()+"睡眠完毕");
		}    
		catch (InterruptedException e)

		{
			System.out.println("得到中断异常");
		}
		System.out.println("run方法执行完毕");
	}
}    
