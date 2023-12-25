interface Shape//�ӿڵĶ���
{
	public final static double PI=3.1415926;//��������
	public abstract double area();//��������
	public abstract double perimeter();//��������
}

class Circle implements Shape//ʵ�ֽӿ�
{
	private double radius;
	
	public Circle(double radius)
	{
		this.radius=radius;
	}
	public double area()//ʵ�ֽӿ��еķ���
	{
		return PI*radius*radius;//�˴�ʹ�õ��ǽӿ��еĳ���PI��������Math.PI
	}
	public double perimeter()//ʵ�ֽӿ��еķ���
	{
		return PI*radius;//�ӿ��еĳ���PI
	}
}
class Rectangle implements Shape//ʵ�ֽӿ�
{
	//ͬ��5.15
}
public class Example5_17
{
	public static void main(String args[])
	{
		Shape aShape;//����һ���ӿڱ���
		
		//aShape=new Shape();���������ܴ����ӿ�ʵ��
				
		aShape=new Circle(10);//�ӿڱ�����ʾ���������ת�Ͷ���
		System.out.print("Բ��������ܳ���");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());

		aShape=new Rectangle(15.2,10.8);//�ӿڱ�����ʾ���������ת�Ͷ���
		System.out.print("���ε�������ܳ���");
		System.out.printf("%.2f,%.2f\n",aShape.area(),aShape.perimeter());
	}
}
