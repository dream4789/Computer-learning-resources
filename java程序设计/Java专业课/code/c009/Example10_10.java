package ch10;
public class Example10_10 
{ 
	public static void main(String[] args) 
	{ 
		User user = new User("����", 100);
		UserThread t1 = new UserThread("�߳�A", user, 20);
		UserThread t2 = new UserThread("�߳�B", user, -60);
		UserThread t3 = new UserThread("�߳�C", user, -80);
		UserThread t4 = new UserThread("�߳�D", user, -30);
		UserThread t5 = new UserThread("�߳�E", user, 32);
		UserThread t6 = new UserThread("�߳�F", user, 21);
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		t5.start();
		t6.start();
	} 
} 

class UserThread extends Thread 
{ 
	private User user; 
	private int y = 0; 
	UserThread(String name, User user, int y) 
	{ 
		super(name); 
		this.user = user; 
		this.y = y; 
	} 
	public void run() 
	{ 
		user.operate(y);
	} 
} 
class User 
{ 
	private String code; 
	private int cash; 
	User(String code, int cash) 
	{ 
		this.code = code; 
		this.cash = cash; 
	} 
	public String getCode() 
	{ 
		return code; 
	} 
	public void setCode(String code) 
	{ 
		this.code = code; 
	}
	public synchronized void operate(int x)//ͬ���������߳���
	{ 
		try
		{
			Thread.sleep(10);
			this.cash += x;
			String threadName=Thread.currentThread().getName();
			System.out.println(threadName+"����������"+x+"���˻����Ϊ��"+cash);
			Thread.sleep(10L);
		}
		catch (InterruptedException e)
		{
			e.printStackTrace();
		} 
	} 
	
	@Override 
	public String toString() 
	{ 
		return "User{"+"code='"+code+'\''+",cash="+cash+ '}'; 
	}
}
