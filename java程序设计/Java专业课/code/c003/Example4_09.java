class Point
{
	int x,y;//�򣬵��λ��

	Point(int x,int y)//�����������Ĺ��췽��
	{
		this.x=x;
		this.y=y;
	}
	public void print()
	{
		System.out.println("("+x+","+y+")");
	}
}
public class Example4_09
{
	public static void main(String args[])
	{
		Point p=new Point(11,22);
		
		System.out.print("����move����ǰ������꣺");
		p.print();
		
		move(p.x,p.y);
		
		System.out.print("����move�����������꣺");
		p.print();
	}
	private static void move(int x,int y) //������������������
	{
		x=x+11;
		y=y+22;
		System.out.print("��move�����е�����꣺");
		System.out.println("("+x+","+y+")");
	}
}
