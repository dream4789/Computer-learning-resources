class BaseClass
{
	private int a;//私有成员，不可被子类直接访问
	protected int b;//b,c,d可以被子类直接访问
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
		String str="  a="+getA();//必须调用getA()方法，不能直接写”a“
		str+=",b="+b+",c="+c;//直接访问继承自父类成员
		str+=",d="+d+",x="+x+",y="+y+",z="+z;
		return str;
	}
}
public class Example5_08
{
	public static void main(String args[])
	{
		DerivedClass d=new DerivedClass(1,2,3,4,-10,-20,-30);
		
		System.out.println("对象中的域值：");
		System.out.println(d.toString());
		
		System.out.println("直接访问输出：");
		System.out.print("  a="+d.getA());//必须调用方法getA()间接得到私有成员
		System.out.print(",b="+d.b+",c="+d.c+",d="+d.d);//父类非私有成员直接访问
		System.out.print(",x="+d.x+",y="+d.y);//本身类非私有成员直接访问
		System.out.println(",z="+d.getZ());//通过公有方法间接获得私有成员
	}
}
