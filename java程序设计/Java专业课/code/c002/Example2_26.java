public class Example2_26
{
	public static void main(String args[])
	{
		int a[]=new int[10],i;//声明一个数组和一个变量
		
		//创建数组后各元素的值
		System.out.println("刚创建数组后各元素的值：");
		for(i=0;i<a.length;i++)
			System.out.printf("%5d",a[i]);
		System.out.println();
		
		for(i=0;i<a.length;i++)
			a[i]=2*i;
		
		//逆序打印出各元素的值
		System.out.println("赋值后各元素值（逆序）：");
		for(i=a.length-1;i>=0;i--)
			System.out.printf("%5d",a[i]);
		System.out.println();
	}
}
