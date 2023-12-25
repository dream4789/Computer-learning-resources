class BaseClass
{
	private int a;//˽�г�Ա�����ɱ�����ֱ�ӷ���
	protected int b;//b,c,d���Ա�����ֱ�ӷ���
	public int c;
	int d;
	
	public BaseClass(int a,int b,int c,int d)
	{
		this.a=a;
		this.b=b;
		this.c=c;
		this.d=d;
	}
	public int getA()
	{
		return a;
	}
}
class DerivedClass extends BaseClass
{
	int x;
	protected int y;
	private int z;
	
	public DerivedClass(int a,int b,int c,int d,int x,int y,int z)
	{
		super(a,b,c,d);
		this.x=x;
		this.y=y;
		this.z=z;
	}
	public int getZ()
	{
		return z;
	}
	public String toString()
	{
		String str="  a="+getA();//�������getA()����������ֱ��д��a��
		str+=",b="+b+",c="+c;//ֱ�ӷ��ʼ̳��Ը����Ա
		str+=",d="+d+",x="+x+",y="+y+",z="+z;
		return str;
	}
}
public class Example5_08
{
	public static void main(String args[])
	{
		DerivedClass d=new DerivedClass(1,2,3,4,-10,-20,-30);
		
		System.out.println("�����е���ֵ��");
		System.out.println(d.toString());
		
		System.out.println("ֱ�ӷ��������");
		System.out.print("  a="+d.getA());//������÷���getA()��ӵõ�˽�г�Ա
		System.out.print(",b="+d.b+",c="+d.c+",d="+d.d);//�����˽�г�Աֱ�ӷ���
		System.out.print(",x="+d.x+",y="+d.y);//�������˽�г�Աֱ�ӷ���
		System.out.println(",z="+d.getZ());//ͨ�����з�����ӻ��˽�г�Ա
	}
}
