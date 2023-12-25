class Point
{
//同例4.9
}
public class Example4_12
{
	public static void main(String args[])
	{
		Point point[]=new Point[5];//创建对象数组
		
		init(point);//对对象数组初始化
		System.out.println("对象数组创建后元素的值：");
		print(point);//打印对象数组
		
		move(point);//移动点
		System.out.println("调用move()方法后元素的值：");
		print(point);
	}
	private static void init(Point p[])//方法，初始化对象数组
	{
		for(int i=0;i<p.length;i++)
			p[i]=new Point(10+i,20+2*i);//为每个元素调用构造方法
	}
	private static void print(Point p)//打印一个点，与下一方法重载
	{
		System.out.print(" ("+p.x+","+p.y+")");
	}
	private static void print(Point p[])//打印所有元素，重载方法
	{
		for(Point p1:p)
			print(p1);
		System.out.println();
	}
	private static void move(Point p[])//对数组中的所有点平移变换
	{
		for(Point p1:p) //改变p中元素值可以用增强型循环（为什么？）
		{
			p1.x+=11;
			p1.y+=12;
		}
	}
}
