class Point
{
	int x,y;
	@Deprecated//表示counter过时
	static int counter=0;

	Point(int x,int y)
	{
		setPosition(x,y);
		counter++;
	}
	void setPosition(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	@Deprecated//表示move方法过时
	void moveTo(int x,int y)//移动到(x,y)
	{
		this.x=x;
		this.y=y;
	}
	public void print()
	{
		System.out.println("("+x+","+y+")");
	}
}
public class Example4_18 
{
	public static void main(String args[])
	{
		Point p1=new Point(10,20);
		Point p2=new Point(-15,-8);
		
		System.out.println("平面上点的个数："+p2.counter);
		
		System.out.print("点p1的位置：");
		p1.print();
		
		p1.moveTo(100, 200);//移动p1点
		System.out.print("p1移动到：");
		p1.print();
	}
}
