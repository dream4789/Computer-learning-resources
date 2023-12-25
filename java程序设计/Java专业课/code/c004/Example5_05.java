import static java.lang.System.out;
class Super
{
	int var;
	
	public Super(int var)
	{
		this.var=var;
	}
}
class Sub extends Super
{
	int var;
	
	public Sub(int var1,int var2)
	{
		super(var2);//调用父类的构造方法
		this.var=var1;//不加this也可
	}
	public void display()
	{
		out.println("继承自父类的域："+super.var);//访问被隐藏的父类的域
		out.println("本身定义的域："+var);//本身类定义的域
	}
}
public class Example5_05
{
	public static void main(String ars[])
	{
		Sub sub=new Sub(10,-200);
		sub.display();
	}
}
