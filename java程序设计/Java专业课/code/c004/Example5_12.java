class Shape
{
//Shape的定义同例5.4
}

class Circle extends Shape
{
//Circle的定义同例5.4
}
class Rectangle extends Shape
{
//Rectangle的定义同例5.4
}

public class Example5_12 
{
	public static void main(String args[])
	{
		Shape aShape=new Circle(10);//父类对象表示Circle子类对象
		System.out.print("圆的面积和周长：");
		//通过父类对象调用子类方法
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());

		aShape=new Rectangle(15.2,10.8);//父类对象表示Rectangle子类对象
		System.out.print("矩形的面积和周长：");
		//通过父类对象调用子类方法
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());
	}
}
