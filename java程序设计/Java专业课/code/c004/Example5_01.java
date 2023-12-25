class Base//定义一个基类
{
	int base_var1;//两个域
	double base_var2;
	
	void setBaseVar(int var1,double var2)//方法，设置域值
	{
		base_var1=var1;
		base_var2=var2;
	}
	
	void basePrint()//方法，打印域值
	{
		System.out.print("base_var1="+base_var1+",");
		System.out.println("base_var2="+base_var2);
	}
}
class Derived extends Base//定义一个基于Base类的派生类
{
	int derived_var1;//子类新定义的两个域
	double derived_var2;
	
	void setDerivedVar(int var1,double var2)//方法，设置域值
	{
		derived_var1=var1;
		derived_var2=var2;
	}
	
	void derivedPrint()//方法，打印域值
	{
		System.out.print("derived_var1="+derived_var1+",");
		System.out.println("derived_var2="+derived_var2);
	}
	
	void print()
	{
		System.out.print("base_var1="+base_var1+",");//子类方法直接访问继承自父类的域
		System.out.println("base_var2="+base_var2);
		System.out.print("derived_var1="+derived_var1+",");
		System.out.println("derived_var2="+derived_var2);
	}
}

public class Example5_01
{
	public static void main(String args[])
	{
		Derived derived=new Derived();//创建派生类对象
		
		derived.setBaseVar(10, 20);//通过派生类对象设置域值
		derived.setDerivedVar(-15, -25);
		
		derived.basePrint();//通过派生类对象打印域值
		derived.derivedPrint();
		
		System.out.println("--------  再打印一遍  --------");
		derived.print();
	}
}
