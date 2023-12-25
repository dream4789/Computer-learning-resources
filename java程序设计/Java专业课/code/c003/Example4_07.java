class Point
{
	int x,y;//域，点的位置
	
	Point()//没有参数的构造方法
	{
		x=0;
		y=0;
	}
	Point(int x1,int y1)//有两个参数的构造方法
	{
		x=x1;
		y=y1;
	}
	
	int getX()//方法，获得x分量
	{
		return x;
	}
	int getY()//方法，获得y分量
	{
		return y;
	}
	void move(int offsetX,int offsetY)//方法，对点平移
{
		x+=offsetX;
		y+=offsetY;
	}
}
public class Example4_07
{
	public static void main(String args[])
	{
		Point p1,p2;//声明对象
		p1=new Point();//调用第1个构造方法
		p2=new Point(5,8);//调用第2个构造方法
		
		System.out.println("p1表示的点坐标：("+p1.x+","+p1.y+")");
		System.out.println("p2表示的点坐标：("+p2.x+","+p2.y+")");
		
		p1.move(11, 22);//对p1平移
		System.out.print("对点p1平移(11,22)后的坐标：");
		//对过对象调用方法getX()和getY()获得对象的域值
		System.out.println("("+p1.getX()+","+p1.getY()+")");
		p2.move(-11, -22);//对p2平移
		System.out.print("对点p2平移(-11,-22)后的坐标：");
		System.out.println("("+p2.getX()+","+p2.getY()+")");		
	}
}
