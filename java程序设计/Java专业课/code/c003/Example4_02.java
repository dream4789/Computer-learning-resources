public class Example4_02
{
	public static void main(String args[])
	{
		int a=10,b=25,c=-90;
		int x[]={98,34,78,934,8,93,48,928,92,8,83};
		
		System.out.println("两个数中的最大数："+max(a,b));//调用第1个max
		System.out.println("三个数中的最大数："+max(a,b,c));//调用第2个max
		System.out.println("多个数中的最大数："+max(x));//调用第3个max
	}
	private static int max(int x,int y)//三个重载方法的形参互不相同
	{
		return x>y?x:y;
	}
	private static int max(int x,int y,int z)
	{
		int m=max(x,y);//调用第1个max方法找前两个数最大数
		return m>z?m:z;
	}
	private static int max(int a[])
	{
		int m=a[0];
		for(int x:a)
			m=m>x?m:x; 
		return m;
	}
}
