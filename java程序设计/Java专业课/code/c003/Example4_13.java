class Point
{
//ͬ��4.9
}
public class Example4_13
{
	public static void main(String args[])
	{
		//���´����Ķ����ʼ������
		Point point[]={new Point(-10,-11),new Point(-20,-21),new Point(-30,-31)};
		
		System.out.println("���������ʼ��Ԫ�ص�ֵ ��");
		print(point);
		move(point);
		System.out.println("�ƶ�����������и�Ԫ�ص�ֵ��");
		print(point);
		
		Point p1=new Point(10,11);
		Point p2=new Point(20,21);
		Point p3=new Point(30,31);
		//���Ѵ��ں��´����Ķ����ʼ������
		Point point1[]={p1,p2,p3,new Point(40,41)};
		System.out.println("--���Ѵ��ں��´����Ķ����ʼ������---");
		System.out.println("���������ʼ��Ԫ�ص�ֵ ��");
		print(point1);
		move(point1);
		System.out.println("�ƶ�����������и�Ԫ�ص�ֵ��");
		print(point1);
		
		//���д�ɣ�point={p1,p2,p3};���������ԣ���Ϊ���ǳ�ʼ��
	}
	private static void init(Point p[])
	{
		for(int i=0;i<p.length;i++)
			p[i]=new Point(10+i,20+2*i);
	}
	private static void print(Point p)
	{
		System.out.print(" ("+p.x+","+p.y+")");
	}
	private static void print(Point p[])
	{
		for(Point p1:p)
			print(p1);
		System.out.println();
	}
	private static void move(Point p[])
	{
		for(Point p1:p)
		{
			p1.x+=11;
			p1.y+=12;
		}
	}
}
