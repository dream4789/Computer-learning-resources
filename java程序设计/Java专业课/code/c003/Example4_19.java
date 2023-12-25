class Point
{
	private int x,y;//˽����
	private static int counter=0;//˽�о�̬��
	
	public Point()//���еĹ��췽��
	{
		x=0;//�ڱ������з���˽�г�Ա�����ƣ�����ͬ
		y=0;
		
		counter++;
	}
	Point(int x,int y)//���еĹ��췽��
	{
		this.x=x;
		this.y=y;
		
		counter++;
	}
	
	public int getX()//���з��������x����
	{
		return x;
	}
	public int getY()//���з��������y����
	{
		return y;
	}
	public void move(int offsetX,int offsetY)//���з������Ե�ƽ��
	{
		x+=offsetX;
		y+=offsetY;
	}
	public void print()//���з������Ե�ƽ��
	{
		System.out.println("("+x+","+y+")");
	}
	public static int getCounter()//���о�̬����
	{
		return counter;
	}
}
public class Example4_19
{
	public static void main(String args[])
	{
		System.out.println("����ƽ���ϵĵ�����"+Point.getCounter());
		//ֱ��ͨ���������ʾ�̬�򲻿ɣ���Ϊ����˽�е�
		//System.out.println("����ƽ���ϵĵ�����"+Point.counter);
		
		Point p1=new Point();
		System.out.print("��p1��λ�ã�");
		p1.print();
		
		p1.move(-11, -12);
		System.out.print("��p1�ƶ���λ�ã�");
		p1.print();
		//����������ķ�ʽ�ƶ�
		//p1.x=p1.x+11;����������
		//p1.y=p1.y+12;����������
		
		Point p2=new Point(11,22);
		System.out.print("��p2��λ�ã�");
		System.out.println("("+p2.getX()+","+p2.getY()+")");
		//ֱ��ͨ������������x��y�����ԣ���Ϊ������˽�е�
		//System.out.println("("+p2.x+","+p2.y+")");		
		
		System.out.println("����ƽ���ϵĵ�����"+Point.getCounter());
	}
}
