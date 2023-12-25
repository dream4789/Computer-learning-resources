class Point
{
//同例4.9
}
public class Example4_13
{
	public static void main(String args[])
	{
		//用新创建的对象初始化数组
		Point point[]={new Point(-10,-11),new Point(-20,-21),new Point(-30,-31)};
		
		System.out.println("对象数组初始各元素的值 ：");
		print(point);
		move(point);
		System.out.println("移动后对象数组中各元素的值：");
		print(point);
		
		Point p1=new Point(10,11);
		Point p2=new Point(20,21);
		Point p3=new Point(30,31);
		//用已存在和新创建的对象初始化数组
		Point point1[]={p1,p2,p3,new Point(40,41)};
		System.out.println("--用已存在和新创建的对象初始化数组---");
		System.out.println("对象数组初始各元素的值 ：");
		print(point1);
		move(point1);
		System.out.println("移动后对象数组中各元素的值：");
		print(point1);
		
		//如果写成：point={p1,p2,p3};——不可以，因为不是初始化
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
