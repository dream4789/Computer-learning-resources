package ch10;
import java.io.*;
public class Example10_04
{
	public static void main(String[] args) throws IOException  
	{
		MyThread thread = new MyThread();
		thread.setName("�����߳�");
		thread.start();
		try 
		{   //main�߳�
			System.out.println(Thread.currentThread().getName()+"����˯��");
			Thread.currentThread().sleep(2000);//˯��2��
			System.out.println(Thread.currentThread().getName()+"˯�����");
		}
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
		thread.interrupt();//�����߳�Ӧ������10�룬�����ж�
	}
}
class MyThread extends Thread
{
	@Override
	public void run() 
	{
		try 
		{   //�����߳�
			System.out.println(Thread.currentThread().getName()+"����˯��");
			Thread.currentThread().sleep(10000);//����10�룬������ǰ�ж�
			System.out.println(Thread.currentThread().getName()+"˯�����");
		}    
		catch (InterruptedException e)

		{
			System.out.println("�õ��ж��쳣");
		}
		System.out.println("run����ִ�����");
	}
}    
