class Shape
{
	public double area()
	{
		return 0;//��Ϊ��֪���Ǻ���ͼ�Σ��޷�����������ܳ�
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
	public double area()//��д�̳��Ը���ķ�������Ϊ�Ǿ���ͼ�Σ�֪�����㷽��
	{
		return Math.PI*radius*radius;
	}
	public double perimeter()//��д
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
	public double area()//��д�̳��Ը���ķ�������Ϊ�Ǿ���ͼ�Σ�֪�����㷽��
	{
		return width*height;
	}
	public double perimeter()//��д
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
		
		System.out.print("Բ��������ܳ���");
		System.out.printf("%.2f,%.2f\n",circle.area(),circle.perimeter());
		
		System.out.print("���ε�������ܳ���");
		System.out.printf("%.2f,%.2f\n",rect.area(),rect.perimeter());
	}
}
