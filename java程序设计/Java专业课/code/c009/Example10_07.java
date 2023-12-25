package ch10;
class DaemonThread implements Runnable 
{    
	public void run() 
	{   
		while (true)//true=线程永远执行
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
			if(Thread.currentThread().getName().equals("非守护线程"))
				break;//“非守护线程”能结束，“守护线程”也随之结束
		}
	}
}
public class Example10_07
{   
	public static void main(String[] args) 
	{  
		Thread daemonThread = new Thread(new DaemonThread());
		daemonThread.setName("守护线程");
		// 设置为守护进程
		daemonThread.setDaemon(true);
		daemonThread.start();

		Thread t = new Thread(new DaemonThread());
		t.setName("非守护线程");
		t.start();
	}
}
