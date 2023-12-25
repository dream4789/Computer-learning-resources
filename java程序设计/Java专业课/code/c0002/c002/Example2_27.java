import java.util.Random;

public class Example2_27
{
	public static void main(String args[])
	{
		int a[]=new int[10];
		
		getElements(a);//这4条语句分别用于调用相应的方法
		print(a);
		sort(a);
		print(a);
	}
	private static void sort(int a[])//方法，用于排序
	{
		int i,j,t;
		
		for(i=0;i<a.length-1;i++)//进行a.length-1趟
		{
			for(j=0;j<a.length-1-i;j++)//每趟比较a.length-1-i次
				if(a[j]>a[j+1])//如果前比后大，则交换值
				{
					t=a[j];
					a[j]=a[j+1];
					a[j+1]=t;
				}
		}
	}
	private static void getElements(int a[])//方法，为数组元素赋随机值
	{
		Random rand=new Random();//随机数类的对象
		
		for(int i=0;i<a.length;i++)
			a[i]=rand.nextInt(100);//每次创建一个不大于100的随机数
	}
	private static void print(int a[])//方法，用于输出数组中各元素
	{
		for(int i=0;i<a.length;i++)
			System.out.printf("%3d", a[i]);
		System.out.println();
	}
}
