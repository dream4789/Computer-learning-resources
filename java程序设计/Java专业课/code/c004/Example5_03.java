class SuperClass
{
	int var;
	
	public void setSuperVar(int var)
	{
		this.var=var;
	}
	public int getSuperVar()
	{
		return var;
	}
}
class SubClass extends SuperClass
{
	int var;//与继承自父类的域同名（覆盖父类的域）
	
	public void setSubVar(int v)
	{
		var=v;//访问本身类所定义的域，访问不到继承自父类的域
	}
	public int getSubVar()
	{
		return var;//访问本身类所定义的域，访问不到继承自父类的域
	}
}
public class Example5_03
{
	public static void main(String args[])
	{
		SubClass obj=new SubClass();
		
		obj.setSubVar(20);
		obj.setSuperVar(-20);
		
		System.out.println("子类对象本身的域的值："+obj.getSubVar());
		System.out.println("子类对象继承父类的域的值："+obj.getSuperVar());
	}
}
