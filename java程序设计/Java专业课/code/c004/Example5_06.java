//���࣬ʵ�ֽӿ�Cloneable
class Point implements Cloneable//������Object
{
	private int x,y;
	
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public void move(int offsetX,int offsetY)
	{
		x+=offsetX;
		y+=offsetY;
	}
	//��д����clone()���������ܻ�����쳣
	protected Point clone()throws CloneNotSupportedException
	{
			return (Point)super.clone();//ͨ��super���ø���clone()�������Ƶ�ǰ����
	}
	//��д����toString()������ʹ���λ���γ�һ���ַ���
	public String toString()
	{
		String str="("+x+","+y+")";
		return str;
	}
	public void print()
	{
		System.out.println(toString());
	}
}

public class Example5_06
{
	public static void main(String args[])throws CloneNotSupportedException
	{
		Point oldPoint=new Point(10,20);
		Point newPoint;
		
		System.out.print("ԭ���ĵ�����꣺");
		oldPoint.print();

		newPoint=oldPoint.clone();//��¡oldPoint����һ���¶���
		System.out.print("�������ɵ��µ�����꣺");
		newPoint.print();//�¶�����ԭ�����ʾͬһ����
		
		oldPoint.move(11, 22);
		System.out.print("ԭ���ĵ��ƶ�������꣺");
		oldPoint.print();
		
		newPoint.move(-11, -33);
		System.out.print("�������ɵ��µ��ƶ�������꣺");
		newPoint.print();
	}
}
