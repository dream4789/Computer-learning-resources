class Point
{
//同例4.9
}
public class Example4_14
{
	public static void main(String args[])
	{
		int counter=0;
		
		Point p1=new Point(1,2);
		counter++;
		
		Point p2=new Point(3,4);
		counter++;
		
		Point point[]={new Point(5,6),new Point(7,8),new Point(9,10)};
		counter+=3;
		
		System.out.println("平面上点的个数："+counter);
	}
}
