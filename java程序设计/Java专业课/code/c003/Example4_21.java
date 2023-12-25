class Point
{
	private int x,y;
	
	public Point()
	{
		x=0;
		y=0;
	}
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public int getX()
	{
		return x;
	}
	public int getY()
	{
		return y;
	}
	public void move(int offsetX,int offsetY)
	{
		x+=offsetX;
		y+=offsetY;
	}
	public double length(Point p)//���㵱ǰ�����p֮��ľ���
	{
		int dx=x-p.x;
		int dy=y-p.y;
		return Math.sqrt(dx*dx+dy*dy);
	}
	public String toString()//���λ���γ�һ���ַ���
	{
		String str="("+x+","+y+")";
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
class Line//�߶��࣬�����
{
	//��Point������������ʾ�߶ζ˵�
	private Point start,end;//�����򣩳�Ա
	
	public Line(int x1,int y1,int x2,int y2)//���췽��
	{
		start=new Point(x1,y1);//����������
		end=new Point(x2,y2);
	}
	public Line(Point p1,Point p2)//���ع��췽��
	{
		start=new Point(p1.getX(),p1.getY());//���´�������
		end=new Point(p2.getY(),p2.getY());
		//��ò�Ҫд��:start=p1;end=p2;
	}
	public int getStartX()
	{
		return start.getX();//��������
	}
	public int getStartY()
	{
		return start.getY();//��������
	}
	public int getEndX()
	{
		return end.getX();//��������
	}
	public int getEndY()
	{
		return end.getY();//��������
	}
	public void move(int offsetX,int offsetY)
	{
		start.move(offsetX, offsetY);//��������
		end.move(offsetX, offsetY);//��������
	}
	public double length()
	{
		return start.length(end);//��������
	}
	public String toString()//���˵��γ�һ���ַ�
	{
		String str=start.toString();//��������
		str+="-"+end.toString();//��������
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
class Circle//Բ�࣬�����
{
	private Point center;//��Point��Ķ����ʾԲ��
	int radius;
	
	public Circle(int x,int y,int radius)//���췽��
	{
		center=new Point(x,y);
		this.radius=radius;
	}
	public Circle(Point p,int radius)//���ع��췽��
	{
		center=new Point(p.getX(),p.getY());
		this.radius=radius;
	}
	public int getX()//��ȡԲ��x����
	{
		return center.getX();//��������
	}
	public int getY()//��ȡԲ��y����
	{
		return center.getY();//��������
	}
	public int getRadius()//��ȡԲ�İ뾶
	{
		return radius;
	}
	public void move(int offsetX,int offsetY)//�ƶ�Բ
	{
		center.move(offsetX, offsetY);//��������
	}
	public double area()//����Բ�����
	{
		return Math.PI*radius*radius;
	}
	public double perim()//����Բ���ܳ�
	{
		return 2*Math.PI*radius;
	}
	public String toString()//��Բ�������γ�һ���ַ���
	{
		String str=radius+",";
		str+=center.toString();//��������
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}
public class Example4_21
{
	public static void main(String args[])
	{
		int x1=10,y1=11;
		int x2=20,y2=15;
		
		//------------������ֱ����Ķ���--------------
		Line line=new Line(x1,y1,x2,y2);
		
		System.out.print("ֱ�ߵ�λ�ã�");
		line.print();//ֱ�ӵ���print()���
		
		System.out.print("ֱ�ߵĳ��ȣ�");
		System.out.printf("%.2f\n",line.length());
		
		line.move(15, 17);
		System.out.print("�ƶ���ֱ�ߵ�λ�ã�");
		System.out.println(line.toString());//�γ��ַ����������
		
		//------------������Բ��Ķ���--------------
		System.out.println("--------------------------------");
		Circle circle=new Circle(-10,-20,10);
		
		System.out.print("Բ�İ뾶��λ�ã�");
		circle.print();
		
		System.out.print("Բ��������ܳ���");
		System.out.printf("%.2f,%.2f\n",circle.area(),circle.perim());
		
		circle.move(5,6);
		System.out.print("�ƶ���Բ�İ뾶��λ�ã�");
		System.out.println(circle.toString());
	}
}
