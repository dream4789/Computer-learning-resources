package ch10;
public class Example10_13 
{ 
	public static void main(String[] args) 
	{ 
		ThreadB b = new ThreadB(); 
		
		//���������߳� 
		 b.start(); 
		 
		//�߳�mainӵ��b�����ϵ�����
		synchronized(b)
		{ 
			try 
			{
				String name=Thread.currentThread().getName();
				System.out.println(name+"�ȴ�����b��ɼ��㡭��");
				//��ǰ�߳�main�ȴ�
				b.wait();
				System.out.println("����b������ɣ����="+b.total);
				System.out.println(name+"�������У�");
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

			//��������ˣ������ڴ˶���������ϵȴ��ĵ����̡߳� 
			notify(); 
		} 
	}
}
