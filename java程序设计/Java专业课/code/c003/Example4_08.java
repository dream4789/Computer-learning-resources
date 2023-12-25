class Point
{
	int x,y;//域，点的位置
	
	Point()//没有参数的构造方法
	{
		x=0;//可以写成this.x
		y=0;//this.y
	}
	Point(int x,int y)//有两个参数的构造方法
	{
		this.x=x;//必须写成this.x，否则访问不到域x
		this.y=y;//必须写成this.y，否则访问不到域y
		System.out.println("构造方法中当前对象地址："+this);
	}
	
	int getX()//方法，获得x分量
	{
		return x;//可以写成this.x
	}
	int getY()//方法，获得y分量
	{
		return y;//可以写成this.y
	}
	void move(int offsetX,int offsetY)//方法，对点平移
	{
		x+=offsetX;//同样可以写成this.x this.y
		y+=offsetY;
	}
	public void print()
	{
		System.out.println("点坐标：("+x+","+y+")");
		System.out.println("print方法中当前对象地址："+this);
	}
}
public class Example4_08
{
	public static void main(String args[])
	{
		Point p=new Point(10,20);
		
		p.move(11, 22);
		
		System.out.println("main方法中对象p的地址："+p);
		
		p.print();
		
		//------再创建一个对象-----------------
		System.out.println("--------再创建一个新对象--------");
		p=new Point(-10,-20);
		
		p.move(-11, -22);
		
		System.out.println("main方法中新对象p的地址："+p);
		
		p.print();
	}
}
