class Point
{
	int x,y;
	int counter=0;//����ʼ��Ҳ��0��Ĭ�ϣ�

	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
		
		counter++;//�������������1
	}
	public void print()
	{
		System.out.println("("+x+","+y+")");
	}
}
public class Example4_15
{
	public static void main(String args[])
	{
		Point p1=new Point(1,2);
	
		Point p2=new Point(3,4);
		
		Point point[]={new Point(5,6),new Point(7,8),new Point(9,10)};
		
		System.out.println("ͨ������p1��õ�����"+p1.counter);
		System.out.println("ͨ������p2��õ�����"+p2.counter);
		
		for(int i=0;i<point.length;i++)
			System.out.println("ͨ������"+i+"��õ�����"+point[i].counter);
	}
}
