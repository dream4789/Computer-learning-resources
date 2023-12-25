class Point
{
	int x,y;
	static int counter=0;//不初始化也是0（默认）

	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
		
		counter++;//创建对象后增加1
	}
	public void print()
	{
		System.out.println("("+x+","+y+")");
	}
	public static int getCounter()//类方法
	{
		return counter;
	}
}
public class Example4_17
{
	public static void main(String args[])
	{
		//通过类名访问类方法
		System.out.println("开始时对象数："+Point.getCounter());

		Point p1=new Point(1,2);
	
		Point p2=new Point(3,4);
		
		Point point[]={new Point(5,6),new Point(7,8),new Point(9,10)};
		
		System.out.println("通过对象名访问静态方法：");//下面调用类方法
		System.out.println("      通过对象p1获得点数："+p1.getCounter());
		System.out.println("      通过对象p2获得点数："+p2.getCounter());
		
		for(int i=0;i<point.length;i++)
			System.out.println("      通过对象"+i+"获得点数："+point[i].getCounter());

		System.out.println("通过类名访问静态方法：");
		System.out.println("      平面上点的个数："+Point.getCounter());
	}
}
