class Point
{
//Point��Ķ���ͬ��4.21
}
class Line extends Point//�߶��࣬��Ϻͼ̳�
{
	//��Point���һ�������ʾ�߶�һ���˵�
	private Point start;//�����򣩳�Ա
	
	public Line(int x1,int y1,int x2,int y2)//���췽��
	{
		super(x2,y2);
		start=new Point(x1,y1);//����������
	}
	public Line(Point p1,Point p2)//���ع��췽��
	{
		super(p2.getX(),p2.getY());
		start=new Point(p1.getX(),p1.getY());//���´�������
	}
	public int getStartX()
	{
		return start.getX();//��������
	}
	public int getStartY()
	{
		return start.getY();//��������
	}
	public int getEndX()
	{
		return getX();//�̳��Ը����getX()
	}
	public int getEndY()
	{
		return getY();//�̳��Ը����getY()
	}
	public void move(int offsetX,int offsetY)
	{
		start.move(offsetX, offsetY);//��������
		super.move(offsetX, offsetY);//���ø���move()�Լ̳��Ը����x��yƽ��
	}
	public double length()
	{
		Point end=new Point(getX(),getY());
		return start.length(end);//��������
	}
	public String toString()//���˵��γ�һ���ַ�
	{
		//Point end=new Point(getX(),getY());

		String str=start.toString();//��������
		str+="-"+super.toString();//��������
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
class Circle extends Point//Բ�࣬�̳�
{
	//private Point center;�����壬�ü̳е�x��y��ʾԲ��
	int radius;
	
	public Circle(int x,int y,int radius)//���췽��
	{
		super(x,y);//���ø���Ĺ��췽���Լ̳е�x��y��ʼ��
		this.radius=radius;
	}
	public Circle(Point p,int radius)//���ع��췽��
	{
		super(p.getX(),p.getY());
		this.radius=radius;
	}
	public int getX()//��ȡԲ��x����
	{
		return super.getX();//���ø���ķ���
	}
	public int getY()//��ȡԲ��y����
	{
		return super.getY();//���ø���ķ���
	}
	public int getRadius()//��ȡԲ�İ뾶
	{
		return radius;
	}
	public void move(int offsetX,int offsetY)//�ƶ�Բ
	{
		super.move(offsetX, offsetY);//���ø���ķ���
	}
	public double area()//����Բ�����
	{
		return Math.PI*radius*radius;
	}
	public double perim()//����Բ���ܳ�
	{
		return 2*Math.PI*radius;
	}
	public String toString()//��Բ�������γ�һ���ַ���
	{
		String str=radius+",";
		str+=super.toString();//���ø���ķ���
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}

public class Example5_11
{
	public static void main(String args[])
	{
//main()����ͬ��4.21
	}
}
