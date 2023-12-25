abstract class Shape//抽象类的定义
{
	public abstract double area();//抽象方法
	public abstract double perimeter();//抽象方法
}

class Circle extends Shape
{
//类的定义同例5.4
}
class Rectangle extends Shape
{
//类的定义同例5.4
}
public class Example5_15
{
	public static void main(String args[])
	{
		Shape aShape;//声明一个抽象类的对象
		
		//aShape=new Shape();不允许，不能创建抽象类的对象
				
		aShape=new Circle(10);//用抽象的父类对象表示子类对象
		System.out.print("圆的面积和周长：");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());

		aShape=new Rectangle(15.2,10.8);//用抽象的父类对象表示子类对象
		System.out.print("矩形的面积和周长：");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());
	}
}
