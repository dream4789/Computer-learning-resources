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
		{//���߳������У�ִ�������������߳��ó�CPU��sub
			Thread.sleep(100);
            wash.join();//ֱ��washִ��������̲߳��ܼ���ִ��
		}
		catch(InterruptedException e)
		{}
		System.out.println(Thread.currentThread().getName()+"���˸�ƻ����");
	}
}

class Pick extends Thread
{
	public void run()
	{
		
try
		{
			sleep(3000);//ģ�����߳�����
		}
		catch(InterruptedException e)
		{
			System.out.println("interrupted!");
		}
		System.out.println(this.getName()+"ժ�˸�ƻ��");
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
         System.out.println(this.getName()+"ϴ�˸�ƻ��");
	}
}
