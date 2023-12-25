class Point
{
	int x,y;//域，点的位置

	Point(int x,int y)//有两个参数的构造方法
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
		
		System.out.print("调用move方法前点的坐标：");
		p.print();
		
		move(p.x,p.y);
		
		System.out.print("调用move方法后点的坐标：");
		p.print();
	}
	private static void move(int x,int y) //基本数据作方法参数
	{
		x=x+11;
		y=y+22;
		System.out.print("在move方法中点的坐标：");
		System.out.println("("+x+","+y+")");
	}
}
