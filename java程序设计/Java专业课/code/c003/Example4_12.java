class Point
{
//ͬ��4.9
}
public class Example4_12
{
	public static void main(String args[])
	{
		Point point[]=new Point[5];//������������
		
		init(point);//�Զ��������ʼ��
		System.out.println("�������鴴����Ԫ�ص�ֵ��");
		print(point);//��ӡ��������
		
		move(point);//�ƶ���
		System.out.println("����move()������Ԫ�ص�ֵ��");
		print(point);
	}
	private static void init(Point p[])//��������ʼ����������
	{
		for(int i=0;i<p.length;i++)
			p[i]=new Point(10+i,20+2*i);//Ϊÿ��Ԫ�ص��ù��췽��
	}
	private static void print(Point p)//��ӡһ���㣬����һ��������
	{
		System.out.print(" ("+p.x+","+p.y+")");
	}
	private static void print(Point p[])//��ӡ����Ԫ�أ����ط���
	{
		for(Point p1:p)
			print(p1);
		System.out.println();
	}
	private static void move(Point p[])//�������е����е�ƽ�Ʊ任
	{
		for(Point p1:p) //�ı�p��Ԫ��ֵ��������ǿ��ѭ����Ϊʲô����
		{
			p1.x+=11;
			p1.y+=12;
		}
	}
}
