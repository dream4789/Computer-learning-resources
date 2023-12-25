package ch10;
class ExtThread extends Thread//基于Thread类派生线程子类
{
	public ExtThread(String name)//构造方法，用于设定线程字符串名字
	{
		super(name);//调用父类构造方法设置线程名
	} 
	public void run() 
	{
		for(int i = 0;i<=4;i++)//每个线程循环4次
		{
			for(long k= 0; k <100000000;k++);//延时
			//输出线程名及其执行次数
			System.out.println(this.getName()+" :"+i);
		}
	} 
}
public class Example10_01
{
	public static void main(String[] args)
	{
		//生成线程对象t1，其字符串名字为A
		Thread t1 = new ExtThread("A"); 
		Thread t2 = new ExtThread("B"); 
		t1.start();//调用start()方法使线程处于可运行状态
		t2.start(); 
	}
}
