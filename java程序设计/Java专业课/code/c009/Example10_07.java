package ch10;
class DaemonThread implements Runnable 
{    
	public void run() 
	{   
		while (true)//true=�߳���Զִ��
		{
			for (int i = 1; i <= 3; i++) 
			{
				System.out.println(Thread.currentThread().getName()+i);
				try
				{
					Thread.sleep(500);
				} 
				catch (InterruptedException e) 
				{   
					e.printStackTrace();
				}
			}
			if(Thread.currentThread().getName().equals("���ػ��߳�"))
				break;//�����ػ��̡߳��ܽ��������ػ��̡߳�Ҳ��֮����
		}
	}
}
public class Example10_07
{   
	public static void main(String[] args) 
	{  
		Thread daemonThread = new Thread(new DaemonThread());
		daemonThread.setName("�ػ��߳�");
		// ����Ϊ�ػ�����
		daemonThread.setDaemon(true);
		daemonThread.start();

		Thread t = new Thread(new DaemonThread());
		t.setName("���ػ��߳�");
		t.start();
	}
}
