class Point
{
	int x,y;
	static int counter=0;//����ʼ��Ҳ��0��Ĭ�ϣ�

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
	public static int getCounter()//�෽��
	{
		return counter;
	}
}
public class Example4_17
{
	public static void main(String args[])
	{
		//ͨ�����������෽��
		System.out.println("��ʼʱ��������"+Point.getCounter());

		Point p1=new Point(1,2);
	
		Point p2=new Point(3,4);
		
		Point point[]={new Point(5,6),new Point(7,8),new Point(9,10)};
		
		System.out.println("ͨ�����������ʾ�̬������");//��������෽��
		System.out.println("      ͨ������p1��õ�����"+p1.getCounter());
		System.out.println("      ͨ������p2��õ�����"+p2.getCounter());
		
		for(int i=0;i<point.length;i++)
			System.out.println("      ͨ������"+i+"��õ�����"+point[i].getCounter());

		System.out.println("ͨ���������ʾ�̬������");
		System.out.println("      ƽ���ϵ�ĸ�����"+Point.getCounter());
	}
}
