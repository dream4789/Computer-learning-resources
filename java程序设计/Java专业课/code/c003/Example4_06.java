
class Point
{
	int x,y;//域，点的位置
	
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

public class Example4_06
{
	public static void main(String args[])
	{
		Point p1,p2;//声明对象
		p1=new Point();//创建对象
		p2=new Point();
		
		System.out.println("p1表示的点坐标：("+p1.x+","+p1.y+")");
		System.out.println("p2表示的点坐标：("+p2.x+","+p2.y+")");
		
		System.out.println("改变p1和p2的坐标后的坐标：");
		p1.x=10;//通过对象名访问其中的域
		p1.y=15;
		p2.x=-20;
		p2.y=-34;
		System.out.println("p1表示的点坐标：("+p1.x+","+p1.y+")");
		System.out.println("p2表示的点坐标：("+p2.x+","+p2.y+")");
		
		p1.move(11, 22); //对p1平移
		System.out.print("对点p1平移(11,22)后的坐标：");
		//对过对象调用方法getX()和getY()获得对象的域值
		System.out.println("("+p1.getX()+","+p1.getY()+")");
		p2.move(-11, -22); //对p2平移
		System.out.print("对点p2平移(-11,-22)后的坐标：");
		System.out.println("("+p2.getX()+","+p2.getY()+")");		
	}
}
