class Point
{
	int x,y;
	@Deprecated//��ʾcounter��ʱ
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
	@Deprecated//��ʾmove������ʱ
	void moveTo(int x,int y)//�ƶ���(x,y)
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
		
		System.out.println("ƽ���ϵ�ĸ�����"+p2.counter);
		
		System.out.print("��p1��λ�ã�");
		p1.print();
		
		p1.moveTo(100, 200);//�ƶ�p1��
		System.out.print("p1�ƶ�����");
		p1.print();
	}
}
