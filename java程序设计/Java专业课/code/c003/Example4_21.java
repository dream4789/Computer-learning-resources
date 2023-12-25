class Point
{
	private int x,y;
	
	public Point()
	{
		x=0;
		y=0;
	}
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public int getX()
	{
		return x;
	}
	public int getY()
	{
		return y;
	}
	public void move(int offsetX,int offsetY)
	{
		x+=offsetX;
		y+=offsetY;
	}
	public double length(Point p)//计算当前点与点p之间的距离
	{
		int dx=x-p.x;
		int dy=y-p.y;
		return Math.sqrt(dx*dx+dy*dy);
	}
	public String toString()//点的位置形成一个字符串
	{
		String str="("+x+","+y+")";
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
class Line//线段类，组合类
{
	//用Point类的两个对象表示线段端点
	private Point start,end;//对象（域）成员
	
	public Line(int x1,int y1,int x2,int y2)//构造方法
	{
		start=new Point(x1,y1);//创建对象域
		end=new Point(x2,y2);
	}
	public Line(Point p1,Point p2)//重载构造方法
	{
		start=new Point(p1.getX(),p1.getY());//重新创建对象
		end=new Point(p2.getY(),p2.getY());
		//最好不要写成:start=p1;end=p2;
	}
	public int getStartX()
	{
		return start.getX();//代码重用
	}
	public int getStartY()
	{
		return start.getY();//代码重用
	}
	public int getEndX()
	{
		return end.getX();//代码重用
	}
	public int getEndY()
	{
		return end.getY();//代码重用
	}
	public void move(int offsetX,int offsetY)
	{
		start.move(offsetX, offsetY);//代码重用
		end.move(offsetX, offsetY);//代码重用
	}
	public double length()
	{
		return start.length(end);//代码重用
	}
	public String toString()//将端点形成一个字符
	{
		String str=start.toString();//代码重用
		str+="-"+end.toString();//代码重用
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
class Circle//圆类，组合类
{
	private Point center;//用Point类的对象表示圆心
	int radius;
	
	public Circle(int x,int y,int radius)//构造方法
	{
		center=new Point(x,y);
		this.radius=radius;
	}
	public Circle(Point p,int radius)//重载构造方法
	{
		center=new Point(p.getX(),p.getY());
		this.radius=radius;
	}
	public int getX()//获取圆心x坐标
	{
		return center.getX();//代码重用
	}
	public int getY()//获取圆心y坐标
	{
		return center.getY();//代码重用
	}
	public int getRadius()//获取圆的半径
	{
		return radius;
	}
	public void move(int offsetX,int offsetY)//移动圆
	{
		center.move(offsetX, offsetY);//代码重用
	}
	public double area()//计算圆的面积
	{
		return Math.PI*radius*radius;
	}
	public double perim()//计算圆的周长
	{
		return 2*Math.PI*radius;
	}
	public String toString()//将圆的数据形成一个字符串
	{
		String str=radius+",";
		str+=center.toString();//代码重用
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
public class Example4_21
{
	public static void main(String args[])
	{
		int x1=10,y1=11;
		int x2=20,y2=15;
		
		//------------先生成直线类的对象--------------
		Line line=new Line(x1,y1,x2,y2);
		
		System.out.print("直线的位置：");
		line.print();//直接调用print()输出
		
		System.out.print("直线的长度：");
		System.out.printf("%.2f\n",line.length());
		
		line.move(15, 17);
		System.out.print("移动后直线的位置：");
		System.out.println(line.toString());//形成字符串后再输出
		
		//------------再生成圆类的对象--------------
		System.out.println("--------------------------------");
		Circle circle=new Circle(-10,-20,10);
		
		System.out.print("圆的半径和位置：");
		circle.print();
		
		System.out.print("圆的面积和周长：");
		System.out.printf("%.2f,%.2f\n",circle.area(),circle.perim());
		
		circle.move(5,6);
		System.out.print("移动后圆的半径和位置：");
		System.out.println(circle.toString());
	}
}
