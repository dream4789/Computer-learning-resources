package ch10;
public class Example10_05
{ 
	public static void main(String[] args) 
	{   //ע�⣬�����̶߳���Ĵ�����ʽ��ͬ
		Thread t1 = new MyThread1();
		Thread t2 = new Thread(new MyRunnable1()); 
		t2.start(); 
		t1.start(); 
     } 
}
class MyThread1 extends Thread//�߳��������
{ 
	public void run() 
	{ 
		for (int i = 1; i <= 10; i++) 
			System.out.println("�߳�1��" + i + "��ִ�У�"); 
	} 
}

class MyRunnable1 implements Runnable//ʵ�ֽӿ�
{ 
	public void run() 
	{ 
		for (int i = 1; i <= 10; i++) 
		{ 
			System.out.println("�߳�2��" + i + "��ִ�У�"); 
			Thread.yield();//�ò�                    
		} 
		for (int i = 1; i <= 10000; i++);//��ʱ
	} 
}
