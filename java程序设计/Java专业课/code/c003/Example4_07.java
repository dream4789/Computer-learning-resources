class Point
{
	int x,y;//�򣬵��λ��
	
	Point()//û�в����Ĺ��췽��
	{
		x=0;
		y=0;
	}
	Point(int x1,int y1)//�����������Ĺ��췽��
	{
		x=x1;
		y=y1;
	}
	
	int getX()//���������x����
	{
		return x;
	}
	int getY()//���������y����
	{
		return y;
	}
	void move(int offsetX,int offsetY)//�������Ե�ƽ��
{
		x+=offsetX;
		y+=offsetY;
	}
}
public class Example4_07
{
	public static void main(String args[])
	{
		Point p1,p2;//��������
		p1=new Point();//���õ�1�����췽��
		p2=new Point(5,8);//���õ�2�����췽��
		
		System.out.println("p1��ʾ�ĵ����꣺("+p1.x+","+p1.y+")");
		System.out.println("p2��ʾ�ĵ����꣺("+p2.x+","+p2.y+")");
		
		p1.move(11, 22);//��p1ƽ��
		System.out.print("�Ե�p1ƽ��(11,22)������꣺");
		//�Թ�������÷���getX()��getY()��ö������ֵ
		System.out.println("("+p1.getX()+","+p1.getY()+")");
		p2.move(-11, -22);//��p2ƽ��
		System.out.print("�Ե�p2ƽ��(-11,-22)������꣺");
		System.out.println("("+p2.getX()+","+p2.getY()+")");		
	}
}
