public class Example4_01
{
	public static void main(String args[])
	{
		int x,y,z;
		
		x=10;
		y=25;
		z=add(x,y);//调用时也可以直接给出常量：add(10,25)
		System.out.println(x+"+"+y+"="+z);
		//也可以直接输出：System.out.println(add(10,25));
		
		int m=max(x,y,z);
		System.out.printf("%d、%d和%d中最大数：%d\n",x,y,z,m);
		
	}
	private static int add(int a,int b)//add方法，返回整型值
	{
		int c=a+b;
		return c;
	}
	//如果add方法如下定义不可以
	/*private static int add(double a,double b)
	{形参a和b都是double，相加结果也是double
	但方法类型是int，将double转换为int时会出现错误
		return a+b;
	}*/
	private static int max(int a,int b,int c)//max方法，返回整型值
	{
	int max;
		max=a>b?a:b;
		max=max>c?max:c;
		return max;
	}
}
