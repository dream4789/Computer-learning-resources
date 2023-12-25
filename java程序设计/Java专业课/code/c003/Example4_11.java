public class Example4_11
{
	public static void main(String args[])
	{
		int a[]={23,93,84,78,48,28,92,38,46};
		
		System.out.println("在main()方法中数组的地址："+a);
		System.out.println("数组中原始值：");
		print(a);//实参数组名
		System.out.println("----------调用add()方法------------");
		
		add(a);//实参数组名
		System.out.println("调用方法add()后数组中元素值：");		
		print(a);//实参数组名
		
		System.out.println("----------调用sort()方法-----------");
		sort(a);//实参数组名
		System.out.println("调用方法sort()排序后数组中元素值：");		
		print(a);//实参数组名
	}
	private static void print(int x[])//输出数组中各元素，形参数组名
	{
		for(int a:x)
			System.out.printf("%3d",a);
		System.out.println();
		//System.out.println("在print()方法中数组的地址："+x);
	}
	private static void add(int x[])//改变数组元素的值，形参数组名
	{
		System.out.println("在add()方法中数组的地址："+x);
		for(int i=0;i<x.length;i++)
			x[i]=x[i]+5;//每个元素都加5
	}
	private static void sort(int x[])//排序，形参数组名
	{
		System.out.println("在sort()方法中数组的地址："+x);
		int i,j,k;
		
		for(i=0;i<x.length-1;i++)
		{
			k=i;
			for(j=i+1;j<x.length;j++)
				if(x[k]>x[j])
					k=j;
			
			if(k!=i)
			{
				int t=x[i];
				x[i]=x[k];
				x[k]=t;
			}
		}
	}
}
