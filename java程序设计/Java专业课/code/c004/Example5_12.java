class Shape
{
//Shape�Ķ���ͬ��5.4
}

class Circle extends Shape
{
//Circle�Ķ���ͬ��5.4
}
class Rectangle extends Shape
{
//Rectangle�Ķ���ͬ��5.4
}

public class Example5_12 
{
	public static void main(String args[])
	{
		Shape aShape=new Circle(10);//��������ʾCircle�������
		System.out.print("Բ��������ܳ���");
		//ͨ���������������෽��
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());

		aShape=new Rectangle(15.2,10.8);//��������ʾRectangle�������
		System.out.print("���ε�������ܳ���");
		//ͨ���������������෽��
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());
	}
}
