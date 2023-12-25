class Line//�߶���
{
	private int x1,y1;//�����˵�
	private int x2,y2;
	
	public Line(int x1,int y1,int x2,int y2)
	{//���췽��
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
	public void move(int offsetX,int offsetY)//�߶�ƽ��
	{
		x1=x1+offsetX;
		y1=y1+offsetY;
		x2=x2+offsetX;
		y2=y2+offsetY;
	}
	public double length()//�����߶γ���
	{
		int dx=x1-x2;
		int dy=y1-y2;
		
		return Math.sqrt(dx*dx+dy*dy);
	}
	public String toString()//���˵��γ�һ���ַ���
	{
		String str="("+x1+","+y1+")-";
		str+="("+x2+","+y2+")";
		return str;
	}
	public void print()//����߶ε�λ��
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
		
		System.out.print("ֱ�ߵ�λ�ã�");
		line.print();//ֱ�ӵ���print()���
		
		System.out.print("ֱ�ߵĳ��ȣ�");
		System.out.printf("%.2f\n",line.length());
		
		line.move(15, 17);
		System.out.print("�ƶ���ֱ�ߵ�λ�ã�");
		System.out.println(line.toString());//�γ��ַ����������
	}
}
