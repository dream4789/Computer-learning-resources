class Point
{
	private int x,y;//私有域
	private static int counter=0;//私有静态域
	
	public Point()//公有的构造方法
	{
		x=0;//在本身类中访问私有成员无限制，以下同
		y=0;
		
		counter++;
	}
	Point(int x,int y)//公有的构造方法
	{
		this.x=x;
		this.y=y;
		
		counter++;
	}
	
	public int getX()//公有方法，获得x分量
	{
		return x;
	}
	public int getY()//公有方法，获得y分量
	{
		return y;
	}
	public void move(int offsetX,int offsetY)//公有方法，对点平移
	{
		x+=offsetX;
		y+=offsetY;
	}
	public void print()//公有方法，对点平移
	{
		System.out.println("("+x+","+y+")");
	}
	public static int getCounter()//公有静态方法
	{
		return counter;
	}
}
public class Example4_19
{
	public static void main(String args[])
	{
		System.out.println("现在平面上的点数："+Point.getCounter());
		//直接通过类名访问静态域不可，因为它是私有的
		//System.out.println("现在平面上的点数："+Point.counter);
		
		Point p1=new Point();
		System.out.print("点p1的位置：");
		p1.print();
		
		p1.move(-11, -12);
		System.out.print("点p1移动后位置：");
		p1.print();
		//不能用下面的方式移动
		//p1.x=p1.x+11;——不可以
		//p1.y=p1.y+12;——不可以
		
		Point p2=new Point(11,22);
		System.out.print("点p2的位置：");
		System.out.println("("+p2.getX()+","+p2.getY()+")");
		//直接通过对象名访问x或y不可以，因为它们是私有的
		//System.out.println("("+p2.x+","+p2.y+")");		
		
		System.out.println("现在平面上的点数："+Point.getCounter());
	}
}
