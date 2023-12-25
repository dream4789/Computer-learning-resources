class Line//线段类
{
	private int x1,y1;//两个端点
	private int x2,y2;
	
	public Line(int x1,int y1,int x2,int y2)
	{//构造方法
		this.x1=x1;
		this.y1=y1;
		this.x2=x2;
		this.y2=y2;
	}
	public int getStartX()
	{
		return x1;
	}
	public int getStartY()
	{
		return y1;
	}
	public int getEndX()
	{
		return x2;
	}
	public int getEndY()
	{
		return y2;
	}
	public void move(int offsetX,int offsetY)//线段平移
	{
		x1=x1+offsetX;
		y1=y1+offsetY;
		x2=x2+offsetX;
		y2=y2+offsetY;
	}
	public double length()//计算线段长度
	{
		int dx=x1-x2;
		int dy=y1-y2;
		
		return Math.sqrt(dx*dx+dy*dy);
	}
	public String toString()//将端点形成一个字符串
	{
		String str="("+x1+","+y1+")-";
		str+="("+x2+","+y2+")";
		return str;
	}
	public void print()//输出线段的位置
	{
		System.out.println(toString());
	}
}
public class Example4_20
{
	public static void main(String args[])
	{
		int x1=10,y1=11;
		int x2=20,y2=15;
		
		Line line=new Line(x1,y1,x2,y2);
		
		System.out.print("直线的位置：");
		line.print();//直接调用print()输出
		
		System.out.print("直线的长度：");
		System.out.printf("%.2f\n",line.length());
		
		line.move(15, 17);
		System.out.print("移动后直线的位置：");
		System.out.println(line.toString());//形成字符串后再输出
	}
}
