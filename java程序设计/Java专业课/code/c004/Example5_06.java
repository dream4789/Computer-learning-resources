//点类，实现接口Cloneable
class Point implements Cloneable//父类是Object
{
	private int x,y;
	
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public void move(int offsetX,int offsetY)
	{
		x+=offsetX;
		y+=offsetY;
	}
	//重写父类clone()方法，可能会产生异常
	protected Point clone()throws CloneNotSupportedException
	{
			return (Point)super.clone();//通过super调用父类clone()方法复制当前对象
	}
	//重写父类toString()方法，使点的位置形成一个字符串
	public String toString()
	{
		String str="("+x+","+y+")";
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}

public class Example5_06
{
	public static void main(String args[])throws CloneNotSupportedException
	{
		Point oldPoint=new Point(10,20);
		Point newPoint;
		
		System.out.print("原来的点的坐标：");
		oldPoint.print();

		newPoint=oldPoint.clone();//克隆oldPoint生成一个新对象
		System.out.print("复制生成的新点的坐标：");
		newPoint.print();//新对象与原对象表示同一个点
		
		oldPoint.move(11, 22);
		System.out.print("原来的点移动后的坐标：");
		oldPoint.print();
		
		newPoint.move(-11, -33);
		System.out.print("复制生成的新点移动后的坐标：");
		newPoint.print();
	}
}
