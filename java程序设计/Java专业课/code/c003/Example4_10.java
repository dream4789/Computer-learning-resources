class Point
{
//同例4.9
}
public class Example4_10
{
	public static void main(String args[])
	{
		Point p=new Point(11,22);
		
		System.out.println("在main()方法中p表示的对象的地址："+p);
		System.out.print("调用move方法前点的坐标：");
		p.print();
		
		move(p);
		
		System.out.print("调用move方法后点的坐标：");
		p.print();
	}
	private static void move(Point p)//对象名作方法的参数
	{
		System.out.println("在move()方法中p表示的对象的地址:"+p);
		p.x=p.x+11;
		p.y=p.y+22;
		System.out.print("在move方法中点的坐标：");
		System.out.println("("+p.x+","+p.y+")");
	}
}
