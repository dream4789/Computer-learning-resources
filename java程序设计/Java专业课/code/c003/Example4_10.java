class Point
{
//ͬ��4.9
}
public class Example4_10
{
	public static void main(String args[])
	{
		Point p=new Point(11,22);
		
		System.out.println("��main()������p��ʾ�Ķ���ĵ�ַ��"+p);
		System.out.print("����move����ǰ������꣺");
		p.print();
		
		move(p);
		
		System.out.print("����move�����������꣺");
		p.print();
	}
	private static void move(Point p)//�������������Ĳ���
	{
		System.out.println("��move()������p��ʾ�Ķ���ĵ�ַ:"+p);
		p.x=p.x+11;
		p.y=p.y+22;
		System.out.print("��move�����е�����꣺");
		System.out.println("("+p.x+","+p.y+")");
	}
}
