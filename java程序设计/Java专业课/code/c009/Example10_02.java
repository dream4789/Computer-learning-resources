package ch10;
class ImpRunnable implements Runnable//ʵ��Runnable�ӿ� 
{ 
	private String name;
	public ImpRunnable(String name)
	{
		this.name = name; 
	} 
	public void run()//�ӿڵķ�����������붨��
	{ 
		for (int i = 0; i < 5; i++) 
		{ 
			for (long k = 0; k < 100000000; k++);//��ʱ
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
		
		Thread t1 = new Thread(ds1);//ds1Ϊt1�ṩ�߳���
		Thread t2 = new Thread(ds2);//ds2Ϊt2�ṩ�߳���
		
		t1.start();//�߳�����
		t2.start();
	} 
}
