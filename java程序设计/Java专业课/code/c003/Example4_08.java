class Point
{
	int x,y;//�򣬵��λ��
	
	Point()//û�в����Ĺ��췽��
	{
		x=0;//����д��this.x
		y=0;//this.y
	}
	Point(int x,int y)//�����������Ĺ��췽��
	{
		this.x=x;//����д��this.x��������ʲ�����x
		this.y=y;//����д��this.y��������ʲ�����y
		System.out.println("���췽���е�ǰ�����ַ��"+this);
	}
	
	int getX()//���������x����
	{
		return x;//����д��this.x
	}
	int getY()//���������y����
	{
		return y;//����д��this.y
	}
	void move(int offsetX,int offsetY)//�������Ե�ƽ��
	{
		x+=offsetX;//ͬ������д��this.x this.y
		y+=offsetY;
	}
	public void print()
	{
		System.out.println("�����꣺("+x+","+y+")");
		System.out.println("print�����е�ǰ�����ַ��"+this);
	}
}
public class Example4_08
{
	public static void main(String args[])
	{
		Point p=new Point(10,20);
		
		p.move(11, 22);
		
		System.out.println("main�����ж���p�ĵ�ַ��"+p);
		
		p.print();
		
		//------�ٴ���һ������-----------------
		System.out.println("--------�ٴ���һ���¶���--------");
		p=new Point(-10,-20);
		
		p.move(-11, -22);
		
		System.out.println("main�������¶���p�ĵ�ַ��"+p);
		
		p.print();
	}
}
