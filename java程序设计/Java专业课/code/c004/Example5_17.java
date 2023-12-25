interface Shape//接口的定义
{
	public final static double PI=3.1415926;//常量定义
	public abstract double area();//方法声明
	public abstract double perimeter();//方法声明
}

class Circle implements Shape//实现接口
{
	private double radius;
	
	public Circle(double radius)
	{
		this.radius=radius;
	}
	public double area()//实现接口中的方法
	{
		return PI*radius*radius;//此处使用的是接口中的常量PI，而不是Math.PI
	}
	public double perimeter()//实现接口中的方法
	{
		return PI*radius;//接口中的常量PI
	}
}
class Rectangle implements Shape//实现接口
{
	//同例5.15
}
public class Example5_17
{
	public static void main(String args[])
	{
		Shape aShape;//声明一个接口变量
		
		//aShape=new Shape();不允许，不能创建接口实例
				
		aShape=new Circle(10);//接口变量表示子类对象，上转型对象
		System.out.print("圆的面积和周长：");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());

		aShape=new Rectangle(15.2,10.8);//接口变量表示子类对象，上转型对象
		System.out.print("矩形的面积和周长：");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());
	}
}
