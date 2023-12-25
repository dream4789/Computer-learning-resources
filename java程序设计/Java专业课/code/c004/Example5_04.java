class Shape
{
	public double area()
	{
		return 0;//因为不知道是何种图形，无法计算面积和周长
	}
	public double perimeter()
	{
		return 0;
	}
}
class Circle extends Shape
{
	private double radius;
	
	public Circle(double radius)
	{
		this.radius=radius;
	}
	public double area()//重写继承自父类的方法，因为是具体图形，知道计算方法
	{
		return Math.PI*radius*radius;
	}
	public double perimeter()//重写
	{
		return 2*Math.PI*radius;
	}
}
class Rectangle extends Shape
{
	private double width,height;
	
	public Rectangle(double width,double height)
	{
		this.width=width;
		this.height=height;
	}
	public double area()//重写继承自父类的方法，因为是具体图形，知道计算方法
	{
		return width*height;
	}
	public double perimeter()//重写
	{
		return 2*(width+height);
	}
}
public class Example5_04
{
	public static void main(String args[])
	{
		Circle circle=new Circle(10);
		Rectangle rect=new Rectangle(15.2,10.8);
		
		System.out.print("圆的面积和周长：");
		System.out.printf("%.2f,%.2f\n",circle.area(),circle.perimeter());
		
		System.out.print("矩形的面积和周长：");
		System.out.printf("%.2f,%.2f\n",rect.area(),rect.perimeter());
	}
}
