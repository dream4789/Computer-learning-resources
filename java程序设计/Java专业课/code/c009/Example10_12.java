package ch10;
class  A
{
	synchronized void first(B b)
	{
		String name = Thread.currentThread().getName();
		System.out.println(name+" entered A.first() ");
		try
		{
			Thread.sleep(1000);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		System.out.println(name+" trying to call B.last()");
		b.last();
	}
	
	synchronized void last()
	{
		System.out.println("inside A.last");
	}
}
class  B
{
	synchronized void first(A a)
	{
		String name = Thread.currentThread().getName();
		System.out.println(name+" entered B.first()");
		try
		{
			Thread.sleep(1000);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		System.out.println(name+" trying to call A.last()");
		a.last();
	}
	
	synchronized void last()
	{
		System.out.println("inside B.last");
	}
}   
class Example10_12  implements Runnable
{
	A a = new A();		
	B b = new B();
	Example10_12()
	{
		Thread.currentThread().setName("main_thread");
		new Thread(this).start();
		a.first(b);
		System.out.println("back in main_thread");
	}
	
	public void run()
	{
		Thread.currentThread().setName("user_thread");
		b.first(a);
		System.out.println("back in user_threaad");
	}
	
	public static void main(String[] args)
	{
		new Example10_12();
	}
}
