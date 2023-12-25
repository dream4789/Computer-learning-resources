class Point
{
//Point类的定义同例4.21
}
class Line extends Point//线段类，组合和继承
{
	//用Point类的一个对象表示线段一个端点
	private Point start;//对象（域）成员
	
	public Line(int x1,int y1,int x2,int y2)//构造方法
	{
		super(x2,y2);
		start=new Point(x1,y1);//创建对象域
	}
	public Line(Point p1,Point p2)//重载构造方法
	{
		super(p2.getX(),p2.getY());
		start=new Point(p1.getX(),p1.getY());//重新创建对象
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
		return getX();//继承自父类的getX()
	}
	public int getEndY()
	{
		return getY();//继承自父类的getY()
	}
	public void move(int offsetX,int offsetY)
	{
		start.move(offsetX, offsetY);//代码重用
		super.move(offsetX, offsetY);//调用父类move()对继承自父类的x和y平移
	}
	public double length()
	{
		Point end=new Point(getX(),getY());
		return start.length(end);//代码重用
	}
	public String toString()//将端点形成一个字符
	{
		//Point end=new Point(getX(),getY());

		String str=start.toString();//代码重用
		str+="-"+super.toString();//代码重用
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
class Circle extends Point//圆类，继承
{
	//private Point center;不定义，用继承的x和y表示圆心
	int radius;
	
	public Circle(int x,int y,int radius)//构造方法
	{
		super(x,y);//调用父类的构造方法对继承的x和y初始化
		this.radius=radius;
	}
	public Circle(Point p,int radius)//重载构造方法
	{
		super(p.getX(),p.getY());
		this.radius=radius;
	}
	public int getX()//获取圆心x坐标
	{
		return super.getX();//调用父类的方法
	}
	public int getY()//获取圆心y坐标
	{
		return super.getY();//调用父类的方法
	}
	public int getRadius()//获取圆的半径
	{
		return radius;
	}
	public void move(int offsetX,int offsetY)//移动圆
	{
		super.move(offsetX, offsetY);//调用父类的方法
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
		str+=super.toString();//调用父类的方法
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}

public class Example5_11
{
	public static void main(String args[])
	{
//main()方法同例4.21
	}
}
