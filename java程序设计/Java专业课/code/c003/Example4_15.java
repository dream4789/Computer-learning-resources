class Point
{
	int x,y;
	int counter=0;//不初始化也是0（默认）

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
}
public class Example4_15
{
	public static void main(String args[])
	{
		Point p1=new Point(1,2);
	
		Point p2=new Point(3,4);
		
		Point point[]={new Point(5,6),new Point(7,8),new Point(9,10)};
		
		System.out.println("通过对象p1获得点数："+p1.counter);
		System.out.println("通过对象p2获得点数："+p2.counter);
		
		for(int i=0;i<point.length;i++)
			System.out.println("通过对象"+i+"获得点数："+point[i].counter);
	}
}
