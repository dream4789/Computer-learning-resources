abstract class Shape//������Ķ���
{
	public abstract double area();//���󷽷�
	public abstract double perimeter();//���󷽷�
}

class Circle extends Shape
{
//��Ķ���ͬ��5.4
}
class Rectangle extends Shape
{
//��Ķ���ͬ��5.4
}
public class Example5_15
{
	public static void main(String args[])
	{
		Shape aShape;//����һ��������Ķ���
		
		//aShape=new Shape();���������ܴ���������Ķ���
				
		aShape=new Circle(10);//�ó���ĸ�������ʾ�������
		System.out.print("Բ��������ܳ���");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());

		aShape=new Rectangle(15.2,10.8);//�ó���ĸ�������ʾ�������
		System.out.print("���ε�������ܳ���");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());
	}
}
