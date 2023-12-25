class A
{
	//符号常量，最终域
	public static final double PI=3.1415926;
	
	int a=10;
	
	public final int getA()//最终方法
	{
		return a;
	}
}
class B extends A
{
	int b=-15;
	
	public B()
	{
		PI=2.71828;//为继承自父类的最终域重新赋值
	}
	
	public int getA()//重写父类方法
	{
		return b;
	}
}
public class Example5_09
{
	public static void main(String args[])
	{
		B obj=new B();
		
		obj.PI=2.71828;//运行中为最终重新赋值
		
		System.out.println(obj.getA());
	}
}
