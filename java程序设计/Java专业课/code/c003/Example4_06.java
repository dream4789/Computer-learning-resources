
class Point
{
	int x,y;//�򣬵��λ��
	
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

public class Example4_06
{
	public static void main(String args[])
	{
		Point p1,p2;//��������
		p1=new Point();//��������
		p2=new Point();
		
		System.out.println("p1��ʾ�ĵ����꣺("+p1.x+","+p1.y+")");
		System.out.println("p2��ʾ�ĵ����꣺("+p2.x+","+p2.y+")");
		
		System.out.println("�ı�p1��p2�����������꣺");
		p1.x=10;//ͨ���������������е���
		p1.y=15;
		p2.x=-20;
		p2.y=-34;
		System.out.println("p1��ʾ�ĵ����꣺("+p1.x+","+p1.y+")");
		System.out.println("p2��ʾ�ĵ����꣺("+p2.x+","+p2.y+")");
		
		p1.move(11, 22); //��p1ƽ��
		System.out.print("�Ե�p1ƽ��(11,22)������꣺");
		//�Թ�������÷���getX()��getY()��ö������ֵ
		System.out.println("("+p1.getX()+","+p1.getY()+")");
		p2.move(-11, -22); //��p2ƽ��
		System.out.print("�Ե�p2ƽ��(-11,-22)������꣺");
		System.out.println("("+p2.getX()+","+p2.getY()+")");		
	}
}
